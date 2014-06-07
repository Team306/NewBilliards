// Copyright (C) 2014 Team306

#ifndef CUE_H
#define CUE_H 


#include "Vector2.h"
#include "Referee.h"

// user controls it
class Cue
{
private:
	Vector2 mousePosition; // update each main loop
	// the position of the cue-ball 
	float ballRadius;
	float cueLength;

public:
	Cue();
	~Cue();

	// init method
	void init(Referee &);

	// update and draw
    void Update(int gameState, Vector2 mousePosition);
	void Draw(QPainter &, Ball& cueBall);	

	void Stroke(int elapsed, Ball& cueBall);
};


#endif
