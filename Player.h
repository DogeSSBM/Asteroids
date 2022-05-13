#pragma once

Vec movePlayer(Vec pos, Vec momentum)
{
    const float magMod = .01*keyState(SDL_SCANCODE_W) - .01*keyState(SDL_SCANCODE_S);
    const float angMod = 2*keyState(SDL_SCANCODE_D) - 2*keyState(SDL_SCANCODE_A);
    momentum = degMagToCf(
        cfToDeg(momentum) + angMod,
        fclamp(cfMag(momentum)+magMod, 0.1f, 3.0f)
    );

    return translateWrap(pos, momentum);
}
