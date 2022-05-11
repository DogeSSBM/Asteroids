#include "Includes.h"

typedef struct{
    Vec pos;
    Vec momentum;
}Player;

Player movePlayer(Player player)
{
    const float magMod = .01*keyState(SDL_SCANCODE_W) - .01*keyState(SDL_SCANCODE_S);
    const float angMod = 2*keyState(SDL_SCANCODE_D) - 2*keyState(SDL_SCANCODE_A);
    player.momentum = degMagToCf(
        cfToDeg(player.momentum) + angMod,
        fclamp(cfMag(player.momentum)+magMod, 0.1f, 3.0f)
    );
    player.pos = cfTranslate(player.pos, player.momentum);
    return player;
}

void drawPlayer(const Player player)
{
    setColor(RED);
    const float facing = cfToDeg(player.momentum);
    const Vec nose = cfTranslate(degMagToCf(facing, 10.0f), player.pos);
    const Vec right = cfTranslate(degMagToCf(facing+120.0f, 10.0f), player.pos);
    const Vec left = cfTranslate(degMagToCf(facing-120.0f, 10.0f), player.pos);
    Coord arr[4] = {CfC(nose), CfC(left), CfC(player.pos),  CfC(right)};
    fillPoly(arr, 4);
}

int main(int argc, char const *argv[])
{
    Length window = {800, 600};
    init();
    setWindowLen(window);

    // Coord arr[9] = {
    //     (Coord){.x = 0, .y = 32},
    //     (Coord){.x = 22, .y = 32},
    //     (Coord){.x = 30, .y = 4},
    //     (Coord){.x = 45, .y = 8},
    //     (Coord){.x = 74, .y = 0},
    //     (Coord){.x = 53, .y = 40},
    //     (Coord){.x = 64, .y = 80},
    //     (Coord){.x = 40, .y = 64},
    //     (Coord){.x = 10, .y = 74}
    // };

    setColor(WHITE);

    Player player = {.pos = CCf(getWindowMid()), .momentum = degMagToCf(0.0f, 20.0f)};

    while(1){
        Ticks t = frameStart();

        player = movePlayer(player);
        drawPlayer(player);

        if(keyPressed(SDL_SCANCODE_ESCAPE))
            return 0;
        frameEnd(t);
    }
    return 0;
}
