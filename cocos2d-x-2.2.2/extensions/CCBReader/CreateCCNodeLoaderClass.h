//
//  CreattCCNodeLoaderClass.h
//  iLostCity
//
//  Created by user on 13-5-23.
//
//

#ifndef CreateCCNodeLoaderClass_h
#define CreateCCNodeLoaderClass_h

#define CREATE_NEW_INHERIT_CCLAYERLOADER_CLASS(CLASSNAME)\
class CLASSNAME##Loader : public cocos2d::extension::CCLayerLoader { \
public: \
CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CLASSNAME##Loader, loader); \
protected: \
CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CLASSNAME); \
};

#define CREATE_NEW_INHERIT_CCNODELOADER_CLASS(CLASSNAME)\
class CLASSNAME##Loader : public cocos2d::extension::CCNodeLoader { \
public: \
CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CLASSNAME##Loader, loader); \
protected: \
CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CLASSNAME); \
};


#endif
