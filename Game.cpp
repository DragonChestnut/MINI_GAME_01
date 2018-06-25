#include "Game.h"
#include "polygon3DTest.h"
#include "Polygon.h"
#include "Xmodel.h"
#include "meshfield.h"
#include "camera.h"
#include "character.h"
#include "Billboard.h"
#include "scene.h"
#include "wall.h"
#include "input.h"
#include "shadow.h"
#include "GameUI.h"
#include "goal.h"
#include "sound.h"

static int time = 0;

static int level = 1;

static bool g_GameStartSwitch = false;

static bool ISClear = false;

static bool Bgm = false;
void InitGame(void)
{
	StopSound();
	time = 0;
	ISClear = false;
	InitCharacter();
	InitGameUI();
	InitGoal();
	level = 1;
	LevelSet();
	Bgm = false;
}


void UninitGame(void)
{
	//UninitPolygon3D();
	UninitCharacter();
	UninitGameUI();
	UninitGoal();
}

void UpdateGame(void)
{
	if (!g_GameStartSwitch)
	{
		if (!GetTimeUpSwitch())
		{
			if (GetKeyboardPress(DIK_RETURN))
			{
				g_GameStartSwitch = true;
				if (!Bgm)
				{
					PlaySound(SOUND_LABEL_BGM00);
					Bgm = true;
				}
			}
		}
	}
	else
	{
		UpdateCharacter();
		time++;
		//
		if (time >= 3600)
		{
			StopSound();
			Bgm = false;
			PlaySound(SOUND_LABEL_TIMEUP);
			ResetTimeUpSwitch();
			ReSetDig();
			ReSetPower();
			if (!ClearJudge())
			{
				g_GameStartSwitch = false;
				ISClear = false;
				level = 1;
			}
			else
			{
				g_GameStartSwitch = false;
				ISClear = true;
				time = 0;
			}
		}
	}
	//UpdatePolygon3D();
	UpdateXModel();
	UpdateCamera();
	UpdateBillboard();
	UpdateMeshField();
	UpdateWall();
	UpdateShadow();
	UpdateGameUI();
	UpdateGoal();
	//test
	if (GetKeyboardPress(DIK_K))
	{
		ResetTimeUpSwitch();
		g_GameStartSwitch = false;
		ISClear = false;
		ChangeScene(SCENE_RESULT);
		level = 1;
	}
}

void DrawGame(void)
{
	//DrawPolygon3D();
	DrawXModel();
	DrawCharacter();
	DrawBillboard();
	DrawMeshField();
	DrawWall();
	DrawShadow();
	DrawGameUI();
	DrawGoal();
}

int GetTime(void)
{
	return time;
}

int GetLevel(void)
{
	return level;
}

void LevelSet(void)
{
	switch (level)
	{
	case 1:SetGoalNum(2); SetGoalLevel(0, 0, 2); break;
	case 2:SetGoalNum(2); SetGoalLevel(0, 1, 1); break;
	case 3:SetGoalNum(2); SetGoalLevel(0, 2, 0); break;
	case 4:SetGoalNum(2); SetGoalLevel(1, 1, 0); break;
	case 5:SetGoalNum(2); SetGoalLevel(2, 0, 0); break;
	case 6:SetGoalNum(2); SetGoalLevel(2, 0, 0); break;
	default:
		break;
	}
}

bool ClearJudge(void)
{
	int score = GetScore();
	switch (level)
	{
	case 1: {
		if (score > CLEAR_1)
		{
			level = 2;
			DestroyGoalLevel();
			LevelSet();
			return true;
		}
		else
		{
			return false;
		}}break;
	case 2: {
		if (score > CLEAR_2)
		{
			level = 3;
			DestroyGoalLevel();
			LevelSet();
			return true;
		}
		else
		{
			return false;
		}}break;
	case 3: {
		if (score > CLEAR_3)
		{
			level = 4;
			DestroyGoalLevel();
			LevelSet();
			return true;
		}
		else
		{
			return false;
		}}break;
	case 4: {
		if (score > CLEAR_4)
		{
			level = 5;
			DestroyGoalLevel();
			LevelSet();
			return true;
		}
		else
		{
			return false;
		}}break;
	case 5: {
		if (score > CLEAR_5)
		{
			level = 6;
			DestroyGoalLevel();
			LevelSet();
			return true;
		}
		else
		{
			return false;
		}
	}break;
	case 6: {
		if (score > CLEAR_6)
		{
			//level = 7;
			DestroyGoalLevel();
			//LevelSet();
			return true;
		}
		else
		{
			return false;
		}
	}break;
	default:
		return false;
		break;
	}
}

bool GetGameStartSwitch(void)
{
	return g_GameStartSwitch;
}

bool GetISClear(void)
{
	return ISClear;
}