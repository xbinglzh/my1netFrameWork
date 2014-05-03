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
#include "CCSpriteExt.h"

const static int KTagBgOne = BASE_TAG + 1;
const static int KTagBgTwo = BASE_TAG + 2;

#define  X_MOVE_SPEED     -2

GameBgRollView::GameBgRollView(): _moveSpeed(X_MOVE_SPEED) {
    
}

GameBgRollView::~GameBgRollView() {
    
}

bool GameBgRollView::init() {
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSpriteExt * bg1 = CCSpriteExt::create("back_5.png");
    bg1->setAnchorPoint(CCPointZero);
    this->addChild(bg1, 0, KTagBgOne);
    bg1->setScaleX(this->getContentSize().width / bg1->getContentSize().width);
//    LayoutUtil::layoutParentLeft(bg1);
    LayoutUtil::layoutParentBottomLeft(bg1);
    
    CCSpriteExt * bg2 = CCSpriteExt::create("back_5.png");
    bg2->setAnchorPoint(CCPointZero);
    this->addChild(bg2, 0, KTagBgTwo);
    bg2->setScaleX(this->getContentSize().width / bg2->getContentSize().width);
//    LayoutUtil::layoutRight(bg2, bg1);
    LayoutUtil::layoutBottomRight(bg2, bg1);
    
    this->scheduleUpdate();
    return true;
}

void GameBgRollView::setMoveSpeed(float speed) {
    this->_moveSpeed = speed * -1;
}

void GameBgRollView::update(float dt) {
    
    CCSprite * bg1 = (CCSprite *)this->getChildByTag(KTagBgOne);
    CCSprite * bg2 = (CCSprite *)this->getChildByTag(KTagBgTwo);
    
    if (bg1->getPositionX() <= -1 * bg1->getContentSize().width * (this->getContentSize().width / bg1->getContentSize().width)) {
        LayoutUtil::layoutRight(bg1, bg2, _moveSpeed);
    } else {
        bg1->setPosition(ccpAdd(bg1->getPosition(), ccp(_moveSpeed, 0)));
    }
    
    if (bg2->getPositionX() <= -1 * bg2->getContentSize().width * (this->getContentSize().width / bg2->getContentSize().width)) {
        LayoutUtil::layoutRight(bg2, bg1, _moveSpeed);
    } else {
        bg2->setPosition(ccpAdd(bg2->getPosition(), ccp(_moveSpeed, 0)));
    }

}

