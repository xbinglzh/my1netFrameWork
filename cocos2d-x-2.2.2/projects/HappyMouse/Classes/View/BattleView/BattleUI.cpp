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
#include "NotifyMessageDef.h"
#include "GameModel.h"
#include "LabelView.h"
#include "FontStylesDef.h"
#include "GameUtils.h"

BattleUI::BattleUI() : _powerNode(NULL), _scoreNode(NULL), _powerBar(NULL), _powerBg(NULL), _scoreLable(NULL), _scoreNameNode(NULL), _scoreLableNode(NULL){
    
}

BattleUI::~BattleUI() {
    CC_SAFE_RELEASE_NULL(_powerNode);
    CC_SAFE_RELEASE_NULL(_scoreNode);
    CC_SAFE_RELEASE_NULL(_scoreNameNode);
    CC_SAFE_RELEASE_NULL(_scoreLableNode);
    
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

BattleUI* BattleUI::createFromCCB() {
    return (BattleUI *)loadClassFromCCBI("BattleUI","BattleUI.ccbi",
                                           BattleUILoader::loader(), NULL);
}

bool BattleUI::initWithCustom() {
    RootUiLayer::initWithCustom();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(BattleUI::onNotifyEnergyValueChangeMessage),KNotifyEnergyChangeMessage, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(BattleUI::onNotifyGameScoreChangeMessage), KNotifyGameScoreChangeMessage, NULL);
    
    _powerBg = CCScale9Sprite::create("bar_bg.png");
    _powerBar = CCScale9ProgressBar::create("bar_fg.png");
    
    _powerBg->setContentSize(CCSizeMake(500, _powerBg->getContentSize().height));
    _powerBar->setContentSize(CCSizeMake(500, _powerBar->getContentSize().height));
    
    _powerBg->addChild(_powerBar);
    LayoutUtil::layoutParentCenter(_powerBar);
    
    _powerNode->addChild(_powerBg);
    LayoutUtil::layoutParentCenter(_powerBg);
    
    _powerBar->setVisibleRatio(GameModel::sharedInstance()->getEnergyRatio());
    
    _scoreLable = LabelView::createWithFontStyle("0", kFontSytle_45_YELLOWE_BLACK, _scoreNameNode->getContentSize());
    _scoreLableNode->addChild(_scoreLable);
    LayoutUtil::layoutParentCenter(_scoreLable);
    
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
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCNode*, scoreNameNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCNode*, scoreLableNode);
    
    return false;
}

void BattleUI::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, getTouchPriority(), false);
}

bool BattleUI::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    
    
    return CCLayer::ccTouchBegan(pTouch, pEvent);
}

void BattleUI::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    CCLayer::ccTouchEnded(pTouch, pEvent);
}

void BattleUI::onNotifyEnergyValueChangeMessage(cocos2d::CCObject *pSender) {
    _powerBar->setVisibleRatio(GameModel::sharedInstance()->getEnergyRatio());
}

void BattleUI::onNotifyGameScoreChangeMessage(cocos2d::CCObject *pSender) {
    float score = GameModel::sharedInstance()->getGameScore();
    _scoreLable->setString(GameUtils::StringMake(score).c_str());
}


