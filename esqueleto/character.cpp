#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>

#include <params.h>
#include "SeekSteering.h"

USVec2D RotateVector(USVec2D _vInitialVector, float _fAngle)
{
	return USVec2D(cos(_fAngle) * _vInitialVector.mX - sin(_fAngle) * _vInitialVector.mY, sin(_fAngle) * _vInitialVector.mX + cos(_fAngle) * _vInitialVector.mY);
}


Character::Character() : mLinearVelocity(200.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
		RTTI_EXTEND(MOAIEntity2D)
		RTTI_END

		m_pSteering = new SeekSteering(this);
}

Character::~Character()
{

}

void Character::OnStart()
{
    ReadParams("params.xml", mParams);
	m_pSteering->m_fMaxAcceleration = mParams.max_acceleration;
}

void Character::OnStop()
{

}

void Character::OnUpdate(float step)
{
	USVec2D vAcceleration = m_pSteering->GetSteering(mParams.targetPosition); 
	USVec2D vCurrentVelocity = GetLinearVelocity() + vAcceleration * step;
	float fDistance = (GetLoc() - mParams.targetPosition).Length();

	float fDistanceFactor = 1;
	if (fDistance < mParams.arrive_radius)
	{
		fDistanceFactor = fDistance / mParams.arrive_radius;
	}
	vCurrentVelocity.SetLength(mParams.max_velocity*fDistanceFactor);
	SetLinearVelocity(vCurrentVelocity.mX, vCurrentVelocity.mY);
	SetLoc(GetLoc() + GetLinearVelocity()*step);

}

void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	m_pSteering->DrawDebug();
	gfxDevice.SetPenColor(1.0f, 1.0f, 0.0f, 0.5f);
	MOAIDraw::DrawLine(GetLoc(), GetLoc() + GetLinearVelocity());
}




// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);
	
	luaL_Reg regTable [] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetLinearVelocity(pX, pY);
	return 0;	
}

int Character::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}
	