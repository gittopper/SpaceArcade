
APP_CPPFLAGS += -std=c++11
# Instruct to use the static GNU STL implementation
#APP_STL := stlport_static
APP_STL := gnustl_static
LOCAL_C_INCLUDES += ${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.8/include

APP_OPTIM        := debug
APP_ABI := armeabi-v7a x86

APP_PLATFORM := android-14
APP_CPPFLAGS += -frtti 
APP_CPPFLAGS += -fexceptions

NDK_TOOLCHAIN_VERSION := 4.8