//
//  DoubleNumber.h
//  MetalWar
//
//  Created by Ryan Yuan on 12-8-2.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef MetalWar_DoubleNumber_h
#define MetalWar_DoubleNumber_h

#include "cocos2d.h"
using namespace cocos2d;
class CCDoubleNumber : public CCObject
{
public:
    CCDoubleNumber(double v)
	: m_nValue(v) {}
    double getValue() const {return m_nValue;}
    void setValue(double v) { m_nValue = v; }
	
	static CCDoubleNumber* doubleNumberWithValue(double v)
    {
        return CCDoubleNumber::create(v);
    }
	
    static CCDoubleNumber* create(double v)
    {
        CCDoubleNumber* pRet = new CCDoubleNumber(v);
        pRet->autorelease();
        return pRet;
    }
private:
    double m_nValue;
};

#endif
