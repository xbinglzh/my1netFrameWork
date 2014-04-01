//
//  RollBgView.cpp
//  motoGame
//
//  Created by xUanBing on 14-3-30.
//
//

#include "RollBgView.h"
#include "LayoutUtil.h"
#include "AnimNode.h"

const static int KTagBgOne = 1001;
const static int KTagBgTwo = 1002;

#define  X_MOVE_SPEED -5

RollBgView::RollBgView() {
    
}

RollBgView::~RollBgView() {
    
}


bool RollBgView::init() {
    if(!CCLayer::init()){
		return false;
	}

    CCSprite * bg1 = CCSprite::create("bg.jpg");
    bg1->setAnchorPoint(CCPointZero);
    this->addChild(bg1, 0, KTagBgOne);
    LayoutUtil::layoutParentLeft(bg1);
    
    AnimNode* anim = AnimNode::createFlashAnimNode("xx_m_204601d.png", "xx_m_204601d.plist", "xx_m_204601d.xml",
                                                   "walk", "xx_m_204601d");
    anim->setContentSize(CCSize(256, 256));
    anim->runAnimation("walk");
    anim->setAnchorPoint(CCPointZero);
    bg1->addChild(anim, 1001);
    LayoutUtil::layoutParentLeft(anim, 800, 0);
    
    CCSprite * bg2 = CCSprite::create("bg.jpg");
    bg2->setAnchorPoint(CCPointZero);
    this->addChild(bg2, 0, KTagBgTwo);
    LayoutUtil::layoutRight(bg2, bg1);

    this->scheduleUpdate();
    
	return true;
}

void RollBgView::update(float t) {
    
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

