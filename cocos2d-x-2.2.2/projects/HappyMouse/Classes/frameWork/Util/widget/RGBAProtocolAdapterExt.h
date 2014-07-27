//
//  RGBAProtocolAdapterExt.h
//  HappyMouse
//
//  Created by xUanBing on 14-7-27.
//
//

#ifndef __HappyMouse__RGBAProtocolAdapterExt__
#define __HappyMouse__RGBAProtocolAdapterExt__

#include "cocos2d.h"

USING_NS_CC;

class RGBAProtocolAdapterExt: public CCRGBAProtocol {
    
protected:
	GLubyte		_displayedOpacity, _realOpacity;
	ccColor3B	_displayedColor, _realColor;
	bool		_cascadeOpacityEnabled, _cascadeColorEnabled;
    
protected:
	virtual CCArray* getRGBAChildren() = 0;
	virtual CCNode* getRGBAParent() = 0;
	
public:
    
	RGBAProtocolAdapterExt();
    ~RGBAProtocolAdapterExt();
	
	virtual void setColor(const ccColor3B& color);
	
    virtual const ccColor3B& getColor(void) ;
	
    virtual const ccColor3B& getDisplayedColor(void) ;
	
    virtual GLubyte getDisplayedOpacity(void) ;
	
    virtual GLubyte getOpacity(void) ;
    
    virtual void setOpacity(GLubyte opacity) ;
	
    virtual void setOpacityModifyRGB(bool bValue) ;
	
    virtual bool isOpacityModifyRGB(void) ;
	
    virtual bool isCascadeColorEnabled(void);
	
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled);
    
    virtual void updateDisplayedColor(const ccColor3B& parentColor);
    
    virtual bool isCascadeOpacityEnabled(void);
	
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
	
    virtual void updateDisplayedOpacity(GLubyte parentOpacity);
    
};




#endif /* defined(__HappyMouse__RGBAProtocolAdapterExt__) */
