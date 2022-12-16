#ifndef TimerCount
#define TimerCount

#include "cocos2d.h"
#include <cmath>

class TimerCountDown : public cocos2d::Layer
{
public:
	virtual void update(float delta);

	float timeCounter;

	virtual bool init();

	cocos2d::Label* timertxt;
	CREATE_FUNC(TimerCountDown);
};

#endif
//#pragma once

