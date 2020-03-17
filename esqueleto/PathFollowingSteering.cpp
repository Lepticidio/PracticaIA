#include "stdafx.h"
#include "PathFollowingSteering.h"
PathFollowingSteering::PathFollowingSteering(SeekSteering* _pSeek, Path* _pPath, Character* _pCharacter) : m_pSeek(_pSeek), m_pPath(_pPath), m_pCharacter(_pCharacter)
{
}
USVec2D PathFollowingSteering::GetSteering()
{
	int iClosestIndex = 0;
	float fClosestDistance = FLT_MAX;
	for (int i = 0; i < m_pPath->m_tPoints.size(); i++)
	{
		USVec2D vPoint = m_pPath->m_tPoints[i];
		USVec2D vDirectionToPoint = m_pCharacter->GetLoc() - vPoint;
		float fDistance = vDirectionToPoint.Length();
		if ( fDistance < fClosestDistance)
		{
			fClosestDistance = fDistance;
			iClosestIndex = i;
		}
	}
	USVec2D vFirstPoint = m_pPath->m_tPoints[iClosestIndex];

	if (iClosestIndex == 0)
	{

	}


	USVec2D vDestination = m_pPath->m_tPoints[m_iCurrentPoint];
	
	if ((vDestination - m_pCharacter->GetLoc()).Length() < m_fDestinationRadius*10)
	{
		m_iCurrentPoint++;
		if (m_iCurrentPoint >= m_pPath->m_tPoints.size())
		{
			m_iCurrentPoint = 0;
		}
	}
	return m_pSeek->GetSteering(vDestination);
}
void PathFollowingSteering::Initialize()
{
	m_fLookAhead = m_pCharacter->GetParams().look_ahead;
	m_fTimeAhead = m_pCharacter->GetParams().time_ahead;
	m_fDestinationRadius = m_pCharacter->GetParams().dest_radius;
}