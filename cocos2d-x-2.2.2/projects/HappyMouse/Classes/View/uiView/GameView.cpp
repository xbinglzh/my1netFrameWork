//
//  GameView.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-15.
//
//

#include "GameView.h"
#include "CCSpriteExt.h"
#include "LayoutUtil.h"

GameView::GameView() : _bg(NULL) {
    
}

GameView::~GameView() {
    
}

GameView* GameView::create() {
    
    GameView* pRet = new GameView();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
    
}

bool GameView::init() {
    this->setAnchorPoint(CCPointZero);
    CCSprite* bg = CCSprite::create("xmap_back_grass.png");
    this->addChild(bg);
//    LayoutUtil::layoutParentBottom(_bg);
    
    
    return true;
}

bool GameView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {

    return true;
}

void GameView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    
}

void GameView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    
}

void GameView::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {
    
}
