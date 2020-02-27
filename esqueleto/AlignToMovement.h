#pragma once
#include "AlignSteering.h"
class AlignToMovement
{
	Character* m_pCharacter;
	AlignSteering* m_pAlign;
public:
	AlignToMovement(Character* _pCharacter, AlignSteering* _pAlign);
	float GetSteering();
};

