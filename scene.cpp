#include "scene.h"
#include "Title.h"
#include "result.h"
#include "Game.h"
#include "shadow.h"
#include "Billboard.h"
#include "wall.h"
#include "meshfield.h"
#include "polygon.h"
#include "Xmodel.h"

//void(*pFunc)() = InitTittle;
//void(*pFunc)(int) = 
//void(*pFunc)(int,int) = 
//int(*pFunc)(int,int) = 


typedef void(*SceneFunc)(void);
static const SceneFunc g_pInit[SERNR_MAX]=
{
	InitTitle,
	InitGame,
	InitResult,
};
static const SceneFunc g_pUninit[SERNR_MAX] =
{
	UninitTitle,
	UninitGame,
	UninitResult,
};
static const SceneFunc g_pUpdate[SERNR_MAX] =
{
	UpdateTitle,
	UpdateGame,
	UpdateResult,
};
static const SceneFunc g_pDraw[SERNR_MAX] =
{
	DrawTitle,
	DrawGame,
	DrawResult,
};


#define START_SCENE (SCENE_TITLE)

static SCENE_ID g_nID= START_SCENE;
static SCENE_ID g_nNextID= START_SCENE;

void InitAllScene(void)
{
	InitPolygon();
	//影設定
	if (!InitShadow())
	{
		MessageBox(NULL, "initshadow読み込めなかった", "エラー", MB_OK);
	}
	if (!ReadShadow())
	{
		MessageBox(NULL, "readshadow読み込めなかった", "エラー", MB_OK);
	}
	SetShadowColor(255, 255, 255, 255);
	SetShadowTex(SHADOW_TEXTURE_1);
	SetShadowType(SHADOW_1);
	InitShadowData();
	if (!InitBillboard())
	{
		MessageBox(NULL, "Billboard読み込めなかった", "エラー", MB_OK);
	}
	if (!InitMeshField())
	{
		MessageBox(NULL, "MeshField読み込めなかった", "エラー", MB_OK);
	}
	if (!InitWall())
	{
		MessageBox(NULL, "Wall読み込めなかった", "エラー", MB_OK);
	}
	if (!InitXModel())
	{
		MessageBox(NULL, "Xmodel読み込めなかった", "エラー", MB_OK);
	}
	InitModelData();
}

void UninitAllScene(void)
{
	UninitPolygon();
	UninitXModel();
	UninitBillboard();
	UninitMeshField();
	UninitWall();
	UninitShadow();
}

void InitScene(void)
{
	g_pInit[g_nID]();
}
void UninitScene(void)
{
	g_pUninit[g_nID]();
}
void UpdateScene(void)
{
	g_pUpdate[g_nID]();
}
void DrawScene(void)
{
	g_pDraw[g_nID]();
	if (g_nNextID != g_nID)
	{
		UninitScene();
		g_nID = g_nNextID;
		InitScene();
	}
}

SCENE_ID ChangeScene(SCENE_ID id)
{
	g_nNextID = id;
	return g_nID;
}