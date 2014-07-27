//
//  RGBAProtocolAdapterExt.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-27.
//
//

#include "RGBAProtocolAdapterExt.h"

RGBAProtocolAdapterExt::RGBAProtocolAdapterExt() :
	_cascadeColorEnabled(true),
	_cascadeOpacityEnabled(true),
	_displayedOpacity(255),
	_realOpacity(255),
	_displayedColor(ccc3(255, 255, 255)),
	_realColor(ccc3(255, 255, 255)) {
}

RGBAProtocolAdapterExt::~RGBAProtocolAdapterExt() {
    
}
	
void RGBAProtocolAdapterExt::setColor(const ccColor3B& color) {
    _displayedColor = _realColor = color;
		
    if (_cascadeColorEnabled) {
        ccColor3B parentColor = ccWHITE;
        CCRGBAProtocol *parent = dynamic_cast<CCRGBAProtocol*>(getRGBAParent());
        
        if (parent && parent->isCascadeColorEnabled()) {
            parentColor = parent->getDisplayedColor();
        }
			
        updateDisplayedColor(parentColor);
    }
}
	
const ccColor3B& RGBAProtocolAdapterExt::getColor(void) {
    return _realColor;
}
	
const ccColor3B& RGBAProtocolAdapterExt::getDisplayedColor(void) {
    return _displayedColor;
}
	
GLubyte RGBAProtocolAdapterExt::getDisplayedOpacity(void) {
    return _displayedOpacity;
}
	
GLubyte RGBAProtocolAdapterExt::getOpacity(void) {
    return _realOpacity;
}
    
void RGBAProtocolAdapterExt::setOpacity(GLubyte opacity) {
    _displayedOpacity = _realOpacity = opacity;
		
    if (_cascadeOpacityEnabled) {
        GLubyte parentOpacity = 255;
        CCRGBAProtocol* pParent = dynamic_cast<CCRGBAProtocol*>(getRGBAParent());
        
        if (pParent && pParent->isCascadeOpacityEnabled()) {
            parentOpacity = pParent->getDisplayedOpacity();
        }
        
        this->updateDisplayedOpacity(parentOpacity);
    }
}
	
void RGBAProtocolAdapterExt::setOpacityModifyRGB(bool bValue) {
}
	
bool RGBAProtocolAdapterExt::isOpacityModifyRGB(void) {
    return false;
}
	
bool RGBAProtocolAdapterExt::isCascadeColorEnabled(void) {
    return _cascadeColorEnabled;
}
	
void RGBAProtocolAdapterExt::setCascadeColorEnabled(bool cascadeColorEnabled) {
    _cascadeColorEnabled = cascadeColorEnabled;
}
    
void RGBAProtocolAdapterExt::updateDisplayedColor(const ccColor3B& parentColor) {
    _displayedColor.r = _realColor.r * parentColor.r/255.0;
    _displayedColor.g = _realColor.g * parentColor.g/255.0;
    _displayedColor.b = _realColor.b * parentColor.b/255.0;
		
    if (_cascadeColorEnabled) {
        CCObject *obj = NULL;
        CCARRAY_FOREACH(getRGBAChildren(), obj) {
            CCRGBAProtocol *item = dynamic_cast<CCRGBAProtocol*>(obj);
            if (item) {
                item->updateDisplayedColor(_displayedColor);
            }
        }
    }
}
    
bool RGBAProtocolAdapterExt::isCascadeOpacityEnabled(void) {
    return _cascadeOpacityEnabled;
}
	
void RGBAProtocolAdapterExt::setCascadeOpacityEnabled(bool cascadeOpacityEnabled) {
    _cascadeOpacityEnabled = cascadeOpacityEnabled;
}
	
void RGBAProtocolAdapterExt::updateDisplayedOpacity(GLubyte parentOpacity) {
    _displayedOpacity = _realOpacity * parentOpacity/255.0;
		
    if (_cascadeOpacityEnabled) {
        CCObject* pObj;
        CCARRAY_FOREACH(getRGBAChildren(), pObj) {
            CCRGBAProtocol* item = dynamic_cast<CCRGBAProtocol*>(pObj);
            if (item) {
                item->updateDisplayedOpacity(_displayedOpacity);
            }
        }
    }
}


