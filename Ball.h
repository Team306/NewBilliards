// Copyright (C) 2014 Team306

#ifndef BALL_H
#define BALL_H 


#include <QPainter>
#include <QColor>
#include <string>
#include "Vector2.h"

enum BALL_STATE { STILL, RUNNING, ON_THE_POCKET };

class Ball
{
private:
	Vector2 position; // center position
	Vector2 speed;
	float radius;

	// 2 degree of freedom in rotation
	float rightRotation;
	float upRotation;
	// should put them into a vector?

	// ball's info
	std::string name;
	QColor color;

	BALL_STATE ballState;

public:
	Ball();
    Ball(Vector2 position, float radius);
	~Ball();

	// get and set methods
	Vector2 getPosition() const;
	void setPosition(Vector2);
	Vector2 getSpeed() const;
	void setSpeed(Vector2);
	float getRadius() const;
	int getBallState() const;
	void setBallState(int);

	std::string getName() const;
	void setName(std::string);
	void setColor(QColor);
	
	// getRotation

	// update and draw
	virtual void Update();
	virtual void Draw(QPainter &);

	// collision detection
	bool collidesWith(Ball &);
};


#endif
