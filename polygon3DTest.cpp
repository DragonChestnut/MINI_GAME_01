#include "polygon3DTest.h"
#include "input.h"
#include "camera.h"


static D3DXMATRIX g_mtxWorld;
static D3DXMATRIX g_mtxCube0;
static D3DXMATRIX g_mtxCube1;
static D3DXMATRIX g_mtxCube2;
static D3DXMATRIX g_mtxCube3;
static D3DXMATRIX g_mtxT0;
static D3DXMATRIX g_mtxT1;
static D3DXMATRIX g_mtxT2;
static D3DXMATRIX g_mtxT3;
static D3DXMATRIX g_mtxFun0;
static D3DXMATRIX g_mtxFun1;
static D3DXMATRIX g_mtxFun2;
static D3DXMATRIX g_mtxFun3;
static D3DXMATRIX g_mtxFun4;
static LPDIRECT3DTEXTURE9 g_pTexture[TEX_3DMAX] = { NULL };
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;



static D3DCOLOR color = 0xffffffff;
static int TexNum = 0;

static float tx = 0.0f;
static float ty = 0.0f;
static float tz = 0.0f;

static float sx = 1.0f;
static float sy = 1.0f;
static float sz = 1.0f;

static bool sconter = false;
static int stime = 0;


static float fRotx = 0.0f;
static float fRoty=0.0f;
static float fRotz = 0.0f;

static float ftext = 0.0f;

static float fup = 0.0f;

static int funconter = 0;
static bool funco = false;

bool InitPolygon3D()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	for (int count = 0; count < TEX_3DMAX; count++)
	{
		HRESULT hr;

		hr = D3DXCreateTextureFromFile
		(
			pDevice,
			TextureMessage3D[count].filename,
			&g_pTexture[count]
		);

		if (FAILED(hr))
		{
			MessageBox(NULL, "テクスチャが読み込めなかった", "エラー", MB_OK);
			return false;
		}

		hr = pDevice->CreateVertexBuffer
		(
			sizeof(VERTEX3D) * 24,
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
			sizeof(WORD) * 36,
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
void UninitPolygon3D(void)
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
	for (int count = 0; count < TEX_3DMAX; count++)
	{
		if (g_pTexture[count] != NULL)
		{
			g_pTexture[count]->Release();
			g_pTexture[count] = NULL;
		}
	}
}
void UpdatePolygon3D(void)
{
	//中心
	D3DXVECTOR3 mid(-4.5f, 0.0f, 4.5f);
	//ワールド変換行列

	//何もしない行列（単位行列）
	D3DXMatrixIdentity(&g_mtxWorld);

	//座標変換
	D3DXMatrixTranslation(&g_mtxT0, -4.5f, 0.0f, 4.5f);
	D3DXMatrixTranslation(&g_mtxT1, 4.5f, 0.0f, 4.5f);
	D3DXMatrixTranslation(&g_mtxT2, -4.5f, 0.0f, -4.5f);
	D3DXMatrixTranslation(&g_mtxT3, 4.5f, 0.0f, -4.5f);
	//自由
	D3DXMatrixRotationAxis(&g_mtxCube0, &mid, ftext);
	D3DXMatrixMultiply(&g_mtxCube0, &g_mtxCube0, &g_mtxT0);
	ftext += 0.2;
	//回転
	D3DXMatrixRotationY(&g_mtxCube2, fRoty);
	D3DXMatrixMultiply(&g_mtxCube2, &g_mtxCube2, &g_mtxT2);
	fRoty+=0.2f;
	//並行移動
	D3DXMatrixTranslation(&g_mtxCube3, tx, ty, tz);
	D3DXMatrixMultiply(&g_mtxCube3, &g_mtxCube3, &g_mtxT3);
	ty += 0.01;
	if (ty>2)
	{
		ty = 0;
	}
	//拡大
	D3DXMatrixScaling(&g_mtxCube1, sx, sy, sz);
	D3DXMatrixMultiply(&g_mtxCube1, &g_mtxCube1, &g_mtxT1);

	if (sx>5)
	{
		sx = 0;
	}
	if (sy>5)
	{
		sy = 0;
	}
	if (sz>5)
	{
		sz = 0;
	}
	if (!sconter)
	{
		sx += 0.1;
		sy += 0.1;
		sz += 0.1;
		stime++;
		if (stime>10)
		{
			sconter = true;
			stime = 0;
		}
	}
	else
	{
		sx -= 0.05;
		sy -= 0.05;
		sz -= 0.05;
		stime++;
		if (stime>15)
		{
			sconter = false;
			stime = 0;
		}
	}

	//合成mtxOut=mtxleft*mtxright
	//D3DXMatrixMultiply(&mtxOut, &mtxleft, &mtxright);
	
}

void SetPolygonColor3D(D3DCOLOR nColor)
{
	color = nColor;
}

void SetTexture3D(int nNumTex)
{
	TexNum = nNumTex;
}

void DrawPolygon3D()
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



	////fun
	//funconter++;
	//if (!funco)
	//{
	//	if (funconter>5)
	//	{
	//		funconter = 0;
	//		funco = true;
	//	}
	//	pDevice->LightEnable(0, TRUE);
	//	pDevice->LightEnable(1, TRUE);
	//	pDevice->LightEnable(2, FALSE);
	//}
	//else
	//{
	//	if (funconter>5)
	//	{
	//		funconter = 0;
	//		funco = false;
	//	}
	//	pDevice->LightEnable(0, TRUE);
	//	pDevice->LightEnable(1, FALSE);
	//	pDevice->LightEnable(2, TRUE);
	//}

	//線
	for (int i = 0; i <= 10; i++)
	{
		VERTEX3D v[] = { { D3DXVECTOR3(-5.0f,0.f,-5.0f + i), D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_RGBA(192,192,0,255) },
		{ D3DXVECTOR3(5.0f,0.f,-5.0f + i),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_RGBA(192,192,0,255) },
		};
		//行列の設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		pDevice->DrawPrimitiveUP
		(
			//D3DPT_TRIANGLESTRIP,
			D3DPT_LINELIST,
			1,
			&v[0],
			sizeof(VERTEX3D)
		);
	}

	for (int i = 0; i <= 10; i++)
	{
		VERTEX3D vline[] = { { D3DXVECTOR3(-5.0f + i,0.f,-5.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_RGBA(192,192,0,255) },
		{ D3DXVECTOR3(-5.0f + i,0.f,5.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_RGBA(192,192,0,255) },
		};
		//行列の設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorld);
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		pDevice->DrawPrimitiveUP
		(
			//D3DPT_TRIANGLESTRIP,
			D3DPT_LINELIST,
			1,
			&vline[0],
			sizeof(VERTEX3D)
		);
	}
	SetTexture3D(TEX_CUBE);

		int tw = TextureMessage3D[TexNum].width;
		int th = TextureMessage3D[TexNum].height;
		int tcx[6] = { 0,256,512,768,0,256 };
		int tcy[6] = { 0,0,0,0,256,256};
		int tcw = 256;
		int tch = 256;
		float u0[6];
		float v0[6];
		float u1[6];
		float v1[6];
		for (int i=0; i < 6; i++)
		{
			u0[i]= (float)tcx[i] / tw;
			v0[i]= (float)tcy[i] / th;
			u1[i] = (float)(tcx[i] + tcw) / tw;
			v1[i] = (float)(tcy[i] + tch) / th;
		}
		for (int i = 0; i < 4; i++)
		{
			//頂点
			VERTEX3D v[] = { {D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0[0],v0[0]) },//前
							{ D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1[0],v0[0]) },
							{ D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1[0],v1[0]) },
							{ D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0[0],v1[0]) },

							{ D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1[1],v0[1]) },//
							{ D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1[1],v1[1]) },
							{ D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0[1],v1[1]) },
							{ D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0[1],v0[1]) },

							{ D3DXVECTOR3(-0.5f ,0.5f,-0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0[2],v1[2]) },
							{ D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0[2],v0[2]) },
							{ D3DXVECTOR3(0.5f ,0.5f,0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1[2],v0[2]) },
							{ D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1[2],v1[2]) },

							{ D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0[3],v1[3]) },
							{ D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0[3],v0[3]) },
							{ D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1[3],v0[3]) },
							{ D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1[3],v1[3]) },

							{ D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0[4],v1[4]) },
							{ D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0[4],v0[4]) },
							{ D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1[4],v1[4]) },
							{ D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(2555,255,255,255),D3DXVECTOR2(u1[4],v0[4]) },

							{ D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1[5],v1[5]) },
							{ D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1[5],v0[5]) },
							{ D3DXVECTOR3(-0.5f,-0.5f,0.5f ),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0[5],v0[5]) },
							{ D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0[5],v1[5]) },

			};

			memcpy(&pV[0], &v[0], sizeof(VERTEX3D) * 24);

			g_pVertexBuffer->Unlock();

			WORD index[] = {
				0,1,2,
				0,2,3,
				4,5,6,
				6,7,4,
				8,9,10,
				8,10,11,
				12,13,14,
				14,15,12,
				16,17,18,
				18,17,19,
				20,21,22,
				20,22,23,
			};

			memcpy(&pIndex[0], &index[0], sizeof(WORD) * 36);

			g_pIndexBuffer->Unlock();

			pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(VERTEX3D));
			pDevice->SetIndices(g_pIndexBuffer);

			//FVFの設定
			pDevice->SetFVF(FVF_VERTEX3D);
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			//行列の設定
			switch (i)
			{
			case 0:pDevice->SetTransform(D3DTS_WORLD, &g_mtxCube0); break;
			case 1:pDevice->SetTransform(D3DTS_WORLD, &g_mtxCube1); break;
			case 2:pDevice->SetTransform(D3DTS_WORLD, &g_mtxCube2); break;
			case 3:pDevice->SetTransform(D3DTS_WORLD, &g_mtxCube3); break;
			default:break;
			}
			/*pDevice->SetTransform(D3DTS_WORLD, &g_mtxCube0);*/

			pDevice->SetTexture
			(
				0,
				g_pTexture[TexNum]
			);

			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
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
}



