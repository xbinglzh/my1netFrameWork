//
//  HelloView.cpp
//  motoGame
//
//  Created by xUanBing on 14-3-24.
//
//

#include "HelloView.h"

cocos2d::CCScene* UiLoadingView::scene() {
    CCScene *scene = CCScene::create();
    UiLoadingView *layer = UiLoadingView::createFromCCB();
    scene->addChild(layer);
    
    return scene;
}

UiLoadingView::UiLoadingView(){
    //    ResourceLoader::loadClassResources("XXUiLoadingView");
}

UiLoadingView::~UiLoadingView() {

    //    ResourceLoader::unloadClassResources("XXUiLoadingView");
}

UiLoadingView* UiLoadingView::createFromCCB(){
    return (UiLoadingView *)loadClassFromCCBI("XXUiLoadingView",
                                                "XXUiLoadingView.ccbi",
                                                UiLoadingViewLoader::loader(),
                                                NULL);
}

bool UiLoadingView::initWithCustom(){
    RootUiLayerWithNetwork::initWithCustom();
    
    return true;
}

void UiLoadingView::onEnterTransitionDidFinish(){
    RootUiLayerWithNetwork::onEnterTransitionDidFinish();
}


SEL_MenuHandler UiLoadingView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName){
    return NULL;
}

SEL_CCControlHandler UiLoadingView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName){
    
    return NULL;
}

bool UiLoadingView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName,  CCNode * pNode){
//    CCB_MEMBERVARIABLEASSIGNER_GLUE2(CCSprite*, bgSprite);
    return false;
}
