#include "MainLayer.h"

USING_NS_CC;


enum ImgState {
	img_bgtag_one,
	img_bgtag_two,
};

bool MainLayer::init(){
	if( !CCLayer::init()){
		return false;
	}
	steupView("bg.jpg");
	return true;
}
CCScene* MainLayer::scene(){
	CCScene* sc = CCScene::create();
	MainLayer* layer = MainLayer::create();
	sc->addChild(layer);
	return sc;
}

void MainLayer::steupView(const char* fileName){
	 CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //创建两张图片精灵来回切换
    CCSprite * turnImg1 = CCSprite::create(fileName);
    turnImg1->setPosition(CCPointMake(turnImg1->getContentSize().width/2, turnImg1->getContentSize().height/2));
    this->addChild(turnImg1,0,img_bgtag_one);
    
    CCSprite * turnImg2 = CCSprite::create(fileName);
    turnImg2->setPosition(CCPointMake(turnImg2->getContentSize().width * 1.5, turnImg2->getContentSize().height /2));
    this->addChild(turnImg2,0,img_bgtag_two);
    
    //启动定时器来实现两张背景图片的循环交叉滚动
    this->scheduleUpdate();
}
void MainLayer::update(float t){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite * sp1 = (CCSprite *)this->getChildByTag(img_bgtag_one);
    //如果第一张背景图的中点到达屏幕下方背景图高度的一半的时候(也就是第一张图片移除图片下面的时候)重新设置他的位置到屏幕上面，图片下边缘跟手机屏幕上边缘重合-1个像素
    if (sp1->getPositionX()<=-sp1->getContentSize().width/2) {
        sp1->setPosition(CCPointMake(sp1->getContentSize().width * 1.5f -1 , sp1->getContentSize().height/2));
    }
    //如果还没需要换位置就让他向下移动一个像素
    else
    {
        sp1->setPosition(ccpAdd(sp1->getPosition(), ccp(-1,0)));
    }
    
    CCSprite * sp2 = (CCSprite *)this->getChildByTag(img_bgtag_two);
    //如果第二张背景图移出屏幕最下方则重新设置他的位置在屏幕的最上方
    if (sp2->getPositionX() <= -sp2->getContentSize().width / 2) {
        sp2->setPosition(CCPointMake(sp2->getContentSize().width * 1.5f -1, sp2->getContentSize().height / 2));
    }
    //向下移动
    else{
        sp2->setPosition(ccpAdd(sp2->getPosition(), ccp(-1,0)));
    }
}