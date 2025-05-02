#!/usr/bin/env bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
echo SCRIPT_DIR=$SCRIPT_DIR
NDK_PATH=/home/stanislav/Android/Sdk/ndk/27.0.12077973/
THRD_PARTY_INSTALL_DIR=$SCRIPT_DIR/../../build/install/android/
mkdir -p $THRD_PARTY_INSTALL_DIR/Debug
mkdir -p $THRD_PARTY_INSTALL_DIR/Release

#sudo apt-get install libudev-dev libvorbis-dev libflac-dev

function buildABI() {
    abi=$1
    build_type=$2
    echo abi=$abi
    cd $SCRIPT_DIR/SFML/build/$build_type
    mkdir $abi
    cd $abi

    mkdir $THRD_PARTY_INSTALL_DIR/$build_type/$abi
    cmake ../../.. \
    -DCMAKE_INSTALL_PREFIX=$THRD_PARTY_INSTALL_DIR/$abi \
    -DANDROID_ABI=$abi \
    -DANDROID_NATIVE_API_LEVEL=29 \
    -DANDROID_PLATFORM=android-21 \
    -DCLANG_DEFAULT_CXX_STDLIB=libc++ \
    -DCMAKE_EXE_LINKER_FLAGS=-stdlib=libc++ \
    -DCMAKE_TOOLCHAIN_FILE=${NDK_PATH}/build/cmake/android.toolchain.cmake \
    -DCMAKE_ANDROID_NDK_TOOLCHAIN_VERSION=clang \
    -DCMAKE_SYSTEM_NAME=Android \
    -DCMAKE_ANDROID_NDK=${NDK_PATH} \
    -DCMAKE_ANDROID_STL_TYPE=c++_static \
    -DCMAKE_BUILD_TYPE=$build_type \
    -G "Unix Makefiles"

    make -j
    cmake --install . --prefix $THRD_PARTY_INSTALL_DIR/$build_type/$abi
}

mkdir -p $SCRIPT_DIR/SFML/build/Debug
mkdir -p $SCRIPT_DIR/SFML/build/Release
#abis=(x86 armeabi-v7a arm64-v8a x86_64)
buildABI 'x86_64' Debug
buildABI 'armeabi-v7a' Debug
buildABI 'arm64-v8a' Debug

buildABI 'x86_64' Release
buildABI 'armeabi-v7a' Release
buildABI 'arm64-v8a' Release
