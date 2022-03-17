#pragma once
#include "Maps.h"
class CJelly :
	public CMaps
{
public:
	CJelly();
	virtual ~CJelly();

	// CMaps을(를) 통해 상속됨
	virtual void Render(HDC hDC) override;
};

