#pragma once
#include "Maps.h"
class CJelly :
	public CMaps
{
public:
	CJelly();
	virtual ~CJelly();
	explicit CJelly(MAPINFO& mapInfo, INMAP eINID);


	// CMaps��(��) ���� ��ӵ�
	virtual void Render(HDC hDC) override;

	// CMaps��(��) ���� ��ӵ�
	virtual int Update() override;
};

