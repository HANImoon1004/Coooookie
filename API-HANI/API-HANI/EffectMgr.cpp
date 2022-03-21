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
{//�̹��� ����
	/*m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameAnimation = 0;*/
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tFrame, sizeof(m_tFrame));

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Coin_Effect.bmp", L"Coin_Effect");



}

void CEffectMgr::Update()
{
	//MoveFrame �ϵζ� ��ġ ������ �����ؼ��� �׸��θ� �ȵ� 
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
{//�̹��� Ű�� �´� �̹��� ã��, �̹��� ������
	//���Ϲ��� �� ������ �־�? 
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

