#include "stdafx.h"
#include "BigGDcoin.h"

BigGDcoin::BigGDcoin()
{
	m_tInfo = MAPINFO(GCOINB_CX, GCOINB_CY);
	m_eINID = COIN_GB;
}

BigGDcoin::BigGDcoin(MAPINFO& mapInfo, INMAP eINID)
	: CMaps(mapInfo, eINID)
{
}

BigGDcoin::~BigGDcoin()
{
}

void BigGDcoin::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BigGoldCoin");

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

int BigGDcoin::Update()
{
	if (m_bDead)
		return MAP_DEAD;

	Update_Rect();
	return MAP_NOEVENT;
}
