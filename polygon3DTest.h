#pragma once
#ifndef _POLYGON3D_H_
#define _POLYGON3D_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "Game.h"

typedef enum TEXTURE3D_NUM
{
	TEX_CUBE,
	TEX_HANYI,
	TEX_3DMAX
};

const TEXTURE TextureMessage3D[TEX_3DMAX] =
{
	{ "Texture/horoCube.png", 1024, 1024 },
	{ "Texture/hanyi.png", 100, 100 },
};

bool InitPolygon3D();
void UninitPolygon3D(void);
void UpdatePolygon3D(void);
void DrawPolygon3D();
void SetPolygonColor3D(D3DCOLOR nColor);
void SetTexture3D(int nNumTex);

#define FVF_VERTEX3D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL|D3DFVF_TEX1)



#endif