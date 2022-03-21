#include "stdafx.h"
#include "MidairBlock.h"


MidairBlock::MidairBlock()
{
	m_tInfo = MAPINFO(MIDBLOCK_CX, MIDBLOCK_CY);
	m_eINID = MIDBLOCK;
	m_bDead = false;
}

MidairBlock::MidairBlock(MAPINFO& mapInfo, INMAP eINID)
	: CMaps(mapInfo, eINID)
{
}


MidairBlock::~MidairBlock()
{
}

void MidairBlock::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MidBlock");


	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	GdiTransparentBlt(hDC, m_tInfo.tPoint.fX - m_tInfo.tPoint.iCX / 2.f + iScrollX,
		m_tInfo.tPoint.fY - m_tInfo.tPoint.iCY / 2.f,
		m_tInfo.tPoint.iCX,
		m_tInfo.tPoint.iCY,
		hMemDC,
		0, 0,
		m_tInfo.tPoint.iCX,
		m_tInfo.tPoint.iCY,
		ASHBLUE);
}

int MidairBlock::Update()
{
	if (m_bDead)
		return MAP_DEAD;

	Update_Rect();
	return MAP_NOEVENT;
}
