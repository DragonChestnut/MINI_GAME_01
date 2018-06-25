#pragma once
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <d3dx9.h>
#include "Game.h"
#include "Billboard.h"

typedef struct
{
	D3DXVECTOR3 CharacterPos;/*���W*/
	float speed_x;//���X�s�[�h
	float speed_z;//�c�X�s�[�h
	bool IsCharacter;
}CHARACTER;

typedef struct
{
	D3DXVECTOR3 BallPos;/*���W*/
	D3DXVECTOR3 BallPos_start;
	float Bspeed_v;//���X�s�[�h
	float Bspeed_z;//�c�X�s�[�h
	float Bangle;
	float Bg;
	float Ba;
	float Bz;
	int Btime;
	float Ballx0;
	float Ballx1;
	int BallAnimeCounter;
	int BallISAnime;
	int BallMaxAnime;
	bool BallAnime;
	bool BallAnglecounter;
	bool ISAngle;
	bool NoWalkcounter;
	bool Isball;
}BALL;

void InitCharacter(void);
void UninitCharacter(void);
void UpdateCharacter(void);
void DrawCharacter(void);


bool GetISBall(void);

int GetScore(void);
void SetScore(int num);

bool GetISCharacter(void);

float GetPower(void);

bool GetISBallAngle(void);

float GetDig(void);

void DestroyBall(void);

void ReSetDig(void);

void ReSetPower(void);
#endif