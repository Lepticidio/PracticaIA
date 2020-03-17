#include "stdafx.h"
#include "PursueSteering.h"
PursueSteering::PursueSteering(ArriveSteering* _pArrive, Character* _pCharacter) : m_pArrive(_pArrive), m_pCharacter(_pCharacter)
{
}
USVec2D PursueSteering::GetSteering()
{

	USVec2D vDestination = m_pTarget->GetLoc();
	
	vDestination += m_pTarget->GetLinearVelocity();

	return m_pArrive->GetSteering(vDestination);
}
void PursueSteering::Initialize()
{
	m_fLookAhead = m_pCharacter->GetParams().look_ahead;
	m_fTimeAhead = m_pCharacter->GetParams().time_ahead;
	m_fDestinationRadius = m_pCharacter->GetParams().dest_radius;
}
void PursueSteering::SetTarget(Character* _pTarget)
{
	m_pTarget = _pTarget;
}