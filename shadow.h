#ifndef _SHADOW_H_
#define _SHADOW_H_
#include<d3dx9.h>

#define SHADOW_X_NUM (1)
#define SHADOW_Y_NUM (1)
#define SHADOW_V_MAXPOINT (SHADOW_X_NUM*SHADOW_Y_NUM+SHADOW_X_NUM+SHADOW_Y_NUM+1)//(2w+2)�Eh-(w+1)(h-1)->wh+w+h+1
#define SHADOW_IDENTITY_WIDTH (10.f)
#define SHADOW_IDENTITY_HEIGHT (10.f)
#define SHADOW_WIDTH (SHADOW_IDENTITY_WIDTH*SHADOW_X_NUM)
#define SHADOW_HEIGHT (SHADOW_IDENTITY_HEIGHT*SHADOW_Y_NUM)
#define SHADOW_INDEX_MAXPOINT (2*SHADOW_X_NUM*SHADOW_Y_NUM+4*SHADOW_Y_NUM-2)//2wh+4h-2

typedef struct
{
	char fileName[256];
	int width;
	int height;
}SHADOW_TEXTURE;


typedef struct
{
	D3DXMATRIX MtxShadow;
	D3DXMATRIX MtxShadowT;
	D3DXMATRIX MtxShadowS;
	D3DXMATRIX MtxShadowR;
	D3DXVECTOR3 pos;
}SHADOWS;

//3D�p���_�f�[�^
typedef struct
{
	D3DXVECTOR3 pos; //�|���S�����W
	D3DXVECTOR3	normal;//�@��
	D3DCOLOR color; //�F
	D3DXVECTOR2 texcoord; //�e�N�X�`�����W
}SHADOW_VERTEX;



typedef enum
{
	SHADOW_TEXTURE_1,
	SHADOW_TEXTURE_MAX
}SHADOW_TEXTURE_ENUM;

typedef enum
{
	SHADOW_1,
	SHADOW_2,
	SHADOW_GOAL_1,
	SHADOW_GOAL_2,
	SHADOW_GOAL_3,
	SHADOW_GOAL_4,
	SHADOW_GOAL_5,
	SHADOW_GOAL_6,
	SHADOW_GOAL_7,
	SHADOW_GOAL_8,
	SHADOW_GOAL_9,
	SHADOW_GOAL_10,
	SHADOW_MAX
}SHADOW_ID;


#define SHADOW_TEXTURE_FILENAME1 "Texture/hanyi_2.png"


bool InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
bool ReadShadow(void);

void SetShadowColor(int r, int g, int b, int a);
void SetShadowTex(SHADOW_TEXTURE_ENUM TexNum);
void SetShadowType(SHADOW_ID typenum);


void InitShadowData(void);
#endif // _SHADOW_H_