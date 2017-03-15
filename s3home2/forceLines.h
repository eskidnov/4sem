#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Vector2.h"

struct LineOfForce
{
	std::vector<Vector2> positiveBranch;
	std::vector<Vector2> negativeBranch;
};

struct Charge
{
	float value;
	Vector2 pos;
};

struct ElectricField
{
	std::vector<Charge> charges;
	std::vector<Vector2> lines;
	Vector2 findForce(const Charge& c) const;
};