#include "result.h"
#include "Polygon.h"
#include "input.h"
#include "scene.h"
#include "character.h"
#include "Number.h"
#include "sound.h"
#include<d3d9.h>

static int Talpha = 245;
static bool TalphaIn = false;
static bool TalphaOut = false;

void InitResult(void)
{
	StopSound();
	Talpha = 245;
	TalphaIn = true;
	TalphaOut = false;
	InitPolygon();
	InitCharacter();
	PlaySound(SOUND_LABEL_END);
}
void UninitResult(void)
{
	SetScore(0);
}
void UpdateResult(void)
{
	if (TalphaIn)
	{
		Talpha -= 3;
		if (Talpha <=10)
		{
			TalphaIn = false;
			Talpha = 0;
		}
	}
	if (GetKeyboardPress(DIK_RETURN))
	{
		TalphaOut = true;
	}
	if (TalphaOut)
	{
		Talpha += 3;
		if (Talpha >= 250)
		{
			TalphaOut = false;
			ChangeScene(SCENE_TITLE);
			StopSound(SOUND_LABEL_END);
		}
	}

	UpdatePolygon();
}
void DrawResult(void)
{
	SetDUIChange(2);
	SetTexture(TEX_P2_RESULT);
	SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	DrawPolygon(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	int score = GetScore();
	if (score>1000)
	{
		score = 99;
	}
	int sn = score / 100;
	DrawNumber(sn, 590, 240);
	int sb = (score%100) / 10;
	DrawNumber(sb, 660, 240);
	sb = score % 10;
	DrawNumber(sb, 730, 240);
	SetTexture(TEX_P2_TITLE_02);
	SetPolygonColor(D3DCOLOR_ARGB(Talpha, 255, 255, 255));
	DrawPolygon(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}