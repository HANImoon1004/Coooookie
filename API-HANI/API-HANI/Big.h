#pragma once
#include "Maps.h"
class Big :
	public CMaps
{
public:
	Big();
	explicit Big(MAPINFO& mapInfo, INMAP eINID);
	virtual ~Big();

public:
	virtual void Move_Frame() override;
	virtual void Animation_Change() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

	// CMaps��(��) ���� ��ӵ�
	virtual int Late_Update(HDC hDC) override;
};

