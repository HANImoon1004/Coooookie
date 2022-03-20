#include "stdafx.h"
#include "Booster.h"


Booster::Booster()
{
	m_tInfo = MAPINFO(BOOSTER_CX, BOOSTER_CY);
	m_eINID = BOOSTER;
	m_iMoney = 0;
	m_iScore = 50;
}

Booster::Booster(MAPINFO& mapInfo, INMAP eINID)
	: CMaps(mapInfo, eINID)
{
	m_bDead = false;
	/*m_tRect.left = m_tInfo.tPoint.fX - m_tInfo.tPoint.iCX * 0.5;
	m_tRect.right = m_tInfo.tPoint.fX + m_tInfo.tPoint.iCX * 0.5;
	m_tRect.top = m_tInfo.tPoint.fY - m_tInfo.tPoint.iCY * 0.5;
	m_tRect.bottom = m_tInfo.tPoint.fY + m_tInfo.tPoint.iCY * 0.5;
*/
	m_iMoney = 0;
	m_iScore = 0;
	m_tFrame.iFrameStart = 0;//가로 시작
	m_tFrame.iFrameEnd = 3; //가로 끝
	m_tFrame.iFrameAnimation = 0;//세로 시작 위치
	m_tFrame.dwSpeed = 100; //낮을 수록 빠름
}


Booster::~Booster()
{
}

void Booster::Move_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

void Booster::Animation_Change()
{
}

int Booster::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void Booster::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Booster");

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
