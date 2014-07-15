//
//  PitObject.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-15.
//
//

#include "PitObject.h"
#include "CCScale9ProgressBar.h"
#include "CCSpriteExt.h"
#include "LayoutUtil.h"

#define TopPitOrder     1
#define MidNodeOrder    3
#define BottomPitOrder  5

#define TopPitTag       1
#define MidNodeTag      3
#define BottomPitTag    5

PitObject::PitObject() : _pit(NULL) {
    
}

PitObject::~PitObject() {
    
}

PitObject* PitObject::create() {
    PitObject* obj = new PitObject();
    
    if (obj && obj->init()) {
        obj->autorelease();
        return obj;
    } else {
        CC_SAFE_DELETE(obj);
        return NULL;
    }
    
}

bool PitObject::init() {
    
    _pit = CCSpriteExt::create("grass_pit.png");
    this->setContentSize(_pit->getContentSize());
    this->addChild(_pit);
    LayoutUtil::layoutParentBottom(_pit);
    
    return true;
}

void PitObject::addNodeToContent(cocos2d::CCNode *node) {
    
    //绘制裁剪区域
    CCDrawNode* shap = CCDrawNode::create();
    
    CCPoint point[4] = {ccp(0,0), ccp(node->getContentSize().width, 0), ccp(node->getContentSize().width, node->getContentSize().height), ccp(0, node->getContentSize().height)};
    
    shap->drawPolygon(point, 4, ccc4f(255, 100, 100, 255), 2, ccc4f(255, 255, 255, 255));
    
    CCClippingNode* cliper = CCClippingNode::create();
    cliper->setStencil(shap);
    cliper->setAnchorPoint(ccp(0, 0));
    cliper->setContentSize(node->getContentSize());
    
    cliper->addChild(node);
    
    this->addChild(cliper, MidNodeOrder, MidNodeTag);

    LayoutUtil::layoutParentBottom(cliper, 0, 30);
    LayoutUtil::layoutParentBottom(node, 0 , -90);
}

