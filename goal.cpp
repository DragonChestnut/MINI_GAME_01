#include "goal.h"
#include "stdlib.h"
#include "Xmodel.h"
#include "Billboard.h"
#include "sound.h"

#define MAX_POINT_BILL (3)

GOAL g_goal[MAX_GOAL];

static int g_Goalnum=MAX_GOAL;

static int g_GoalType_S = 0;
static int g_GoalType_M = 0;
static int g_GoalType_L= 0;
static int g_ISGoalType_S = 0;
static int g_ISGoalType_M = 0;
static int g_ISGoalType_L = 0;
//
//

SCOREANIME g_scoreanime[MAX_POINT_BILL];

void InitGoal(void)
{
	g_GoalType_S = 0;
	g_GoalType_M = 0;
	g_GoalType_L = 0;
	g_ISGoalType_S = 0;
	g_ISGoalType_M = 0;
	g_ISGoalType_L = 0;
	for (int i = 0; i < MAX_GOAL; i++)
	{
		g_goal[i].GoalPos.x = 0.0f;
		g_goal[i].GoalPos.y = 0.0f;
		g_goal[i].GoalPos.z = 0.0f;
		g_goal[i].IsGoal = false;
	}
	for (int m = 0; m < MAX_POINT_BILL; m++)
	{
		g_scoreanime[m].pos.x = 0;
		g_scoreanime[m].pos.y = 0;
		g_scoreanime[m].pos.z = 0;
		g_scoreanime[m].ScoreAlpha = 0;
		g_scoreanime[m].ScoreISy= 0.f;
		g_scoreanime[m].ISScoreAnime = false;
	}
}
void UninitGoal(void)
{
	g_Goalnum = MAX_GOAL;
	for (int i = 0; i < MAX_GOAL; i++)
	{
		g_goal[i].GoalPos.x = 0.0f;
		g_goal[i].GoalPos.y = 0.0f;
		g_goal[i].GoalPos.z = 0.0f;
		g_goal[i].IsGoal = false;
	}
}

void UpdateGoal(void)
{
	for (int i = 0; i < g_Goalnum; i++)
	{
		if (!g_goal[i].IsGoal)
		{
			g_goal[i].IsGoal = true;
			g_goal[i].GoalPos.x = rand() % 15+3;
			g_goal[i].GoalPos.y = 0;
			g_goal[i].GoalPos.z = rand() % 36-18;
			SetModelPos(i,g_goal[i].GoalPos.x, g_goal[i].GoalPos.y, g_goal[i].GoalPos.z);
			if (g_ISGoalType_S<g_GoalType_S)
			{
				SetModelScale(i, 1.0f, 1.0f, 1.0f);
				g_goal[i].GoalType = 0;
				g_ISGoalType_S += 1;
			}
			else if (g_ISGoalType_M<g_GoalType_M)
			{
				SetModelScale(i, 2.0f, 2.0f, 2.0f);
				g_goal[i].GoalType = 1;
				g_ISGoalType_M += 1;
			}
			else if (g_ISGoalType_L<g_GoalType_L)
			{
				SetModelScale(i,3.0f, 3.0f, 3.0f);
				g_goal[i].GoalType = 2;
				g_ISGoalType_L += 1;
			}
		}
	}
	for (int m = 0; m < MAX_POINT_BILL; m++)
	{
		if (g_scoreanime[m].ISScoreAnime)
		{
			g_scoreanime[m].ScoreISy += 0.2f;
			switch (m)
			{
			case 0:
			{
				SetBillboardPos(BILL_POINT_1, g_scoreanime[m].pos.x, g_scoreanime[m].pos.y+ g_scoreanime[m].ScoreISy, g_scoreanime[m].pos.z);
			}break;
			case 1:
			{
				SetBillboardPos(BILL_POINT_2, g_scoreanime[m].pos.x, g_scoreanime[m].pos.y + g_scoreanime[m].ScoreISy, g_scoreanime[m].pos.z);
			}break;
			case 2:
			{
				SetBillboardPos(BILL_POINT_3, g_scoreanime[m].pos.x, g_scoreanime[m].pos.y + g_scoreanime[m].ScoreISy, g_scoreanime[m].pos.z);
			}break;
			default:
				break;
			}
			SetBillboardPos(BILL_RANNKO, g_scoreanime[m].pos.x, g_scoreanime[m].pos.y + g_scoreanime[m].ScoreISy-3, g_scoreanime[m].pos.z);
		}
		if (g_scoreanime[m].ScoreISy>3)
		{
			StopSound(SOUND_LABEL_POINT);
			switch (m)
			{
			case 0:
			{
				DestroyBillboard(BILL_POINT_1);
			}break;
			case 1:
			{
				DestroyBillboard(BILL_POINT_2);
			}break;
			case 2:
			{
				DestroyBillboard(BILL_POINT_3);
			}break;
			default:
				break;
			}
			//
			DestroyBillboard(BILL_RANNKO);
			g_scoreanime[m].ISScoreAnime = false;
			g_scoreanime[m].pos.x = 0;
			g_scoreanime[m].pos.y = 0;
			g_scoreanime[m].pos.z = 0;
			g_scoreanime[m].ScoreAlpha = 0;
			g_scoreanime[m].ScoreISy = 0.f;
		}
	}
}
void DrawGoal(void)
{

}

void SetGoalNum(int GoalNum)
{
	g_Goalnum = GoalNum;
}

bool GetIsGoal(int num)
{
	return g_goal[num].IsGoal;
}

D3DXVECTOR3 GetGoalPos(int num)
{
	return g_goal[num].GoalPos;
}

//êî
int GetGoalNum(void)
{
	return g_Goalnum;
}

//
int GetGoalType(int num)
{
	return g_goal[num].GoalType;
}

void DestroyGoal(int num)
{
	ScorePlus(g_goal[num].GoalPos, g_goal[num].GoalType);
	g_goal[num].GoalPos.x = 0.0f;
	g_goal[num].GoalPos.y = 0.0f;
	g_goal[num].GoalPos.z = 0.0f;
	g_goal[num].IsGoal = false;
}

void SetGoalLevel(int snum,int mnum,int lnum)
{
	g_GoalType_S = snum;
	g_GoalType_M = mnum;
	g_GoalType_L = lnum;
}

void DestroyGoalLevel(void)
{
	g_GoalType_S = 0;
	g_GoalType_M = 0;
	g_GoalType_L = 0;
	g_ISGoalType_S = 0;
	g_ISGoalType_M = 0;
	g_ISGoalType_L = 0;
	for (int i = 0; i < MAX_GOAL; i++)
	{
		g_goal[i].GoalPos.x = 0.0f;
		g_goal[i].GoalPos.y = 0.0f;
		g_goal[i].GoalPos.z = 0.0f;
		g_goal[i].IsGoal = false;
	}
}

void ScorePlus(D3DXVECTOR3 pos,int type)
{
	for (int m = 0; m < MAX_POINT_BILL; m++)
	{
		if (!g_scoreanime[m].ISScoreAnime)
		{
			g_scoreanime[m].pos.x = pos.x-2.f;
			g_scoreanime[m].pos.y = pos.y+1.f;
			g_scoreanime[m].pos.z = pos.z;
			g_scoreanime[m].ISScoreAnime = true;
			PlaySound(SOUND_LABEL_POINT);
			switch (m)
			{
			case 0: 
			{
				CreateBillboardWHN(BILL_POINT_1, 3.98f, 1.99f, 1);
				SetBillboardPos(BILL_POINT_1, g_scoreanime[m].pos.x, g_scoreanime[m].pos.y, g_scoreanime[m].pos.z);
				switch (type)
				{
				case 0:SetBillboardISTexNum(BILL_POINT_1, TEX_PLUS_3); break;
				case 1:SetBillboardISTexNum(BILL_POINT_1, TEX_PLUS_2); break;
				case 2:SetBillboardISTexNum(BILL_POINT_1, TEX_PLUS_1); break;
				default:
					break;
				}
			}break;
			case 1:
			{
				CreateBillboardWHN(BILL_POINT_2, 3.98f, 1.99f, 1);
				SetBillboardPos(BILL_POINT_2, g_scoreanime[m].pos.x, g_scoreanime[m].pos.y, g_scoreanime[m].pos.z);
				switch (type)
				{
				case 0:SetBillboardISTexNum(BILL_POINT_2, TEX_PLUS_3); break;
				case 1:SetBillboardISTexNum(BILL_POINT_2, TEX_PLUS_2); break;
				case 2:SetBillboardISTexNum(BILL_POINT_2, TEX_PLUS_1); break;
				default:
					break;
				}
			}break;
			case 2:
			{
				CreateBillboardWHN(BILL_POINT_3, 3.98f, 1.99f, 1);
				SetBillboardPos(BILL_POINT_3, g_scoreanime[m].pos.x, g_scoreanime[m].pos.y, g_scoreanime[m].pos.z);
				switch (type)
				{
				case 0:SetBillboardISTexNum(BILL_POINT_3, TEX_PLUS_3); break;
				case 1:SetBillboardISTexNum(BILL_POINT_3, TEX_PLUS_2); break;
				case 2:SetBillboardISTexNum(BILL_POINT_3, TEX_PLUS_1); break;
				default:
					break;
				}
			}break;
			default:
				break;
			}
			//
			CreateBillboardWHN(BILL_RANNKO, 3.87f, 3.01f, 1);
			SetBillboardPos(BILL_RANNKO, g_scoreanime[m].pos.x, g_scoreanime[m].pos.y - 3, g_scoreanime[m].pos.z);
			SetBillboardISTexNum(BILL_RANNKO, TEX_RANNKO);
			break;
		}
	}
}