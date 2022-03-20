#include "stdafx.h"
#include "Otte.h"


COtte::COtte()
{
	m_tInfo = MAPINFO(OTTE_CX, OTTE_CY);
	m_eINID = OTTE;
}

COtte::COtte(MAPINFO & mapInfo, INMAP eINID)
	: CMaps(mapInfo, eINID)
{
}


COtte::~COtte()
{
}

void COtte::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Otte");

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

int COtte::Update()
{
	if (m_bDead)
		return MAP_DEAD;

	Update_Rect();
	return MAP_NOEVENT;
}
