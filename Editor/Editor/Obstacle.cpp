#include "stdafx.h"
#include "Obstacle.h"


CObstacle::CObstacle()
{
	m_tInfo = MAPINFO(CAT_CX, CAT_CY);
	m_eINID = OBSTACLE;
}

CObstacle::CObstacle(MAPINFO & mapInfo, INMAP eINID)
	: CMaps(mapInfo, eINID)
{
}


CObstacle::~CObstacle()
{
}

void CObstacle::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Cat");

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
