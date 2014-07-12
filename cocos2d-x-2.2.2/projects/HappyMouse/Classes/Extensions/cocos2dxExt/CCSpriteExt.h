//
//  AnimNode.h
//  iLostCity
//
//  Created by Ryan_Y on 13-6-6.
//
//

#ifndef iLostCity_CCSpriteExt_h
#define iLostCity_CCSpriteExt_h

#include "cocos2d.h"

USING_NS_CC;

class  CCSpriteExt : public CCSprite {
public:
    CCSpriteExt();
    virtual ~CCSpriteExt();
    static CCSpriteExt* create(const char *pszFileName);
    bool initWithFile(const char *pszFilename);
private:
    static std::map<std::string, int32_t> _textureRefs;
private:
    std::string _texturefileName;
};

#endif
