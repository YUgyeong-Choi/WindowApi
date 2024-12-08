#include "pch.h"
#include "CBlock.h"

CBlock::CBlock()
{
	ZeroMemory(&m_BlockType, sizeof(BLOCKTYPE));
}

void CBlock::Initialize()
{
}

int CBlock::Update()
{
	return 0;
}

void CBlock::LateUpdate()
{
}

void CBlock::Render(HDC hDC)
{
}

void CBlock::Release()
{
}
