#pragma once

#include "stdafx.h"
#include "CollisionMgr.h"

#include "Maps.h"
#include "Block.h"
#include "KeyMgr.h"

CollisionMgr::CollisionMgr()
{
}

CollisionMgr::~CollisionMgr()
{
}

void CollisionMgr::Collision_Mouse(list<CMaps*>& Dest, RECT rect)
{
	RECT rc{};

	for (auto& DestIter : Dest) //����Ʈ�� �ִ� �� �������ϴϱ� 
	{
		if (IntersectRect(&rc, &(DestIter->Get_Rect()), &rect)) //�浹 ������
		{
			//DestIter�� ��ü�� ������� �ؾ��� 
			DestIter->Set_Dead();
		}
	}


}


