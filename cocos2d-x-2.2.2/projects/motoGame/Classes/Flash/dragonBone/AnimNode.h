//
//  AnimNode.h
//  iLostCity
//
//  Created by Ryan_Y on 13-6-6.
//
//

#ifndef iLostCity_AnimNode_h
#define iLostCity_AnimNode_h

#include "cocos-ext.h"
#include "AnimationDelegateExt.h"

/**
 显示用的节点类，支持包装了一个动画
 */
#pragma mark-
#pragma mark AnimNode

class AnimNodeDelegate:public cocos2d::extension::CCBAnimationManagerDelegate,
public cocos2d::extension::CCBSelectorResolver,
public cocos2d::extension::CCBMemberVariableAssigner,
public cocos2d::extension::CCNodeLoaderListener  {
    
public:
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget,
                                                                    const char* pSelectorName);
    
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget,
                                                                                   const char* pSelectorName);
    
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget,
                                           const char* pMemberVariableName,
                                           cocos2d::CCNode * pNode);
    
    virtual void onNodeLoaded(cocos2d::CCNode * pNode,
                              cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    virtual void notifyCompletedAnimationSequenceNamed(const char *name, const bool loopCompleted);
    
    virtual void completedAnimationSequenceNamed(const char *name);
    
    virtual void animationSequenceFrameChanged(cocos2d::CCNode * animNode,
                                               const char *animName,
                                               const char *lastframeName,
                                               const char *newframeName);
};

class AnimNode : public cocos2d::CCNodeRGBA, public AnimNodeDelegate, public AnimationDelegateExt {

public:
    enum EAnimNodeTypeId {
		K_SPRITE_FILE  	  =0,//sprite
        K_ARMATURE_FRAME  =1,//Armature spriteframe
        K_SPRITE_FRAME    =2,//spriteframe
	};
    
public:
    
	AnimNode();
	virtual ~AnimNode();
    CREATE_FUNC(AnimNode);
    
    static AnimNode* createAnim(cocos2d::CCDictionary * dict, AnimNodeDelegate * delegate);
    
    static AnimNode* createFlashAnimNode(const char* pngFile, const char* plistFile, const char* xmlFile,
                                         const char* runAnim, const char* skeleton);
    
	const bool runAnimation(const std::string & name = "", const float delay = 0.0f, cocos2d::CCCallFuncO * calll = NULL);
    
    void  stopAnimation();
    void  resumeAnimation();
    void  pauseAnimation();
    const cocos2d::CCSize & getContentSize();
    void  setFrameITScale(const float value);
    void  updateAnimFrame(float dt);
    
    const std::string& getDefaultAnimation()const;
    void setDefaultAnimation(const std::string& value);
    
public:
    void  update(float dt);
    
public:
    
#pragma mark AnimNode AnimationDelegateExt
    virtual void onAnimationEvent(void * animation, const char * eventType, const char * movementID);
    inline cocos2d::CCNode * getChildAnimNode(){ return _animNode; }
    inline float getOrginalAnimScale(){ return _animScale; }
    void scaleAnim(float scale);
    
public:
    void setAutoRemoveOnFinish(const bool autoRemoveOnFinish);
    
protected:
    CC_SYNTHESIZE(AnimNodeDelegate *, _animNodeDelegate,AnimNodeDelegate);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCCallFuncO *, _currentCalll,CurrentCalll);
    CC_SYNTHESIZE(bool, _autoUpdateFrame, AutoUpdateFrame);
    
protected:
	cocos2d::extension::CCBAnimationManager *_animationManager;
    cocos2d::CCNode  *  _animNode;
    std::string _defaultAnimation;
    std::string _currentFrame;
    
    bool _autoRemoveOnFinish;
    float _animScale;
    
    EAnimNodeTypeId  _typeId;
};

#endif
