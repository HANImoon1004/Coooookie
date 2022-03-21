#pragma once
#include "Maps.h"
class MidairBlock :
    public CMaps
{
public:
	MidairBlock();
	explicit MidairBlock(MAPINFO& mapInfo, INMAP eINID);
	virtual ~MidairBlock();

public:
	virtual void Render(HDC hDC) override;

	// CMaps을(를) 통해 상속됨
	virtual int Update() override;
};

