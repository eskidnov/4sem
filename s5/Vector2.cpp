#include "Vector2.h"

Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(float _x, float _y) {
	x = _x;
	y = _y;
}

Vector2::Vector2(const Vector2& other) {
	x = other.x;
	y = other.y;
}

std::ostream& operator<<(std::ostream& stream, const Vector2& v) {
	stream << v.x << " " << v.y;
	return stream;
}

std::istream& operator>>(std::istream& stream, Vector2& v) {
	stream >> v.x >> v.y;
	return stream;
}

float Vector2::len() const {
	return sqrt(x * x + y * y);
}

float Vector2::squareLen() const {
	return x * x + y * y;
}

Vector2& Vector2::rotate(const float angle) {
	const float _angle = angle * 3.14 / 180;
	const float _x = x;
	const float _y = y;
	x = 0 + _x * cos(_angle) - _y * sin(_angle);
	y = 0 + _y * cos(_angle) + _x * sin(_angle);
	return *this;
}

Vector2 Vector2::getRotated(const float angle) const {
	const float _angle = angle * 3.14 / 180;
	return Vector2(0 + x * cos(_angle) - y * sin(_angle),
				   0 + y * cos(_angle) + x * sin(_angle));
}

Vector2& Vector2::operator=(const Vector2& v) {
	x = v.x; 
	y = v.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2& v) const {
	return Vector2(x + v.x, y + v.y);
}

Vector2& Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& v) const {
	return Vector2(x - v.x, y - v.y);
}

Vector2& Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

float Vector2::operator*(const Vector2& v) const {
	return x * v.x + y * v.y;
}

float Vector2::operator^(const Vector2& v) const {
	return x * v.y - y * v.x;
}

Vector2 Vector2::operator*(float n) const {
	return Vector2(x * n, y * n);
}

Vector2 operator*(float n, const Vector2& v) {
	return Vector2(v.x * n, v.y * n);
}

Vector2& Vector2::operator*=(float n) {
	x *= n;
	y *= n;
	return *this;
}

Vector2 Vector2::operator/(float n) const {
	return Vector2(x / n, y / n);
}

Vector2& Vector2::operator/=(float n) {
	x /= n;
	y /= n;
	return *this;
}

Vector2 Vector2::norm() const {
	Vector2 temp(x, y);
	return temp / temp.len();
}

Vector2 Vector2::ort() const {
	Vector2 temp(0-y, x);
	return temp / temp.len();
}

Vector2 Vector2::operator-() const {
	return Vector2(0-x, 0-y);
}

int Vector2::operator==(const Vector2& v) const {
	return x == v.x && y == v.y;
}

int Vector2::operator!=(const Vector2& v) const {
	return x != v.x || y != v.y;
}

int Vector2::operator||(const Vector2& v) const {
	return !(x * v.y - y * v.x);
}