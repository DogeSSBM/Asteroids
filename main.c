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

    player.pos = translateWrap(player.pos, player.momentum);
    return player;
}

void drawPlayer(const Player player)
{
    const float facing = cfToDeg(player.momentum);
    const Vec nose = cfTranslate(degMagToCf(facing, 10.0f), player.pos);
    const Vec right = cfTranslate(degMagToCf(facing+120.0f, 10.0f), player.pos);
    const Vec left = cfTranslate(degMagToCf(facing-120.0f, 10.0f), player.pos);
    Vec arr[4] = {nose, left, player.pos, right};
    setColor(RED);
    fillPolyWrap(arr, 4);
}

int main(int argc, char const *argv[])
{
    Length window = {800, 600};
    init();
    setWindowLen(window);

    setColor(WHITE);

    Player player = {.pos = CCf(getWindowMid()), .momentum = degMagToCf(0.0f, 20.0f)};
    Ast ast = newAst(8, closestSide(player.pos));
    while(1){
        Ticks t = frameStart();

        if(keyPressed(SDL_SCANCODE_SPACE))
            ast = newAst(6 + rand() % 8, closestSide(player.pos));

        player = movePlayer(player);
        ast = moveAst(ast);

        drawAst(ast);
        drawPlayer(player);

        if(keyPressed(SDL_SCANCODE_ESCAPE))
            return 0;

        frameEnd(t);
    }
    return 0;
}
