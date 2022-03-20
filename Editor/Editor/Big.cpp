#include "stdafx.h"
#include "Big.h"

Big::Big()
{
	m_tInfo = MAPINFO(BIG_CX, BIG_CY);
	m_eINID = BIG;
}

Big::~Big()
{

}

Big::Big(MAPINFO& mapInfo, INMAP eINID)
	: CMaps(mapInfo, eINID)
{
}

void Big::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Big");

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

int Big::Update()
{
	if (m_bDead)
		return MAP_DEAD;

	Update_Rect();
	return MAP_NOEVENT;
}
