// Copyright (C) 2014 Team306

#ifndef VECTOR2_H
#define VECTOR2_H 


class Vector2
{
private:
	float x;
	float y;

public:
	Vector2(float x = 0, float y = 0);
	~Vector2();

	// get and set methods
	float getX() const;
	float getY() const;
	void setXY(float, float);

	// override operators
    Vector2 operator+(Vector2 &) const;
    Vector2 operator-(Vector2 &) const;
    Vector2 operator*(float) const;
    float dotProduct(Vector2 &) const;
	// Vector2 crossProduct(Vector2 &);

	Vector2 operator+=(Vector2 &);
	Vector2 operator-=(Vector2 &);

	float Length() const; // length
    float distanceBetween(Vector2 &) const;

    Vector2 getNormalize() const;
    Vector2 getVertical() const;
};


#endif
