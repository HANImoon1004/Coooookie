#include "stdafx.h"
#include "BGCoin.h"


BGCoin::BGCoin()
{
	m_tInfo = MAPINFO(GCOINB_CX, GCOINB_CY);
	m_eINID = COIN_GB;
	m_iMoney = 150;
	m_iScore = 100;
}

BGCoin::BGCoin(MAPINFO& mapInfo, INMAP eINID)
	: CMaps(mapInfo, eINID)
{
	m_bDead = false;
	/*m_tRect.left = m_tInfo.tPoint.fX - m_tInfo.tPoint.iCX * 0.5;
	m_tRect.right = m_tInfo.tPoint.fX + m_tInfo.tPoint.iCX * 0.5;
	m_tRect.top = m_tInfo.tPoint.fY - m_tInfo.tPoint.iCY * 0.5;
	m_tRect.bottom = m_tInfo.tPoint.fY + m_tInfo.tPoint.iCY * 0.5;
*/
	m_iMoney = 50;
	m_iScore = 30;
	m_tFrame.iFrameStart = 0;//가로 시작
	m_tFrame.iFrameEnd = 3; //가로 끝
	m_tFrame.iFrameAnimation = 0;//세로 시작 위치
	m_tFrame.dwSpeed = 100; //낮을 수록 빠름
}


BGCoin::~BGCoin()
{
}

void BGCoin::Move_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

void BGCoin::Animation_Change()
{
}

int BGCoin::Update()
{

	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void BGCoin::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BigGoldCoin");

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

int BGCoin::Late_Update(HDC hDC)
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
