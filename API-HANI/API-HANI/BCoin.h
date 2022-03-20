#pragma once
#include "Maps.h"
class BCoin :
	public CMaps
{
public:
	BCoin();
	explicit BCoin(MAPINFO& mapInfo, INMAP eINID);
	virtual ~BCoin();

public:
	virtual void Move_Frame() override;
	virtual void Animation_Change() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
};

