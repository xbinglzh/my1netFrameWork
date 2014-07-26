//
//  DistanceItem.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-26.
//
//

#include "DistanceItem.h"

DistanceItem::DistanceItem() : _object(NULL), _distance(0){
    
}

DistanceItem::~DistanceItem(){
    CC_SAFE_RELEASE_NULL(_object);
}

bool DistanceItem::init(){
    return true;
}

static int compareDistance(const void * p1,const void * p2){
    DistanceItem * item1 = *((DistanceItem**)p1);
    DistanceItem * item2 = *((DistanceItem**)p2);
    
    if(item1->getDistance() > item2->getDistance()){
        return 1;
    }
    else if(item1->getDistance() < item2->getDistance()){
        return -1;
    }
    return 0 ;
}