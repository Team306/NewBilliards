// Copyright (C) 2014 Team306

#ifndef MENU_H
#define MENU_H


#include <QRect>
#include <QRectF>
#include <QPainter>
#include "MyMath.h"
#include "Player.h"

class Menu
{
private:
	// start frame
	QRectF titleRect;
	QRectF titleBackRect;

	QRect practiceModeRectChosen;
	QRectF practiceModeRectSmall;
	QRectF practiceModeRectBig;
	QRect versusModeRectChosen;
	QRectF versusModeRectSmall;
	QRectF versusModeRectBig;
	QRect networkModeRectChosen;
	QRectF networkModeRectSmall;
	QRectF networkModeRectBig;

	QRectF eightBallRuleRect;
	QRectF nineBallRuleRect;
	QRectF snookerRuleRect;

	QRectF eightBallTick;
	QRectF nineBallTick;
	QRectF snookerTick;

	QRect eightBallChosen;
	QRect nineBallChosen;
	QRect snookerChosen;

	QRectF copyrightRect;

	// end frame
	QRectF endTitleRect;
	QRectF endContinueRect;

	// player
	QRectF player1RectBig;
	QRectF player1RectSmall;
	QRectF player2RectBig;
	QRectF player2RectSmall;

	// waiting frame
	QRectF waitingRect;

	// connect frame
	QRect startRectChosen;
	QRectF startRectBig;
	QRectF startRectSmall;
	QRect connectRectChosen;
	QRectF connectRectBig;
	QRectF connectRectSmall;

	// hit point
	float hitPointRadius;
	Vector2 hitPointCenterPosition;
    float redPointRadius;

public:
	Menu();
	~Menu();

	void displayStartFrame(QPainter &, Vector2 mousePosition, int gameRule);
    void displayEndFrame(QPainter& painter, const Player& player1);
    void displayPlayer(QPainter& painter, bool);
	void displayWaitingFrame(QPainter& painter);
	void displayConnectFrame(QPainter& painter, Vector2 mousePosition);
	void displayHitPoint(QPainter& painter, Vector2 hitPosition);
	void displayPauseButton(QPainter& painter);

	QRect getPracticeChosen() const;
	QRect getVersusChosen() const;
    QRect getNetworkChosen() const;
	QRect getEightBallChosen() const;
	QRect getNineBallChosen() const;
	QRect getSnookerChosen() const;
	QRect getStartChosen() const;
	QRect getConnectChosen() const;	

	Vector2 getHitCenterPosition() const;
	float getHitRadius() const;
};


#endif
