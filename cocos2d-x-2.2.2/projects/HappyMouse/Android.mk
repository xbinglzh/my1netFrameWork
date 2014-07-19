

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CPPFLAGS += -fexceptions

LOCAL_CPPFLAGS += -DCRYPTOPP_DISABLE_ASM -DCRYPTOPP_DISABLE_SSE2 -DCRYPTOPP_ENABLE_NAMESPACE_WEAK=1

LOCAL_MODULE := cocos_happymouse_common

LOCAL_MODULE_FILENAME := libhappymousecommon


LOCAL_SRC_FILES := \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/SPFrameData.cpp \
Classes/frameWork/Util/shader/CCRGBSprite.cpp \
Classes/frameWork/Util/shader/CCShaderEffectSprite.cpp \
Classes/frameWork/Extensions/LevelHelper/LevelHelperLoader.cpp \
Classes/frameWork/Extensions/cocos2dxExt/CCSpriteExt.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/external_tool/Json/SPContentJsonDictionary.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/SPTextureData.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHNode.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/utils/SPArmatureDataManager.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/external_tool/Json/lib_json/json_value.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHBatch.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/display/SPDecorativeDisplay.cpp \
Classes/frameWork/Extensions/ResourceExt/ResourceLoader.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHTouchMgr.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHFixture.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/animation/SPTween.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHPathNode.cpp \
Classes/Controller/AppLauncher.cpp \
Classes/frameWork/Util/GameUtils.cpp \
Classes/frameWork/Util/shader/ShaderManager.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHContactInfo.cpp \
Classes/frameWork/Util/Particles/SmallSoybeanParticle.cpp \
Classes/frameWork/Extensions/LevelHelper/Utilities/LHObject.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/utils/SPTransformHelp.cpp \
Classes/frameWork/Util/widget/CCLabelTTFStroke.cpp \
Classes/frameWork/Util/resourse/ResourceManager.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/SPContourData.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/display/SPDisplayManager.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHContactListener.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/display_data/SPSpriteDisplayData.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHCuttingEngineMgr.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/external_tool/Json/lib_json/json_writer.cpp \
Classes/frameWork/Extensions/GLESRender/GLES-Render.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/utils/SPBatchNode.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/SPMovementBoneData.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/SPNode.cpp \
Classes/frameWork/Flash/dragonBone/AnimNode.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHAnimationNode.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/SPMovementData.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/utils/SPTweenFunction.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHLayer.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/display/SPContourPoints.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/SPBoneData.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHCustomSpriteMgr.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/display_data/SPShaderDisplayData.cpp \
Classes/frameWork/Util/tinyxml/tinyxml.cpp \
Classes/View/uiView/GameView.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHBezier.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/display_data/SPParticleDisplayData.cpp \
Classes/frameWork/Util/tinyxml/tinyxmlerror.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/display/SPShaderNode.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/display_data/SPDisplayData.cpp \
Classes/View/root/RootUiLayer.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/SHDocumentLoader.cpp \
Classes/frameWork/Extensions/LevelHelper/Utilities/LHArray.cpp \
Classes/frameWork/Util/widget/CCScale9ProgressBar.cpp \
Classes/frameWork/Util/layout/LayoutUtil.cpp \
Classes/frameWork/Util/UiUtils.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/display/display_factory/SPDisplayFactoryManager.cpp \
Classes/Controller/GameController.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHSettings.cpp \
Classes/frameWork/Util/Particles/ParticleEffect.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/SPBone.cpp \
Classes/Model/GameObject/MouseObject.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/SPArmatureData.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/display/SPContourSprite.cpp \
Classes/Model/GameObject/PitObject.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/animation/SPProcessBase.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHContactNode.cpp \
Classes/frameWork/Util/tinyxml/tinystr.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/external_tool/Json/lib_json/json_reader.cpp \
Classes/frameWork/Flash/dragonBone/ArmatureAnim.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/SPJsonData.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHJoint.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/animation/SPAnimation.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/display/display_factory/SPDisplayFactory.cpp \
Classes/frameWork/Util/widget/LabelView.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHParallaxNode.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/utils/SPUtilMath.cpp \
Classes/AppDelegate.cpp \
Classes/frameWork/Util/HMD5.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/display/display_factory/SPParticleDisplayFactory.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/display_data/SPArmatureDisplayData.cpp \
Classes/frameWork/Extensions/LevelHelper/Utilities/LHDictionary.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/SPMovementFrameData.cpp \
Classes/frameWork/Util/tinyxml/tinyxmlparser.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/display/display_factory/SPArmatureDisplayFactory.cpp \
Classes/Controller/SceneController.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/display/CCTexture2DMutable.cpp \
Classes/frameWork/Extensions/LevelHelper/CustomClasses/TemporaryDummyClass.cpp \
Classes/Controller/GameConfig.cpp \
Classes/View/uiView/WelcomeView.cpp \
Classes/frameWork/Extensions/LevelHelper/Nodes/LHSprite.cpp \
Classes/frameWork/Util/widget/ModelDialog.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/utils/SPBatchNodeManager.cpp \
Classes/frameWork/Extensions/AudioHelper/AudioManager.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/datas/SPAnimationData.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/utils/SPDataReaderHelper.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/display/display_factory/SPShaderDisplayFactory.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/display/display_factory/SPSpriteDisplayFactory.cpp \
Classes/frameWork/Flash/dragonBone/SPArmature/SPArmature.cpp


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/Classes \
                    $(LOCAL_PATH)/Classes/Controller \
                    $(LOCAL_PATH)/Classes/Def \
                    $(LOCAL_PATH)/Classes/frameWork \
                    $(LOCAL_PATH)/Classes/frameWork/Extensions \
                    $(LOCAL_PATH)/Classes/frameWork/Extensions/ResourceExt \
                    $(LOCAL_PATH)/Classes/frameWork/Extensions/AudioHelper \
                    $(LOCAL_PATH)/Classes/frameWork/Extensions/AnimationExt \
                    $(LOCAL_PATH)/Classes/frameWork/Extensions/cocos2dxExt \
                    $(LOCAL_PATH)/Classes/frameWork/Extensions/GLESRender \
                    $(LOCAL_PATH)/Classes/frameWork/Flash \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/animation \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/datas \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/datas/display_data \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/display \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/display/display_factory \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/external_tool \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/external_tool/Json \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/external_tool/Json/json \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/external_tool/Json/lib_json \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/utils \
                    $(LOCAL_PATH)/Classes/frameWork/Util \
                    $(LOCAL_PATH)/Classes/frameWork/Util/layout \
                    $(LOCAL_PATH)/Classes/frameWork/Util/Particles \
                    $(LOCAL_PATH)/Classes/frameWork/Util/rapidjson \
                    $(LOCAL_PATH)/Classes/frameWork/Util/rapidjson/internal \
                    $(LOCAL_PATH)/Classes/frameWork/Util/resourse \
                    $(LOCAL_PATH)/Classes/frameWork/Util/shader \
                    $(LOCAL_PATH)/Classes/frameWork/Util/tinyxml \
                    $(LOCAL_PATH)/Classes/frameWork/Util/widget \
                    $(LOCAL_PATH)/Classes/Model \
                    $(LOCAL_PATH)/Classes/Model/GameObject \
                    $(LOCAL_PATH)/Classes/View \
                    $(LOCAL_PATH)/Classes/View/root \
                    $(LOCAL_PATH)/Classes/View/uiView \



LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/Classes \
                    $(LOCAL_PATH)/Classes/Controller \
                    $(LOCAL_PATH)/Classes/Def \
                    $(LOCAL_PATH)/Classes/frameWork \
                    $(LOCAL_PATH)/Classes/frameWork/Extensions \
                    $(LOCAL_PATH)/Classes/frameWork/Extensions/ResourceExt \
                    $(LOCAL_PATH)/Classes/frameWork/Extensions/AudioHelper \
                    $(LOCAL_PATH)/Classes/frameWork/Extensions/AnimationExt \
                    $(LOCAL_PATH)/Classes/frameWork/Extensions/cocos2dxExt \
                    $(LOCAL_PATH)/Classes/frameWork/Extensions/GLESRender \
                    $(LOCAL_PATH)/Classes/frameWork/Flash \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/animation \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/datas \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/datas/display_data \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/display \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/display/display_factory \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/external_tool \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/external_tool/Json \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/external_tool/Json/json \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/external_tool/Json/lib_json \
                    $(LOCAL_PATH)/Classes/frameWork/Flash/dragonBone/SPArmature/utils \
                    $(LOCAL_PATH)/Classes/frameWork/Util \
                    $(LOCAL_PATH)/Classes/frameWork/Util/layout \
                    $(LOCAL_PATH)/Classes/frameWork/Util/Particles \
                    $(LOCAL_PATH)/Classes/frameWork/Util/rapidjson \
                    $(LOCAL_PATH)/Classes/frameWork/Util/rapidjson/internal \
                    $(LOCAL_PATH)/Classes/frameWork/Util/resourse \
                    $(LOCAL_PATH)/Classes/frameWork/Util/shader \
                    $(LOCAL_PATH)/Classes/frameWork/Util/tinyxml \
                    $(LOCAL_PATH)/Classes/frameWork/Util/widget \
                    $(LOCAL_PATH)/Classes/Model \
                    $(LOCAL_PATH)/Classes/Model/GameObject \
                    $(LOCAL_PATH)/Classes/View \
                    $(LOCAL_PATH)/Classes/View/root \
                    $(LOCAL_PATH)/Classes/View/uiView \



LOCAL_WHOLE_STATIC_LIBRARIES += boost
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
TARGET_CPU_ABI := armeabi
LOCAL_ARM_MODE := arm

include $(BUILD_SHARED_LIBRARY)

$(call import-module,projects/HappyMouse)
$(call import-module,boost_1_44_0)
$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)

