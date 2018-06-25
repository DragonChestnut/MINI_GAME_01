#include "Number.h"
#include "main.h"
#include "Polygon.h"
#include "Game.h"
#include "Billboard.h"

#define TEXNUMBER_WIDTH (200)
#define TEXNUMBER_HEIGTH (200)

void DrawNumber(int n, float x, float y)
{
	if (n < 0 || n>9)
	{
		return;
	}

	switch (n)
	{
	case 1:SetTexture(TEX_P2_1);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH*3, NUMBER_HEIGHT*3, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 2:SetTexture(TEX_P2_2);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 3, NUMBER_HEIGHT * 3, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 3:SetTexture(TEX_P2_3);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 3, NUMBER_HEIGHT * 3, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 4:SetTexture(TEX_P2_4);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 3, NUMBER_HEIGHT * 3, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 5:SetTexture(TEX_P2_5);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 3, NUMBER_HEIGHT * 3, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 6:SetTexture(TEX_P2_6);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 3, NUMBER_HEIGHT * 3, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 7:SetTexture(TEX_P2_7);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 3, NUMBER_HEIGHT * 3, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 8:SetTexture(TEX_P2_8);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 3, NUMBER_HEIGHT * 3, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 9:SetTexture(TEX_P2_9);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 3, NUMBER_HEIGHT * 3, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 0:SetTexture(TEX_P2_0);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 3, NUMBER_HEIGHT * 3, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	default:
		break;
	}
}

void DrawNumberB(int n, float x, float y)
{
	if (n < 0 || n>9)
	{
		return;
	}

	switch (n)
	{
	case 1:SetTexture(TEX_P2_1_B);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 2, NUMBER_HEIGHT * 2, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 2:SetTexture(TEX_P2_2_B);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 2, NUMBER_HEIGHT * 2, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 3:SetTexture(TEX_P2_3_B);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 2, NUMBER_HEIGHT * 2, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 4:SetTexture(TEX_P2_4_B);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 2, NUMBER_HEIGHT * 2, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 5:SetTexture(TEX_P2_5_B);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 2, NUMBER_HEIGHT * 2, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 6:SetTexture(TEX_P2_6_B);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 2, NUMBER_HEIGHT * 2, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 7:SetTexture(TEX_P2_7_B);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 2, NUMBER_HEIGHT * 2, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 8:SetTexture(TEX_P2_8_B);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 2, NUMBER_HEIGHT * 2, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 9:SetTexture(TEX_P2_9_B);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 2, NUMBER_HEIGHT * 2, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 0:SetTexture(TEX_P2_0_B);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH * 2, NUMBER_HEIGHT * 2, 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	default:
		break;
	}
}

void DrawNumberC(int n, float x, float y)
{
	if (n < 0 || n>9)
	{
		return;
	}

	switch (n)
	{
	case 1:SetTexture(TEX_P2_1);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH , NUMBER_HEIGHT , 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 2:SetTexture(TEX_P2_2);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH , NUMBER_HEIGHT , 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 3:SetTexture(TEX_P2_3);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH , NUMBER_HEIGHT , 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 4:SetTexture(TEX_P2_4);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH , NUMBER_HEIGHT , 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 5:SetTexture(TEX_P2_5);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH , NUMBER_HEIGHT , 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 6:SetTexture(TEX_P2_6);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH , NUMBER_HEIGHT , 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 7:SetTexture(TEX_P2_7);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH , NUMBER_HEIGHT , 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 8:SetTexture(TEX_P2_8);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH , NUMBER_HEIGHT , 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 9:SetTexture(TEX_P2_9);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH , NUMBER_HEIGHT , 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	case 0:SetTexture(TEX_P2_0);	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255)); DrawPolygon(x, y, NUMBER_WIDTH , NUMBER_HEIGHT , 0, 0, TEXNUMBER_WIDTH, TEXNUMBER_HEIGTH); break;
	default:
		break;
	}
}

