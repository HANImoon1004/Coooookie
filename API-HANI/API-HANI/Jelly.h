#pragma once
#include "Maps.h"
class Jelly :
	public CMaps
{
public:
	Jelly();
	explicit Jelly(MAPINFO& mapInfo, INMAP eINID);
	virtual ~Jelly();

public:
	virtual void Move_Frame() override;
	virtual void Animation_Change() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

	// CMaps을(를) 통해 상속됨
	virtual int Late_Update(HDC hDC) override;
};

