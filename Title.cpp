#include "Title.h"
#include "Polygon.h"
#include "input.h"
#include "scene.h"
#include "sound.h"
#include<d3d9.h>

static int Talpha = 0;
static bool TalphaOn = false;

static bool ballswitch = false;
static float ballisx = 0;
static float ballisy = WINDOW_HEIGHT;
static int ballistime = 0;
static int alicey = WINDOW_HEIGHT;

static bool mojiswitch = false;
static int mojix = -400;

static bool startswitch = false;
static int startalpha = 0;

void InitTitle(void)
{
	StopSound();
	Talpha = 0;
	TalphaOn = false;
	PlaySound(SOUND_LABEL_BGM01);
	PlaySound(SOUND_LABEL_NIU);
	//
	ballswitch = false;
	ballisx = 0;
	ballisy = WINDOW_HEIGHT;
	ballistime = 0;
	alicey = WINDOW_HEIGHT;

	mojiswitch = false;
	mojix = -400;

	startswitch = false;
	startalpha = 0;
}
void UninitTitle(void)
{
}
void UpdateTitle(void)
{
	if (startswitch)
	{
		if (GetKeyboardPress(DIK_RETURN))
		{
			TalphaOn = true;
		}
	}
	if (TalphaOn)
	{
		Talpha += 3;
		if (Talpha >= 250)
		{
			TalphaOn = false;
			StopSound(SOUND_LABEL_BGM01);
			ChangeScene(SCENE_GAME);
			ballswitch = false;
			ballisx = 0;
			ballisy = WINDOW_HEIGHT;
			ballistime = 0;
			alicey = WINDOW_HEIGHT;

			mojiswitch = false;
			mojix = -400;

			startswitch = false;
			startalpha = 0;
		}
	}

	UpdatePolygon();
}
void DrawTitle(void)
{
	SetDUIChange(2);
	SetTexture(TEX_P2_TITLE_01);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTexture(TEX_P2_TITLE_NETBALL);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(ballisx, ballisy, 309.6f, 240.8f, 0, 0, 387, 301);
	SetTexture(TEX_P2_TITLE_ALICE);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(0, alicey, 375, 200, 0, 0, 750, 400);
	SetTexture(TEX_P2_TITLE_GE);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(mojix, 300, 400, 200, 0, 0, 800, 400);
	SetTexture(TEX_P2_TITLE_NA);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(mojix-400, 100, 400, 200, 0, 0, 800, 400);
	SetTexture(TEX_P2_TITLE_START);
	SetPolygonColor(D3DCOLOR_ARGB(startalpha, 255, 255, 255));
	DrawPolygon(400, 550, 550, 75, 0, 0, 1100, 150);
	if (!startswitch)
	{
		if (!mojiswitch)
		{
			if (!ballswitch)
			{
				ballistime++;
				ballisx = ((cosf(30 * 3.14 / 180) * 1000 - ballistime / 60.f)*ballistime / 60.f);
				ballisy = (-((sinf(30 * 3.14 / 180) * 1000 - ballistime / 60.f)*ballistime / 60.f)) + WINDOW_HEIGHT;
				if (ballisy<200)
				{
					ballswitch = true;
					StopSound(SOUND_LABEL_NIU);
				}
			}
			else
			{
				alicey -= 5;
				if (alicey<500)
				{
					mojiswitch = true;
				}
			}
		}
		else
		{
			mojix += 10;
			if (mojix>500)
			{
				startswitch = true;
			}
		}
	}
	else
	{
		if (startalpha<255)
		{
			startalpha+=1;
		}
	}
	SetTexture(TEX_P2_TITLE_02);
	SetPolygonColor(D3DCOLOR_ARGB(Talpha, 255, 255, 255));
	DrawPolygon(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}