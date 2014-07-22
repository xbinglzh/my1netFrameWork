//
//  StateFactory.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-22.
//
//

#ifndef __HappyMouse__StateFactory__
#define __HappyMouse__StateFactory__

#include <map>

class State;

class  StateFactory {
    
protected:
	StateFactory();
	virtual ~StateFactory();
	bool init();
    
public:
    static StateFactory *sharedInstance();
    static void purgeInstance();
    State * getStateByTypeId(const int32_t id);
    State * getAdditionStateById(const int32_t id);
    
private:
	std::map<int32_t,State* > 	_stateMap;
    std::map<int32_t,State* > 	_skillStateMap;
    
};

#endif /* defined(__HappyMouse__StateFactory__) */
