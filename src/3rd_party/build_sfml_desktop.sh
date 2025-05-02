#!/usr/bin/env bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
echo SCRIPT_DIR=$SCRIPT_DIR
THRD_PARTY_INSTALL_DIR=$SCRIPT_DIR/../../build/install/desktop
mkdir -p $THRD_PARTY_INSTALL_DIR

#sudo apt-get install libudev-dev libvorbis-dev libflac-dev

function buildSFML() {
    build_type=$1
    mkdir -p $THRD_PARTY_INSTALL_DIR/$build_type
    cd $SCRIPT_DIR/SFML
    mkdir -p build/$build_type/desktop
    cd build/$build_type/desktop
    cmake ../../.. -DCMAKE_INSTALL_PREFIX=$THRD_PARTY_INSTALL_DIR/$build_type
    make -j
    make install
}

buildSFML Debug
buildSFML Release
