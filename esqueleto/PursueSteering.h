#pragma once
#include "ArriveSteering.h"
#include "Path.h"
class PursueSteering
{
protected:
	int m_iCurrentPoint = 0;
	float m_fLookAhead = 0;
	float m_fTimeAhead = 0;
	float m_fDestinationRadius = 0;
	Character* m_pCharacter;
	Character* m_pTarget;
public:
	ArriveSteering* m_pArrive;
	PursueSteering(ArriveSteering* _pArrive, Character* _pCharacter);
	void SetTarget(Character* _pTarget);
	USVec2D GetSteering();
	void Initialize();
};

