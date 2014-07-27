//
//  BattleUiView.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-27.
//
//

#include "BattleUiView.h"
#include "LayoutUtil.h"

BattleUiView::BattleUiView() :
_blazeButton(NULL),
_thunderButton(NULL),
_levelbg(NULL),
_crystalBg(NULL),
_scroeBg(NULL),
_skillControlButton(NULL),
_toxicantButton(NULL),
_isSkillControllButtonOpen(true) {
    
}

BattleUiView::~BattleUiView() {
    
    CC_SAFE_RELEASE_NULL(_blazeButton);
    CC_SAFE_RELEASE_NULL(_thunderButton);
    CC_SAFE_RELEASE_NULL(_levelbg);
    CC_SAFE_RELEASE_NULL(_crystalBg);
    CC_SAFE_RELEASE_NULL(_scroeBg);
    CC_SAFE_RELEASE_NULL(_skillControlButton);
    CC_SAFE_RELEASE_NULL(_toxicantButton);
    
}

BattleUiView* BattleUiView::createFromCCB() {
    return (BattleUiView *)loadClassFromCCBI("BattleUiView", "BattleUiView.ccbi",
        BattleUiViewLoader::loader(), NULL);
}

void  BattleUiView::onEnterTransitionDidFinish() {
    
}

bool BattleUiView::initWithCustom() {
    _toxicantPos = _toxicantButton->getPosition();
    _blazePos = _blazeButton->getPosition();
    _thunderPos = _thunderButton->getPosition();
    
    this->setTouchEnabled(true);
    
    return true;
}

SEL_MenuHandler BattleUiView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE2(BattleUiView, onSkillControlButtonCallBack);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE2(BattleUiView, onToxicantButtonCallBack);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE2(BattleUiView, onThunderButtonCallBack);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE2(BattleUiView, onBlazeButtonCallBack);
    
    return NULL;
}

SEL_CCControlHandler BattleUiView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    
    return NULL;
}

bool BattleUiView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName,  CCNode * pNode) {
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCSprite*, levelbg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCSprite*, crystalBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCSprite*, scroeBg);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCMenuItem*, skillControlButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCMenuItem*, toxicantButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCMenuItem*, blazeButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCMenuItem*, thunderButton);
    
    return false;
}

void BattleUiView::onSkillControlButtonCallBack() {
    
    if (_isSkillControllButtonOpen) {
        closeSkillButton();
    } else {
        openSkillButton();
    }
    
}

void BattleUiView::onToxicantButtonCallBack() {
    
}

void BattleUiView::onThunderButtonCallBack() {
    
}

void BattleUiView::onBlazeButtonCallBack() {
    
}

void BattleUiView::openSkillButton() {
    
    CCCallFuncO* endFun = CCCallFuncO::create(this, callfuncO_selector(BattleUiView::setSkillControllButtonOpenFalg), CCInteger::create(1));
    
    CCMoveTo* toxicantMove = CCMoveTo::create(0.3f, _toxicantPos);
    _toxicantButton->runAction(toxicantMove);
    
    CCMoveTo* blazeMove = CCMoveTo::create(0.3f,_blazePos);
    _blazeButton->runAction(blazeMove);
    
    CCMoveTo* thunderMove = CCMoveTo::create(0.3f,_thunderPos);
    _thunderButton->runAction(CCSequence::create(thunderMove, endFun, NULL));
    
    CCRotateBy* rotateAction = CCRotateBy::create(-45, 0.2f);
    _skillControlButton->runAction(rotateAction);

}

void BattleUiView::closeSkillButton() {
    
    CCPoint endPos = CCPointMake(_toxicantButton->getParent()->getContentSize().width + 20, -20);
    
    CCCallFuncO* endFun = CCCallFuncO::create(this, callfuncO_selector(BattleUiView::setSkillControllButtonOpenFalg), CCInteger::create(0));
    
    CCMoveTo* toxicantMove = CCMoveTo::create(0.3f, endPos);
    _toxicantButton->runAction(toxicantMove);
    
    CCMoveTo* blazeMove = CCMoveTo::create(0.3f, endPos);
    _blazeButton->runAction(blazeMove);
  
    CCMoveTo* thunderMove = CCMoveTo::create(0.3f, endPos);
    _thunderButton->runAction(CCSequence::create(thunderMove, endFun, NULL));
    
    CCRotateBy* rotateAction = CCRotateBy::create(0.2f, 45);

    _skillControlButton->runAction(rotateAction);
    
}

void BattleUiView::setSkillControllButtonOpenFalg(cocos2d::CCInteger *obj) {
    _isSkillControllButtonOpen = obj->getValue() == 1 ? true : false;
}

void BattleUiView::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, getTouchPriority(), false);
}

bool BattleUiView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    
    return true;
}

void BattleUiView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    
}

void BattleUiView::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    
}

void BattleUiView::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    
}




