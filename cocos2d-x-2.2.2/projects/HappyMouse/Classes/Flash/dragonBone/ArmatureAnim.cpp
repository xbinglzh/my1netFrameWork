//
//  ArmatureAnim.cpp
//  n2studio
//
//  Created by Ryan_Y on 13-5-20.
//
//

#include "ArmatureAnim.h"
#include "SPArmature/utils/SPArmatureDataManager.h"
#include "SPArmature/utils/SPBatchNodeManager.h"
#include "SPArmature/animation/SPAnimation.h"

using namespace sp;

ArmatureAnim::ArmatureAnim():_armature(NULL),
_animDelegateExt(NULL),
_frameITScale(1),
_frameCT(0){
	_frameIT = CCDirector::sharedDirector()->getAnimationInterval();
	std::stringstream layerName;
	layerName << "n2studio_" << (int32_t)this;
	initWithLayer(this,layerName.str());
    
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
}

ArmatureAnim::~ArmatureAnim(){
    unscheduleUpdate();
	std::stringstream layerName;
	layerName << "n2studio_" << (int32_t)this;
	removeBatchNodes(layerName.str());
	CC_SAFE_RELEASE_NULL(_armature);
}

ArmatureAnim * ArmatureAnim::create(){
	ArmatureAnim * anim = new ArmatureAnim();
	anim->autorelease();
	anim->ignoreAnchorPointForPosition(false);
	anim->setAnchorPoint(CCPoint(0.5, 0.5));
	return anim;
}

void ArmatureAnim::initWithLayer(CCLayer *layer, const std::string & layerName){
#if USING_BATCHNODE_ARMATURE
	BatchNodeManager::sharedBatchNodeManager()->initWithLayer(layer,layerName);
#endif
}

void ArmatureAnim::removeBatchNodes(const std::string & layerName){
#if USING_BATCHNODE_ARMATURE
	BatchNodeManager::sharedBatchNodeManager()->removeBatchNodes(layerName);
#endif
}

void ArmatureAnim::load(const std::string & armatureName,
						const std::vector<sp::ImageInfo> & list,
						const std::string & xmlFilePath,
						const float positionReadScale){
    ArmatureDataManager * sharedArmatureDataManager = ArmatureDataManager::sharedArmatureDataManager();
#if USING_BATCHNODE_ARMATURE
    BatchNodeManager * sharedBatchNodeManager = BatchNodeManager::sharedBatchNodeManager();
#endif
	for (std::vector<sp::ImageInfo>::const_iterator iter = list.begin();
         iter != list.end();
         iter++) {
        const sp::ImageInfo & info = (*iter);
        sharedArmatureDataManager->addArmatureFileInfo(armatureName.c_str(),
                                                      info.imagePath.c_str(),
                                                      info.plistPath.c_str(),
                                                      xmlFilePath.c_str(),
													  positionReadScale);
#if USING_BATCHNODE_ARMATURE
       sharedBatchNodeManager->getBatchNode((*iter).imagePath)->setRenderType(BATCHNODE_VERTEXZ);
#endif
    }
	_armature = Armature::create(armatureName.c_str(),this);
    _armature->retain();
	_armature->setScale(1);
	_armature->setZOrder(1);
	_armature->getAnimation()->MovementEventSignal.connect(this, &ArmatureAnim::onMovementEvent);
}

void ArmatureAnim::update(float dt){
	_frameCT += (dt * _frameITScale);
	if (_frameCT >= _frameIT) {
		do {
			if (_armature) {
				_armature->update(_frameIT);
			}
			_frameCT -= _frameIT;
		} while (_frameCT >= _frameIT);
	}
}

/**
 设置frameITScale
 */
void ArmatureAnim::setFrameITScale(const float value){
    _frameITScale = value;
}
    
bool ArmatureAnim::runAnimation(const std::string & animName){
	if (_armature && _armature->getAnimation()) {
		return _armature->getAnimation()->play(animName.c_str());
	}
	return false;
}

void ArmatureAnim::stopAnimation(){
  	if (_armature && _armature->getAnimation()) {
		_armature->getAnimation()->stop();
	}
}

void ArmatureAnim::pauseAnimation(){
  	if (_armature && _armature->getAnimation()) {
		_armature->getAnimation()->pause();
	}
}

void ArmatureAnim::resumeAnimation(){
  	if (_armature && _armature->getAnimation()) {
		_armature->getAnimation()->resume();
	}
}

#if USING_COCOS2D_2_1_PLUS
const CCSize & ArmatureAnim::getContentSize()
#else
CCSize ArmatureAnim::getContentSize()
#endif
{
    return CCLayer::getContentSize();
}

const CCSize & ArmatureAnim::getMaxContentSize(){
	return _maxContentSize;
}

void ArmatureAnim::setMaxContentSize(const CCSize & s){
	_maxContentSize = s;
}

const std::string ArmatureAnim::currentAnimation(){
	if (_armature && _armature->getAnimation()) {
        std::string name = _armature->getAnimation()->getMovementID().c_str();
		return name;
	}
	return "";
}

const std::string ArmatureAnim::currentFrame(){
	if (_armature && _armature->getAnimation()) {
        Animation * anim = _armature->getAnimation();
        std::stringstream key;
        key << anim->getMovementID() << "_" << anim->getCurrentFrameIndex() << "_" << anim->getTotalFrames();
        return key.str();
	}
	return "";
}

void ArmatureAnim::showFrame(const std::string & frameName){
    
}

void ArmatureAnim::onMovementEvent(Armature *armature, const char *eventType, const char *movementID){
    if (_armature == armature && _animDelegateExt) {
        _animDelegateExt->onAnimationEvent(this, eventType, movementID);
    }
}

void ArmatureAnim::setAnimDelegateExt(AnimationDelegateExt * delegateExt){
    _animDelegateExt = delegateExt;
}
	