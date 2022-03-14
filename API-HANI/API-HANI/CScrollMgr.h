#pragma once

#include "Include.h"

#define	SCROLL_LOCKX	CScrollMgr::Get_Instance()->Get_ScLockX()
#define  SCROLL_LOCKY	CScrollMgr::Get_Instance()->Get_ScLockY()

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float			Get_ScrollX() { return m_fScrollX; }
	float			Get_ScrollY() { return m_fScrollY; }

	float			Get_ScLockX() { return m_fScrollLockX; }
	float			Get_ScLockY() { return m_fScrollLockY; }

public:
	void			Set_ScrollX(float _fX) { m_fScrollX += _fX; }
	void			Set_ScrollY(float _fY) { m_fScrollY += _fY; }

	void			Set_ScLock_Pos(float _fX, float _fY) { m_fScrollLockX = _fX; m_fScrollLockY = _fY; }

	void			Scroll_Lock(void);

	POINT			Cursor_Scroll_Pos(void);
public:
	static	CScrollMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CScrollMgr;
		}

		return m_pInstance;
	}
	static	void		Destroy_Instance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static	CScrollMgr* m_pInstance;
	float						m_fScrollX = 0.f;
	float						m_fScrollY = 0.f;
	float						m_fScrollLockX;
	float						m_fScrollLockY;

	int							m_iX;
	int							m_iY;
};


