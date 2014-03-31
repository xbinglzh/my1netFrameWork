#ifndef __MainLayer__
#define __MainLayer__

#include "cocos2d.h"
USING_NS_CC;

class MainLayer : public CCLayer{
public:
	virtual bool init();
	static CCScene* scene();
	void steupView(const char* fileName);
	virtual void update(float t);
	CREATE_FUNC(MainLayer);
};


#endif