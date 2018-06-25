//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM00 = 0,// BGM0
	SOUND_LABEL_BGM01,// BGM1
	SOUND_LABEL_WUWU,			// �I��
	SOUND_LABEL_NIU,			// ��s
	SOUND_LABEL_POINT,		// ���_
	SOUND_LABEL_WIN,			// ����
	SOUND_LABEL_LOSE,	// ����
	SOUND_LABEL_TIMEUP,
	SOUND_LABEL_LEVEL,
	SOUND_LABEL_END,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
