//
//  GameBgRollView.cpp
//  motoGame
//
//  Created by xUanBing on 14-4-7.
//
//

#include "GameBgRollView.h"
#include "LayoutUtil.h"
#include "ConstansDef.h"

const static int KTagBgOne = BASE_TAG + 1;
const static int KTagBgTwo = BASE_TAG + 2;

#define  X_MOVE_SPEED     -5

GameBgRollView::GameBgRollView() {
    
}

GameBgRollView::~GameBgRollView() {
    
}

bool GameBgRollView::init() {
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSprite * bg1 = CCSprite::create("bg.jpg");
    bg1->setAnchorPoint(CCPointZero);
    this->addChild(bg1, 0, KTagBgOne);
    LayoutUtil::layoutParentLeft(bg1);
    
    CCSprite * bg2 = CCSprite::create("bg.jpg");
    bg2->setAnchorPoint(CCPointZero);
    this->addChild(bg2, 0, KTagBgTwo);
    LayoutUtil::layoutRight(bg2, bg1);
    
    this->scheduleUpdate();
    return true;
}

void GameBgRollView::update(float dt) {
    
    CCSprite * bg1 = (CCSprite *)this->getChildByTag(KTagBgOne);
    CCSprite * bg2 = (CCSprite *)this->getChildByTag(KTagBgTwo);
    
    if (bg1->getPositionX() <= -1 * bg1->getContentSize().width) {
        LayoutUtil::layoutRight(bg1, bg2, X_MOVE_SPEED);
    } else {
        bg1->setPosition(ccpAdd(bg1->getPosition(), ccp(X_MOVE_SPEED, 0)));
    }
    
    if (bg2->getPositionX() <= -1 * bg2->getContentSize().width) {
        LayoutUtil::layoutRight(bg2, bg1);
    } else {
        bg2->setPosition(ccpAdd(bg2->getPosition(), ccp(X_MOVE_SPEED, 0)));
    }

}

