#include "GameUI.h"
#include "camera.h"
#include "polygon.h"
#include "Number.h"
#include "input.h"
#include "character.h"
#include "scene.h"
#include "sound.h"

static float power = 0.f;
static float dig = 0.f;
static int ChangeAlpha = 0;
static bool timeupswitch = false;
static bool timeupswitchend = false;
static int TimeUpAlpha = 0;
static float CEy = -500.f;
static bool CEyswitch = false;

static bool check = false;
static bool levelswitch = false;

void InitGameUI(void)
{
	timeupswitch = false;
	timeupswitchend = false;
	CEyswitch = false;
	ChangeAlpha = 0;
	TimeUpAlpha = 0;
	CEy = -500.f;
	check = false;
}
void UninitGameUI(void)
{

}
void UpdateGameUI(void)
{
	UpdatePolygon();
	if (timeupswitch)
	{
		if (timeupswitchend)
		{
			if (!CEyswitch)
			{
				if (GetKeyboardPress(DIK_SPACE))
				{
					CEyswitch = true;
				}
			}
		}
	}
}
void DrawGameUI(void)
{
	SetDUIChange(3);
	if (GetGameStartSwitch())
	{
		if (levelswitch)
		{
			StopSound(SOUND_LABEL_LEVEL);
		}
		CEy = -500.f;
		ChangeAlpha = 0;
		float dig = GetDig();
		if (GetISBallAngle())
		{
			SetTexture(TEX_P2_UI_ALLOW);
			SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
			SetPolygonRotation(-15.f, 25.f, (360 - dig)*D3DX_PI / 180.f);
			DrawPolygon(200.f, 280.f, 150, 50, 0, 0, 300, 100, true);
		}
		SetTexture(TEX_P2_UI_BOARD);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(0.f, -70.f, 250, 250, 0, 0, 500, 500);
		SetTexture(TEX_P2_UI_BOARDSCORE);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(230.f, -70.f, 250, 250, 0, 0, 500, 500);
		int time = GetTime();
		int n = (60 - (time / 60)) / 10;
		DrawNumber(n, 40, 20);
		n = (60 - (time / 60)) % 10;
		DrawNumber(n, 120, 20);
		SetTexture(TEX_P2_UI_BOARDGAME);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(-20.f, 380.f, 400, 400, 0, 0, 500, 500);
		SetTexture(TEX_P2_UI_BOARDCONTROL);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(340.f, 380.f, 400, 400, 0, 0, 500, 500);
		//score
		int score = GetScore();
		int s = score / 100;
		DrawNumberB(s, 285, 35);
		s = (score%100) / 10;
		DrawNumberB(s, 325, 35);
		s = score % 10;
		DrawNumberB(s, 365, 35);
		//
		//level
		int level = GetLevel();
		DrawNumberC(level, 380, 100);
		//
		//’ñŽ¦
		int clear;
		switch (level)
		{
		case 1:
		{
			clear = CLEAR_1;
		}break;
		case 2:
		{
			clear = CLEAR_2;
		}break;
		case 3:
		{
			clear = CLEAR_3;
		}break;
		case 4:
		{
			clear = CLEAR_4;
		}break;
		case 5:
		{
			clear = CLEAR_5;
		}break;
		default:
			break;
		}
		int c = clear / 100;
		DrawNumberB(c, 565, 645);
		c = (clear%100) / 10;
		DrawNumberB(c, 605, 645);
		c = clear % 10;
		DrawNumberB(c, 645, 645);
		//
		float power = GetPower();
		SetTexture(TEX_P2_UI_CLOCK);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(80.f + power * 236 / 200.000f, 485.f, 30, 52, 0, 0, 30, 52);

		SetTexture(TEX_P2_UI_CLOCK);
		SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
		DrawPolygon(46.f + dig * 236 / 80.000f, 640.f, 30, 52, 0, 0, 30, 52);
	}
	else
	{
		if (timeupswitch)
		{
			if (!timeupswitchend)
			{
				SetTexture(TEX_P2_UI_TIMEUP);
				SetPolygonColor(D3DCOLOR_ARGB(TimeUpAlpha, 255, 255, 255));
				DrawPolygon(200, 200, 800, 200, 0, 0, 800, 200);
				if (TimeUpAlpha<254)
				{
					TimeUpAlpha += 2;
				}
				if (TimeUpAlpha==254)
				{
					timeupswitchend = true;
					TimeUpAlpha = 0;
					StopSound(SOUND_LABEL_TIMEUP);
				}
			}
			else
			{
				if (GetISClear())
				{
					if (!check)
					{
						PlaySound(SOUND_LABEL_WIN);
						check = true;
					}
					SetTexture(TEX_P2_UI_BOARDCLEAR);
					SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
					DrawPolygon(400, CEy, 500, 500, 0, 0, 500, 500);
					if (!CEyswitch)
					{
						if (CEy <80)
						{
							CEy += 4;
						}
					}
					else
					{
						if (CEy >-500)
						{
							CEy -= 8;
						}
						else
						{
							if (check)
							{
								StopSound(SOUND_LABEL_WIN);
								check = false;
							}
							CEy = -500;
							CEyswitch = false;
							timeupswitchend = false;
							timeupswitch = false;
						}
					}
				}
				else
				{
					if (!check)
					{
						PlaySound(SOUND_LABEL_LOSE);
						check = true;
					}
					SetTexture(TEX_P2_UI_BOARDGAMEOVER);
					SetPolygonColor(D3DCOLOR_ARGB(255, 255, 255, 255));
					DrawPolygon(400, CEy, 500, 500, 0, 0, 500, 500);
					if (!CEyswitch)
					{
						if (CEy <80)
						{
							CEy += 4;
						}
					}
					else
					{
						if (CEy >-500)
						{
							CEy -= 8;
						}
						else
						{
							if (check)
							{
								StopSound(SOUND_LABEL_LOSE);
								check = false;
							}
							CEy = -500;
							CEyswitch = false;
							timeupswitchend = false;
							timeupswitch = false;
							StopSound(SOUND_LABEL_BGM00);
							ChangeScene(SCENE_RESULT);
						}
					}
					
				}
			}
		}
		else
		{
			if (!levelswitch)
			{
				PlaySound(SOUND_LABEL_LEVEL);
				levelswitch = true;
			}
			SetTexture(TEX_P2_UI_BOARDCHANGE);
			SetPolygonColor(D3DCOLOR_ARGB(ChangeAlpha, 255, 255, 255));
			DrawPolygon(400, -100, 500, 800, 0, 0, 500, 800);
			if (ChangeAlpha<255)
			{
				ChangeAlpha += 5;
			}
			int level = GetLevel();
			DrawNumber(level, 720, 125);
			int clear;
			switch (level)
			{
			case 1:
			{
				clear = CLEAR_1;
			}break;
			case 2:
			{
				clear = CLEAR_2;
			}break;
			case 3:
			{
				clear = CLEAR_3;
			}break;
			case 4:
			{
				clear = CLEAR_4;
			}break;
			case 5:
			{
				clear = CLEAR_5;
			}break;
			default:
				break;
			}
			int c = clear / 100;
			DrawNumberB(c, 700, 540);
			c = (clear % 100) / 10;
			DrawNumberB(c, 740, 540);
			c = clear % 10;
			DrawNumberB(c, 780, 540);
		}

	}
}

void ResetTimeUpSwitch(void)
{
	timeupswitch = true;
}

bool GetTimeUpSwitch(void)
{
	return timeupswitch;
}