#include "stdafx.h"
#include "AlignToMovement.h"
AlignToMovement::AlignToMovement(Character* _pCharacter, AlignSteering* _pAlign) : m_pCharacter(_pCharacter), m_pAlign(_pAlign)
{
	
}
float AlignToMovement::GetSteering()
{
	USVec2D vVel = m_pCharacter->GetLinearVelocity();
	USVec2D vOri(1, 0);
	float fOriDegrees = m_pCharacter->GetRot();

	float fRotation = fOriDegrees/ 57.2958f;
	float fCos = cos(fRotation);
	float fSin = sin(fRotation);
	//vOri = USVec2D(fCos * vOri.mX - fSin * vOri.mY, fSin*vOri.mX + fCos*vOri.mY);
	//float fAngle = UKismetMathLibrary::Atan2(vActorDirection.Y, vActorDirection.X) - UKismetMathLibrary::Atan2(vForward.Y, vForward.X);
	//float fAngleRadians = acos(vVel.Dot(vOri) / (vVel.Length() * vOri.Length()));
	float fAngleRadians = atan2(vVel.mY, vVel.mX) - atan2(vOri.mY, vOri.mX);
	float fAngleDegrees = fAngleRadians * 57.2958f;
	//while (fAngleDegrees >= 360 || fAngleDegrees < 0)
	//{
	//	if (fAngleDegrees >= 360)
	//	{
	//		fAngleDegrees -= 360;
	//	}
	//	else if (fAngleDegrees < 0)
	//	{
	//		fAngleDegrees += 360;
	//	}

	//}

	//float fAlternateAngle = fAngleDegrees - 360;
	//
	//if (abs(fOriDegrees - fAlternateAngle) < abs(fOriDegrees - fAngleDegrees))
	//{
	//	fAngleDegrees = fAlternateAngle;
	//}
	return m_pAlign->GetSteering(fAngleDegrees);
}