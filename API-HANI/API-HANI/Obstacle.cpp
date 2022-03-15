#include "stdafx.h"
#include "Obstacle.h"

Obstacle::Obstacle()
{
	m_tInfo = MAPINFO(CAT_CX, CAT_CY);
	m_eINID = OBSTACLE;
}

Obstacle::Obstacle(MAPINFO& mapInfo, INMAP eINID)
	: CMaps(mapInfo, eINID)
{
}

Obstacle::~Obstacle()
{
	Release();
}


void Obstacle::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Cat");

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	GdiTransparentBlt(hDC, m_tInfo.tPoint.fX - m_tInfo.tPoint.iCX / 2.f + iScrollX, //Q
		m_tInfo.tPoint.fY - m_tInfo.tPoint.iCY / 2.f,
		m_tInfo.tPoint.iCX,
		m_tInfo.tPoint.iCY,
		hMemDC,
		0, 0,
		m_tInfo.tPoint.iCX,
		m_tInfo.tPoint.iCY,
		ASHBLUE);
}

void Obstacle::Release()
{
}

