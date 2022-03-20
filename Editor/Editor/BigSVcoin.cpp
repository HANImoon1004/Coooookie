#include "stdafx.h"
#include "BigSVcoin.h"

BigSVcoin::BigSVcoin()
{
	m_tInfo = MAPINFO(SCOINB_CX, SCOINB_CY);
	m_eINID = COIN_SB;
}

BigSVcoin::BigSVcoin(MAPINFO& mapInfo, INMAP eINID)
	: CMaps(mapInfo, eINID)
{
}

BigSVcoin::~BigSVcoin()
{
}

void BigSVcoin::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BigSilverCoin");

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

int BigSVcoin::Update()
{
	if (m_bDead)
		return MAP_DEAD;

	Update_Rect();
	return MAP_NOEVENT;
}
