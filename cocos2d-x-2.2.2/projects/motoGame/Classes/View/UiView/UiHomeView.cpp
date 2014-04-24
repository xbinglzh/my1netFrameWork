//
//  UiHomeView.cpp
//  motoGame
//
//  Created by xUanBing on 14-4-20.
//
//

#include "UiHomeView.h"

UiHomeView::UiHomeView() {
    
}

UiHomeView::~UiHomeView() {
    
}

UiHomeView* UiHomeView::createFromCCB() {
    return (UiHomeView *)loadClassFromCCBI("UiHomeView",
                                              "XXUiHomeView.ccbi",
                                              UiHomeViewLoader::loader(),
                                              NULL);
}

bool UiHomeView::initWithCustom() {
    RootUiLayerWithNetwork::initWithCustom();
    
    return true;
}

void UiHomeView::onEnterTransitionDidFinish(){
    RootUiLayerWithNetwork::onEnterTransitionDidFinish();
}

SEL_MenuHandler UiHomeView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE2(UiHomeView, onNewGameCallBack);
    
    return NULL;
}

SEL_CCControlHandler UiHomeView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;
}

bool UiHomeView::onAssignCCBMemberVariable(CCObject * pTarget, const char *pMemberVariableName, CCNode * pNode) {
    
    return false;
}

void UiHomeView::onNewGameCallBack() {
    int i = 0;
}
