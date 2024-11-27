#pragma once
#include <Windows.h>

#define WINCX		800
#define WINCY		600

#define	PURE		= 0
#define PI			3.141592f

#define OBJ_NOEVENT			0
#define OBJ_DEAD			1	

extern HWND		g_hWnd;

typedef struct tagInfo
{
	float		fX, fY;
	float		fCX, fCY;

}INFO;


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

enum DIR{ LEFT, UP, RIGHT, DOWN, NONE};
enum OBJID{OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_END};