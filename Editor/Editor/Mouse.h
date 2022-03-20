#pragma once
#include "Include.h"

class CMouse
{
public:
	CMouse();
	virtual ~CMouse();

public:

	RECT Get_Rect() { return m_tRect; }
	void	Update();
	void	Render(HDC hDC);
	void	Release();


	static CMouse* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CMouse;
			return m_pInstance;
		}
		else
			return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
		else return;
	}
private:
	static CMouse* m_pInstance;
	INFO  m_tInfo;
	RECT	m_tRect; 
};

