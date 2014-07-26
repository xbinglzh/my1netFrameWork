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
#include "GameEventParams.h"
#include <boost/function.hpp>
#include <boost/variant.hpp>

USING_NS_CC;

class GameObject : public CCNodeRGBA, public AnimNodeDelegate {
    
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
    static GameObject * create(CCDictionary * dict,const uint32_t id);
    
protected:
	virtual bool init();
    virtual bool initWithDictionary(cocos2d::CCDictionary * dict);
    
public: /* 设置基本属性 */
    void setId(const uint32_t value);
    void setType(const uint8_t type);
    void setRace(const uint8_t race);
    void setLevel(const int32_t level);
    void setLastState(const uint32_t lastState);
    void setHurtType(const uint8_t hurtType);
    void setHurt(const uint32_t hurt);
    
    void setHP(const uint32_t hp);
    void setFullHp(const uint32_t fullHp);
    void setSpeed(const float speed);
    
    void setBufferTop(const std::string bufferTop);
    void setBufferBottom(const std::string bufferBottom);
    
    const uint32_t getId()const;
    const uint8_t  getType()const;
    const uint8_t  getRace()const;
    const int32_t  getLevel()const;
    const int32_t  getLastState() const;
    const int8_t   getHurtType() const;
    const int32_t  getHurt() const;
    const int32_t  getHp() const;
    const int32_t  getFullHp() const;
    const float    getSpeed() const;
    //buffer
    const std::string getBufferTop() const;
    const std::string getBufferBottom() const;

public:
    const bool runAnimation(const std::string & name = "",
                            const float delay = 0.0f);
    void  stopAnimation();
    void  pauseAnimation();
    void  resumeAnimation();
    void  update(const float dt);
    void  setFrameITScale(const float value);
    
public:
    /**
     动画节点加载完成
     */
	virtual void onNodeLoaded(cocos2d::CCNode * pNode,
                              cocos2d::extension::CCNodeLoader * pNodeLoader);
    /**
     动画播放完成
     */
    virtual void notifyCompletedAnimationSequenceNamed(const char *name, const bool loopCompleted);
    /**
     动画播放换帧
     */
    virtual void animationSequenceFrameChanged(cocos2d::CCNode * animNode,
                                               const char *animName,
                                               const char *lastframeName,
                                               const char *newframeName);
    
    static bool runStateAnimation(GameObject * obj,int stateId);
    
    //    static boost::shared_ptr<n2studio::network::Buffer> encode(GameObject * obj);
    //    static GameObject * decode(const boost::shared_ptr<n2studio::network::Buffer> & buf);
    
public:
    void initDisplay(const char* animId);
    
public: /*状态机*/
    void changeState(const int32_t value);
    /**
     接收一个消息，交给状态机处理
     */
	void onMessage(GameEventParams * params);
    void initStateMachine(std::string& stateGroupId);
    void addState(const int32_t stateTypeId ,const int32_t stateId);
    
public:
    void setValue(const std::string & key,CCObject * value);
    CCObject* getValue(const std::string & key);
    
public:
    void doCallFunc(cocos2d::CCObject * data);
    void doAutoremoveCallFunc(cocos2d::CCObject * node);
    
public:
    void complete();
    CCNode* getFgNode();
    CCNode* getMidNode();
    CCNode* getBgNode();
    void    setObjContentSize(const CCSize size);
    
public:
    void initHpBar();
    
private:
    
    CCNode*                       _bgNode;
    CCNode*                       _fgNode;
    CCNode*                       _midNode;
    
    AnimNode*                     _flashNode;
    StateMachine*                 _stateMachine;
    GameCharactar                 _charactar;
    cocos2d::CCDictionary*        _properties;
    
};

#endif /* defined(__HappyMouse__GameObject__) */
