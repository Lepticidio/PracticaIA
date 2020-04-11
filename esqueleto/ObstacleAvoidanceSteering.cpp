#include "stdafx.h"
#include "ObstacleAvoidanceSteering.h"



//----------------------------------------------------------------//
USVec2D Rotate90Anticlockwise(USVec2D _vVector)
{
	USVec2D vResult(_vVector.mY, -_vVector.mX);
	return vResult;
}

//----------------------------------------------------------------//
USVec2D Rotate90Clockwise(USVec2D _vVector)
{

	USVec2D vResult(-_vVector.mY, _vVector.mX);
	return vResult;
}

USVec2D ClosestSegmentPoint(USVec2D _vASegment, USVec2D _vBSegment, USVec2D _vPoint)
{
	USVec2D vV = _vBSegment - _vASegment;
	USVec2D vU = _vASegment - _vPoint;

	float fT = -vV.Dot(vU) / vV.Dot(vV);

	if (fT < 0)
	{
		fT = 0;
	}
	else if (fT > 1)
	{
		fT = 1;
	}

	return USVec2D((1 - fT) * _vASegment.mX, (1 - fT) * _vASegment.mY) + USVec2D(fT * _vBSegment.mX, fT * _vBSegment.mY);
}


ObstacleAvoidanceSteering::ObstacleAvoidanceSteering(SeekSteering* _pSeek, Obstacles* _pObstacles, Character* _pCharacter) : m_pSeek(_pSeek), m_pObstacles(_pObstacles), m_pCharacter(_pCharacter)
{
}
USVec2D ObstacleAvoidanceSteering::GetSteering(USVec2D _vTarget)
{
	USVec2D vDestination = _vTarget;
	USVec2D vCurrentVelocity = m_pCharacter->GetLinearVelocity();
	USVec2D vCurrentPos = m_pCharacter->GetLoc();
	USVec2D vNormalizedVelocity = vCurrentVelocity / vCurrentVelocity.Length();
	USVec2D vLookAhead = vNormalizedVelocity * m_fLookAhead;
	USVec2D vPointAhead = vLookAhead + vCurrentPos;
	for (int i = 0; i < m_pObstacles->m_tObstacles.size(); i++)
	{
		Obstacle* pObstacle = &(m_pObstacles->m_tObstacles[i]);
		USVec2D vNearPoint = ClosestSegmentPoint(vCurrentPos, vPointAhead, pObstacle->m_vPosition);
		USVec2D vDiff = vNearPoint - pObstacle->m_vPosition;
		USVec2D vPlayerToObstacle = pObstacle->m_vPosition - vCurrentPos;
		if (vPlayerToObstacle.Length() < pObstacle->m_fRadius + m_fCharacterRadius)
		{
			pObstacle->m_bColliding = true;
		}
		else
		{
			pObstacle->m_bColliding = false;
		}
		float fDist = vDiff.Length();
		
		if (fDist < pObstacle->m_fRadius + m_fCharacterRadius)
		{
			USVec2D vDirection(0, 0);
			float fCross = vPlayerToObstacle.Cross(vLookAhead);
			if (fCross > 0)
			{
				vDirection = Rotate90Clockwise(vPlayerToObstacle);
			}
			else
			{
				vDirection = Rotate90Anticlockwise(vPlayerToObstacle);
			}
			vDestination = vCurrentPos + vDirection;
		}

	}
	return m_pSeek->GetSteering(vDestination);
}

void ObstacleAvoidanceSteering::DrawDebug()
{

}
void ObstacleAvoidanceSteering::Initialize()
{
	m_fLookAhead = m_pCharacter->GetParams().look_ahead;
	m_fCharacterRadius = m_pCharacter->GetParams().character_radius;
}
