#include "shadow.h"
#include "Camera.h"
#include "main.h"
#include "input.h"
#include "polygon3dtest.h"
#include"xmodel.h"
#include "Billboard.h"
#include "character.h"
#include "goal.h"
//***************************************************************************************
//	グローバル変数宣言
//***************************************************************************************
static SHADOWS g_pShadows[SHADOW_MAX];
static LPDIRECT3DVERTEXBUFFER9 g_pShadowVertexBuffer3D = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pShadowIndexBuffer = NULL;
static const SHADOW_TEXTURE g_pShadowTexture[SHADOW_TEXTURE_MAX] = { { SHADOW_TEXTURE_FILENAME1 , 32, 32 } };
static LPDIRECT3DTEXTURE9  g_pShadowTextures[SHADOW_TEXTURE_MAX] = { NULL };
static WORD g_ShadowIndex[SHADOW_INDEX_MAXPOINT];
static SHADOW_VERTEX g_Shadowv[SHADOW_V_MAXPOINT];
static int g_nIndexPoint = 0;
static int g_nColorR[SHADOW_MAX];
static int g_nColorG[SHADOW_MAX];
static int g_nColorB[SHADOW_MAX];
static int g_nColorA[SHADOW_MAX];
static SHADOW_TEXTURE_ENUM g_eTexNum;
static SHADOW_ID g_eTypeNum;
//逆行列　D3DXMatrixInverse(出力アドレス,NULL,入力先アドレス);
//転置行列 D3DXMatrixTranspose(出力アドレス,入力先アドレス);



bool InitShadow(void)
{
	HRESULT hr;
	hr = ReadShadow();
	InitShadowData();
	return hr;
}
void UninitShadow(void)
{
	if (g_pShadowVertexBuffer3D)
	{
		g_pShadowVertexBuffer3D->Release();
		g_pShadowVertexBuffer3D = NULL;
	}
	if (g_pShadowIndexBuffer)
	{
		g_pShadowIndexBuffer->Release();
		g_pShadowIndexBuffer = NULL;
	}
	for (int i = 0; i < SHADOW_TEXTURE_MAX; i++)
	{
		if (g_pShadowTextures[i])
		{
			g_pShadowTextures[i]->Release();
			g_pShadowTextures[i] = NULL;
		}
	}
}
void UpdateShadow(void)
{
	if (GetISBall())
	{
		D3DXVECTOR3 Ballpos = GetBillboardPos(BILL_BALL);
		g_pShadows[0].pos.x = Ballpos.x;
		g_pShadows[0].pos.y = 0;
		g_pShadows[0].pos.z = Ballpos.z;
	}
	else
	{
		g_pShadows[0].pos.x = 500;
		g_pShadows[0].pos.y = 0;
		g_pShadows[0].pos.z = 500;
	}
	D3DXMatrixTranslation(&g_pShadows[0].MtxShadowT,
		g_pShadows[0].pos.x,
		g_pShadows[0].pos.y,
		g_pShadows[0].pos.z);
	D3DXMatrixScaling(&g_pShadows[0].MtxShadowS, 0.05f, 0.05f, 0.05f);
	D3DXMatrixMultiply(&g_pShadows[0].MtxShadow, &g_pShadows[0].MtxShadowS, &g_pShadows[0].MtxShadowT);
	if (GetISCharacter())
	{
		D3DXVECTOR3 characterpos = GetBillboardPos(BILL_CHARACTER);
		g_pShadows[1].pos.x = characterpos.x;
		g_pShadows[1].pos.y = 0;
		g_pShadows[1].pos.z = characterpos.z;
	}
	else
	{
		g_pShadows[1].pos.x = 500;
		g_pShadows[1].pos.y = 50;
		g_pShadows[1].pos.z = 500;
	}
	D3DXMatrixTranslation(&g_pShadows[1].MtxShadowT,
		g_pShadows[1].pos.x,
		g_pShadows[1].pos.y,
		g_pShadows[1].pos.z);
	D3DXMatrixScaling(&g_pShadows[1].MtxShadowS, 0.2f, 0.05f, 0.05f);
	D3DXMatrixMultiply(&g_pShadows[1].MtxShadow, &g_pShadows[1].MtxShadowS, &g_pShadows[1].MtxShadowT);
	//new
	int goalnum=GetGoalNum();
	for (int i = 0; i < goalnum; i++)
	{
		if (GetIsGoal(i))
		{
			D3DXVECTOR3 GoalPos = GetGoalPos(i);
			g_pShadows[i+2].pos.x = GoalPos.x;
			g_pShadows[i+2].pos.y = 0;
			g_pShadows[i+2].pos.z = GoalPos.z;
		}
		else
		{
			g_pShadows[i + 2].pos.x = 500;
			g_pShadows[i + 2].pos.y = 0;
			g_pShadows[i + 2].pos.z = 500;
		}
		D3DXMatrixTranslation(&g_pShadows[i + 2].MtxShadowT,
			g_pShadows[i + 2].pos.x,
			g_pShadows[i + 2].pos.y,
			g_pShadows[i + 2].pos.z);
		
			switch (GetGoalType(i))
			{
			case 0:D3DXMatrixScaling(&g_pShadows[i + 2].MtxShadowS, 0.2f, 0.2f, 0.2f); break;
			case 1:D3DXMatrixScaling(&g_pShadows[i + 2].MtxShadowS, 0.4f, 0.4f, 0.4f); break;
			case 2:D3DXMatrixScaling(&g_pShadows[i + 2].MtxShadowS, 0.6f, 0.6f, 0.6f); break;
			default:
				break;
			}
		D3DXMatrixMultiply(&g_pShadows[i + 2].MtxShadow, &g_pShadows[i + 2].MtxShadowS, &g_pShadows[i + 2].MtxShadowT);
	}

}

void DrawShadow(void)
{
	for (int i = 0; i < SHADOW_MAX; i++)
	{
		LPDIRECT3DDEVICE9 pDevice3d = GetD3DDevice();
		//
		pDevice3d->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		LPWORD pIndex;
		SHADOW_VERTEX* pV;


		//各種類行列の設定
		pDevice3d->SetTransform(D3DTS_WORLD, &g_pShadows[i].MtxShadow);


		g_pShadowVertexBuffer3D->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);



		memcpy(&pV[0], &g_Shadowv[0], sizeof(SHADOW_VERTEX) * SHADOW_V_MAXPOINT);

		g_pShadowVertexBuffer3D->Unlock();


		g_pShadowIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);


		memcpy(&pIndex[0], &g_ShadowIndex[0], sizeof(WORD) * SHADOW_INDEX_MAXPOINT);
		g_pShadowIndexBuffer->Unlock();

		for (int y = 0; y < (SHADOW_Y_NUM + 1); y++)
		{
			for (int x = 0; x < (SHADOW_X_NUM + 1); x++)
			{
				g_Shadowv[y * (SHADOW_X_NUM + 1) + x] = {
					D3DXVECTOR3(-SHADOW_WIDTH + SHADOW_WIDTH / 2 + SHADOW_IDENTITY_WIDTH*x,//x
					0,//y
					SHADOW_HEIGHT - SHADOW_HEIGHT / 2 - SHADOW_IDENTITY_HEIGHT*y),//z
					D3DXVECTOR3(0,1.f,0),
					D3DCOLOR_RGBA(255,255,255,255),
					D3DXVECTOR2(x,y)
				};
			}
		}

		g_nIndexPoint = 0;
		for (int y = 0; y < SHADOW_Y_NUM; y++)
		{
			for (int x = 0; x <= SHADOW_X_NUM; x++)
			{
				g_ShadowIndex[g_nIndexPoint] = (SHADOW_X_NUM + 1)*(y + 1) + x;
				g_ShadowIndex[g_nIndexPoint + 1] = (SHADOW_X_NUM + 1)*y + x;
				g_nIndexPoint += 2;

			}
			if (y != SHADOW_Y_NUM - 1)
			{
				g_ShadowIndex[g_nIndexPoint] = g_ShadowIndex[g_nIndexPoint - 1];
				g_ShadowIndex[g_nIndexPoint + 1] = (SHADOW_X_NUM + 1)*(y + 2);
				g_nIndexPoint += 2;
			}
		}
		pDevice3d->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice3d->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice3d->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


		pDevice3d->SetStreamSource(0, g_pShadowVertexBuffer3D, 0, sizeof(SHADOW_VERTEX));
		pDevice3d->SetIndices(g_pShadowIndexBuffer);

		//テクスチャ設定
		pDevice3d->SetTexture(0, g_pShadowTextures[g_eTexNum]);

		//FVFの設定
		pDevice3d->SetFVF(FVF_VERTEX3D);
		pDevice3d->SetRenderState(D3DRS_LIGHTING, TRUE);


		//DrawPrimitiveUP 遅い、簡単
		pDevice3d->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, SHADOW_V_MAXPOINT, 0, SHADOW_INDEX_MAXPOINT - 2);
		//
		pDevice3d->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}
}


bool ReadShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice3d = GetD3DDevice();
	for (int i = 0; i < SHADOW_TEXTURE_MAX; i++)
	{
		HRESULT hr3D;

		hr3D = D3DXCreateTextureFromFile(pDevice3d,
			g_pShadowTexture[i].fileName,//ファイル名
			&g_pShadowTextures[i]);

		if (FAILED(hr3D))
		{
			MessageBox(NULL, "テクスチャが読み込めなかった", "エラー", MB_OK);
			return false;
		}

		hr3D = pDevice3d->CreateVertexBuffer(sizeof(SHADOW_VERTEX) * SHADOW_V_MAXPOINT, D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &g_pShadowVertexBuffer3D, NULL);
		if (FAILED(hr3D))
		{
			MessageBox(NULL, "頂点バッファが作れなかった", "エラー", MB_OK);
			return false;
		}
		hr3D = pDevice3d->CreateIndexBuffer(sizeof(WORD) * SHADOW_INDEX_MAXPOINT, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pShadowIndexBuffer, NULL);
		if (FAILED(hr3D))
		{
			MessageBox(NULL, "インデックス頂点バッファが作れなかった", "エラー", MB_OK);
			return false;
		}
	}

	

	return true;

}

void SetShadowColor(int r, int g, int b, int a)
{
	g_nColorR[g_eTypeNum] = r;
	g_nColorG[g_eTypeNum] = g;
	g_nColorB[g_eTypeNum] = b;
	g_nColorA[g_eTypeNum] = a;
}
void SetShadowTex(SHADOW_TEXTURE_ENUM TexNum)
{
	g_eTexNum = TexNum;
}
void SetShadowType(SHADOW_ID typenum)
{
	g_eTypeNum = typenum;
}
void InitShadowData(void)
{
	g_nColorR[g_eTypeNum] = 255;
	g_nColorG[g_eTypeNum] = 255;
	g_nColorB[g_eTypeNum] = 255;
	g_nColorA[g_eTypeNum] = 255;
}
