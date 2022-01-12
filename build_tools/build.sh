#!/bin/bash

build()
{
    cd ../src/
    if [ -d "build/" ]
    then
        rm -rf build
        echo "Build Folder Removed due to it already existing..."
        mkdir build
        echo "Build Folder Created..."
    else
        mkdir build
        echo "Build folder Created due to it not existing..."
    fi

    cd build/
    export PICO_SDK_PATH=../../pico-sdk
    cmake ..
    make -j4

    echo "Finished Build Process..."
    echo "Proceed to flash the board..."
}

build
