//
//  GameModel.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#ifndef __HappyMouse__GameModel__
#define __HappyMouse__GameModel__

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <deque>

#include "cocos2d.h"
#include "ConstansDef.h"
#include "KeyConfigDef.h"
#include "GameObject.h"
#include "GameConfig.h"
#include "StateFactory.h"
#include "AudioManager.h"

USING_NS_CC;

class GameModel : public cocos2d::CCObject {

protected:
	GameModel();
	virtual ~GameModel();
	bool init(void);
    
public:
    static GameModel *sharedInstance(void);
    static void purgeInstance(void);
    
    /**
     战斗场景业务逻辑循环
     */
	void update(float dt);
    
public: /*战斗部分*/
    /**
     重置战斗场景
     */
	void resetBattlelayer(cocos2d::CCLayer * battlelayer);
    
    void addChildToGroundMap(cocos2d::CCNode *child, int zOrder = 0,
                             int tag = -1);
    /**
     清理置战斗场景－非资源数据
     */
	void clearCache();
    void clearGameObjects();
    /**
     初始化战斗场景资源
     */
	void loadResoure(const boost::function<void ()> &finishCallback);
    /**
     释放战斗场景资源
     */
	void unloadResoure();
    
public: /* GameObject */
    /**
     依照ID生成一个使用pTemplateDict初始化的GameObject
     */
	GameObject * generateById(const uint32_t pid);
    /**
     依照typeId返回所有相关的gameobject
     */
    cocos2d::CCSet * getGameObjectsInBattleAllStates(const std::set<int> & idTypes);
    cocos2d::CCSet * getGameObjectsInBattleWithStates(const std::set<int> & idTypes,
                                                      const std::set<int> & states);
    
    /**
     在GameObject * obj上面播放一个特效，并且在结束的时候执行action
     */
	void playEffect(const char * effectId,
                    cocos2d::CCNode * effectParent,
                    GameObject * obj,
                    const cocos2d::CCPoint & pos,
                    cocos2d::CCDictionary *pDict = NULL,
                    cocos2d::CCAction * action = NULL);
    
    /**
     在effectParent上面播放一个特效，并且在结束的时候执行action
     */
	void playEffectById(const char * effectId,
                        cocos2d::CCNode * effectParent,
                        const cocos2d::CCPoint & pos,
                        cocos2d::CCAction * action = NULL);
    
    /**
     添加一个游戏对象到战斗场景,返回加入到那个set
     */
    cocos2d::CCSet * addGameObjectToBattle(GameObject * obj);
    cocos2d::CCSet * findGameObjectsInBattle(const int32_t gid);
    
    /**
     从战斗场景去除一个节点
     */
	void removeGameObjectFromBattle(GameObject * node);
    
    /**
     broadcast to game objects
     */
    void broadcast(const uint32_t typeId,GameEventParams * params);
    
    /**
     部署一个角色对象
     */
    void putGameObject(GameObject* batteObj);
    
    
public: /* Map */
    /**
     布置基地
     */
    void loadMap(const int32_t Id);
    /**
     获得某个兵当前在地图上的位置
     */
    const cocos2d::CCPoint getPositionByIndex(const std::list<int>::const_iterator& index);
    const cocos2d::CCPoint getPositionByIndex(int index);
    
    /**
     获得当前地图
     */
//    GroundMap* getGroundMap();
    
protected:
    /**
     关卡加载资源成功
     */
    void didFinishedLoadingResources(const boost::function<void ()> &finishCallback);
    
private:
	cocos2d::CCDirector          * _director;
	GameConfig                   * _gameConfig;
    StateFactory                 * _stateFactory;
    AudioManager                 * _sharedAudioManager;
    
    cocos2d::CCDictionary        * _gameObjectsDict;
    
};


#endif /* defined(__HappyMouse__GameModel__) */
