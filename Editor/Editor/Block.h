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
};

