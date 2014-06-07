// Copyright (C) 2014 Team306

#include <cmath>
#include "Vector2.h"

Vector2::Vector2(float x, float y)
    : x(x), y(y)
{
//	this->x = x;
//	this->y = y;
}

Vector2::~Vector2()
{
}

// get and set methods
float Vector2::getX() const
{
	return x;
}

float Vector2::getY() const
{
	return y;
}

void Vector2::setXY(float x, float y)
{
	this->x = x;
	this->y = y;
}

// override operators
Vector2 Vector2::operator+(Vector2& v) const
{
	Vector2 result;
	result.x = this->x + v.x;
	result.y = this->y + v.y;
	return result;
}
	
Vector2 Vector2::operator-(Vector2& v) const
{
	Vector2 opposite(-v.getX(), -v.getY());
	Vector2 result = *this + opposite;
	return result;
}

Vector2 Vector2::operator*(float scale) const
{
	Vector2 result = *this;
	result.x *= scale;
	result.y *= scale;
	return result;
}

float Vector2::dotProduct(Vector2& v) const
{
	float result = this->x * v.x + this->y * v.y;
	return result;
}

Vector2 Vector2::operator+=(Vector2& v)
{
	Vector2 result = *this + v;
    this->x = result.x;
    this->y = result.y;
	return result;
}

Vector2 Vector2::operator-=(Vector2& v)
{
	Vector2 result = *this - v;
	this->x = result.x;
	this->y = result.y;
	return result;
}

float Vector2::Length() const
{
	return sqrt(x * x + y * y);
}

float Vector2::distanceBetween(Vector2& v) const
{
    Vector2 distance = (*this) - v;
    return distance.Length();
}

Vector2 Vector2::getNormalize() const
{
	Vector2 result(x / Length(), y / Length());
	return result;
}

Vector2 Vector2::getVertical() const
{
	Vector2 result(-y, x);
	return result;
}
