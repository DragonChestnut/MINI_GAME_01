#include "character.h"
#include "Game.h"
#include "camera.h"
#include "input.h"
#include "math.h"
#include "Hit.h"
#include "goal.h"
#include "sound.h"

static CHARACTER g_character;

static float power = 0.f;
static bool powerlcounter = false;
static bool digcounter = false;
static float dig = 0.f;

static float character_speed = 0.1f;//
static float camera_WS_speed = 0.1f;//カメラ縦スピード
static float camera_AD_speed = 0.1f;//カメラ横スピード

static BALL ball;
static float pi = 3.14f;
static int score = 0;

//se
static bool wuwuswitch = false;

D3DXVECTOR3 CameraEyeReset;
D3DXVECTOR3 CameraAtReset;

void InitCharacter(void)
{
	D3DXVECTOR3 IsCameraEye = GetEye();
	CameraEyeReset = IsCameraEye;
	D3DXVECTOR3 IsCameraAt = GetAt();
	CameraAtReset = IsCameraAt;

	g_character.CharacterPos.x = -10.f;
	g_character.CharacterPos.y = -0.26f;
	g_character.CharacterPos.z = 0.f;
	g_character.speed_x = 0.1f;
	g_character.speed_z = 0.1f;
	g_character.IsCharacter = true;
	wuwuswitch = false;
	CreateBillboardWHN(BILL_CHARACTER, 3.8f, 2.1f, 1);
	SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
	SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_ALICE_01);
	//
	ball.BallPos.x = 500.0f;
	ball.BallPos.y = 0.0f;
	ball.BallPos.z = 0.0f;
	ball.BallPos_start.x = 0.0f;
	ball.BallPos_start.y = 0.0f;
	ball.BallPos_start.z = 0.0f;
	ball.Bspeed_v = 0.0f;
	ball.Bspeed_z = 0.0f;
	ball.Bangle = 0.0f;
	ball.Bg = 9.8f;
	ball.Ba = 1.0f;
	ball.Bz = 0.0f;
	ball.Btime = 0;
	ball.Ballx0 = 0.000f;
	ball.Ballx1 = 0.000f;
	ball.Isball = false;
	ball.BallAnimeCounter= 0;
	ball.BallISAnime = 1;
	ball.BallMaxAnime = 8;
	ball.BallAnime = false;
	ball.BallAnglecounter = false;
	ball.NoWalkcounter = false;
	ball.ISAngle = false;
	//
	power = 0.f;
	powerlcounter = false;
}
void UninitCharacter(void)
{
	DestroyBillboard(BILL_CHARACTER);
	g_character.IsCharacter = false;
	DestroyBillboard(BILL_BALL);
	SetCameraPos(CameraEyeReset);
	SetCameraAt(CameraAtReset);
}
void UpdateCharacter(void)
{
	D3DXVECTOR3 characterpos = GetBillboardPos(BILL_CHARACTER);
	//CHARACTER操作
	if (!ball.Isball)
	{
		if (ball.BallAnglecounter)
		{
			if (GetKeyboardPress(DIK_SPACE))
			{
				if (!wuwuswitch)
				{
					PlaySound(SOUND_LABEL_WUWU);
					wuwuswitch = true;
				}
				if (!powerlcounter)
				{
					if (power < 200)
					{
						power += 10.f;
					}
					else
					{
						powerlcounter = true;
					}
				}
				else
				{
					if (power > 0)
					{
						power -= 10.f;
					}
					else
					{
						powerlcounter = false;
					}
				}
			}

			if (GetKeyboardRelease(DIK_SPACE))
			{
				if (wuwuswitch)
				{
					StopSound(SOUND_LABEL_WUWU);
					wuwuswitch = false;
				}
				PlaySound(SOUND_LABEL_NIU);
				ball.Isball = true;
				ball.BallPos_start.x = characterpos.x + 1.74f;
				ball.BallPos_start.y = characterpos.y + 1.68f;
				ball.BallPos_start.z = characterpos.z;
				ball.Bspeed_v = 25.0f*power / 236.00f;
				CreateBillboardWHN(BILL_BALL, 0.2f, 0.2f, 1);
				SetBillboardPos(BILL_BALL, ball.BallPos_start.x, ball.BallPos_start.y, ball.BallPos_start.z);
				SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_ALICE_05);
				SetBillboardISTexNum(BILL_BALL, TEX_BALL);
			}
		}
		else
		{
			if (GetKeyboardPress(DIK_SPACE))
			{
				if (!wuwuswitch)
				{
					PlaySound(SOUND_LABEL_WUWU);
					wuwuswitch = true;
				}
				ball.ISAngle = true;
				ball.NoWalkcounter = true;
				if (!digcounter)
				{
					if (dig < 80)
					{
						dig += 1.f;
					}
					else
					{
						digcounter = true;
					}
				}
				else
				{
					if (dig > 0)
					{
						dig -= 1.f;
					}
					else
					{
						digcounter = false;
					}
				}
			}
			if (GetKeyboardRelease(DIK_SPACE))
			{
				if (wuwuswitch)
				{
					StopSound(SOUND_LABEL_WUWU);
					wuwuswitch = false;
				}
				ball.Bangle = dig;
				ball.BallAnglecounter = true;
				ball.NoWalkcounter = false;
			}
		}
		if (!ball.NoWalkcounter)
		{
			if (GetKeyboardPress(DIK_W))
			{
				g_character.CharacterPos = GetBillboardPos(BILL_CHARACTER);
				if (g_character.CharacterPos.z <= 20.0f)
				{
					g_character.CharacterPos.z += character_speed;
					SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
					//カメラも移動タイプ
					D3DXVECTOR3 IsCameraFront = GetFront();
					IsCameraFront.y = 0;
					D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
					D3DXVECTOR3 IsCameraEye = GetEye();
					IsCameraEye += IsCameraFront* camera_WS_speed;
					D3DXVECTOR3 IsCameraAt = GetAt();
					IsCameraAt += IsCameraFront*camera_WS_speed;
					SetCameraPos(IsCameraEye);
					SetCameraAt(IsCameraAt);
				}
			}

			if (GetKeyboardPress(DIK_S))
			{
				g_character.CharacterPos = GetBillboardPos(BILL_CHARACTER);
				if (g_character.CharacterPos.z >= -20.0f)
				{
					g_character.CharacterPos.z -= character_speed;
					SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
					//カメラも移動タイプ
					D3DXVECTOR3 IsCameraFront = GetFront();
					IsCameraFront.y = 0;
					D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
					D3DXVECTOR3 IsCameraEye = GetEye();
					IsCameraEye -= IsCameraFront*camera_WS_speed;
					D3DXVECTOR3 IsCameraAt = GetAt();
					IsCameraAt -= IsCameraFront*camera_WS_speed;
					SetCameraPos(IsCameraEye);
					SetCameraAt(IsCameraAt);
				}
			}
			if (GetKeyboardPress(DIK_D))
			{
				g_character.CharacterPos = GetBillboardPos(BILL_CHARACTER);
				if (ball.Isball)
				{
					SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_ALICE_05);
				}
				else
				{
					SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_ALICE_01);
				}
				if (g_character.CharacterPos.x <= 0.0f)
				{
					g_character.CharacterPos.x += 0.1f;
					SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
					//カメラも移動タイプ
					D3DXVECTOR3 IsCameraRight = GetRight();
					D3DXVECTOR3 IsCameraUp = GetUp();
					D3DXVECTOR3 IsCameraFront = GetFront();
					D3DXVec3Cross(&IsCameraRight, &IsCameraUp, &IsCameraFront);
					D3DXVec3Normalize(&IsCameraRight, &IsCameraRight);
					D3DXVECTOR3 IsCameraEye = GetEye();
					IsCameraEye += IsCameraRight*camera_AD_speed;
					D3DXVECTOR3 IsCameraAt = GetAt();
					IsCameraAt += IsCameraRight*camera_AD_speed;
					SetCameraPos(IsCameraEye);
					SetCameraAt(IsCameraAt);
				}
			}
			if (GetKeyboardPress(DIK_A))
			{
				g_character.CharacterPos = GetBillboardPos(BILL_CHARACTER);
				if (ball.Isball)
				{
					SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_ALICE_04);
				}
				else
				{
					SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_ALICE_02);
				}
				if (g_character.CharacterPos.x >= -20.0f)
				{
					g_character.CharacterPos.x -= 0.1f;
					SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
					//カメラも移動タイプ
					D3DXVECTOR3 IsCameraRight = GetRight();
					D3DXVECTOR3 IsCameraUp = GetUp();
					D3DXVECTOR3 IsCameraFront = GetFront();
					D3DXVec3Cross(&IsCameraRight, &IsCameraUp, &IsCameraFront);
					D3DXVec3Normalize(&IsCameraRight, &IsCameraRight);
					D3DXVECTOR3 IsCameraEye = GetEye();
					IsCameraEye -= IsCameraRight*camera_AD_speed;
					D3DXVECTOR3 IsCameraAt = GetAt();
					IsCameraAt -= IsCameraRight*camera_AD_speed;
					SetCameraPos(IsCameraEye);
					SetCameraAt(IsCameraAt);
				}
			}
			//
			if (GetKeyboardPress(DIK_W) && GetKeyboardPress(DIK_LSHIFT))
			{
				g_character.CharacterPos = GetBillboardPos(BILL_CHARACTER);
				if (g_character.CharacterPos.z <= 20.0f)
				{
					g_character.CharacterPos.z += character_speed * 2;
					SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
					//カメラも移動タイプ
					D3DXVECTOR3 IsCameraFront = GetFront();
					IsCameraFront.y = 0;
					D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
					D3DXVECTOR3 IsCameraEye = GetEye();
					IsCameraEye += IsCameraFront* camera_WS_speed * 2;
					D3DXVECTOR3 IsCameraAt = GetAt();
					IsCameraAt += IsCameraFront*camera_WS_speed * 2;
					SetCameraPos(IsCameraEye);
					SetCameraAt(IsCameraAt);
				}
			}
			if (GetKeyboardPress(DIK_S) && GetKeyboardPress(DIK_LSHIFT))
			{
				g_character.CharacterPos = GetBillboardPos(BILL_CHARACTER);
				if (g_character.CharacterPos.z >= -20.0f)
				{
					g_character.CharacterPos.z -= character_speed * 2;
					SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
					//カメラも移動タイプ
					D3DXVECTOR3 IsCameraFront = GetFront();
					IsCameraFront.y = 0;
					D3DXVec3Normalize(&IsCameraFront, &IsCameraFront);
					D3DXVECTOR3 IsCameraEye = GetEye();
					IsCameraEye -= IsCameraFront*camera_WS_speed * 2;
					D3DXVECTOR3 IsCameraAt = GetAt();
					IsCameraAt -= IsCameraFront*camera_WS_speed * 2;
					SetCameraPos(IsCameraEye);
					SetCameraAt(IsCameraAt);
				}
			}
			if (GetKeyboardPress(DIK_D) && GetKeyboardPress(DIK_LSHIFT))
			{
				g_character.CharacterPos = GetBillboardPos(BILL_CHARACTER);
				if (ball.Isball)
				{
					SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_ALICE_05);
				}
				else
				{
					SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_ALICE_01);
				}
				if (g_character.CharacterPos.x <= 0.0f)
				{
					g_character.CharacterPos.x += 0.2f;
					SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
					//カメラも移動タイプ
					D3DXVECTOR3 IsCameraRight = GetRight();
					D3DXVECTOR3 IsCameraUp = GetUp();
					D3DXVECTOR3 IsCameraFront = GetFront();
					D3DXVec3Cross(&IsCameraRight, &IsCameraUp, &IsCameraFront);
					D3DXVec3Normalize(&IsCameraRight, &IsCameraRight);
					D3DXVECTOR3 IsCameraEye = GetEye();
					IsCameraEye += IsCameraRight*camera_AD_speed * 2;
					D3DXVECTOR3 IsCameraAt = GetAt();
					IsCameraAt += IsCameraRight*camera_AD_speed * 2;
					SetCameraPos(IsCameraEye);
					SetCameraAt(IsCameraAt);
				}
			}
			if (GetKeyboardPress(DIK_A) && GetKeyboardPress(DIK_LSHIFT))
			{
				g_character.CharacterPos = GetBillboardPos(BILL_CHARACTER);
				if (ball.Isball)
				{
					SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_ALICE_04);
				}
				else
				{
					SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_ALICE_02);
				}
				if (g_character.CharacterPos.x >= -20.0f)
				{
					g_character.CharacterPos.x -= 0.2f;
					SetBillboardPos(BILL_CHARACTER, g_character.CharacterPos.x, g_character.CharacterPos.y, g_character.CharacterPos.z);
					//カメラも移動タイプ
					D3DXVECTOR3 IsCameraRight = GetRight();
					D3DXVECTOR3 IsCameraUp = GetUp();
					D3DXVECTOR3 IsCameraFront = GetFront();
					D3DXVec3Cross(&IsCameraRight, &IsCameraUp, &IsCameraFront);
					D3DXVec3Normalize(&IsCameraRight, &IsCameraRight);
					D3DXVECTOR3 IsCameraEye = GetEye();
					IsCameraEye -= IsCameraRight*camera_AD_speed * 2;
					D3DXVECTOR3 IsCameraAt = GetAt();
					IsCameraAt -= IsCameraRight*camera_AD_speed * 2;
					SetCameraPos(IsCameraEye);
					SetCameraAt(IsCameraAt);
				}
			}
		}
	}

	if (ball.Isball)
	{
		if (!ball.BallAnime)
		{
			ball.BallPos.x = ((cosf(ball.Bangle*pi / 180)*ball.Bspeed_v - ball.Ba*ball.Btime / 60)*ball.Btime / 60) + ball.BallPos_start.x;
			ball.BallPos.y = ((sinf(ball.Bangle*pi / 180)*ball.Bspeed_v - ball.Bg*ball.Btime / 60)*ball.Btime / 60) + ball.BallPos_start.y;
			ball.BallPos.z = ((ball.Bspeed_z + ball.Bz*ball.Btime / 60)*ball.Btime / 60) + ball.BallPos_start.z;
			SetBillboardPos(BILL_BALL, ball.BallPos.x, ball.BallPos.y, ball.BallPos.z);
			SetBillboardTexCoord(BILL_BALL, 0.0f, 0.0f, 1.0f, 1.0f);
			ball.Btime++;
			int goalnum = GetGoalNum();
			//
			if (ball.BallPos.y <= 0)
			{
				ball.BallAnime = true;
			}
			for (int i = 0; i < goalnum; i++)
			{
				D3DXVECTOR3 goal = GetGoalPos(i);
				int goaltype = GetGoalType(i);
				switch (goaltype)
				{
				case 0:
				{
					if (ISHit(ball.BallPos, goal, 0.1f, 1.f))
					{
						StopSound(SOUND_LABEL_NIU);
						score += 4;
						DestroyBall();
						DestroyGoal(i);
						break;
					}
				}break;
				case 1:
				{
					if (ISHit(ball.BallPos, goal, 0.1f, 2.f))
					{
						StopSound(SOUND_LABEL_NIU);
						score += 2;
						DestroyBall();
						DestroyGoal(i);
						break;
					}
				}break;
				case 2:
				{
					if (ISHit(ball.BallPos, goal, 0.1f, 3.f))
					{
						StopSound(SOUND_LABEL_NIU);
						score += 1;
						DestroyBall();
						DestroyGoal(i);
						break;
					}
				}break;
				default:
					break;
				}

			}
		}
		else
		{
			StopSound(SOUND_LABEL_NIU);
			ball.BallPos.y = 0.492f;
			if (ball.BallAnimeCounter >= 3)
			{
				ball.BallISAnime++;
				ball.BallAnimeCounter = 0;
			}
			ball.BallAnimeCounter++;
			ball.Ballx0 = ball.BallISAnime / (float)ball.BallMaxAnime;
			ball.Ballx1 = (ball.BallISAnime + 1) / (float)ball.BallMaxAnime;
			DestroyBillboard(BILL_BALL);
			CreateBillboardWHN(BILL_BALL, 0.875f, 0.492f, 1);
			SetBillboardISTexNum(BILL_BALL, TEX_SMOKE);
			SetBillboardTexCoord(BILL_BALL, ball.Ballx0, 0.0f, ball.Ballx1, 1.0f);
			SetBillboardPos(BILL_BALL, ball.BallPos.x, ball.BallPos.y, ball.BallPos.z);
			if (ball.BallISAnime >= ball.BallMaxAnime)
			{
				DestroyBall();
			}
			//}
		}
	}
}
void DrawCharacter(void)
{
}

bool GetISBall(void)
{
	return ball.Isball;
}

int GetScore(void)
{
	return score;
}

void SetScore(int num)
{
	score=num;
}

bool GetISCharacter(void)
{
	return g_character.IsCharacter;
}

float GetPower(void)
{
	return power;
}

bool GetISBallAngle(void)
{
	return ball.ISAngle;
}

float GetDig(void)
{
	return dig;
}

void DestroyBall(void)
{
	DestroyBillboard(BILL_BALL);
	SetBillboardISTexNum(BILL_CHARACTER, TEX_CHARACTER_ALICE_01);
	ball.BallPos.x = 500.0f;
	ball.BallPos.y = 0.0f;
	ball.BallPos.z = 0.0f;
	ball.BallPos_start.x = 0.0f;
	ball.BallPos_start.y = 0.0f;
	ball.BallPos_start.z = 0.0f;
	ball.Bspeed_v = 0.0f;
	ball.Bspeed_z = 0.0f;
	ball.Bangle = 0.0f;
	ball.Bg = 9.8f;
	ball.Ba = 1.0f;
	ball.Bz = 0.0f;
	ball.Btime = 0;
	ball.Ballx0 = 0.000f;
	ball.Ballx1 = 0.000f;
	ball.Isball = false;
	ball.BallAnimeCounter = 0;
	ball.BallISAnime = 1;
	ball.BallMaxAnime = 8;
	ball.BallAnime = false;
	ball.BallAnglecounter = false;
	ball.NoWalkcounter = false;
	ball.ISAngle = false;
	dig = 0;
	power = 0;
}

void ReSetDig(void)
{
	dig = 0;
}
void ReSetPower(void)
{
	power = 0;
}