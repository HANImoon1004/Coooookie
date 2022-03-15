#pragma once

#include "Include.h"

class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();


public:
	bool			Key_Pressing(int _Key); // ������ ���� �� ��� true
	bool			Key_Down(DWORD dwKey); // ó�� �� ���� true
	bool			Key_Up(int _Key);	// �����ٰ� ���� �� true
	bool			Key_DdoDown(int _Key);

	void			Update(void);

public:
	static	CKeyMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CKeyMgr;
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
	static	CKeyMgr* m_pInstance;
	bool						m_bKeyState[VK_MAX];

	DWORD						m_dwKey = 0;
	DWORD						m_dwKeyDOWN = 0;
};

