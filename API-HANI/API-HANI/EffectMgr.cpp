#include "stdafx.h"
#include "EffectMgr.h"
#include "BmpMgr.h"
#include "CScrollMgr.h"

CEffectMgr* CEffectMgr::m_pInstance = nullptr;

CEffectMgr::CEffectMgr()
{
}

CEffectMgr::~CEffectMgr()
{
}



void CEffectMgr::Initialize()
{//이미지 삽입
	/*m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameAnimation = 0;*/
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tFrame, sizeof(m_tFrame));

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Coin_Effect.bmp", L"Coin_Effect");



}

void CEffectMgr::Update()
{
	//MoveFrame 완두랑 까치 엄지를 생각해서라도 그만두면 안돼 
	for (int i = 0; i < EF_END; ++i)
	{
		for (int j = 0; j < sizeof(m_Eflist[i]); ++j)
		{
			auto& iter = m_Eflist[i].begin();

			for (; iter != m_Eflist[i].end();)
			{
				(*iter)->Update();
			}
		}
	}


}

void CEffectMgr::Render(HDC hDC)
{//이미지 키에 맞는 이미지 찾기, 이미지 랜더링
	//리턴받은 걸 랜더에 넣어? 
	for (int i = 0; i < EF_END; ++i)
	{
		for (int j = 0; j < sizeof(m_Eflist[i]); ++j)
		{
			auto& iter = m_Eflist[i].begin();

			for (; iter != m_Eflist[i].end();)
			{
				(*iter)->Render(hDC);
			}
		}
	}
}

void CEffectMgr::Release()
{
	for (int i = 0; i < EF_END; ++i)
	{
		for_each(m_Eflist[i].begin(), m_Eflist[i].end(), Safe_Delete<CEffect*>);
	}
}

