#pragma once

Vec translateWrap(const Vec pos, const Vec momentum)
{
    Vec new = cfTranslate(pos, momentum);
    const Vec lim = CCf(getWindowLen());
    if(new.x < 0.0f)
        new.x = lim.x+new.x;
    else if(new.x >= lim.x)
        new.x -= lim.x;

    if(new.y < 0.0f)
        new.y = lim.y+new.y;
    else if(new.y >= lim.y)
        new.y -= lim.y;

    return new;
}

void fillPolyWrap(Vec *vtx, const uint numVtx)
{
    const Length win = getWindowLen();
    Coord arr[numVtx];
    for(uint i = 0; i < numVtx; i++)
        arr[i] = CfC(vtx[i]);

    fillPoly(arr, numVtx);
    for(uint i = 0; i < numVtx; i++){
        Coord refl[numVtx];
        for(uint j = 0; j < numVtx; j++){
            refl[j] = coordShift(arr[j], i, dirUD(i) ? win.y : win.x);
        }
        fillPoly(refl, numVtx);
    }
}

void entityDraw(const Entity ent)
{
    Vec pts[ast.numVtx];
    for(uint i = 0; i < ast.numVtx; i++)
        pts[i] = cfTranslate(ast.pos, ast.vtx[i]);

    setColor(WHITE);
    fillPolyWrap(pts, ast.numVtx);


    const float facing = cfToDeg(ent.momentum);
    Vec arr[ent.numVtx];
    for(uint i = 0; i < ent.numVtx; i++)
        arr[i] = cfTranslate(cfRotateDeg(ent.vtx[i], facing), ent.pos);

    switch(ent.type){
        case E_PLAYER:
            setColor(RED);
            break;
        case E_AST:
            setColor(WHITE);
            break;
        case E_LASER:
            setColor(GREEN);
            break;
        default:
            fprintf(stderr, "Error: default case in entityDraw\n(int)ent.type: %i\n", ent.type);
            exit(EXIT_FAILURE);
            break;
    }

    fillPolyWrap(arr, ent.numVtx);
}

Entity newEntity(const Vec pos, const )
