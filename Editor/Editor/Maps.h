#pragma once
#include "CScrollMgr.h"
#include "BmpMgr.h"

class CMaps
{
public:
	CMaps();
	explicit CMaps(MAPINFO & mapInfo, INMAP eINID);
	virtual ~CMaps();

public:
	MAPINFO*		Get_MapInfo() { return &m_tInfo; }
	INMAP*				Get_INID() { return &m_eINID; }
	void					Set_Pos(const float fX, const float fY) { m_tInfo.tPoint.Set_Position(fX, fY); }

public:
	virtual void		Render(HDC hDC) PURE; 

protected:
	MAPINFO		m_tInfo;
	bool				m_bDead = false;
	INMAP			m_eINID;
};

