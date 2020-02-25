#include "stdafx.h"
#include "SeekSteering.h"

USVec2D SeekSteering::GetSteering( USVec2D _vTarget)
{
	USVec2D vResult = USVec2D(0, 0);
	USVec2D vCurrentPos = m_pChararacter->GetLoc();
	if (Sqrt((vCurrentPos.mX - _vTarget.mX) * (vCurrentPos.mX - _vTarget.mX) + (vCurrentPos.mY - _vTarget.mY) * (vCurrentPos.mY - _vTarget.mY)) > 1.f)
	{
		m_vDesiredSpeed = _vTarget - vCurrentPos;
		vResult = m_vDesiredSpeed - m_pChararacter->GetLinearVelocity();
		if (vResult.Length() > m_fMaxAcceleration)
		{
			vResult.SetLength(m_fMaxAcceleration);
		}
	}
	m_vCurrentAcceleration = vResult;
	return vResult;
}

void SeekSteering::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);
	MOAIDraw::DrawLine(m_pChararacter->GetLoc(), m_pChararacter->GetLoc() + m_vDesiredSpeed);

	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 0.5f);
	MOAIDraw::DrawLine(m_pChararacter->GetLoc(), m_pChararacter->GetLoc() + m_vCurrentAcceleration);
}
SeekSteering::SeekSteering(Character* _pCharacter) : m_pChararacter(_pCharacter)
{
}