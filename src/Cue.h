// Copyright (C) 2014 Team306

#ifndef CUE_H
#define CUE_H 


#include <QImage>
#include "MyMath.h"
#include "Referee.h"
#include <QSound>

// user controls it
class Cue
{
private:
	Vector2 mousePosition; // update each main loop
	// the position of the cue-ball 
	float ballRadius;
	float cueLength;

	// power gauge
    // QImage *image[44];
    QImage cueImage;
    bool powerGainEnableFlag;
    int powerGainCount;
    QSound *sound;
    bool powerGainIncrement;

public:
	Cue();
	~Cue();

	// init method
	void init(Referee &);

	// update and draw
    void Update(int gameState, Vector2 mousePosition);
	void Draw(QPainter &, Ball& cueBall, Vector2 mousePosition);	

    void Stroke(Ball& cueBall, Vector2 mousePosition, Vector2 hitPosition, int hitAngle,int HitRadius);

    // power gauge
    void enablePowerGain();
    void disablePowerGain();
    int getPowerCount() const;
    void setPowerCount(int powerCount);
};


#endif
