#include "stdafx.h"
#include "Maps.h"
#include "CScrollMgr.h"
CMaps::CMaps()
{
}

CMaps::CMaps(MAPINFO & mapInfo, INMAP eINID)
	: m_tInfo(mapInfo), m_eINID(eINID)
{
}


CMaps::~CMaps()
{
}

void CMaps::Update_Rect()
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	m_tRect.left = long(m_tInfo.tPoint.fX - (m_tInfo.tPoint.iCX * 0.5f) + iScrollX);
	m_tRect.top = long(m_tInfo.tPoint.fY - (m_tInfo.tPoint.iCY * 0.5f));
	m_tRect.right = long(m_tInfo.tPoint.fX + (m_tInfo.tPoint.iCX*0.5f) + iScrollX);
	m_tRect.bottom = long(m_tInfo.tPoint.fY + (m_tInfo.tPoint.iCY * 0.5f));
}
