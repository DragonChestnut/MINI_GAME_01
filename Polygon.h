#pragma once
#ifndef POLYGON_H
#define POLYGON_H

#include "game.h"
#include "main.h"

// ç\ë¢ëÃíËã`
typedef struct {
	D3DXVECTOR4 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX_2D;

typedef enum TEXTURE_NUM
{
	TEX_P2_TITLE_01,
	TEX_P2_TITLE_02,
	TEX_P2_RESULT,
	TEX_P2_0,
	TEX_P2_1,
	TEX_P2_2,
	TEX_P2_3,
	TEX_P2_4,
	TEX_P2_5,
	TEX_P2_6,
	TEX_P2_7,
	TEX_P2_8,
	TEX_P2_9,
	TEX_P2_0_B,
	TEX_P2_1_B,
	TEX_P2_2_B,
	TEX_P2_3_B,
	TEX_P2_4_B,
	TEX_P2_5_B,
	TEX_P2_6_B,
	TEX_P2_7_B,
	TEX_P2_8_B,
	TEX_P2_9_B,
	TEX_P2_UI_BOARD,
	TEX_P2_UI_BOARDGAME,
	TEX_P2_UI_BOARDCONTROL,
	TEX_P2_UI_BOARDSCORE,
	TEX_P2_UI_BOARDCHANGE,
	TEX_P2_UI_BOARDCLEAR,
	TEX_P2_UI_BOARDGAMEOVER,
	TEX_P2_UI_TIMEUP,
	TEX_P2_UI_CLOCK,
	TEX_P2_UI_ALLOW,
	TEX_P2_TITLE_ALICE,
	TEX_P2_TITLE_GE,
	TEX_P2_TITLE_NA,
	TEX_P2_TITLE_NETBALL,
	TEX_P2_TITLE_START,
	TEX_P2_MAX
};

const TEXTURE TextureMessage[TEX_P2_MAX] =
{
	{ "Texture/title.png",WINDOW_WIDTH, WINDOW_HEIGHT },
	{ "Texture/title_2.png",WINDOW_WIDTH, WINDOW_HEIGHT },
	{ "Texture/result.png",WINDOW_WIDTH, WINDOW_HEIGHT },	
	{ "Texture/0.png", 200, 200 },
	{ "Texture/1.png", 200, 200 },
	{ "Texture/2.png", 200, 200 },
	{ "Texture/3.png", 200, 200 },
	{ "Texture/4.png", 200, 200 },
	{ "Texture/5.png", 200, 200 },
	{ "Texture/6.png", 200, 200 },
	{ "Texture/7.png", 200, 200 },
	{ "Texture/8.png", 200, 200 },
	{ "Texture/9.png", 200, 200 },
	{ "Texture/num_s/0.png", 200, 200 },
	{ "Texture/num_s/1.png", 200, 200 },
	{ "Texture/num_s/2.png", 200, 200 },
	{ "Texture/num_s/3.png", 200, 200 },
	{ "Texture/num_s/4.png", 200, 200 },
	{ "Texture/num_s/5.png", 200, 200 },
	{ "Texture/num_s/6.png", 200, 200 },
	{ "Texture/num_s/7.png", 200, 200 },
	{ "Texture/num_s/8.png", 200, 200 },
	{ "Texture/num_s/9.png", 200, 200 },
	{ "Texture/board.png", 500, 500 },
	{ "Texture/boardgame.png", 500, 500 },
	{ "Texture/boardcontrol.png", 500, 500 },
	{ "Texture/boardscore.png", 500, 500 },
	{ "Texture/boardchange.png", 500, 800 },
	{ "Texture/board_clear.png", 500, 500 },
	{ "Texture/board_gameover.png", 500, 500 },
	{ "Texture/timeup.png", 800, 200 },
	{ "Texture/clock.png", 30, 52 },
	{ "Texture/allow.png",300,100 },
	{ "Texture/title/alice_00.png",750,400 },
	{ "Texture/title/ge.png",800,400 },
	{ "Texture/title/na.png",800,400 },
	{ "Texture/title/rannko.png",387,301 },
	{ "Texture/title/start.png",1100,150 },
};


bool InitPolygon();
void UninitPolygon();
void UpdatePolygon();


void SetPolygonColor(D3DCOLOR nColor);
void SetTexture(int nNumTex);
void SetPolygonRotation(float cx, float cy, float angle);
void SetPolygonScale(float cx, float cy, float sx, float sy);
void DrawPolygon(float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch,bool bAffine = false);

void SetDUIChange(int num);
#endif
