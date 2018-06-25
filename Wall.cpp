#include "Wall.h"
#include "input.h"
#include "camera.h"


static D3DXMATRIX g_mtxWall;
static LPDIRECT3DTEXTURE9 g_pTexture[WALL_MAX] = { NULL };
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;



static D3DCOLOR color = 0xffffffff;
static int TexNum = 0;


bool InitWall()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	for (int count = 0; count < WALL_MAX; count++)
	{
		HRESULT hr;

		hr = D3DXCreateTextureFromFile
		(
			pDevice,
			TextureWallMessage[count].filename,
			&g_pTexture[count]
		);

		if (FAILED(hr))
		{
			MessageBox(NULL, "テクスチャが読み込めなかった", "エラー", MB_OK);
			return false;
		}

		hr = pDevice->CreateVertexBuffer
		(
			sizeof(VERTEX3D) * 16,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX3D,
			D3DPOOL_MANAGED,
			&g_pVertexBuffer,
			NULL
		);
		if (FAILED(hr))
		{
			MessageBox(NULL, "頂点バッファが作れなかった", "エラー", MB_OK);
			return false;
		}

		hr = pDevice->CreateIndexBuffer
		(
			sizeof(WORD) * 24,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pIndexBuffer,
			NULL
		);
		if (FAILED(hr))
		{
			MessageBox(NULL, "インデックスバッファが作れなかった", "エラー", MB_OK);
			return false;
		}
	}
	return true;
}
void UninitWall(void)
{
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
	if (g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
	for (int count = 0; count < WALL_MAX; count++)
	{
		if (g_pTexture[count] != NULL)
		{
			g_pTexture[count]->Release();
			g_pTexture[count] = NULL;
		}
	}
}
void UpdateWall(void)
{
	//中心
	D3DXVECTOR3 mid(-4.5f, 0.0f, 4.5f);
	//ワールド変換行列

	////何もしない行列（単位行列）
	//D3DXMatrixIdentity(&g_mtxWorld);

	//座標変換
	D3DXMatrixTranslation(&g_mtxWall, 0.0f, 0.0f, 0.0f);
}


void SetTextureWall(int nNumTex)
{
	TexNum = nNumTex;
}

void DrawWall()
{
	VERTEX3D* pV;
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
	LPWORD pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);

	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	if (pDevice == NULL)
	{
		return;
	}

	SetTextureWall(WALL_1);

	float tw = TextureWallMessage[TexNum].width/2;
	float th = TextureWallMessage[TexNum].height;

		//頂点
		VERTEX3D v[] = { { D3DXVECTOR3(-tw,th,tw),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0,0) },//後
		{ D3DXVECTOR3(tw,th,tw),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1,0) },
		{ D3DXVECTOR3(tw,0.0f,tw),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1,1) },
		{ D3DXVECTOR3(-tw,0.0f,tw),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0,1) },

		{ D3DXVECTOR3(tw,th,-tw),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1,0) },//右
		{ D3DXVECTOR3(tw,0.0f,-tw),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1,1) },
		{ D3DXVECTOR3(tw,0.0f,tw),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0,1) },
		{ D3DXVECTOR3(tw,th,tw),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0,0) },

		{ D3DXVECTOR3(-tw,0.0f,-tw),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0,1) },//左
		{ D3DXVECTOR3(-tw,th,-tw),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0,0) },
		{ D3DXVECTOR3(-tw,th,tw),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1,0) },
		{ D3DXVECTOR3(-tw,0.0f,tw),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1,1) },

		{ D3DXVECTOR3(tw,0.0f,-tw),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0,1) },//前
		{ D3DXVECTOR3(tw,th,-tw),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0,0) },
		{ D3DXVECTOR3(-tw,0.0f,-tw),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1,1) },
		{ D3DXVECTOR3(-tw,th,-tw),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(2555,255,255,255),D3DXVECTOR2(1,0) },
		};

		memcpy(&pV[0], &v[0], sizeof(VERTEX3D) * 16);

		g_pVertexBuffer->Unlock();

		WORD index[] = {
			0,1,2,
			0,2,3,
			4,5,6,
			6,7,4,
			8,9,10,
			10,11,8,
			12,13,14,
			14,13,15,
		};

		memcpy(&pIndex[0], &index[0], sizeof(WORD) * 24);

		g_pIndexBuffer->Unlock();

		pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
		pDevice->SetIndices(g_pIndexBuffer);

		//FVFの設定
		pDevice->SetFVF(FVF_VERTEX3D);
		//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		//行列の設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWall);

		pDevice->SetTexture
		(
			0,
			g_pTexture[TexNum]
		);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 16, 0, 8);
		//pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 24, 12, &pIndex[0], D3DFMT_INDEX16, &pV[0], sizeof(VERTEX3D));
		//pDevice->DrawPrimitiveUP
		//(
		//	//D3DPT_TRIANGLESTRIP,
		//	D3DPT_TRIANGLELIST,
		//	12,
		//	&v[0],
		//	sizeof(VERTEX3D)
		//);
}



