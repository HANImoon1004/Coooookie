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
	RECT*				 Get_MapRect()
	{
		RECT tRect;
		tRect.left = m_tRect.left + m_fSpeed;
		tRect.right = m_tRect.right + m_fSpeed;
		tRect.top = m_tRect.top;
		tRect.bottom = m_tRect.bottom;
		return &tRect;
	}//0320

	int						Get_Score() { return m_iScore; }
	int						Get_Money() { return m_iMoney; }


	void					Set_Pos(const float fX, const float fY) { m_tInfo.tPoint.Set_Position(fX, fY); }
	void					Set_PosX(const float fX) { m_tInfo.tPoint.Set_PosX(fX); }
	void					Set_PosY(const float fY) { m_tInfo.tPoint.Set_PosY(fY); }
	void					Set_Dead() { m_bDead = true; }
	void					Set_Speed(float fScroll) { m_fScroll= fScroll; }

	virtual int 		Update_();
	virtual int		Late_Update(HDC hDC) PURE;
	virtual void		Update_Rect();
	virtual void			Move_Frame() PURE;
	virtual void			Animation_Change() PURE;

public:
	virtual int			Update() PURE;
	virtual void		Render(HDC hDC) PURE;

protected:
	
	bool						m_bDead = false;
	FRAME					m_tFrame;
	RECT						m_tRect;
	MAPINFO				m_tInfo;
	INFO						m_tInfos;
	INMAP					m_eINID;
	DWORD					m_dwTime = GetTickCount();

	int							m_iScore;
	int							m_iMoney;
	float						m_fSpeed;
	float						m_fScroll = 8.f;
	float						m_fAngle;
};



