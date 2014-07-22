//
//  GameAction.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#ifndef HappyMouse_GameAction_h
#define HappyMouse_GameAction_h

#include "cocos2d.h"

class GameObject;

class GameAction : public cocos2d::CCObject{
    
public:
	virtual bool doAction(GameObject * aGameObject, cocos2d::CCDictionary * dic, cocos2d::CCObject * params) = 0;
    
};

#endif
