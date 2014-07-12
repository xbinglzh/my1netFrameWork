//
//  battle.h
//  motoGame
//
//  Created by xUanBing on 14-5-4.
//
//

#ifndef motoGame_battle_h
#define motoGame_battle_h

#include <boost/function.hpp>
#include <boost/variant.hpp>

namespace battle {
    
    struct Reward {
        int32_t     propId;
        int32_t     quantity;
    };
    
    typedef std::vector<Reward> RewardsList;
    
    struct Rewards {
        RewardsList props;
        int32_t     level;
        int32_t     score; //分数
    };
    
}


#endif
