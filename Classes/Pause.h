#pragma once

#include "cocos2d.h"

class Pause : public cocos2d::Layer
{
public:
	virtual bool init();

	CREATE_FUNC(Pause);

	bool verif;

	void pauseMenu();

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

