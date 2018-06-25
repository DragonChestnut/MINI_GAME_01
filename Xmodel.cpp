#include "main.h"
#include "input.h"
#include "xmodel.h"
#include "Camera.h"

#define MESHFIELD_GLASS_SIZEX (30)
#define MESHFIELD_GLASS_SIZEZ (30)
//***************************************************************************************
//	グローバル変数宣言
//***************************************************************************************

//Xモデルの描画
static LPD3DXMESH g_pMesh[MODEL_MAX] = { NULL };
static DWORD g_nMaterialNum[MODEL_MAX] = { 0 };
static LPD3DXBUFFER g_pMaterial[MODEL_MAX] = { NULL };
static const MODEL_TEXTURE g_TextureModelMessage[MODEL_MAX][MODEL_TEXTURE_MAX] =
{
	{ "Xmodel/ob1/ob1.png", 1024, 1024},
	{ "Xmodel/ob1/ob2.png", 1024, 1024 },
	{ "Xmodel/ob1/ob3.png", 1024, 1024 },
	{ "Xmodel/ob1/ob4.png", 1024, 1024 },
	{ "Xmodel/ob1/ob5.png", 1024, 1024 },
	{ "Xmodel/ob1/ob1.png", 1024, 1024 },
	{ "Xmodel/ob1/ob1.png", 1024, 1024 },
	{ "Xmodel/ob1/ob1.png", 1024, 1024 },
};
static LPDIRECT3DTEXTURE9 g_pModelTexture[MODEL_MAX][MODEL_TEXTURE_MAX] = { NULL };

static const MODELS g_pModelMessage[MODEL_MAX] =
{
	{ { "Xmodel/ob1/ob1.x" } },
	{ { "Xmodel/ob1/ob2.x" } },
	{ { "Xmodel/ob1/ob3.x" } },
	{ { "Xmodel/ob1/ob4.x" } },
	{ { "Xmodel/ob1/ob5.x" } },
	{ { "Xmodel/ob1/ob1.x" } },
	{ { "Xmodel/ob1/ob1.x" } },
	{ { "Xmodel/ob1/ob1.x" } },
};
static MODELMTX* g_pMtxModel;
static MODELS_DATE* g_pModelData;
static LPD3DXMATERIAL* g_pMaterialSet;
//サブ変数
static int g_nModelColorR[MODEL_MAX];
static int g_nModelColorG[MODEL_MAX];
static int g_nModelColorB[MODEL_MAX];
static int g_nModelColorA[MODEL_MAX];
//static MODEL_ENUM g_eTypeNum;
static D3DXVECTOR3 g_vCameraMove = { 0,0,0 };
static int TexNum = 0;
static float g_flength = 0;
static int g_nShootCount;
bool InitXModel(void)
{
	LPD3DXMESH pTempMesh;
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	LPD3DXBUFFER pAdjacency;
	g_pMaterialSet = new LPD3DXMATERIAL[MODEL_MAX];
	InitModelData();
	for (int i = 0; i < MODEL_MAX; i++)
	{
		HRESULT hr;
		hr = D3DXLoadMeshFromX(g_pModelMessage[i].FileName/*ファイル名*/,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			&pAdjacency,
			&g_pMaterial[i],
			NULL,
			&g_nMaterialNum[i],
			&g_pMesh[i]);
		if (FAILED(hr))
		{
			MessageBox(NULL, "モデルの生成に失敗しました", "エラー", MB_OK);
			return false;
		}
		for (int num = 0; num <g_nMaterialNum[i]; num++)
		{
			hr = D3DXCreateTextureFromFile
			(
				pDevice,
				g_TextureModelMessage[i][num].fileName,
				&g_pModelTexture[i][num]
			);

			if (FAILED(hr))
			{
				MessageBox(NULL, "テクスチャが読み込めなかった", "エラー", MB_OK);
				return false;
			}
		}

		//メッシュの最適化
		hr = g_pMesh[i]->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, (DWORD*)pAdjacency->GetBufferPointer(), NULL, NULL, NULL);
		pAdjacency->Release();

		D3DVERTEXELEMENT9 elements[MAXD3DDECLLENGTH];
		g_pMesh[i]->GetDeclaration(elements);
		hr = g_pMesh[i]->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, elements, pDevice, &pTempMesh);//Clone->pTempMesh
		g_pMesh[i]->Release();
		g_pMesh[i] = pTempMesh;
	}

	return true;
}

void UninitXModel(void)
{
	for (int m = 0; m < MODEL_MAX; m++)
	{
		for (int i = 0; i < MODEL_TEXTURE_MAX; i++)
		{
			if (g_pModelTexture[m][i] != NULL)
			{
				g_pModelTexture[m][i]->Release();
				g_pModelTexture[m][i] = NULL;
			}
		}
	}
	delete g_pMtxModel;
	delete g_pModelData;
	delete g_pMaterialSet;
}

void UpdateXModel(void)
{
	for (int m = 0; m < MODEL_MAX; m++)
	{

		D3DXMatrixTranslation(&g_pMtxModel[m].MtxModelT,
			g_pModelData[m].Pos.x,
			g_pModelData[m].Pos.y,
			g_pModelData[m].Pos.z);
		//拡大
		D3DXMatrixScaling(&g_pMtxModel[m].MtxModelS,
			g_pModelData[m].fScalex,
			g_pModelData[m].fScaley,
			g_pModelData[m].fScalez);
		//回転
		D3DXMatrixRotationAxis(&g_pMtxModel[m].MtxModelR,
			&g_pModelData[m].TurnVec,
			g_pModelData[m].fOldDeg*D3DX_PI / 180.f);
		//合成
		D3DXMatrixMultiply(&g_pMtxModel[m].MtxModel,
			&g_pMtxModel[m].MtxModelS,
			&g_pMtxModel[m].MtxModelT);

		D3DXMatrixMultiply(&g_pMtxModel[m].MtxModel,
			&g_pMtxModel[m].MtxModelR,
			&g_pMtxModel[m].MtxModel);
	}

}

void DrawXModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	for (int m = 0; m < MODEL_MAX;m++)
	{
		pDevice->SetTransform(D3DTS_WORLD, &g_pMtxModel[m].MtxModel);
		for (int i = 0; i < g_nMaterialNum[m]; i++)
		{
			g_pMaterialSet[m] = (LPD3DXMATERIAL)g_pMaterial[m]->GetBufferPointer();
			pDevice->SetTexture(0, g_pModelTexture[m][i]);
			g_pMaterialSet[m][i].MatD3D.Ambient.a = 1.0f;
			g_pMaterialSet[m][i].MatD3D.Ambient.g = 1.0f;
			g_pMaterialSet[m][i].MatD3D.Ambient.b = 1.0f;
			g_pMaterialSet[m][i].MatD3D.Ambient.r = 1.0f;
			//pMaterial[i].pTextureFilename= "Xmodel/00tex_master.png";	
			g_pMesh[m]->DrawSubset(i);
		}
	}

}
void InitModelData(void)
{
	g_pMtxModel = new MODELMTX[MODEL_MAX];
	g_pModelData = new MODELS_DATE[MODEL_MAX];

	for (int m = 0; m < MODEL_MAX; m++)
	{
		SetModelPos(m,0, -5.f, 0);
		SetModelScale(m,1, 1, 1);
		SetModelColor(m,255, 255, 255, 255);
		g_pModelData[m].fSpeed = 0.1f;
		g_pModelData[m].fTurnSpeed = 5.f;
		g_pModelData[m].fOldDeg = 0;
		g_pModelData[m].fNewDeg = 0;
		g_pModelData[m].TurnVec.x = 0;
		g_pModelData[m].TurnVec.y = 1.f;
		g_pModelData[m].TurnVec.z = 0;
		g_pModelData[m].Waybutton = 0;
	}
}
void SetModelPos(int typenum,float x, float y, float z)
{
	g_pModelData[typenum].Pos.x = x;
	g_pModelData[typenum].Pos.y = y;
	g_pModelData[typenum].Pos.z = z;
}
void SetModelScale(int typenum,float x, float y, float z)
{
	g_pModelData[typenum].fScalex = x;
	g_pModelData[typenum].fScaley = y;
	g_pModelData[typenum].fScalez = z;
}
void SetModelColor(int typenum,int r, int g, int b, int a)
{
	g_nModelColorR[typenum] = 255;
	g_nModelColorG[typenum] = 255;
	g_nModelColorB[typenum] = 255;
	g_nModelColorA[typenum] = 255;
}

const D3DXVECTOR3* GetModelPos(int typenum)
{
	return &g_pModelData[typenum].Pos;
}
const D3DXVECTOR3* GetCameraMove(void)
{
	return &g_vCameraMove;
}
float GetModelWay(int num)
{
	return g_pModelData[num].fOldDeg;
}