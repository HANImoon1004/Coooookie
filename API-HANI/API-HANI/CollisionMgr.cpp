#pragma once

#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "Player.h"
#include "Maps.h"
#include "Block.h"
#include "Player.h"

CollisionMgr::CollisionMgr()
{
}

CollisionMgr::~CollisionMgr()
{
}



void CollisionMgr::Collision_RectEX(list<CMaps*> Dest, list<CObj*> Sour)
{
	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(DestIter, SourIter, &fX, &fY))
			{
				/*DestIter->Set_Dead();
				SourIter->Set_Dead();*/

				// 상, 하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (DestIter->Get_MapInfo()->tPoint.fY < SourIter->Get_Info().fY)
					{
						DestIter->Set_PosY(-fY);
					}
					// 하 충돌
					else
					{
						DestIter->Set_PosY(fY);
					}
				}

				// 좌, 우 충돌
				else
				{
					// 좌 충돌
					if (DestIter->Get_MapInfo()->tPoint.fX < SourIter->Get_Info().fX)
					{
						DestIter->Set_PosX(-fX);
					}
					// 우 충돌
					else
					{
						DestIter->Set_PosX(fX);
					}
				}
			}
		}
	}

}

bool CollisionMgr::Collision_Rect(list<CMaps*> Dest, list<CObj*> Sour) //Que
{
	bool isColl = false;

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(DestIter, SourIter, &fX, &fY))
			{
				isColl = true;
				float SfX = SourIter->Get_Info().fX; //Obj의 위치 
				float SfY = SourIter->Get_Info().fY;

				// 상, 하 충돌
				//if (fX > fY)
				//{
					// 상 충돌
				if (SourIter->Get_Info().fY < DestIter->Get_MapInfo()->tPoint.fY)
				{
					fY *= -1.f;
					//DestIter->Set_PosY(-fY);
				}
				SourIter->Set_Pos(SfX, SfY + fY);

				//체력 다 하면 죽음
				// 
				//// 하 충돌
				//else
				//{
				//	DestIter->Set_PosY(fY);
				//}
			}

			//// 좌, 우 충돌
			//else
			//{
			//	// 좌 충돌
			//	if (DestIter->Get_MapInfo()->tPoint.fX < SourIter->Get_Info().fX)
			//	{
			//		DestIter->Set_PosX(-fX);
			//	}
			//	// 우 충돌
			//	else
			//	{
			//		DestIter->Set_PosX(fX);
			//	}


		}
	}
	return isColl;
}

bool CollisionMgr::Collision_Block(list<CMaps*> Dest, list<CObj*> Sour)
{
	RECT rc{};
	bool   isColl = false;

	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_Rect())))
			{
				isColl = true;
				DestIter->Set_PosY(-(rc.bottom - rc.top));
			}
		}
	}
	return isColl;
}

bool CollisionMgr::Collision_Map(list<CMaps*> Dest, list<CObj*> Sour)
{

	RECT rc{};
	
	for (auto& DestIter : Dest)
	{
		for (auto& SourIter : Sour)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SourIter->Get_Rect())))
			{
 				return true;
				//DestIter->Set_PosY(-(rc.bottom - rc.top));
			}

			else
				return false;
		}
	}


}

//&붙이는 거랑 안 붙이는 거.. 
void CollisionMgr::Collision_Item(list<CMaps*>& Dest, list<CObj*>& Sour)
{
	RECT rc = {};
	for (auto& Destiter : Dest)
	{
		for (auto& Souriter : Sour)
		{
			if (IntersectRect(&rc, &Destiter->Get_Rect(), &Souriter->Get_Rect()))
			{
				int iMoney = Destiter->Get_Money();
				int iScore = Destiter->Get_Score(); //코인꺼를 가져오고 싶다고! 
				//map 생성자에 0으로 넣어놔서 안됐었어
				INMAP eINID = *Destiter->Get_INID();

				switch (eINID)
				{
				case BLOCK:
					break;
				case OBSTACLE:
					if (false == dynamic_cast<Player*>(Souriter)->Get_isSuper())
					{
						dynamic_cast<Player*>(Souriter)->Set_Hp(-5);
						dynamic_cast<Player*>(Souriter)->Set_Status(PLAYER_HIT);
					}
					break;
				case OTTE:
					dynamic_cast<Player*>(Souriter)->Set_Hp(-5);
					dynamic_cast<Player*>(Souriter)->Set_Status(PLAYER_HIT);
					break;
				case COIN_SS:
					dynamic_cast<Player*>(Souriter)->Set_Money(iMoney);
					Destiter->Set_Dead(); // 죽여
					break;
				case COIN_SB:
					dynamic_cast<Player*>(Souriter)->Set_Money(iMoney);
					dynamic_cast<Player*>(Souriter)->Set_Score(iScore);
					Destiter->Set_Dead();
					break;
				case COIN_GS:
					dynamic_cast<Player*>(Souriter)->Set_Money(iMoney);
					dynamic_cast<Player*>(Souriter)->Set_Score(iScore);
					Destiter->Set_Dead();
					break;
				case COIN_GB:
					dynamic_cast<Player*>(Souriter)->Set_Money(iMoney);
					dynamic_cast<Player*>(Souriter)->Set_Score(iScore);
					Destiter->Set_Dead();
					break;
				case JELLY:
					dynamic_cast<Player*>(Souriter)->Set_Score(iScore);
					Destiter->Set_Dead();
					break;
				case BOOSTER:
					dynamic_cast<Player*>(Souriter)->Set_Booster();
					Destiter->Set_Dead();
					break;
				case BIG:
					dynamic_cast<Player*>(Souriter)->Set_Big();
					dynamic_cast<Player*>(Souriter)->Set_Status(PLAYER_BIG);
					Destiter->Set_Dead();
					break;
				case MAGNET:

					Destiter->Set_Dead();
					break;
				default:
					break;
			}
		}
	}
}
}

bool CollisionMgr::Check_Sphere(const CObj* pDstObject, const CObj* rSrcObject)
{
	float fRadiusSum = static_cast<float>((int(pDstObject->Get_Info().fCX) >> 1) + (int(rSrcObject->Get_Info().fCY) >> 1));
	float fX = pDstObject->Get_Info().fX - rSrcObject->Get_Info().fX;
	float fY = pDstObject->Get_Info().fX - rSrcObject->Get_Info().fY;
	float fDist = sqrtf(fX * fX + fY * fY);

	return fDist < fRadiusSum;
}

bool CollisionMgr::Check_Rect(CMaps* pDest, CObj* pSour, float* pfX, float* pfY)
{
	float		fWidth = fabs(pDest->Get_MapInfo()->tPoint.fX - pSour->Get_Info().fX);
	float		fHeight = fabs(pDest->Get_MapInfo()->tPoint.fY - pSour->Get_Info().fY);

	float		fRadiusX = (pDest->Get_MapInfo()->tPoint.iCX + pSour->Get_Info().fCX) * 0.5f;
	float		fRadiusY = (pDest->Get_MapInfo()->tPoint.iCY + pSour->Get_Info().fCY) * 0.5f;

	if (fRadiusX > fWidth && fRadiusY > fHeight)
	{
		*pfX = fRadiusX - fWidth;
		*pfY = fRadiusY - fHeight;

		return true;
	}//거리가 더 짧으면 충돌

	return false;
}


