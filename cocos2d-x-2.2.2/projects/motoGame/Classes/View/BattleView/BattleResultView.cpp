//
//  BattleResultView.cpp
//  motoGame
//
//  Created by xUanBing on 14-5-4.
//
//

#include "BattleResultView.h"
#include "LabelView.h"
#include "FontStylesDef.h"
#include "GameUtils.h"
#include "ModelDialog.h"

BattleResultView::BattleResultView() : _restartButton(NULL), _scoreNode(NULL) {
    
}

BattleResultView::~BattleResultView() {
    CC_SAFE_RELEASE_NULL(_restartButton);
    CC_SAFE_RELEASE_NULL(_scoreNode);
}

BattleResultView* BattleResultView::show(const battle::Rewards &reward, const BattleResultCallback& callback) {
    BattleResultView* resultView = BattleResultView::createFromCCB();
    resultView->fillData(reward);
    resultView->setCallback(callback);
    
    return resultView;
}

BattleResultView* BattleResultView::createFromCCB() {
    return (BattleResultView *)loadClassFromCCBI("BattleResultView","BattleResultView.ccbi",
                                         BattleResultViewLoader::loader(), NULL);
}


bool BattleResultView::initWithCustom() {
    
    _score= LabelView::createWithFontStyle("0", kFontSytle_45_YELLOWE_BLACK, _scoreNode->getContentSize());
    
    return true;
}

void BattleResultView::fillData(const battle::Rewards &rewards) {
    
    _score->setString(GameUtils::StringMake(rewards.score).c_str());
}

SEL_MenuHandler BattleResultView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE2(BattleResultView, onRestartButtonCallBack);
    
    return NULL;
}

SEL_CCControlHandler BattleResultView::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName) {
    
    return NULL;
}

bool BattleResultView::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode) {
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCNode*, scoreNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCMenuItem*, restartButton);
    
    return false;
}

void BattleResultView::onRestartButtonCallBack() {
    
}