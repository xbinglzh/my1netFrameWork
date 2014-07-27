//
//  BattleUiView.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-27.
//
//

#ifndef __HappyMouse__BattleUiView__
#define __HappyMouse__BattleUiView__

#include "cocos2d.h"
#include "RootUiLayer.h"

USING_NS_CC;

class BattleUiView : public RootUiLayer {
    
public:
    BattleUiView();
    virtual ~BattleUiView();
    CREATE_FUNC(BattleUiView);
    static BattleUiView * createFromCCB();
    
public:
    virtual void onEnterTransitionDidFinish();
    
protected:
    virtual bool initWithCustom();
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName,  CCNode * pNode);
    
private:
    void onSkillControlButtonCallBack();
    void onToxicantButtonCallBack();
    void onBlazeButtonCallBack();
    void onThunderButtonCallBack();
    
private:
    void openSkillButton();
    void closeSkillButton();
    void setSkillControllButtonOpenFalg(CCInteger* obj);
    
private:
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    CCMenuItem*  _skillControlButton;
    CCMenuItem*  _toxicantButton;
    CCMenuItem*  _blazeButton;
    CCMenuItem*  _thunderButton;
    
    CCSprite*    _levelbg;
    CCSprite*    _crystalBg;
    CCSprite*    _scroeBg;
    
    bool         _isSkillControllButtonOpen;
    
    CCPoint      _toxicantPos;
    CCPoint      _blazePos;
    CCPoint      _thunderPos;
    
};

CREATE_NEW_INHERIT_CCLAYERLOADER_CLASS(BattleUiView);

#endif /* defined(__HappyMouse__BattleUiView__) */
