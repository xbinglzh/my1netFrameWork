//
//  MonsterObject.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-24.
//
//

#ifndef __HappyMouse__MonsterObject__
#define __HappyMouse__MonsterObject__

#include "cocos2d.h"
#include "GameObject.h"

USING_NS_CC;

class MonsterObject : public GameObject {
    
public:
    MonsterObject();
    ~MonsterObject();
    
    static MonsterObject* create(CCDictionary * dict);
    bool init();
    bool initWithDictionary(CCDictionary * dict);
    
    void setIsAddParent(bool isAdd);
    bool isAddParent();
    
    CCNode* getMoveNode();
    bool strikenMouse(cocos2d::CCTouch *pTouch);
    
private:
    void makeMidNodeInClipNode();
    void changeStateToMove();
    
private:
    bool          _isAddParent;
};

#endif /* defined(__HappyMouse__MonsterObject__) */
