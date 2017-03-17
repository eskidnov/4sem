#include "Figures.h"
#include <iostream>

MaterialPoint::MaterialPoint() {
	mass = 1;
	acceleration = Vector2(0, 0);
	velocity = Vector2(rand() % 150 - 75, rand() % 150 - 75);
	position = Vector2(0, 0);
}

void MaterialPoint::UpdatePosition(float dt) {
	position += velocity * dt;
}

Vector2 MaterialPoint::GetImpulse() const {
	return Vector2(mass * velocity);
}

Ball::Ball() {
	radius = 5;
	type = 1;

	position = Vector2(radius + 1, radius + 1);
}