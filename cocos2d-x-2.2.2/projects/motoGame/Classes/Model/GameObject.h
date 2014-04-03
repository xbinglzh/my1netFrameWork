//
//  GameObject.h
//  motoGame
//
//  Created by xUanBing on 14-4-3.
//
//

#ifndef __motoGame__GameObject__
#define __motoGame__GameObject__

#include "cocos2d.h"
#include "LHSprite.h"

USING_NS_CC;

class GameObject :public CCSprite {
    
public:
    
    struct GamePhysical {
        
        float            _bodyWidth;
        float            _bodyHeight;
        
        float            _density; //密度
        float            _friction;//摩擦力
        float            _restitution;//弹性系数
        
    };
    
    struct GameCharactar{
        uint32_t           _id;         //角色ID
        int32_t            _level;      //等级(1-5级)
        
        uint32_t           _hp;         //角色当前血量
        uint32_t           _fullHp;     //角色全满时的血量
    };
    
    
public:
    GameObject();
    virtual ~GameObject();
    
    virtual bool init();
    
private:
    LHSprite*      _lhSprite;
    GamePhysical   _gamePhysical;
    GameCharactar  _gameCharactar;
    
};

#endif /* defined(__motoGame__GameObject__) */
