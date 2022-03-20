#pragma once
#include "Maps.h"

class CBlock :
	public CMaps
{
public:
	CBlock();
	explicit CBlock(MAPINFO& mapInfo, INMAP eINID);
	virtual ~CBlock();

public:
	virtual void Render(HDC hDC) override;

	// CMaps을(를) 통해 상속됨
	virtual int Update() override;
};

