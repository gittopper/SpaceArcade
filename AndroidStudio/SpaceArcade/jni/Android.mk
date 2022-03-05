LOCAL_PATH := $(call my-dir)/../../../src

include $(CLEAR_VARS)

LOCAL_MODULE    := GameEngine
LOCAL_SRC_FILES := android/GameEngine.cpp \
				   math/vector.cpp \
				   math/boundingbox.cpp \
				   math/mat.cpp \
				   math/mat44.cpp \
				   math/mathutils.cpp \
				   math/vector4.cpp \
				   game/collider.cpp \
				   game/collisionrules.cpp \
				   game/igame.cpp \
				   game/iobject.cpp \
				   game/physics.cpp \
				   game/regressvisitor.cpp \
				   game/spacegame.cpp \
				   game/objects/asteroid.cpp \
				   game/objects/bullet.cpp \
				   game/objects/scene.cpp \
				   game/objects/spaceship.cpp \
				   rendering/glesrenderer.cpp \
				   rendering/glesspacegamerenderer.cpp \
				   rendering/rendererfactory.cpp \
				   rendering/androidresourceloader.cpp \
				   rendering/spacegamerenderer.cpp

LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -lOpenSLES  -ldl  -lGLESv1_CM
#LOCAL_LDLIBS    := -llog -lGLESv2 -landroid -ldl -lOpenSLES

LOCAL_CFLAGS := -DGL_GLEXT_PROTOTYPES=1 -DANDROID_NDK -DDISABLE_IMPORTGL -fexceptions -std=gnu++11
#LOCAL_CXXFLAGS  := -gstabs+

include $(BUILD_SHARED_LIBRARY)
