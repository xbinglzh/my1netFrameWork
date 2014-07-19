//
//  GameObject.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-19.
//
//

#ifndef __HappyMouse__GameObject__
#define __HappyMouse__GameObject__

#include "cocos2d.h"
#include "StateDef.h"
#include "State.h"
#include "StateMachine.h"
#include "AnimNode.h"

USING_NS_CC;

class GameObject : public CCNodeRGBA {
    
public:
    /**
     游戏角色对象的基本信息
     */
    struct GameCharactar{
        uint32_t           _id;         //角色ID
        uint8_t            _type;       //类型(例如所属于的卡牌组)
        uint8_t            _race;       //种族
        int32_t            _level;      //等级(1-5级)
        uint32_t           _lastState;
        uint8_t            _hurtType;   //攻击的时候伤害类型
        uint32_t           _hp;         //角色当前血量
        uint32_t           _fullHp;     //角色全满时的血量
        uint32_t           _hurt;       //当前伤害力
        float              _speed;

        std::string              _bufferTop;      //buffer
        std::string              _bufferBottom;
    };

    
public:
	GameObject();
	virtual ~GameObject();
	static GameObject * create(const uint32_t id);
    
public: /* 设置基本属性 */
    void setId(const uint32_t value);
    void setType(const uint8_t type);
    void setRace(const uint8_t race);
    void setLevel(const int32_t level);
    void setLastState(const uint32_t lastState);
    void setHurtType(const uint8_t hurtType);
    
    void setHP(const uint32_t hp);
    void setFullHp(const uint32_t fullHp);
    
    void setHurt(const uint32_t hurt);
    void setSpeed(const float speed);
    
    void setBufferTop(const std::string bufferTop);
    void setBufferBottom(const std::string bufferBottom);
    
public:
    const bool runAnimation(const std::string & name,const float delay);
    void  stopAnimation();
    void  pauseAnimation();
    void  resumeAnimation();
    void  update(const float dt);
    
protected:
	bool init();
    
private:
    
    CCNode*                       _bgNode;
    CCNode*                       _fgNode;
    AnimNode*                     _flashNode;
    StateMachine*                 _stateMachine;
    GameCharactar                 _charactar;
};

#endif /* defined(__HappyMouse__GameObject__) */
