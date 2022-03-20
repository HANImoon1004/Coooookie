#include "stdafx.h"
#include "Jelly.h"


Jelly::Jelly()
{
	m_tInfo = MAPINFO(JELLY_CX, JELLY_CY);
	m_eINID = JELLY;
	m_iMoney = 0;
	m_iScore = 50;
}

Jelly::Jelly(MAPINFO& mapInfo, INMAP eINID)
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
	m_tFrame.iFrameEnd = 2; //가로 끝
	m_tFrame.iFrameAnimation = 0;//세로 시작 위치
	m_tFrame.dwSpeed = 100; //낮을 수록 빠름
}


Jelly::~Jelly()
{
}

void Jelly::Move_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

void Jelly::Animation_Change()
{
}

int Jelly::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

void Jelly::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Jelly");

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
