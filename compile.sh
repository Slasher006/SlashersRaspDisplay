#!/bin/bash
# Script zum compilieren fuer mein Display


gcc -o slashdispshow pcd8544_rpi.cpp PCD8544.cpp -L/usr/lib -lwiringPi

#sudo cp LCDslash.service /etc/systemd/system/LCDslash.service

sudo systemctl stop LCDslash.service


cp slashdispshow /home/slasher006/slashdispshow

sudo systemctl restart LCDslash.service
