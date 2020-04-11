#pragma once
#include "SeekSteering.h"
#include "Obstacles.h"
class ObstacleAvoidanceSteering
{
	Character* m_pCharacter;
	float m_fLookAhead = 0;
	float m_fCharacterRadius = 0;
public:
	SeekSteering* m_pSeek;
	Obstacles* m_pObstacles;
	ObstacleAvoidanceSteering(SeekSteering* _pSeek, Obstacles* _pObstacles, Character* _pCharacter);
	USVec2D GetSteering(USVec2D _vTarget);
	void Initialize();
	void DrawDebug();
};

