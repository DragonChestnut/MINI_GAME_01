#ifndef _XMODEL_H_
#define _XMODEL_H_

#include<d3d9.h>
#include<d3dx9.h>

#define MAX_MESH (8)
typedef struct
{
	char fileName[256];
	int width;
	int height;
}MODEL_TEXTURE;

typedef struct {
	char FileName[256];

}MODELS;

typedef struct {
	D3DXMATRIX MtxModel;
	D3DXMATRIX MtxModelT;
	D3DXMATRIX MtxModelS;
	D3DXMATRIX MtxModelR;
}MODELMTX;

typedef struct {
	float fSpeed;
	float fOldDeg;
	float fNewDeg;
	D3DXVECTOR3 TurnVec;
	D3DXVECTOR3 Pos;
	float fScalex;
	float fScaley;
	float fScalez;
	float fTurnSpeed;
	int Waybutton;
}MODELS_DATE;

typedef enum
{
	MODEL_GOAL_1,
	MODEL_GOAL_2,
	MODEL_GOAL_3,
	MODEL_GOAL_4,
	MODEL_GOAL_5,
	MODEL_GOAL_6,
	MODEL_GOAL_7,
	MODEL_GOAL_8 ,
	MODEL_MAX
}MODEL_ENUM;

typedef enum
{
	MODEL_TEXTURE_GOAL_1,
	MODEL_TEXTURE_GOAL_2,
	MODEL_TEXTURE_GOAL_3,
	MODEL_TEXTURE_GOAL_4,
	MODEL_TEXTURE_GOAL_5,
	MODEL_TEXTURE_GOAL_6,
	MODEL_TEXTURE_GOAL_7,
	MODEL_TEXTURE_GOAL_8,
	MODEL_TEXTURE_MAX
}MODEL_TEXTURE_ENUM;

bool InitXModel(void);
void UninitXModel(void);
void UpdateXModel(void);
void DrawXModel(void);
void InitModelData(void);

void SetModelPos(int typenum,float x, float y, float z);
void SetModelScale(int typenum,float x, float y, float z);
void SetModelColor(int typenum,int r, int g, int b, int a);

const D3DXVECTOR3* GetModelPos(int typenum);
const D3DXVECTOR3* GetCameraMove(void);

float GetModelWay(int num);

#endif //_XMODEL_H_
