#pragma once

typedef Vec (*Translate)(Vec, Vec);

typedef enum{E_PLAYER, E_AST, E_LASER}EntityType;

typedef struct{
    EntityType type;
    Vec pos;
    Vec momentum;
    uint numVtx;
    Vec *vtx;
    Translate move;
}Entity;
