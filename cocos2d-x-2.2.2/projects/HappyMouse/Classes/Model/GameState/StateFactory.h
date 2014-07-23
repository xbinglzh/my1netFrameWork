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
    static StateFactory *getInstance();
    static void purgeInstance();
    State * getStateByTypeId(const int stateType);
//    State * getAdditionStateById(const int stateId );
    
private:
	std::map<int, State* > 	_stateMap;
    std::map<int, State* > 	_skillStateMap;
    
};

#endif /* defined(__HappyMouse__StateFactory__) */
