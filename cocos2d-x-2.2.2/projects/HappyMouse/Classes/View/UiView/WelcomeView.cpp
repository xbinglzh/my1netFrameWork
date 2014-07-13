//
//  WelcomeView.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-13.
//
//

#include "WelcomeView.h"
#include "LayoutUtil.h"
#include "LabelView.h"
#include "GameResultView.h"

USING_NS_CC;

WelcomeView::WelcomeView() : _startBtn(NULL),_view(NULL) {
    
}

WelcomeView::~WelcomeView() {
    CC_SAFE_RELEASE_NULL(_startBtn);
    CC_SAFE_RELEASE_NULL(_view);
}

WelcomeView* WelcomeView::createFromCCB() {
    return (WelcomeView *)loadClassFromCCBI( "WelcomeView", "WelcomeView.ccbi",
            WelcomeViewLoader::loader(), NULL);
}

bool WelcomeView::initWithCustom() {
    _view = GameResultView::createFromCCB();
    
    return true;
}

void WelcomeView::onStartBtnClickCallBack() {
    _view->show();
}


SEL_MenuHandler WelcomeView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName){
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE2(WelcomeView, onStartBtnClickCallBack);
    
    return NULL;
}

SEL_CCControlHandler WelcomeView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName){
    
    return NULL;
}

bool WelcomeView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName,  CCNode * pNode){
    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCMenuItem*, startBtn);
    return false;
}


