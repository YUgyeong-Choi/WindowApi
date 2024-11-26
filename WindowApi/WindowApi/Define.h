#pragma once
#include <Windows.h>

#define WINCX		800
#define WINCY		600

#define	PURE		= 0
#define PI			3.141592f

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

enum Direction{ LEFT, UP, RIGHT, DOWN, NONE};