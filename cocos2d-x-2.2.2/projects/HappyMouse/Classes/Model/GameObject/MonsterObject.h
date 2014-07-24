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
    struct MonsterDetail {
        
        int            _id;
        int            _hp;
        int            _hurt;
        std::string    _display;
        int            _speed;
        
    };
    
public:
    MonsterObject();
    ~MonsterObject();
    
    static MonsterObject* create(CCDictionary * dict);
    bool initWithDictionary(CCDictionary * dict);
    MonsterDetail& getMonsterDetail() ;
    
private:
    MonsterDetail _monsterDetail;
};

#endif /* defined(__HappyMouse__MonsterObject__) */
