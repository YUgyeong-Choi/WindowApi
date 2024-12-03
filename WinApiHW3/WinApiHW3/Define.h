#pragma once
#define WINCX		800
#define WINCY		600

extern HWND		g_hWnd;

typedef struct tagInfo
{
	float		fX, fY;
	float		fCX, fCY; //±Ê¿Ã 

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

enum OBJID { OBJ_PLAYER, OBJ_GROUND, OBJ_END };
enum DIR{LEFT, RIGHT, DIR_END};