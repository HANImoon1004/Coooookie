#pragma once
#include "Obj.h"
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
	const RECT&	Get_Rect() { return m_tRect; }

	void					Set_Pos(const float fX, const float fY) { m_tInfo.tPoint.Set_Position(fX, fY); }
	void					Set_PosX(const float fX) { m_tInfo.tPoint.Set_PosX(fX); }
	void					Set_PosY(const float fY) { m_tInfo.tPoint.Set_PosY(fY); }

public:
	virtual void		Render(HDC hDC) PURE;

protected:
	RECT				m_tRect;
	MAPINFO		m_tInfo;
	bool				m_bDead = false;
	INMAP			m_eINID;
};



