#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "Player.h"
#include "Maps.h"
#include "Block.h"

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

bool CollisionMgr::Check_Sphere(const CObj * pDstObject, const CObj * rSrcObject)
{
	float fRadiusSum = static_cast<float>((int(pDstObject->Get_Info().fCX) >> 1) + (int(rSrcObject->Get_Info().fCY) >> 1));
	float fX = pDstObject->Get_Info().fX - rSrcObject->Get_Info().fX;
	float fY = pDstObject->Get_Info().fX - rSrcObject->Get_Info().fY;
	float fDist = sqrtf(fX * fX + fY * fY);

	return fDist <fRadiusSum;
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


