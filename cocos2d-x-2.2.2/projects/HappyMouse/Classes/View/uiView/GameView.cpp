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
#include "GameController.h"
#include "GameConfig.h"

#define Pit_Node_Tag    1001
#define Mouse_Node_Tag  1002

#define PitBaseTag      2000
#define MouseBaseTag    3000

#define PaddingWidth    80
#define PaddingHeight   20

GameView::GameView() : _bg(NULL), _pitNode(NULL), _mouseNode(NULL) {
    
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
    
    this->setContentSize(CCSizeMake(CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().width, CCDirector::sharedDirector()->getOpenGLView()->getFrameSize().height));
    this->setAnchorPoint(CCPointZero);
    
    _bg = CCSpriteExt::create("xmap_back_grass.png");
    _bg->setScaleX(this->getContentSize().width / _bg->getContentSize().width);
    _bg->setScaleY(this->getContentSize().height / _bg->getContentSize().height);
    
    this->addChild(_bg);
    _bg->setAnchorPoint(CCPointZero);
    LayoutUtil::layoutParentBottom(_bg);
    
    _pitNode = CCNode::create();
    this->addChild(_pitNode, 2, Pit_Node_Tag);
    
    _mouseNode = CCNode::create();
    this->addChild(_mouseNode, 3, Mouse_Node_Tag);
    
    initPitData();
    
    LayoutUtil::layoutParentCenter(_pitNode, 100, 0);
    LayoutUtil::layoutParentCenter(_mouseNode);
    
    this->scheduleUpdate();
    
    return true;
}

void GameView::initPitData() {
    float pitWidth  = 0;
    float pitHeight = 0;
    
    for (int i = 0; i < GameConfig::sharedInstance()->getPitNumCount(); i++) {
        CCSpriteExt* pit = CCSpriteExt::create("grass_pit.png");
        _pitNode->addChild(pit, 1, PitBaseTag + i);
        
        pitWidth = pit->getContentSize().width + PaddingWidth;
        pitHeight = pit->getContentSize().height +PaddingHeight;
        
    }
    
    _pitNode->setContentSize(CCSizeMake(3 * (pitWidth + PaddingWidth), 3 * (PaddingHeight + pitHeight)));

    for (int i = 0; i < GameConfig::sharedInstance()->getPitNumCount(); i++) {
        LayoutUtil::layoutParentTopLeft(_pitNode->getChildByTag(PitBaseTag + i), (pitWidth+PaddingWidth)*(i % 3), -1 *(pitHeight + PaddingHeight) * (i / 3));
    }
    
    initMouseData();
}

void GameView::initMouseData() {
    
    for (int i = 0; i < GameConfig::sharedInstance()->getPitNumCount(); i++) {
        CCSpriteExt* mouse = CCSpriteExt::create("mouse1.png");
        _pitNode->addChild(mouse, 2, MouseBaseTag + i);
        
        LayoutUtil::layoutCenter(mouse, _pitNode->getChildByTag(PitBaseTag + i), 0, 50);
    }
}

void GameView::update(float dt) {
    GameController::getInstance()->update(dt);
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
