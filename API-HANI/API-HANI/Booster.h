#pragma once
#include "Maps.h"
class Booster :
	public CMaps
{
public:
	Booster();
	explicit Booster(MAPINFO& mapInfo, INMAP eINID);
	virtual ~Booster();

public:
	virtual void Move_Frame() override;
	virtual void Animation_Change() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

	// CMaps��(��) ���� ��ӵ�
	virtual int Late_Update(HDC hDC) override;
};

