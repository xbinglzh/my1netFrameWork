//
//  ArmatureAnim.h
//  n2studio
//
//  Created by Ryan_Y on 13-5-20.
//
//

#ifndef N2Studio_ArmatureAnim_h
#define N2Studio_ArmatureAnim_h

#include "cocos2d.h"
#include "SPArmature/SPArmature.h"
#include "SPArmature/external_tool/sigslot.h"
#include "AnimationDelegateExt.h"

USING_NS_CC;

class ArmatureAnim : public CCLayerRGBA , public sigslot::has_slots<>{
public:
	ArmatureAnim();
	virtual ~ArmatureAnim();
	static ArmatureAnim * create();
public:
	virtual void onMovementEvent(sp::Armature *armature, const char *eventType, const char *movementID);
private:
	static void initWithLayer(CCLayer * layer, const std::string & layerName);
	static void removeBatchNodes(const std::string & layerName);
public:
	void update(float dt);
#if USING_COCOS2D_2_1_PLUS
    virtual const CCSize& getContentSize();
#else
    virtual CCSize getContentSize();
#endif
public:
    void load(const std::string & armatureName,
			  const std::vector<sp::ImageInfo> & list,
			  const std::string & xmlFilePath,
			  const float positionReadScale = 1.0f);
    
	bool runAnimation(const std::string & animName);
    void stopAnimation();
    void pauseAnimation();
    void resumeAnimation();
    
    void setAnimDelegateExt(AnimationDelegateExt * delegateExt);
    void showFrame(const std::string & frameName);
    const std::string currentAnimation();
    const std::string currentFrame();
	const CCSize & getMaxContentSize();
	void setMaxContentSize(const CCSize & s);
    void setFrameITScale(const float value);
public:
	std::string  _layerName;
	sp::Armature * _armature;
    CCSize _maxContentSize;
    AnimationDelegateExt * _animDelegateExt;
    float _frameITScale;
	float _frameIT;
	float _frameCT;
};

#endif
