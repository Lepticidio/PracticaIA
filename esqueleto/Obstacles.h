#pragma once
#include <stdafx.h>
#include <tinyxml.h>
#include <vector>

struct Obstacle
{
	bool m_bColliding = false;
	float m_fRadius;
	USVec2D m_vPosition;
	Obstacle(float _fRadius, USVec2D _vPosition) : m_fRadius(_fRadius), m_vPosition(_vPosition) { m_bColliding = false; };
};
class Obstacles
{
public:
	std::vector<Obstacle> m_tObstacles;
	Obstacles(const char* filename);
	void DrawDebug();
};

