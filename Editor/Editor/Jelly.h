#pragma once
#include "Maps.h"
class CJelly :
	public CMaps
{
public:
	CJelly();
	virtual ~CJelly();

	// CMaps��(��) ���� ��ӵ�
	virtual void Render(HDC hDC) override;
};

