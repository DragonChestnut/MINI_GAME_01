#pragma once
#ifndef _WALL_H_
#define _WALL_H_
#include <d3dx9.h>
#include <d3d9.h>

#include "polygon3DTest.h"

typedef enum WALL_NUM
{
	WALL_1,
	WALL_MAX
};

const TEXTURE TextureWallMessage[WALL_MAX] =
{
	{ "Texture/wall3.png", 65, 39.6f },
};

bool InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);

void SetTextureWall(int nNumTex);
#endif
