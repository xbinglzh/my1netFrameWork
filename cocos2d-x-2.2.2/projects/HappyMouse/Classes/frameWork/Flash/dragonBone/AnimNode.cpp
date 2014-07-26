//
//  AnimNode.cpp
//  iLostCity
//
//  Created by Ryan_Y on 13-6-6.
//
//

#include "AnimNode.h"
#include "ArmatureAnim.h"
#include "SPConstValue.h"
#include "GameUtils.h"
#include "KeyConfigDef.h"
#include "CCSpriteExt.h"
#include "SPConstValue.h"

USING_NS_CC;
USING_NS_CC_EXT;

SEL_MenuHandler AnimNodeDelegate::onResolveCCBCCMenuItemSelector(CCObject * pTarget,  const char* pSelectorName){
	return NULL;
	
}

SEL_CCControlHandler AnimNodeDelegate::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
	return NULL;
}

bool AnimNodeDelegate::onAssignCCBMemberVariable(CCObject * pTarget, const char*  pMemberVariableName, CCNode * pNode){
	return false;
}

void AnimNodeDelegate::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader){
}

void AnimNodeDelegate::notifyCompletedAnimationSequenceNamed(const char *name, const bool loopCompleted){
}

void AnimNodeDelegate::completedAnimationSequenceNamed(const char *name){
    
}

void AnimNodeDelegate::animationSequenceFrameChanged(cocos2d::CCNode * animNode,
                                                     const char *animName,
                                                     const char *lastframeName,
                                                     const char *newframeName){
}

#pragma mark-
#pragma mark AnimNode

AnimNode::AnimNode():CCNodeRGBA()
,_animationManager(NULL)
,_animNodeDelegate(NULL)
,_typeId(AnimNode::K_SPRITE_FILE)
,_animNode(NULL)
,_autoRemoveOnFinish(false)
,_animScale(1.0f)
,_currentCalll(NULL)
,_autoUpdateFrame(true)
{
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
}

AnimNode::~AnimNode(){
    if(AnimNode::K_ARMATURE_FRAME == _typeId){
        unscheduleUpdate();
    }
    CC_SAFE_RELEASE_NULL(_currentCalll);
	CC_SAFE_RELEASE_NULL(_animationManager);
}

AnimNode * AnimNode::createAnim(CCDictionary * dict,
                                AnimNodeDelegate * delegate){
    AnimNode * node = NULL;
    CCDictionary * tmpDict = dict;
    
    if (tmpDict) {
        CCString * strValue = (CCString *)tmpDict->objectForKey(KKeyType);
        const uint32_t typeValue = strValue->uintValue();
        strValue = (CCString *)tmpDict->objectForKey(KKeyFile);
        CCString * scaleVal = (CCString *)tmpDict->objectForKey(KKeyScale);
        CCString * flipXVal = (CCString *)tmpDict->objectForKey(KKeyFlipX);
        
        switch (typeValue) {
            case AnimNode::K_SPRITE_FRAME:
            {
                node = new AnimNode;
                node->autorelease();
                node->_typeId = AnimNode::K_SPRITE_FRAME;
                CCSpriteFrameCache * cache = CCSpriteFrameCache::sharedSpriteFrameCache();
                CCSpriteFrame *pFrame = cache->spriteFrameByName(strValue->getCString());
                if (!pFrame) {
                    const std::string & imagePath = static_cast<CCString *>(tmpDict->objectForKey(KKeyImageTexture))->m_sString;
                    const std::string & plistPath = static_cast<CCString *>(tmpDict->objectForKey(KKeyImagePlist))->m_sString;
                    cache->addSpriteFramesWithFile(plistPath.c_str(), imagePath.c_str());
                    pFrame = cache->spriteFrameByName(strValue->getCString());
                }
                node->_animNode = CCSprite::createWithSpriteFrame(pFrame);
                node->addChild(node->_animNode);
                node->setDefaultAnimation(strValue->m_sString);
            }
                break;
            case AnimNode::K_SPRITE_FILE:
            {
                node = new AnimNode;
                node->autorelease();
                node->_typeId = AnimNode::K_SPRITE_FILE;
                node->_animNode = CCSpriteExt::create(strValue->getCString());
                
                if(!node->_animNode){
                    node->_animNode = CCSprite::create();
                    CCLOG("CCSprite::create %s not found",strValue->getCString());
                }
                
                node->addChild(node->_animNode);
                node->setDefaultAnimation(strValue->m_sString);
            }
                break;
            case AnimNode::K_CCBI_FILE:
            {
                //动画加载
                cocos2d::extension::CCBAnimationManager *_animationManager = NULL;;
                std::string ccbifile = strValue->getCString();
                CCNodeLoaderLibrary *ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
                ccNodeLoaderLibrary->registerCCNodeLoader("AnimNode",AnimNodeLoader::loader());
                CCBReader * ccBReader = new CCBReader(ccNodeLoaderLibrary);
                _animationManager = ccBReader->getAnimationManager();
                node = dynamic_cast<AnimNode *>(ccBReader->readNodeGraphFromFile(ccbifile.c_str()));
                node->setAnchorPoint(ccp(0.5, 0.5));
                node->ignoreAnchorPointForPosition(false);
                CCAssert(node != NULL, "AnimNode file class type must set be AnimNode!");
                _animationManager->setDelegate(node);
                //                node->retain(); // FIXME:(hhy) 这里会不会引起内存泄漏？
                node->_typeId = AnimNode::K_CCBI_FILE;
                node->_animationManager = _animationManager;
                node->_animationManager->retain();
                node->setAnimNodeDelegate(delegate);
                
                CC_SAFE_RELEASE_NULL(ccBReader);
                CCArray* sequences = node->_animationManager->getSequences();
                CCString * defaulAnim = (CCString *)tmpDict->objectForKey(KKeyDefault);
                if (defaulAnim) {
                    node->setDefaultAnimation(defaulAnim->m_sString);
                }
                else if(sequences && sequences->count() > 0){
                    node->setDefaultAnimation(((CCBSequence *) sequences->objectAtIndex(0))->getName());
                }
                //               node->autorelease();
            }
                break;
            case AnimNode::K_ARMATURE_FRAME:
            {
                node = new AnimNode;
                node->autorelease();
                node->_typeId = AnimNode::K_ARMATURE_FRAME;
                ArmatureAnim * _animNode = ArmatureAnim::create();
                _animNode->setAnimDelegateExt(node);
                node->_animNode = _animNode;
                node->setAnimNodeDelegate(delegate);
                std::vector<sp::ImageInfo> list;
                
                sp::ImageInfo inf;
                inf.imagePath = static_cast<CCString *>(tmpDict->objectForKey(KKeyImageTexture))->m_sString;
                inf.plistPath = static_cast<CCString *>(tmpDict->objectForKey(KKeyImagePlist))->m_sString;
                list.push_back(inf);
                
                CCString * armatureValue = (CCString *)tmpDict->objectForKey(KKeyskeleton);
                CCString * defaulAnim = (CCString *)tmpDict->objectForKey(KKeyDefault);
                
                if (defaulAnim) {
                    node->setDefaultAnimation(defaulAnim->m_sString);
                }
                
                _animNode->load(armatureValue->m_sString,list,strValue->m_sString,1.0f);
                node->addChild(_animNode);
                
                CCString * sizeVal = (CCString *)tmpDict->objectForKey(KKeySize);
                if (_animNode && sizeVal) {
                    CCSize size  = GameUtils::string2Size(sizeVal->m_sString);
                    _animNode->setMaxContentSize(CCSizeMake(size.width, size.height));
                }
                
                
                node->scheduleUpdate();
            }
                break;
                
            default:
                CCAssert(false, "AnimNode file type invalid....");
                break;
        }
        
        if (node) {
            
            if(node->_animNode){
                
                node->_animNode->setAnchorPoint(CCPoint(0.5, 0.5));
                
                if (scaleVal) {
                    node->_animScale = scaleVal->floatValue();
                    node->_animNode->setScale(node->_animScale);
                }
                
                if (flipXVal && flipXVal->boolValue()) {
                    node->_animNode->setScaleX(node->_animNode->getScaleX() * -1);
                }
            }
        }
    }
	return node;
}

void AnimNode::scaleAnim(float scale){
    float scaleVal = 1;
    if (_animNode->getScaleX() < 0) {
        scaleVal = -1;
    }
    _animNode->setScale(scale);
    _animNode->setScaleX(_animNode->getScaleX() * scaleVal);
}

const std::string  & AnimNode::getDefaultAnimation()const{
    return _defaultAnimation;
}

void AnimNode::setDefaultAnimation(const std::string  & value){
    _defaultAnimation = value;
}

void AnimNode::setAutoRemoveOnFinish(const bool autoRemoveOnFinish){
    _autoRemoveOnFinish = autoRemoveOnFinish;
}


const bool  AnimNode::runAnimation(const std::string & name,
                                   const float delay,
                                   cocos2d::CCCallFuncO * calll){
	if (_animationManager) {
        if (name.length() == 0) {
            if(_defaultAnimation.length() > 0)
                _animationManager->runAnimationsForSequenceNamedTweenDuration(_defaultAnimation.c_str(), delay);
        }
		else _animationManager->runAnimationsForSequenceNamedTweenDuration(name.c_str(), delay);
        return true;
	}
    else if(_typeId == AnimNode::K_ARMATURE_FRAME){
        _currentFrame = name;
        _currentFrame.append("_0_0");
        ArmatureAnim * anim = static_cast<ArmatureAnim * >(_animNode);
        if (name.length() == 0) {
            if(_defaultAnimation.length() > 0){
                this->setCurrentCalll(calll);
                return anim->runAnimation(_defaultAnimation);
            }
        }
        else{
            this->setCurrentCalll(calll);
            return anim->runAnimation(name);
        }
    }
    return false;
}


void AnimNode::stopAnimation(){
	if (_typeId == AnimNode::K_CCBI_FILE) {
        _animNode->stopAllActions();
    }
    else if (_typeId == AnimNode::K_ARMATURE_FRAME) {
        ArmatureAnim * anim = static_cast<ArmatureAnim * >(_animNode);
        anim->stopAnimation();
    }
    
}

void AnimNode::resumeAnimation(){
	if (_typeId == AnimNode::K_CCBI_FILE) {
        
    }
    else if (_typeId == AnimNode::K_ARMATURE_FRAME) {
        ArmatureAnim * anim = static_cast<ArmatureAnim * >(_animNode);
        anim->resumeAnimation();
    }
    
}

void AnimNode::pauseAnimation(){
	if (_typeId == AnimNode::K_CCBI_FILE) {
        _animNode->stopAllActions();
    }
    else if (_typeId == AnimNode::K_ARMATURE_FRAME) {
        ArmatureAnim * anim = static_cast<ArmatureAnim * >(_animNode);
        anim->pauseAnimation();
    }
}

void AnimNode::updateAnimFrame(float dt){
    if (_typeId == AnimNode::K_ARMATURE_FRAME){
        ArmatureAnim * anim = static_cast<ArmatureAnim * >(_animNode);
        _animNode->update(dt);
    }
}

void  AnimNode::update(float dt){
    cocos2d::CCNodeRGBA::update(dt);
    if(_autoUpdateFrame) updateAnimFrame(dt);
}

const cocos2d::CCSize & AnimNode::getContentSize(){
    if (_animNode) {
        return ((_typeId == AnimNode::K_ARMATURE_FRAME) ? static_cast<ArmatureAnim * >(_animNode)->getMaxContentSize() :_animNode->getContentSize());
    }
    return CCNode::getContentSize();
}

/**
 设置frameITScale
 */
void AnimNode::setFrameITScale(const float value){
    if (_animNode && (_typeId == AnimNode::K_ARMATURE_FRAME) ) {
        (static_cast<ArmatureAnim * >(_animNode))->setFrameITScale(value);
    }
}

#pragma mark-
#pragma mark AnimNode CCBSelectorResolver
SEL_MenuHandler AnimNode::onResolveCCBCCMenuItemSelector(CCObject * pTarget,  const char* pSelectorName){
	if (_animNodeDelegate) {
        return _animNodeDelegate->onResolveCCBCCMenuItemSelector(pTarget,pSelectorName);
    }
	return NULL;
	
}

SEL_CCControlHandler AnimNode::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName){
    if (_animNodeDelegate) {
        return _animNodeDelegate->onResolveCCBCCControlSelector(pTarget,pSelectorName);
    }
	return NULL;
}

#pragma mark-
#pragma mark AnimNode CCBMemberVariableAssigner
bool AnimNode::onAssignCCBMemberVariable(CCObject * pTarget, const char*  pMemberVariableName, CCNode * pNode){
    if (_animNodeDelegate) {
        return _animNodeDelegate->onAssignCCBMemberVariable(pTarget,pMemberVariableName,pNode);
    }
	return false;
}

#pragma mark-
#pragma mark AnimNode CCBNodeLoaderListener
void AnimNode::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader){
    if (_animNodeDelegate) {
        _animNodeDelegate->onNodeLoaded(pNode,pNodeLoader);
    }
}

#pragma mark-
#pragma mark AnimNode CCBAnimationManagerDelegate
void AnimNode::completedAnimationSequenceNamed(const char *name){
    if (_animNodeDelegate) {
        _animNodeDelegate->notifyCompletedAnimationSequenceNamed(name,false);
        if (_autoRemoveOnFinish) {
            this->stopAnimation();
            this->removeFromParentAndCleanup(true);
        }
    }
}

#pragma mark-
#pragma mark AnimNode AnimationDelegateExt
void AnimNode::onAnimationEvent(void * animation, const char * eventType, const char * movementID){
    std::string even =  eventType;
    if ((_animNodeDelegate || _currentCalll) && _animNode == animation) {
        ArmatureAnim * anim = static_cast<ArmatureAnim * >(_animNode);
        bool completed = even.compare(sp::COMPLETE) == 0;
        bool loopCompleted = even.compare(sp::LOOP_COMPLETE) == 0;
        if (completed || loopCompleted) {
            
            if(_animNodeDelegate){
                _animNodeDelegate->notifyCompletedAnimationSequenceNamed(movementID,loopCompleted);
            }
            
            if (completed) {
                if (_currentCalll) {
                    _currentCalll->execute();
                }
                else if (_autoRemoveOnFinish) {
                    this->stopAnimation();
                    this->removeFromParentAndCleanup(true);
                }
            }
        }
        else if (even.compare(sp::MOVEMENT_RUNNING) == 0){
            if (_currentFrame.compare(anim->currentFrame()) != 0) {
                
                if(_animNodeDelegate){
                    _animNodeDelegate->animationSequenceFrameChanged(this,movementID,
                                                                     _currentFrame.c_str(),
                                                                     anim->currentFrame().c_str());
                }
                _currentFrame = anim->currentFrame();
            }
            
        }
    }
}