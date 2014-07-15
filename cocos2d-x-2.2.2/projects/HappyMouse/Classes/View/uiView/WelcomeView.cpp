//
//  WelcomeView.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-15.
//
//

#include "WelcomeView.h"

WelcomeView::WelcomeView() {
    
}

WelcomeView::~WelcomeView() {
    
}

WelcomeView* WelcomeView::createFromCCB() {
    
    return (WelcomeView *)loadClassFromCCBI("WelcomeView", "WelcomeView.ccbi",
             WelcomeViewLoader::loader(), NULL);
    
}

void WelcomeView::onEnterTransitionDidFinish() {
    
}

bool WelcomeView::initWithCustom() {
    
    return true;
}

SEL_MenuHandler WelcomeView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName){
    
    return NULL;
}

SEL_CCControlHandler WelcomeView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName){
    
    return NULL;
}

bool WelcomeView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName,  CCNode * pNode){
    //    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCSprite*, bgSprite);
    return false;
}