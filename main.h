#pragma once
//===================================
//
//ÉÅÉCÉìÉwÉbÉ_
//
//                    2017.06.05 Zhao
//===================================

#ifndef _MAIN_H_
#define _MAIN_H_

#include<d3d9.h>
#include <Windows.h>
#include <d3dx9.h>
#include <stdio.h>

#define WINDOW_WIDTH    (1280)
#define WINDOW_HEIGHT   (720)


LPDIRECT3DDEVICE9 GetD3DDevice(void);

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


#endif // _MAIN_H_