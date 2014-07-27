//
//  LablePngFont.cpp
//  HappyMouse
//
//  Created by xUanBing on 14-7-27.
//
//

#include "LablePngFont.h"
#include "ResourceLoader.h"

LablePngFont* LablePngFont::create(const char* fileImage, unsigned int capacity, std::vector<const char*>& map, float scale /*字体间距*/) {
    
    LablePngFont* pRet = new LablePngFont();
    if (pRet && pRet->doMyInit(fileImage, capacity, map, scale)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool LablePngFont::doMyInit(const char* fileImage, unsigned int capacity, std::vector<const char*>& map, float _scale /*字体间距*/)  {
    
    this->scale = _scale;
    int size = map.size();
    
    std::stringstream pngSstm;
    std::stringstream plistSstm;
    
    pngSstm << fileImage << ".png";
    plistSstm << fileImage << ".plist";
    
    
    if (!initWithFile(pngSstm.str().c_str(), capacity) || size % 2 != 0) {
        return false;
    }
    
    CCSpriteFrameCache * sharedSpriteFrameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
    sharedSpriteFrameCache->addSpriteFramesWithFile(plistSstm.str().c_str());
    
    size /= 2;
    for (int i=0; i<size; i++) {
        char key = map[2*i][0];
        const char* fn = map[2*i+1];
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(fn);
        if (!sprite) {
            CCLog("[MyLabel] The sprite with name '%s' is not exists!", fn);
            return false;
        }
        words[key] = sprite;  // insert the sprites
        sprite->retain();  // keep sprite from deleting
    }
    return true;
}
	
LablePngFont::~LablePngFont() { // delete the sprite
    for (std::map<char, CCSprite*>::iterator it = words.begin(); it!=words.end(); it++) {
        CC_SAFE_DELETE(it->second);
    }
}
	
const char* LablePngFont::getString() {
    return label;
}
	
void LablePngFont::setString(const char* _label) {
    this->label = _label;
    _setString(label);
}
	
void LablePngFont::_setString(std::string str) {
		// clean and make enough room for new str
    m_pobTextureAtlas->removeAllQuads();
    quads.resize(str.length());
    int index = 0;
    mlWidth = 0;
    mlHeight = 0;
		
    if (str.length() > m_pobTextureAtlas->getCapacity()) {
        increaseAtlasCapacity();
    }
		
    for (std::string::iterator it = str.begin(); it!=str.end(); it++, index++) {
        CCSprite * sprite = NULL;
			
        // make sure the character is in the map
        std::map<char, CCSprite*>::iterator wit = words.find(*it);
        if (wit==words.end()) {
            CCLog("The character '%c' is not found in the map, please check!", *it);
            return;
        } else {
            sprite = wit->second;
        }
			
        // calculate the position of the sprite;
        CCSize size = sprite->getContentSize();
        sprite->setPosition(ccp(mlWidth + size.width/2*scale, 0));
        mlWidth += size.width * scale;
        mlHeight = size.height > mlHeight ? size.height : mlHeight;
			
        // insert the quote, the sprite->updateTransform() will do the following job
        sprite->setBatchNode(this);
        sprite->setAtlasIndex(index);
        sprite->setDirty(true);
        sprite->updateTransform();
        
        quads[index] = sprite->getQuad();
    }
    // correct the size of batch
    setContentSize(ccp(mlWidth, mlHeight));
}
	

CCArray* LablePngFont::getRGBAChildren() {
    return getChildren();
}
	
CCNode* LablePngFont::getRGBAParent() {
    return getParent();
}
	
void LablePngFont::updateDisplayedColor(const ccColor3B& parentColor) {
    _displayedColor.r = _realColor.r * parentColor.r / 255.0;
    _displayedColor.g = _realColor.g * parentColor.g / 255.0;
    _displayedColor.b = _realColor.b * parentColor.b / 255.0;
		
    _updateMLColor();
}
	
void LablePngFont::updateDisplayedOpacity(GLubyte parentOpacity) {
    _displayedOpacity = _realOpacity * parentOpacity/255.0;
		
    _updateMLColor();
}
	
	
void LablePngFont::_updateMLColor() {
    ccColor4B color4 = {
    _displayedColor.r * _displayedOpacity/255.0f,
    _displayedColor.g * _displayedOpacity/255.0f,
    _displayedColor.b * _displayedOpacity/255.0f,
    _displayedOpacity
    };
    int idx = 0;
    for (std::vector<ccV3F_C4B_T2F_Quad>::iterator it = quads.begin(); it!=quads.end(); it++, idx++) {
        it->bl.colors = color4;
        it->br.colors = color4;
        it->tl.colors = color4;
        it->tr.colors = color4;
        m_pobTextureAtlas->updateQuad(&(*it), idx);
    }
}
