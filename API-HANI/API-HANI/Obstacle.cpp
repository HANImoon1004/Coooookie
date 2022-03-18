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
	m_bDead = false;

	m_tFrame.iFrameStart = 0;//���� ����
	m_tFrame.iFrameEnd = 5; //���� ��
	m_tFrame.iFrameAnimation = 0;//���� ���� ��ġ
	m_tFrame.dwSpeed = 100; //���� ���� ����
	//����̰� ���� ������~~~ ����� �ӵ� �� ������
}

Obstacle::~Obstacle()
{
	Release();
}


void Obstacle::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Cat");

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	GdiTransparentBlt(hDC, m_tInfo.tPoint.fX - m_tInfo.tPoint.iCX / 2.f + iScrollX, //Q
		m_tInfo.tPoint.fY - m_tInfo.tPoint.iCY / 2.f,
		m_tInfo.tPoint.iCX,
		m_tInfo.tPoint.iCY,
		hMemDC,
		m_tFrame.iFrameStart*m_tInfo.tPoint.iCX,
		m_tFrame.iFrameAnimation*m_tInfo.tPoint.iCY,
		m_tInfo.tPoint.iCX,
		m_tInfo.tPoint.iCY,
		ASHBLUE);
}

void Obstacle::Release()
{
}

void Obstacle::Animation_Change()
{
	
	
	
}

void Obstacle::Move_Frame()
{

	if (m_tFrame.dwSpeed + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_tFrame.iFrameStart++;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

int Obstacle::Update()
{
	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

