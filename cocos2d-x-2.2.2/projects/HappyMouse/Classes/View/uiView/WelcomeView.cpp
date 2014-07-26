//
//  WelcomeView.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-15.
//
//

#include "WelcomeView.h"
#include "LayoutUtil.h"
#include "AnimUtils.h"

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
    
//    AnimNode* hero = AnimNode::createFlashAnimNode( "xx_monster_1001.png", "xx_monster_1001.plist", "xx_monster_1001.xml",
//                                                   "walk", "xx_monster_1001");
    
    AnimNode* hero = AnimUtils::createAnimById("204201#display",NULL);
    hero->runAnimation("injured");
//    hero->setContentSize(CCSizeMake(139, 264));
    this->addChild(hero,1000);
    
    LayoutUtil::layoutParentCenter(hero);
    
    
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