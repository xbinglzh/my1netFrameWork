//
//  Role.h
//  MetalWar
//
//  Created by huang.haiyang on 12-8-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef MetalWar_Role_h
#define MetalWar_Role_h

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/mpl/vector/vector30.hpp>
#include <boost/variant.hpp>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "slave.h"
#include "map.h"
#include "props.h"
#include "card.h"
#include "base.h"
#include "jxp.h"
#include "luck.h"
#include "arena.h"
#include "cashcow.h"

namespace role {
    
    struct InitialFinished {
        
    };
        
    struct RefreshGold {
        int32_t golden;
    };
    
    struct RefreshSilver {
        int32_t silver;
    };
    
    struct NotifyLevelUp {
        int32_t level;
    };

    struct RefreshExecution {
        int32_t execution;
    };
    
    struct UpdateDefensePoints {
        int32_t pts;
    };
    
    struct UpdateExperiencePoints {
        int32_t pts;
    };

    struct UpdateAchievementPoints {
        int32_t pts;
    };
    
    struct UpdateFriendshipPoints {
        int32_t pts;
    };
    
    struct UpdateSingleInstanceLevel {
        int32_t level;
    };
    
    struct UpdateMultipleInstanceLevel {
        int32_t level;
    };
    
    struct UpdateRequestHelpUsage {
        int32_t maxUsage;
        int32_t currentUsage;
    };
    
    struct UpdateStoryLevel {
        int32_t level;
    };
    
    struct UpdateLeftTownAttackTimes {
        int32_t leftFreeTimes;
        int32_t leftPayedTimes;
    };
    
    struct UpdateLeftSPVETimes {
        int32_t leftFreeTimes;
        int32_t leftPayedTimes;
    };
    
    struct UpdateLeftMPVETimes {
        int32_t leftFreeTimes;
        int32_t leftPayedTimes;
    };
    
    struct UpdateSetupMap {
        int32_t mapId;
    };
    
    struct UpdateSetupChip {
        int32_t chipId;
    };
    
    struct UpdateStoryLevelRate {
        int32_t levelId;
        int32_t scores;
        int32_t rate;
    };
    
    struct UpdateVIPLevel {
        int32_t vipLevel;
//        int32_t vipExperiencePts;
//        int64_t remainingVIPSeconds;
    };
    
    struct UpdateReceiveVIPRewardStatus {
        int64_t leftTimeInSeconds;      // 0:表示可以领取， > 0:表示剩余时间
    };
    
    struct UpdateIconId {
        int32_t iconId;
    };
    
    typedef boost::mpl::vector22<RefreshGold, RefreshSilver, NotifyLevelUp, RefreshExecution, UpdateExperiencePoints, UpdateDefensePoints, UpdateFriendshipPoints, UpdateAchievementPoints, UpdateSingleInstanceLevel, UpdateMultipleInstanceLevel, UpdateRequestHelpUsage, UpdateStoryLevel, UpdateLeftTownAttackTimes, UpdateLeftSPVETimes, UpdateLeftMPVETimes, InitialFinished, UpdateSetupMap, UpdateSetupChip, UpdateStoryLevelRate, UpdateVIPLevel, UpdateReceiveVIPRewardStatus, UpdateIconId> Types;
    typedef boost::make_variant_over<Types>::type MessageType;
    
    typedef std::map<int32_t, c2smap::Map> MapSet;
    typedef std::map<int32_t, card::Card> CardSet;
    typedef std::map<int32_t, card::Chip> ChipSet;
    
class Detail {
public:
    Detail():_place(0){
    
    }
public:
    void addProps(int32_t propId) {
        int count = _props[propId];
        _props[propId] = count + 1;
    }
    
    std::map<int32_t, int32_t> takeAllProps() {
        std::map<int32_t, int32_t> props = _props;
        _props.clear();
        return props;
    }
    
public:
    const std::string &getUIN() const {
        return _uin;
    }
    void setUIN(const std::string &uin) {
        _uin = uin;
    }
    
    int32_t getPlayerId() const {
        return _playerId;
    }
    void setPlayerId(const int32_t playerId) {
        _playerId = playerId;
    }
    
    const std::string &getName() const {
        return _name;
    }
    void setName(const std::string &name) {
        _name = name;
    }
    
    int32_t getIconId() const {
        return _iconId;
    }
    
    void setIconId(int32_t iconId) {
        _iconId = iconId;
    }
    
    int32_t getExecutionPts() const {
        return _executionPts;
    }
    
    void setExecutionPts(int32_t pts) {
        _executionPts = pts;
    }
    
    int32_t getDefensePts() const {
        return _defensePts;
    }
    
    void setDefensePts(int32_t pts) {
        _defensePts = pts;
    }
    
    int32_t getAchievementPts() const {
        return _achievementPts;
    }
    void setAchievementPts(int32_t pts) {
        _achievementPts = pts;
    }
    
    
    int32_t getExperiencePts() const {
        return _experiencePts;
    }
    void setExperiencePts(int32_t pts) {
        _experiencePts = pts;
    }
    
    int32_t getFriendshipPts() const {
        return _friendshipPts;
    }
    void setFriendshipPts(int32_t pts) {
        _friendshipPts = pts;
    }

    int32_t getRequestHelpMaxUsage() const {
        return _requestHelpMaxUsage;
    }
    
    void setRequestHelpMaxUsage(int32_t usage) {
        _requestHelpMaxUsage = usage;
    }
    
    int32_t getRequestHelpUsage() const {
        return _requestHelpUsage;
    }
    
    void setReqeustHelpUsage(int32_t usage) {
        _requestHelpUsage = usage;
    }
    
    int32_t getGolds() const {
        return _golds;
    }
    void setGolds(int32_t golds) {
        _golds = golds;
    }
    
    int32_t getSilvers() const {
        return _silvers;
    }
    void setSilvers(int32_t silvers) {
        _silvers = silvers;
    }
    
    int32_t getLevel() const {
        return _level;
    }
    void setLevels(int32_t level) {
        _level = level;
    }
    
    int32_t getStoryLevel() const {
        return _storyLevel;
    }
    
    void setStoryLevel(int32_t level) {
        _storyLevel = level;
    }
    
    int32_t getSingleInstanceLevel() const {
        return _instanceLevel;
    }
    void setSingleInstanceLevel(int32_t level) {
        _instanceLevel = level;
    }
    
    int32_t getMultipleInstanceLevel() const {
        return _teamInstanceLevel;
    }
    void setMultiplyInstanceLevel(int32_t level) {
        _teamInstanceLevel = level;
    }
    
    int32_t getCardCompletion() const {
        return _cardCompletion;
    }
    void setCardCompletion(int32_t comp) {
        _cardCompletion = comp;
    }
    
    bool isCurrentInBattle() const {
        return _isInBattle;
    }
    void setIsCurrentInBattle(bool isInBattle) {
        _isInBattle = isInBattle;
    }
    
public: // 地图
    void setSetupedMapId(int32_t mapId) {
        _setupedMapId = mapId;
    }
    
    int32_t getSetupedMapId() const {
        return _setupedMapId;
    }
    
    void setSetupedMapPrivateId(const std::string &privateId) {
        _setupedMapPrivateId = privateId;
    }
    
    const std::string & getSetupedMapPrivateId() const {
        return _setupedMapPrivateId;
    }
    
    void setUnlockedMaps(const MapSet &maps) {
        _unlockedMaps = maps;
    }
    
    const MapSet &getUnlockedMaps() const {
        return _unlockedMaps;
    }
    
    MapSet &getMutableUnlockedMaps() {
        return _unlockedMaps;
    }
    
public: // 卡片&芯片
    void setUnlockedCards(const CardSet &cards) {
        _unlockedCards = cards;
    }
    
    const CardSet &getUnlockedCards() const {
        return _unlockedCards;
    }
    
    CardSet &getMutableUnlockedCards() {
        return _unlockedCards;
    }
    
    void setInstalledCards(const CardSet &cards) {
        _installedCards = cards;
    }
    
    const CardSet & getInstalledCards() const {
        return _installedCards;
    }
    
    CardSet &getInstalledCards() {
        return _installedCards;
    }
    
    
    void setFragmentMap(const props::FragmentMap &fragment) {
        _fragmentMap = fragment;
    }
    
    const props::FragmentMap & getFragmentMap() const {
        return _fragmentMap;
    }
    
    int32_t getDefaultChipId() const {
        return _defaultChipId;
    }
    
    void setDefaultChipId(int32_t chipId) {
        _defaultChipId = chipId;
    }
    
    const std::string &getDefaultChipPrivateId() const {
        return _defaultChipPrivateId;
    }
    
    void setDefaultChipPrivateId(const std::string &privateId) {
        _defaultChipPrivateId = privateId;
    }
    
    void setUnlockedChips(const ChipSet &chips) {
        _unlockedChips = chips;
    }
    
    const ChipSet &getUnlockedChips() const {
        return _unlockedChips;
    }
    
    ChipSet &getMutableUnlockedChips() {
        return _unlockedChips;
    }
    
    void setJXPDetail(const jxp::Detail &detail) {
        _jxp = detail;
        _jxp.level = 0;
        for (int i = 0 ; i < JXP_ITEM_SIZE; i++) {
            const int32_t id = detail.roles[i];
            if (id > jxp::JXPItemState_UNOPEN) {
                _jxp.level = _jxp.level + 1;
            }
        }
    }
    
    jxp::Detail &getJXPDetail() {
        return _jxp;
    }
    
    const int32_t getJXPRolesSize() const {
        int i = 0;
        for (; i < JXP_ITEM_SIZE; i++) {
            if(_jxp.roles[i] < 0){
                break;
            }
        }
        return i;
    }
    
    arena::Detail& getArenaDetail() {
        return _arenaDetail;
    }
    
    void setArenaDetail(const arena::Detail &detail) {
        _arenaDetail = detail;
    }
    
    
    int32_t getFreeTownAttackTimes() const {
        return _leftFreeAttackTownTimes;
    }
    
    void setFreeTownAttackTimes(int32_t times) {
        _leftFreeAttackTownTimes = times;
    }
    
    int32_t getPayTownAttackTimes() const {
        return _leftPayedAttackTownTimes;
    }
    
    void setPayTownAttackTimes(int32_t times) {
        _leftPayedAttackTownTimes = times;
    }
    
    
    int32_t getFreeSPVETimes() const {
        return _leftFreeSPVETimes;
    }
    
    void setFreeSPVETimes(int32_t times) {
        _leftFreeSPVETimes = times;
    }
    
    int32_t getPaySPVETimes() const {
        return _leftPayedSPVETimes;
    }
    
    void setPaySPVETimes(int32_t times) {
        _leftPayedSPVETimes = times;
    }
    
    int32_t getFreeMPVETimes() const {
        return _leftFreeMPVETimes;
    }
    
    void setFreeMPVETimes(int32_t times) {
        _leftFreeMPVETimes = times;
    }
    
    int32_t getPayMPVETimes() const {
        return _leftPayedMPVETimes;
    }
    
    void setPayMPVETimes(int32_t times) {
        _leftPayedMPVETimes = times;
    }
    
    void setVIPLevel(int32_t level) {
        _VIPLevel = level;
    }
    
    int32_t getVIPLevel() const {
        return _VIPLevel;
    }
    
    void setPlace(int32_t place)  {
        _arenaDetail.areaPosition = place;
    }
    
    int32_t getPlace() const {
        return _arenaDetail.areaPosition;
    }
    
    void setVipRewardLeftTimeInSeconds (int64_t seconds) {
        _vipRewardLeftTimeInSeconds = seconds;
    }
    
    int64_t getVipRewardLeftTimeInSeconds() const {
        return _vipRewardLeftTimeInSeconds;
    }
    
public: // 仓库
    void setStorage(const props::TotalStorage &store) {
        _storage = store;
    }
    
    const props::TotalStorage &getStorage() const {
        return _storage;
    }
    
    props::TotalStorage &getMutableStorage() {
        return _storage;
    }
    
public: // 奴役信息
    void setSlaveDetail(const slave::Detail &detail) {
        _slave = detail;
    }
    
    const slave::Detail &getSlaveDetail() const {
        return _slave;
    }
    
    slave::Detail &getMutableSlaveDetail() {
        return _slave;
    }
    
public: // 基地
    void setBaseStatus(const base::Status &status) {
        _base = status;
    }
    
    const base::Status &getBaseStatus() const {
        return _base;
    }
    
public: // 抽卡
    void setLuckyCardDetail(const luck::Detail &detail) {
        _luckyCard = detail;
    }
    
    const luck::Detail &getLuckyCardDetail() const {
        return _luckyCard;
    }
    
public: // 摇钱树
    void setCashCowDetail(const cashcow::Detail &detail) {
        _cashcow = detail;
    }
    
    const cashcow::Detail &getCashCowDetail() const {
        return _cashcow;
    }
    
public:
    float getPos_X() const {
        return pos_x;
    }
    
    void setPos_X(float value) {
        pos_x = value;
    } 
    
    float getPos_Y() const {
        return pos_y;
    }
    
    void setPos_Y(float value) {
        pos_y = value;
    } 
    
public:
    std::string     _uin;            /* 平台id */
    
    int32_t         _playerId;
    std::string     _name;
    int32_t         _iconId;
    int32_t         _executionPts;          /* 行动力 */
    int32_t         _defensePts;            /* 防御点数 */
    int32_t         _achievementPts;        /* 成就点数 */
    int32_t         _experiencePts;         /* 经验点数 */
    int32_t         _friendshipPts;         /* 友情点数 */
    int32_t         _requestHelpMaxUsage;   /* 请求支援使用上限 */
    int32_t         _requestHelpUsage;      /* 累计请求支援次数*/
    int32_t         _golds;
    int32_t         _silvers;
    int32_t         _level;
    int32_t         _storyLevel;            /* 剧情关卡成绩 */
    int32_t         _instanceLevel;         /* 单人副本成绩 */
    int32_t         _teamInstanceLevel;     /* 多人副本成绩 */
    int32_t         _cardCompletion;        /* 卡片碎片完成度 */
    bool            _isInBattle;            /* 当前正在战斗中*/
    
    int32_t         _leftFreeAttackTownTimes;   /* 剩余的免费打城镇次数*/
    int32_t         _leftPayedAttackTownTimes;    /* 剩余的付费打城镇次数 */

    int32_t         _leftFreeSPVETimes;    /* 剩余免费闯单人副本次数*/
    int32_t         _leftPayedSPVETimes;   /* 剩余付费闯单人副本次数 */
    
    int32_t         _leftFreeMPVETimes;    /* 剩余免费闯多人副本次数 */
    int32_t         _leftPayedMPVETimes;   /* 剩余付费闯多人副本次数 */
    
    int32_t         _VIPLevel;
    
    int64_t         _vipRewardLeftTimeInSeconds;
    
    int32_t         _place;
    int32_t         _setupedMapId;
    std::string     _setupedMapPrivateId;
    MapSet          _unlockedMaps;
    
    props::TotalStorage  _storage;

    CardSet         _unlockedCards;
    
    //[[ The attributes should be REMOVED, take care to use those.
    int32_t         _defaultChipId;
    std::string     _defaultChipPrivateId;
    ChipSet         _unlockedChips;
    //]]
    jxp::Detail     _jxp;                   /* 将星盘 */
    
    slave::Detail   _slave;
    
    base::Status    _base;
    luck::Detail    _luckyCard;             /* 幸运抽卡 */
    arena::Detail   _arenaDetail;           /* 竞技场 */
    
    cashcow::Detail _cashcow;               //摇钱树
    CardSet         _installedCards;        //战斗选好的卡片
    props::FragmentMap                  _fragmentMap;//碎片
    
private:
    std::map<int32_t, int32_t> _props;      /* 消耗品、提车单 */
    
    float   pos_x;
    float   pos_y;
};

} // end of namespace role

typedef boost::function<void (const role::MessageType &)> RoleMessageHandler;
typedef boost::function<void (int32_t)> CreateRoleCallback;
typedef boost::function<void (const role::Detail &)> LoadRoleInfoCallback;

typedef boost::function<void (int32_t)> BuyGamePropsCallback;

#endif
