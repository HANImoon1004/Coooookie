#include "stdafx.h"
#include "Otte.h"

Otte::Otte()
{
	m_tInfo = MAPINFO(OTTE_CX, OTTE_CY);
	m_eINID = OTTE;
}

Otte::Otte(MAPINFO& mapInfo, INMAP eINID)
	: CMaps(mapInfo, eINID)
{
	m_bDead = false;
	m_iMoney = 0;
	m_iScore = 0;
	m_tFrame.iFrameStart = 0;//가로 시작
	m_tFrame.iFrameEnd = 1; //가로 끝
	m_tFrame.iFrameAnimation = 0;//세로 시작 위치
	m_tFrame.dwSpeed = 500; //낮을 수록 빠름
	//고양이가 드디어 움직여~~~ 고양이 속도 더 빠르게

	m_bRotation = false;
	m_tCenter.x = (long)m_tInfo.tPoint.fX;
	m_tCenter.y = (long)m_tInfo.tPoint.fY;
	m_fRotAngle = 0.f;
	m_fRotSpeed = 30.f;
	m_fRotDistance = 50.f;

}

Otte::~Otte()
{
	Release();
}


void Otte::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Otte");

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

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

	if (m_bRotation)
	{
		m_tCenter.x += long(m_fSpeed * cosf(m_fAngle * (PI / 180.f)));
		m_tCenter.y -= long(m_fSpeed * sinf(m_fAngle * (PI / 180.f)));

		m_fRotAngle += m_fRotSpeed;

		m_tInfo.tPoint.fX = m_tCenter.x + m_fRotDistance * cosf(m_fRotAngle * (PI / 180.f));
		m_tInfo.tPoint.fY = m_tCenter.y + m_fRotDistance * sinf(m_fRotAngle * (PI / 180.f));

	}
}

void Otte::Release()
{
}

void Otte::Update_Rect()
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	m_tRect.left = long(m_tInfo.tPoint.fX - (m_tInfo.tPoint.iCX * 0.3f) + iScrollX);
	m_tRect.top = long(m_tInfo.tPoint.fY - (m_tInfo.tPoint.iCY * 0.3f));
	m_tRect.right = long(m_tInfo.tPoint.fX + (m_tInfo.tPoint.iCX * 0.3f) + iScrollX);
	m_tRect.bottom = long(m_tInfo.tPoint.fY + (m_tInfo.tPoint.iCY * 0.3f));
}

void Otte::Animation_Change()
{



}

void Otte::Move_Frame()
{

	if (m_tFrame.dwSpeed + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

int Otte::Late_Update(HDC hDC)
{
	return OBJ_NOEVENT;

}

int Otte::Update()
{
	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

