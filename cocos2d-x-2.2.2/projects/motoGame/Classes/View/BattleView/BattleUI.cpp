//
//  BattleUI.cpp
//  motoGame
//
//  Created by xUanBing on 14-5-1.
//
//

#include "BattleUI.h"
#include "LayoutUtil.h"
#include "CCScale9ProgressBar.h"
#include "CCSpriteExt.h"

BattleUI::BattleUI() : _powerNode(NULL), _scoreNode(NULL), _powerBar(NULL), _powerBg(NULL){
    
}

BattleUI::~BattleUI() {
    CC_SAFE_RELEASE_NULL(_powerNode);
    CC_SAFE_RELEASE_NULL(_scoreNode);
}

BattleUI* BattleUI::createFromCCB() {
    return (BattleUI *)loadClassFromCCBI("BattleUI","BattleUI.ccbi",
                                           BattleUILoader::loader(), NULL);
}

bool BattleUI::initWithCustom() {
    RootUiLayer::initWithCustom();
    
    _powerBg = CCScale9Sprite::create("bar_bg.png");
    _powerBar = CCScale9ProgressBar::create("bar_fg.png");
    
    _powerBg->setContentSize(CCSizeMake(500, _powerBg->getContentSize().height));
    _powerBar->setContentSize(CCSizeMake(500, _powerBar->getContentSize().height));
    
    _powerBg->addChild(_powerBar);
    LayoutUtil::layoutParentCenter(_powerBar);
    
    _powerNode->addChild(_powerBg);
    LayoutUtil::layoutParentCenter(_powerBg);
    
    _powerBar->setVisibleRatio(0.56f);
    
    return true;
}

SEL_MenuHandler BattleUI::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;
}

SEL_CCControlHandler BattleUI::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;
}

bool BattleUI::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName,  CCNode * pNode) {
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCNode*, powerNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCNode*, scoreNode);
    
    return false;
}




