//
//  FontStyle.h
//  iLostCity
//
//  Created by Ryan_Y on 13-4-27.
//
//

#ifndef iLostCity_FontStyle_h
#define iLostCity_FontStyle_h
#include "cocos2d.h"

USING_NS_CC;

class FontStyle {
public:
    std::string _font;
    uint32_t    _size;
    ccColor3B   _color;
    ccColor3B   _stroke_color;
    int         _type;
};


#endif
