#pragma once

#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>

#include <params.h>

class SeekSteering
{
	float m_fMaxAcceleration = 30;
	USVec2D m_vDesiredSpeed = USVec2D(0, 0);
	USVec2D m_vCurrentAcceleration = USVec2D(0, 0);
	Character* m_pChararacter;
public:
	SeekSteering(Character* _pCharacter);
	USVec2D GetSteering(USVec2D _vTarget);
	void DrawDebug();

};

