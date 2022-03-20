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
	RECT					 Get_Rect() { return m_tRect; }

	void					Set_Pos(const float fX, const float fY) { m_tInfo.tPoint.Set_Position(fX, fY); }
	void					Set_Dead() { m_bDead = true; }
	

public:
	void					Update_Rect();
	virtual int			Update() PURE;
	virtual void		Render(HDC hDC) PURE; 

protected:

	MAPINFO		m_tInfo;
	bool				m_bDead = false;
	INMAP			m_eINID;
	RECT				m_tRect;
};

