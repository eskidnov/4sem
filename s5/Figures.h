#pragma once
#include "Vector2.h"

class MaterialPoint {
public:
	float mass;
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;

	MaterialPoint();

	void UpdatePosition(float dt);
	Vector2 GetImpulse() const;
};

class Ball : public MaterialPoint {
public:
	float radius;
	int type;

	Ball();
};