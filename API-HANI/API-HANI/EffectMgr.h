#pragma once
#include "ObjMgr.h"
#include "Effect.h"

class CEffectMgr
{
public:
	CEffectMgr();
	~CEffectMgr();


	void Initialize();
	void Update();
	void Render(HDC hDC);
	void Release();
	list<CEffect*>	Get_Effect(EFFECT eID) { return m_Eflist[eID]; }
	

public:
	static	CEffectMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CEffectMgr;
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
	static	CEffectMgr* m_pInstance;

	INFO		m_tInfo;
	
	FRAME	m_tFrame;

	list<CEffect*>	m_Eflist[EF_END];

	CEffect*			m_pEffect;

	//HDC		hMemDC; 

	
};

