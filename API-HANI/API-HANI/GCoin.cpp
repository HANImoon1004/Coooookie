#include "stdafx.h"
#include "GCoin.h"


CGCoin::CGCoin()
{
	m_tInfo = MAPINFO(GCOINS_CX, GCOINS_CY);
	m_eINID = COIN_GS;
	m_iMoney = 70;
	m_iScore = 50;
}

CGCoin::CGCoin(MAPINFO& mapInfo, INMAP eINID)
	: CMaps(mapInfo, eINID)
{
	m_bDead = false;
	m_iMoney = 70;
	m_iScore = 50;
	m_tFrame.iFrameStart = 0;//가로 시작
	m_tFrame.iFrameEnd = 5; //가로 끝
	m_tFrame.iFrameAnimation = 0;//세로 시작 위치
	m_tFrame.dwSpeed = 100; //낮을 수록 빠름
}


CGCoin::~CGCoin()
{
}

void CGCoin::Move_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

void CGCoin::Animation_Change()
{
}

int CGCoin::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CGCoin::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"GoldCoin");

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	GdiTransparentBlt(hDC, m_tInfo.tPoint.fX - m_tInfo.tPoint.iCX / 2.f + iScrollX, //Q
		m_tInfo.tPoint.fY - m_tInfo.tPoint.iCY / 2.f,
		m_tInfo.tPoint.iCX,
		m_tInfo.tPoint.iCY,
		hMemDC,
		m_tFrame.iFrameStart * m_tInfo.tPoint.iCX,
		m_tFrame.iFrameAnimation * m_tInfo.tPoint.iCY,
		m_tInfo.tPoint.iCX,
		m_tInfo.tPoint.iCY,
		ASHBLUE);


}

int CGCoin::Late_Update(HDC hDC)
{
	if (true == m_bDead)
	{
		HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Coin_Effect");
		//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

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

		return OBJ_DEAD;
	}
	return OBJ_NOEVENT;

}
