#include "stdafx.h"
#include "AlignToMovement.h"
AlignToMovement::AlignToMovement(Character* _pCharacter, AlignSteering* _pAlign) : m_pCharacter(_pCharacter), m_pAlign(_pAlign)
{
	
}
float AlignToMovement::GetSteering()
{
	USVec2D vVel = m_pCharacter->GetLinearVelocity();
	USVec2D vOri(1, 0);

	float fAngleRadians = acos(vVel.Dot(vOri) / (vVel.Length() * vOri.Length()));
	float fAngleDegrees = fAngleRadians * 57.2958f;

	return m_pAlign->GetSteering(fAngleDegrees);
}