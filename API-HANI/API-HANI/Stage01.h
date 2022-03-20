#pragma once
#include "Scene.h"

class CStage01 :
	public CScene
{
public:
	CStage01();
	virtual ~CStage01();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Set_Scroll(float fScroll) { m_fScroll = fScroll; }

private:
	DWORD		m_dwTime;
	int				m_iScroll;
	float			m_fScroll = DEFAULT_SPEED;
};

