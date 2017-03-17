#pragma once
#include <iostream>

struct Vector2 {
	float x, y;
	Vector2();
	Vector2(float, float);
	Vector2(const Vector2&);
	//~Vector2();
	Vector2& operator=(const Vector2&);
	float len() const;	// Length
	float squareLen() const;
	Vector2& rotate(const float);
	Vector2 getRotated(const float) const;
	Vector2 operator+(const Vector2&) const;	// c = a + b
	Vector2& operator+=(const Vector2&);	// a += b
	Vector2 operator-(const Vector2&) const;	//	c = a - b
	Vector2& operator-=(const Vector2&);	// a -= b
	float operator*(const Vector2&) const;	// f = (a, b)
	float operator^(const Vector2&) const;	// f = [a, b] (in 2d)
	Vector2 operator*(float) const;		// b = a * f
	Vector2& operator*=(float);		// a *= f
	Vector2 operator/(float) const;	// b = a * (1/f)
	Vector2& operator/=(float);		// a *= (1/f)
	Vector2 norm() const;		// t = a/|a|
	Vector2 ort() const;		// n _|_ a, |n| = 1
	Vector2 operator-() const;	// b = -a
	int operator==(const Vector2&) const;	// a == b
	int operator!=(const Vector2&) const;	// a != b
	int operator||(const Vector2&) const;	// a || b (Xa = f * Xb, Ya = f * Yb)
};
std::ostream& operator<<(std::ostream&, const Vector2&);	// Output
std::istream& operator>>(std::istream&, Vector2&);		// Input
Vector2 operator*(float, const Vector2&);	// b = f * a