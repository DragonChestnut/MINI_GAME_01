#pragma once
#ifndef _GOAL_H_
#define _GOAL_H_

#include <d3dx9.h>
#include "Billboard.h"

typedef struct
{
	D3DXVECTOR3 GoalPos;/*ç¿ïW*/
	bool IsGoal;
	int GoalType;
}GOAL;

typedef struct
{
	D3DXVECTOR3 pos;
	int ScoreAlpha;
	float ScoreISy;
	bool ISScoreAnime;
}SCOREANIME;

#define MAX_GOAL (20)

void InitGoal(void);
void UninitGoal(void);

void UpdateGoal(void);
void DrawGoal(void);

void SetGoalNum(int GoalNum);

bool GetIsGoal(int num);

D3DXVECTOR3 GetGoalPos(int num);
int GetGoalNum(void);


int GetGoalType(int num);

void DestroyGoal(int num);

void SetGoalLevel(int snum, int mnum, int lnum);

void DestroyGoalLevel(void);

void ScorePlus(D3DXVECTOR3 pos, int type);
#endif