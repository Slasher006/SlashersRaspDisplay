#!/bin/bash
# Script zum compilieren fuer mein Display


gcc -o slashdispshow pcd8544_rpi.c PCD8544.c -L/usr/lib -lwiringPi

sudo systemctl stop LCDslash.service

cp slashdispshow /home/slasher006/slashdispshow

sudo systemctl restart LCDslash.service
