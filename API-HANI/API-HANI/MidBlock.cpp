#include "stdafx.h"
#include "MidBlock.h"

MidBlock::MidBlock()
{
	m_tInfo = MAPINFO(MIDBLOCK_CX, MIDBLOCK_CY);
	m_eINID = MIDBLOCK;
}

MidBlock::MidBlock(MAPINFO& mapInfo, INMAP eINID)
	: CMaps(mapInfo, eINID)
{
}


MidBlock::~MidBlock()
{
	Release();
}

void MidBlock::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MidBlock");
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	GdiTransparentBlt(hDC, m_tInfo.tPoint.fX - m_tInfo.tPoint.iCX / 2.f + iScrollX,
		//Que hani 
		m_tInfo.tPoint.fY - m_tInfo.tPoint.iCY / 2.f,
		m_tInfo.tPoint.iCX,
		m_tInfo.tPoint.iCY,
		hMemDC,
		0, 0,
		m_tInfo.tPoint.iCX,
		m_tInfo.tPoint.iCY,
		ASHBLUE);

}

void MidBlock::Release()
{
}

void MidBlock::Animation_Change()
{
}

void MidBlock::Move_Frame()
{
}

int MidBlock::Late_Update(HDC hDC)
{
	return OBJ_NOEVENT;

}

int MidBlock::Update()
{
	Move_Frame();
	Animation_Change();
	Update_Rect();
	return OBJ_NOEVENT;
}
