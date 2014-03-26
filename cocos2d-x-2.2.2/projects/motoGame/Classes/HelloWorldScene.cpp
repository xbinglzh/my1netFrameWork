#include "HelloWorldScene.h"
#include "LayoutUtil.h"
#include "CCShaderEffectSprite.h"
#include "ShaderManager.h"

#include "ArmatureAnim.h"
#include "AnimNode.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
//    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    CCShaderEffectSprite* shaderSprite = CCShaderEffectSprite::create("HelloWorld.png", ShaderManager::effect_color_gray);

    // position the sprite on the center of the screen
//    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(shaderSprite, 0);
    LayoutUtil::layoutParentLeft(shaderSprite);
    
//    std::vector<sp::ImageInfo> list;
//    
//    sp::ImageInfo image;
//    image.imagePath = "xx_m_100041.png";
//    image.plistPath = "xx_m_100041.plist";
//    list.push_back(image);
//    
//    ArmatureAnim* anim = ArmatureAnim::create();
//    anim->load("xx_m_100041", list, "xx_m_100041.xml",1.0f);
//    anim->runAnimation("walk");
    
    AnimNode* anim = AnimNode::createFlashAnimNode("xx_m_100041.png", "xx_m_100041.plist", "xx_m_100041.xml",
                                                   "walk", "xx_m_100041");
    anim->runAnimation("walk");
    this->addChild(anim, 1001);
    anim->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
