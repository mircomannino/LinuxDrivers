#!/bin/bash

INSTALL="on"

if [[ "$#" -eq 1 ]]; then
    INSTALL="off"
    if [[ "$1" = "remove" ]]; then
        sudo rmmod base_driver
        echo "[INFO] Module removed"
    else
        echo "Usage: \"./instal_module.sh remove\" for removing module" 
    fi
fi

if [[ ${INSTALL} = "on" ]]; then
    sudo insmod base_driver.ko
    echo "[INFO] Module added"
fi