//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM00 = 0,// BGM0
	SOUND_LABEL_BGM01,// BGM1
	SOUND_LABEL_WUWU,			// 選択
	SOUND_LABEL_NIU,			// 飛行
	SOUND_LABEL_POINT,		// 得点
	SOUND_LABEL_WIN,			// 勝つ
	SOUND_LABEL_LOSE,	// 負け
	SOUND_LABEL_TIMEUP,
	SOUND_LABEL_LEVEL,
	SOUND_LABEL_END,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
