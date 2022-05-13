#pragma once

Coord arr[9] = {
    (Coord){.x = 0, .y = 32},
    (Coord){.x = 22, .y = 32},
    (Coord){.x = 30, .y = 4},
    (Coord){.x = 45, .y = 8},
    (Coord){.x = 74, .y = 0},
    (Coord){.x = 53, .y = 40},
    (Coord){.x = 64, .y = 80},
    (Coord){.x = 40, .y = 64},
    (Coord){.x = 10, .y = 74}
};


typedef struct{
    bool wrap;
    Vec pos;
    Vec momentum;
    uint numVtx;
    Vec *vtx;
}Ast;

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
    const Length win = coordAdd(getWindowLen(), -10);
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

Direction closestSide(const Vec pos)
{
    const Length win = getWindowLen();
    uint closestDist = UINT_MAX;
    Direction side = DIR_U;
    for(uint i = 0; i < 4; i++){
        const Coord cpos = CfC(pos);
        uint curDist = UINT_MAX;
        if(dirPOS(i))
            curDist = dirLR(i) ? win.x - cpos.x : win.y - cpos.y;
        else
            curDist = dirLR(i) ? cpos.x : cpos.y;

        if(curDist < closestDist){
            closestDist = curDist;
            side = i;
        }
    }
    return side;
}

void delAst(Ast ast)
{
    if(ast.vtx)
        free(ast.vtx);
}

Ast newAst(const uint numVtx, const Direction playerDir)
{
    if(numVtx < 3 || numVtx > 100){
        fprintf(stderr, "Cannot create a new asteroid with %u vertice(s)!\n Must be: 3 <= numVtx <= 100\n", numVtx);
        exit(EXIT_FAILURE);
    }

    Ast ast = {
        .wrap = false,
        .numVtx = numVtx,
        .vtx = calloc(numVtx, sizeof(Vec))
    };

    const Coord mid = getWindowMid();
    const uint bufferLen = coordMin(getWindowLen()) / 4;
    Direction spawnDir = rand() % 3;
    if(spawnDir == playerDir)
        spawnDir = (spawnDir + 1) % 4;

    ast.pos = CCf(coordShift(
        coordShift(mid, spawnDir, bufferLen),
        rand() & 1 ? dirROL(spawnDir) : dirROR(spawnDir),
        rand() % (dirUD(spawnDir) ? mid.y : mid.x)
    ));

    ast.momentum = dirToVec(dirINV(spawnDir));

    for(uint i = 0; i < numVtx; i++)
        ast.vtx[i] = degMagToCf(i*(360.0f/numVtx), rand()%100+100);

    return ast;
}

void drawAst(const Ast ast)
{
    Vec pts[ast.numVtx];
    for(uint i = 0; i < ast.numVtx; i++)
        pts[i] = cfTranslate(ast.pos, ast.vtx[i]);

    setColor(WHITE);
    fillPolyWrap(pts, ast.numVtx);
}

Ast moveAst(Ast ast)
{
    ast.pos = translateWrap(ast.pos, ast.momentum);
    return ast;
}
