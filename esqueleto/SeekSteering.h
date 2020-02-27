#pragma once

#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>

#include <params.h>

class SeekSteering
{
	USVec2D m_vDesiredSpeed = USVec2D(0, 0);
	USVec2D m_vCurrentAcceleration = USVec2D(0, 0);
	Character* m_pChararacter;
public:
	float m_fMaxAcceleration;
	SeekSteering(Character* _pCharacter);
	USVec2D GetSteering(USVec2D _vTarget);
	void DrawDebug();

};

