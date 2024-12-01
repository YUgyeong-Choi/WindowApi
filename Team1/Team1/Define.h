#pragma once
#define WINCX		800
#define WINCY		600

#define GAME_WINCX      600
#define GAME_WINCY      600

#define GAME_WIN_LEFT      0.f
#define GAME_WIN_TOP       0.f
#define GAME_WIN_RIGHT      GAME_WINCX 
#define GAME_WIN_BOTTOM     GAME_WINCY

#define	PURE		= 0
#define PI			3.141592f

#define OBJ_NOEVENT			0
#define OBJ_DEAD			1
#define OBJ_CLEAR			2
#define OBJ_FINISH			3

extern HWND		g_hWnd;

enum SCENE { START, STAGE_ONE, STAGE_TWO, END, NONE };
enum DIR { LEFT, TOP, RIGHT, BOTTOM, NODIR };
enum OBJID { OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_MONSTERBULLET, OBJ_ITEM, OBJ_SHIELD, OBJ_END };
enum BULLETTYPE {BULLET_ONE, BULLET_TWO, BULLET_SCREWTWO, BULLET_THREE, BULLET_SCREWTHREE};

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