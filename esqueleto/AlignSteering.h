#pragma once

#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>

#include <params.h>


class AlignSteering
{
	float m_fDesiredAngle;
	float m_fAngularAcceleration;
	Character* m_pChararacter;
public:
	float m_fMaxAcceleration;
	float m_fMaxSpeed;
	AlignSteering (Character* _pCharacter);
	float GetSteering(float _fTarget);
	void DrawDebug();
	void Initialize();
};

