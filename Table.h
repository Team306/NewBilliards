// Copyright (C) 2014 Team306

#ifndef TABLE_H
#define TABLE_H 


#include <QPainter>
#include "Vector2.h"
#include "Ball.h"
#include "Referee.h"

class Table
{
private:
	// table size do not equal picture size
	Vector2 size;
	Vector2 picSize;

	Vector2 position;
	Vector2 picPosition;
    QRect R1,R2,R3,R4,R5,R6,R7,R8;
    float pocketRadius;
    Vector2 p1,p2,p3;

public:
	Table();
	~Table();

	// init method
	void init(Referee &);

	// get and set method
	Vector2 getSize() const;
	
	// update and draw
	void Update();
	void Draw(QPainter &);

	// collision detection
	bool collidesWith(Ball &);
    bool positionIsLegal(Vector2 ,Referee &);

    // check if the ball is into the pocket
    bool checkPockets(Ball &);
};


#endif
