# Makefile fuer das Projekt Raspi2 Nokiadisplay
CC=gcc 
CFLAGS= -Wall -g
LDFLAGS= -lwiringPi

prog: 
	$(CC) $(CFLAGS) -o slashdispshow pcd8544_rpi.cpp PCD8544.cpp $(LDFLAGS)

clean: 
	rm slashdispshow
.PHONY:
