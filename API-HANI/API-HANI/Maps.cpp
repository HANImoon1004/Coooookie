#include "stdafx.h"
#include "Maps.h"
#include "CScrollMgr.h"
CMaps::CMaps()
{
}

CMaps::CMaps(MAPINFO & mapInfo, INMAP eINID)
	: m_tInfo(mapInfo), m_eINID(eINID)
{
	m_bDead = false;
	m_tInfos.fX = m_tInfo.tPoint.fX;
	m_tInfos.fY = m_tInfo.tPoint.fY;
	m_tInfos.fCX = m_tInfo.tPoint.iCX;
	m_tInfos.fCY = m_tInfo.tPoint.iCY;
}

//CMaps::CMaps(MAPINFO& mapInfo, INMAP eINID, CObj* pPet)
//	:  m_tInfo(mapInfo), m_eINID(eINID), m_pPet(pPet)
//{
//	m_bDead = false;
//	m_tInfos.fX = m_tInfo.tPoint.fX;
//	m_tInfos.fY = m_tInfo.tPoint.fY;
//	m_tInfos.fCX = m_tInfo.tPoint.iCX;
//	m_tInfos.fCY = m_tInfo.tPoint.iCY;
//}


CMaps::~CMaps()
{
}

void CMaps::Magnet()
{
	if (m_dwTime + 10 < GetTickCount())
	{
		m_fSpeed -= m_fScroll;
	}
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	if (m_bMagnet)
	{
		m_pPet = CObjMgr::Get_Instance()->Get_Obj(OBJ_PET);



		int iX = m_tInfo.tPoint.fX + iScrollX - m_pPet.front()->Get_Info().fX;
		int iY = m_tInfo.tPoint.fY  - m_pPet.front()->Get_Info().fY;
		int iDistance = sqrt(iX * iX + iY * iY);

		if (iDistance < 600 && iX >= 0)
		{
			if (0 != iDistance)
			{
				m_tInfo.tPoint.fX -= 5 * iX / iDistance;
				m_tInfo.tPoint.fY -= 15 * iY / iDistance;
			}
		}
	}

}





void CMaps::Update_Rect()
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();

	m_tRect.left = long(m_tInfo.tPoint.fX - (m_tInfo.tPoint.iCX * 0.5f) + iScrollX);
	m_tRect.top = long(m_tInfo.tPoint.fY - (m_tInfo.tPoint.iCY * 0.5f));
	m_tRect.right = long(m_tInfo.tPoint.fX + (m_tInfo.tPoint.iCX*0.5f) + iScrollX);
	m_tRect.bottom = long(m_tInfo.tPoint.fY + (m_tInfo.tPoint.iCY * 0.5f));
}
