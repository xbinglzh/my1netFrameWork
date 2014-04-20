//
//  GameObject.h
//  motoGame
//
//  Created by xUanBing on 14-4-15.
//
//

#ifndef __motoGame__GameObject__
#define __motoGame__GameObject__

#include "cocos2d.h"
#include "Box2D.h"
#include "GameConfig.h"
#include "ParticleEffect.h"

USING_NS_CC;

class GameObject : public CCNode, public EffectAutoRemoveOnFinishDelegate {
    
public:
    virtual bool initWithDictionary(CCDictionary* dic, b2World * world,GameObject * parentObject,bool createPhysicsBody=true);
	virtual void createPhysicsBody2World(GameObject * gameObject,b2World * world,CCDictionary* dic = NULL);
	virtual CCSize getContentSize();
    
    //执行一个操作，并且把参数带入
    virtual bool doAction(const string& aActionkey,CCDictionary* dic);
    //停止一个操作，并且把参数带入
	virtual	bool stopAction(const string& aActionkey,CCDictionary* dic);
    
	//执行一个AI脚本，并且把参数带入
    virtual bool runAIScript(const string& aAIScriptName,CCDictionary* dic);
    
    //执行一个特效效果
	virtual bool playEffect(CCNode* parent,const string& aActionkey,const bool autoRemoveEffect=true,const float angle=0,const CCPoint * effectPosInSelf=NULL,const bool hasCallback=true,const int zOderValue = 0);
    
public:
    void  b2FixtureDisable(CCString * box2dString);
	void  b2FixtureEnable(CCString * box2dString);
	
	void setFlipX(bool flipX);
	void setFlipY(bool flipY);
    
    bool isFlipX() const;
    bool isFlipY() const;
    
public: /* box2d & cocos2d state*/
    void updatePosition(const CCPoint& pos);
    void updateAngle(const float angle);
    void updateVariantProperties();
    
    void destroyPhysicsBody();/*销毁掉刚体和关节*/
	void resetPhysicsBody();
    void setPhysicsBodyEnable(bool enable);
    
public:
//    LAYER_CREATE_FUNC(GameObject);
	GameObject();
	virtual ~GameObject();

protected:
    /* internel helper */
    inline void setCategory(const uint32 value);
	inline void setId(const uint32 value);
    
	inline void setPhysicsBody(b2Body * body);
    
	void createPhysicsBody(b2World * world,GameObject * object,b2BodyType bodyType,const bool bullet,const bool fixedRotation,const bool isActive,const CCPoint & bodyCenterposition,const b2FixtureDef & fixtureDef);
	GameObject* addGameObject(const string & gameObjectName, const uint32 id, const CCPoint & position, const float angle, const bool justCreateFixture,const bool createBody,GameObject *parentObject,const int32_t aNodezOrder);
    
    static b2Fixture * addNewFixture(GameObject * gameObject,string fixtureName,CCDictionary* box2dSetting);
	
	void  activeFixture(const string & fixtureName,CCObject * value,bool force_active=false);
    
private:
    bool  playEffectAuto(const string & aActionkey,const bool autoRemoveEffect=true,const float angle=0,const CCPoint * effectPosInSelf=NULL,const bool hasCallback=true,const int zOderValue = 0);
    
};


#endif /* defined(__motoGame__GameObject__) */
