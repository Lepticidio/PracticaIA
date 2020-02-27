#include "stdafx.h"
#include "ArriveSteering.h"

USVec2D ArriveSteering::GetSteering(USVec2D _vTarget)
{
	USVec2D vResult = USVec2D(0, 0);
	USVec2D vCurrentPos = m_pChararacter->GetLoc();

	m_vDesiredSpeed = _vTarget - vCurrentPos;
	float fDistance = (vCurrentPos - _vTarget).Length();
	float fDistanceFactor = 1;

	if (fDistance < m_pChararacter->GetParams().arrive_radius)
	{
		fDistanceFactor = fDistance / m_pChararacter->GetParams().arrive_radius;
	}
	m_vDesiredSpeed.SetLength(m_fMaxSpeed * fDistanceFactor);

	vResult = m_vDesiredSpeed - m_pChararacter->GetLinearVelocity();
	if (vResult.Length() > m_fMaxAcceleration)
	{
		vResult.SetLength(m_fMaxAcceleration);
	}	
	m_vCurrentAcceleration = vResult;
	return vResult;
}

void ArriveSteering::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);
	MOAIDraw::DrawLine(m_pChararacter->GetLoc(), m_pChararacter->GetLoc() + m_vDesiredSpeed);

	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 0.5f);
	MOAIDraw::DrawLine(m_pChararacter->GetLoc(), m_pChararacter->GetLoc() + m_vCurrentAcceleration);

}

ArriveSteering::ArriveSteering(Character* _pCharacter) : m_pChararacter(_pCharacter)
{
}
void ArriveSteering::Initialize()
{
	m_fMaxSpeed = m_pChararacter->GetParams().max_velocity;
	m_fMaxAcceleration = m_pChararacter->GetParams().max_acceleration;
	printf("");
}