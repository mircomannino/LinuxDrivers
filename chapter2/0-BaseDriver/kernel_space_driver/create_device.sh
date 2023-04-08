#!/bin/bash

sudo mknod /dev/base_driver c 60 0 
sudo chmod 666 /dev/base_driver

ls /dev/base_driver