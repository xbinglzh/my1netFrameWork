//
//  LablePngFont.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-27.
//
//

#ifndef __HappyMouse__LablePngFont__
#define __HappyMouse__LablePngFont__

#include "cocos2d.h"
#include "RGBAProtocolAdapterExt.h"
USING_NS_CC;

class LablePngFont : public CCSpriteBatchNode , public CCLabelProtocol, public RGBAProtocolAdapterExt {
    
private:
    std::map<char, CCSprite*> words;
    std::vector<ccV3F_C4B_T2F_Quad> quads;
    float mlWidth, mlHeight, scale;
    const char* label;
        
public:
        
    static LablePngFont* create(const char* fileImage, unsigned int capacity, std::vector<const char*>& map, float scale /*字体间距*/) ;
    bool doMyInit(const char* fileImage, unsigned int capacity, std::vector<const char*>& map, float _scale = 1.0f /*字体间距*/)  ;

    virtual ~LablePngFont();
    
    const char* getString();
    
    void setString(const char* _label);
    void _setString(std::string str) ;
    
protected:
    CCArray* getRGBAChildren() ;
    CCNode* getRGBAParent();
    
    void updateDisplayedColor(const ccColor3B& parentColor) ;
    virtual void updateDisplayedOpacity(GLubyte parentOpacity) ;
        
    void _updateMLColor() ;
    
};


#endif /* defined(__HappyMouse__LablePngFont__) */
