//
//  GameResultView.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-13.
//
//

#include "GameResultView.h"
#include "LayoutUtil.h"

GameResultView::GameResultView() :_winResultNode(NULL), _loseResultNode(NULL), _dialog(NULL) {
    
}

GameResultView::~GameResultView() {
    CC_SAFE_RELEASE_NULL(_winResultNode);
    CC_SAFE_RELEASE_NULL(_loseResultNode);
}

GameResultView* GameResultView::createFromCCB() {
    return (GameResultView *)loadClassFromCCBI( "GameResultView", "GameResultView.ccbi",
                                            GameResultViewLoader::loader(), NULL);
}

bool GameResultView::initWithCustom() {
    
    return true;
}


SEL_MenuHandler GameResultView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName){
    
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE2(WelcomeView, onStartBtnClickCallBack);
    
    return NULL;
}

SEL_CCControlHandler GameResultView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName){
    
    return NULL;
}

bool GameResultView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName,  CCNode * pNode){
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCNode*, winResultNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCNode*, loseResultNode);
    return false;
}

void GameResultView::show() {
    if (!_dialog) {
        _dialog = ModelDialog::create();
        _dialog->addChild(this);
        LayoutUtil::layoutParentCenter(this);
        _dialog->show();
    }
}

void GameResultView::hide() {
    if (_dialog) {
        _dialog->dismiss();
    }
}

