#pragma once
#include "Maps.h"
class CCoin :
	public CMaps
{
public:
	CCoin();
	explicit CCoin(MAPINFO& mapInfo, INMAP eINID);
	virtual ~CCoin();

public:
	virtual void Move_Frame() override;
	virtual void Animation_Change() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
};

