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
#include "LablePngFont.h"

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
    
    AnimNode* hero = AnimUtils::createAnimById("100002#display",NULL);
    hero->runAnimation("injured");
//    hero->setContentSize(CCSizeMake(139, 264));
    this->addChild(hero,1000);
    
    LayoutUtil::layoutParentCenter(hero);
    
    testLablePngFont();
    
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

void WelcomeView::testLablePngFont() {
    
    const char* map[] = {
        
        "0", "score_0.png",
        "1", "score_1.png",
        "2", "score_2.png",
        "3", "score_3.png",
        "4", "score_4.png",
        "5", "score_5.png",
        "6", "score_6.png",
        "7", "score_7.png",
        "8", "score_8.png",
        "9", "score_9.png"
    };
    
    std::vector<const char*> mm(map, map+sizeof(map)/sizeof(map[0]));
    LablePngFont* mylabel = LablePngFont::create("score", 10, mm, .9f);
    mylabel->setString("50");
    mylabel->setScale(1.5f);
    
    this->addChild(mylabel,10000, 10);
    LayoutUtil::layoutParentCenter(mylabel);
}

