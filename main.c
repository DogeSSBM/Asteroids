#include "Includes.h"

typedef struct{
    Coordf pos;
    Coordf vec;
}Player;

Player rotatePlayer(Player player)
{
    const float ang = 2*keyState(SDL_SCANCODE_D) - 2*keyState(SDL_SCANCODE_A);
    player.vec = cfRotateDeg(player.vec, ang);
    return player;
}

void drawPlayer(const Player player)
{
    setColor(RED);
    fillCircleCoord(CfC(player.pos), 3);
    fillCircleCoord(CfC(cfTranslate(player.pos, player.vec)), 3);
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

    Player player = {.pos = CCf(getWindowMid()), .vec = {150.0f,150.0f}};

    while(1){
        Ticks t = frameStart();

        player = rotatePlayer(player);
        drawPlayer(player);

        if(keyPressed(SDL_SCANCODE_ESCAPE))
            return 0;
        frameEnd(t);
    }
    return 0;
}
