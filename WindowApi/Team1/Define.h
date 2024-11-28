#pragma once
#define WINCX		800
#define WINCY		600

#define GAME_WINCX      600
#define GAME_WINCY      550

#define GAME_WIN_LEFT      (WINCX - GAME_WINCX) * 0.5f
#define GAME_WIN_TOP      (WINCY - GAME_WINCY) * 0.5f
#define GAME_WIN_RIGHT      (WINCX - GAME_WINCX) * 0.5f + GAME_WINCX
#define GAME_WIN_BOTTOM      (WINCY - GAME_WINCY) * 0.5f + GAME_WINCY

#define	PURE		= 0
#define PI			3.141592f

#define OBJ_NOEVENT			0
#define OBJ_DEAD			1
#define OBJ_CLEAR			2

extern HWND		g_hWnd;

enum SCENE { START, STAGE_ONE, END, NONE };
enum DIR { LEFT, UP, RIGHT, DOWN, NODIR };
enum OBJID { OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_END };

typedef struct tagInfo
{
	float		fX, fY;
	float		fCX, fCY;	// 가로, 세로 길이

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