#pragma once
#ifndef _GAMEUI_H_
#define _GAMEUI_H_

#include <d3dx9.h>
#include "Game.h"




void InitGameUI(void);
void UninitGameUI(void);
void UpdateGameUI(void);
void DrawGameUI(void);

void ResetTimeUpSwitch(void);

bool GetTimeUpSwitch(void);


#endif