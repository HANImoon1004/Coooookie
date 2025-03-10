#pragma once
#include "Obj.h"
class CEffect :
	public CObj
{
public:
	CEffect();
	virtual ~CEffect();
	CEffect(float fX, float fY, float fCX, float fCY, EFFECT eID, TCHAR* pFrameKey);

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override {};
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Setting_Dead(bool bDead) { m_bDead = bDead; }

private:
	float m_fX;
	float m_fY;
	float m_fCX;
	float m_fCY;
	EFFECT m_eID;
	TCHAR* m_pFrameKey;
	bool	m_bDead;
};

