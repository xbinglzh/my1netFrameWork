//
//  SceneController.h
//  motoGame
//
//  Created by xUanBing on 14-3-30.
//
//

#ifndef __motoGame__SceneController__
#define __motoGame__SceneController__

#include "cocos2d.h"
#include "ConstansDef.h"
#include <deque>

USING_NS_CC;

class SceneController : public cocos2d::CCObject, public cocos2d::CCDirectorDelegate{
    
protected:
	SceneController();
	virtual ~SceneController();
    
public:
    static SceneController *getInstance(void);
    static void purgeInstance(void);
	bool init(void);
    
    void clearUserView();
    
public:
    
    enum SwitchOption {
        SwitchOptionRoot = 0,       /* 替换Root */
        SwitchOptionPush = 1,       /* 压入 */
        SwitchOptionReplace = 2,    /* 替换 */
    };
    
    void switchSence(const ESceneId sceneId,
                     cocos2d::CCObject* param = NULL,
                     const SwitchOption option = SwitchOptionRoot);
    
    
    const bool backToScene();
    void backToRootScene(); 
    void switchBgMusic(const ESceneId sceneId);
    
    ESceneId getCurrentSceneId();
    
protected:
    virtual void updateProjection(void);
    virtual void updateScene(cocos2d::CCScene* scene);
    
private:
    cocos2d::CCDirector* _director;
    ESceneId        _currentSceneId;
    ESceneId        _currentRunningSceneId;
    std::deque<int32_t> _sceneQueue;
    int32_t             _bgMusicId;
};

#endif /* defined(__motoGame__SceneController__) */
