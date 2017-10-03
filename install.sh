#!/usr/bin/env bash

# init submodulewho was not fetch
git submodule update --init --recursive

# stock project directory
PROJECT_DIR=$(pwd)

DEPENDENCIES_DIR="dependencies/"

# install mongo-c-driver
cd $PROJECT_DIR/$DEPENDENCIES_DIR"mongo-c-driver-1.8.0"
./autogen.sh --with-libbson=bundled --prefix=$PROJECT_DIR/shared/mongo-c-driver-1.8.0 --exec-prefix=$PROJECT_DIR/shared/mongo-c-driver-1.8.0 --enable-static
make
make install

# install mongo-cxx-driver
cd $PROJECT_DIR/$DEPENDENCIES_DIR"mongo-cxx-driver-stable/shared"
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PROJECT_DIR/shared/mongo-cxx-driver-stable -DCMAKE_PREFIX_PATH=$PROJECT_DIR/shared/mongo-c-driver-1.8.0 ..
sudo make EP_mnmlstc_core
make
make install
# houra, you've done with mongo driver :)

# set correct pkg after this
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$PROJECT_DIR/"build/mongo-cxx-driver-stable/lib/pkgconfig":$PROJECT_DIR/"build/mongo-c-driver-1.8.0/lib/pkgconfig"

# msu personal framework
cd $PROJECT_DIR/msu
make

# all personal script are exectuted by msu makefile
# no need for more
