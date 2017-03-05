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

float Vector2::len() {
	return sqrt(x * x + y * y);
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
	/*
	можно писать просто return Vector(-y, x) / len();
	т.к. длина у (-y, x) такая же
	*/
}

Vector2 Vector2::operator-() const {
	/*
	Нули можно и не писать:
	return Vector2(-x, -y);
	*/
	return Vector2(0-x, 0-y);
}

/*
 последние три метода, которые вы написали полезные. но из-за ошибок округления такая
 реализация может не сработать.
 
 если вы, например, напишите
 if (v == v.norm() * v.len()) то выражение вполне может оказаться ложным из-за того, что
 в из-за ошибок округления в каком-нибудь 7-м знаке числа могут не совпадать.
 
 Обычно стараются избегать такого рода сравнений. Но если уж прям очень надо, то сравнивают так:
 return fabs(x - v.x) < EPS && fabs(y - v.y) < EPS, где заранее выбирают некоторое EPS равным, например, 1e-6f
*/

int Vector2::operator==(const Vector2& v) const {
	return x == v.x && y == v.y;
}

int Vector2::operator!=(const Vector2& v) const {
	return x != v.x || y != v.y;
}

int Vector2::operator||(const Vector2& v) const {
	return !(x * v.y - y * v.x);
}
