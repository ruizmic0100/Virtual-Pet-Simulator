#!/bin/bash

flash()
{
    echo "Flash process initiated..."
    cp src/build/output.uf2 /media/ghostrunner/RPI-RP2/
    echo "Flash process successfull..."
}

flash