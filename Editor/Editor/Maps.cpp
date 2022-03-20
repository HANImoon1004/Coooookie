#include "stdafx.h"
#include "Maps.h"


CMaps::CMaps()
{
}

CMaps::CMaps(MAPINFO& mapInfo, INMAP eINID)
	: m_tInfo(mapInfo), m_eINID(eINID), m_bDead(false)
{
}


CMaps::~CMaps()
{

}

void CMaps::Update_Rect()
{
	m_tRect.left = long(m_tInfo.tPoint.fX - (m_tInfo.tPoint.iCX * 0.5f));
	m_tRect.top = long(m_tInfo.tPoint.fY - (m_tInfo.tPoint.iCY * 0.5f));
	m_tRect.right = long(m_tInfo.tPoint.fX + (m_tInfo.tPoint.iCX * 0.5f));
	m_tRect.bottom = long(m_tInfo.tPoint.fY + (m_tInfo.tPoint.iCY * 0.5f));
}
