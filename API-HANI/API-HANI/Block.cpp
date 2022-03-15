#pragma once
#include "stdafx.h"
#include "Block.h"


CBlock::CBlock()
{
	m_tInfo = MAPINFO(BLOCK_CX, BLOCK_CY);
	m_eINID = BLOCK;
}

CBlock::CBlock(MAPINFO & mapInfo, INMAP eINID)
	: CMaps(mapInfo, eINID)
{
}


CBlock::~CBlock()
{
	Release();
}

void CBlock::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Block");

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	GdiTransparentBlt(hDC, m_tInfo.tPoint.fX - m_tInfo.tPoint.iCX / 2.f + iScrollX, //Q
		m_tInfo.tPoint.fY - m_tInfo.tPoint.iCY / 2.f,
		m_tInfo.tPoint.iCX,
		m_tInfo.tPoint.iCY,
		hMemDC,
		0, 0,
		m_tInfo.tPoint.iCX,
		m_tInfo.tPoint.iCY,
		RGB(255, 0, 255));

}

void CBlock::Release()
{
}
