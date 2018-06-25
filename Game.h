#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include <d3d9.h>
#include <d3dx9.h>

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 way;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX3D;

typedef struct {
	char filename[256];
	int width;
	int height;
}TEXTURE;

typedef enum TEXTURE_BILLBOARD_NUM
{
	TEX_BILLBOARD_NULL = -1,
	TEX_CHARACTER_ALICE_01,
	TEX_CHARACTER_ALICE_02,
	TEX_CHARACTER_ALICE_04,
	TEX_CHARACTER_ALICE_05,
	TEX_BALL,
	TEX_SMOKE,
	TEX_PLUS_1,
	TEX_PLUS_2,
	TEX_PLUS_3,
	TEX_RANNKO,
	TEX_BILLBOARD_MAX
};

const TEXTURE BillboardTextureMessage[TEX_BILLBOARD_MAX] =
{
	{ "Texture/alice_01.png", 385, 216 },
	{ "Texture/alice_02.png", 385, 216 },
	{ "Texture/alice_04.png", 385, 216 },
	{ "Texture/alice_05.png", 385, 216 },
	{ "Texture/netball_s.png",20,20},
	{ "Texture/somke.png",7000,492 },
	{ "Texture/num_s/plus1.png",398,199 },
	{ "Texture/num_s/plus2.png",398,199 },
	{ "Texture/num_s/plus3.png",398,199 },
	{ "Texture/RANNKO.png",387,301 },
};

typedef struct
{
	D3DXMATRIX MtxBillboard;/*ビルボードの世界*/
	D3DXMATRIX MtxBillboardRotationZ;
	bool RotationZswitch;
	float angle;
	float BillboardWidth;/*ビルボードの幅さ*/
	float BillboardHeight;/*ビルボードの長さ*/
	D3DXVECTOR3 BillboardXYZ;/*ビルボードの座標*/
	int BillboardTexNum;/*ビルボードを使う全テクスチャー数*/
	TEXTURE_BILLBOARD_NUM ISbnum; /*ビルボード今使うテクスチャーの番号*/
	bool ISBillboard; /*ビルボードの存在判定*/
}BILLBOARD;

#define BILL_CHARACTER (1)
#define BILL_BALL (0)
#define BILL_POINT_1 (2)
#define BILL_POINT_2 (3)
#define BILL_POINT_3 (4)
#define BILL_RANNKO (5)

#define CLEAR_1 (3)
#define CLEAR_2 (20)
#define CLEAR_3 (50)
#define CLEAR_4 (100)
#define CLEAR_5 (250)
#define CLEAR_6 (400)

void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

int GetTime(void);
int GetLevel(void);

void LevelSet(void);

bool ClearJudge(void);

bool GetGameStartSwitch(void);

bool GetISClear(void);
#endif
