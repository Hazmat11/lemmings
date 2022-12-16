#pragma once

#include "cocos2d.h"

class Accelerate : public cocos2d::Layer
{
public:
	virtual bool init();

	void speedUp(cocos2d::Ref* pSender);

	void update(float dt);

	CREATE_FUNC(Accelerate);
};

