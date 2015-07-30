/*
=================================================================================
 Name        : pcd8544_rpi.c
 Version     : 0.1

 Copyright (C) 2012 by Andre Wussow, 2012, desk@binerry.de

 Description :
     A simple PCD8544 LCD (Nokia3310/5110) for Raspberry Pi for displaying some system informations.
	 Makes use of WiringPI-library of Gordon Henderson (https://projects.drogon.net/raspberry-pi/wiringpi/)

	 Recommended connection (http://www.raspberrypi.org/archives/384):
	 LCD pins      Raspberry Pi
	 LCD1 - GND    P06  - GND
	 LCD2 - VCC    P01 - 3.3V
	 LCD3 - CLK    P11 - GPIO0
	 LCD4 - Din    P12 - GPIO1
	 LCD5 - D/C    P13 - GPIO2
	 LCD6 - CS     P15 - GPIO3
	 LCD7 - RST    P16 - GPIO4
	 LCD8 - LED    P01 - 3.3V

================================================================================
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
================================================================================
 */
#include <wiringPi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include "PCD8544.h"
#include "unistd.h"
#include <sys/ioctl.h>  /* ioctl()  */
#include <sys/socket.h> /* socket() */
#include <arpa/inet.h>
#include <linux/if.h>   /* struct ifreq */
#include <sys/stat.h>
#include <time.h>
#include "networkstats.h"
#include <string.h>

//#include "timertest.h"

using namespace std;
//TODO Finde alles
// pin setup
int _din = 1;
int _sclk = 0;
int _dc = 2;
int _rst = 4;
int _cs = 3;

// lcd contrast
//may be need modify to fit your screen!  normal: 30- 90 ,default is:45 !!!maybe modify this value!
int contrast = 45;

int main (void)
{
    networkstats nwstats;
    //timertest ymum;

  /*
  int s;
  char ss[10];
  s = ymum.zahl(22);
  sprintf(ss,"%d",s);
*/
  //char debugstrings[20];



  // check wiringPi setup
  if (wiringPiSetup() == -1)
  {
	printf("wiringPi-Error\n");
    exit(1);
  }

  // init and clear lcd
  LCDInit(_sclk, _din, _dc, _cs, _rst, contrast);
  LCDclear();


  //  slasherlogo();

  delay(2000);

  //daemoncode
  pid_t pid, sid; //processid und Sessionid

  // fork off the parentprocess
  pid = fork();
  if (pid < 0){
    exit(EXIT_FAILURE);
  }
  //wenn wir eine gute PID bekommen können wir den parentprocess verlassen
  if (pid > 0)
    {
      exit(EXIT_SUCCESS);
    }

  //ändere filemode makse
  umask(0);

  //erstelle eine neue sessenid fuer den childprocess
  sid = setsid();
  if(sid < 0)
    {
      exit(EXIT_FAILURE);
    }

  //ender das arbeitsverzeichniss
  if ((chdir("/")) < 0)
    {
      exit(EXIT_FAILURE);

    }
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    time_t rawtime;
    struct tm * timeinfo;
    char mytime [80]; // In diesem String speichere ich meine Zeit


    //TODO: RX und TX des Netzwerkstreams holen und ausgeben.
    /*

    */


    //hauptschleife
    while(1){


	  LCDclear();

	  // get system usage / info
	  struct sysinfo sys_info;
	  if(sysinfo(&sys_info) != 0)
	  {
		printf("sysinfo-Error\n");
	  }

	  // cpu info
	  char cpuInfo[15];
	  unsigned long avgCpuLoad = sys_info.loads[0] / 1000;
	  sprintf(cpuInfo, "CPU %ld%%", avgCpuLoad);

	  // ram info
	  char ramInfo[15];
	  unsigned long totalRam = sys_info.freeram / 1024 / 1024;
	  sprintf(ramInfo, "RAM %ld MB", totalRam);

	  //char mprocs[10];
	  //long int processes = sys_info.procs;
	  //sprintf(mprocs,"Procs %ld",processes);


    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (mytime,80,"Zeit %I:%M",timeinfo);

      LCDdrawstring(0,0,mytime);
   	  LCDdrawstring(0,10,cpuInfo);
	  LCDdrawstring(0,20,ramInfo);


	  //char testa[10];

	  //printf(testa, "%d", "dh"); //gib5 aus

	  //LCDdrawstring(0,30,testa);



	  LCDdisplay();
	  delay(1000);

    }


    //    close(fd);

    exit(EXIT_SUCCESS);
     //return 0;
}
