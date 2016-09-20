/*
 Pi_Serial_test.cpp - SerialProtocol library - demo
 Copyright (c) 2014 NicoHood.  All right reserved.
 Program to test serial communication
 
 Compile with:
 sudo gcc -o Pi_Serial_Test.o Pi_Serial_Test.cpp -lwiringPi -DRaspberryPi -pedantic -Wall
 sudo ./Pi_Serial_Test.o
 */




#include "Adafruit_NeoPixel.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
 



// just that the Arduino IDE doesnt compile these files.
#ifdef RaspberryPi 
 
//include system librarys
#include <stdio.h> //for printf
#include <stdint.h> //uint8_t definitions
#include <stdlib.h> //for exit(int);
#include <string.h> //for errno
#include <errno.h> //error output
 
//wiring Pi
#include <wiringPi.h>
#include <wiringSerial.h>
 
// Find Serial device on Raspberry with ~ls /dev/tty*
// ARDUINO_UNO "/dev/ttyACM0"
// FTDI_PROGRAMMER "/dev/ttyUSB0"
// HARDWARE_UART "/dev/ttyAMA0"
char device[]= "/dev/ttyACM0";
// filedescriptor
int fd;
unsigned long baud = 9600;
unsigned long time=0;
 
//prototypes
int main(int argc, char *argv[]);
void loop(char argv[]);
void setup(void);
 
void setup(){
 
  printf("%s \n", "Raspberry Startup!");
  fflush(stdout);
 
  //get filedescriptor
  if ((fd = serialOpen (device, baud)) < 0){
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    exit(1); //error
  }
 
  //setup GPIO in wiringPi mode
//  if (wiringPiSetup () == -1){
//    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
//    exit(1); //error
//  }
 
}
 
void loop(char argv[]){
  // Pong every 3 seconds
int color;

/*
  if(millis()-time>=3000){
    //serialPuts (fd, ""\n");
    // you can also write data from 0-255
    // 65 is in ASCII 'A'
   serialPutchar (fd, 67);
    time=millis();

	
  }
*/

color = atoi(argv);

printf("color %d \n", color);
if(color == 0){
//serialPutchar(fd, 65);
//char newchar = serialGetchar (fd);
//printf("%c",newchar);
pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

pixels.show(); // This sends the updated pixel color to the hardware.
fflush(stdout);
}

else if(color == 1){
//serialPutchar(fd, 66);
/char newchar = serialGetchar (fd);
//printf("%c",newchar);
pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.
fflush(stdout);
}

else if(color == 2){
//serialPutchar(fd, 67);
//char newchar = serialGetchar (fd);
//printf("%c",newchar);
pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.
fflush(stdout);
}

else if(color == 3){
//serialPutchar(fd, 68);
//char newchar = serialGetchar (fd);
//printf("%c",newchar);
pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.
fflush(stdout);
}

else if(color == 4){
//serialPutchar(fd, 69);
//char newchar = serialGetchar (fd);
//printf("%c",newchar);
pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.
fflush(stdout);
}

else if(color == 5){
//serialPutchar(fd, 70);
//char newchar = serialGetchar (fd);
//printf("%c",newchar);
pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.
fflush(stdout);
}

else if(color == 6){
//serialPutchar(fd, 71);
//char newchar = serialGetchar (fd);
//printf("%c",newchar);
pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.
fflush(stdout);
}

else if(color == 7){
//serialPutchar(fd, 72);
//char newchar = serialGetchar (fd);
//printf("%c",newchar);
pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.
fflush(stdout);
}

else if(color == 8){
//serialPutchar(fd, 73);
//char newchar = serialGetchar (fd);
//printf("%c",newchar);
pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.
fflush(stdout);
}


/*
  // read signal
  if(serialDataAvail (fd)){
    char newChar = serialGetchar(fd);
    printf("%c", newChar);
    fflush(stdout);

  }
*/
 

}
 
// main function for normal c++ programs on Raspberry
int main(int argc, char *argv[]){
  int i=0;
  printf("%s %s %s", argv[1], argv[2], argv[3]);
  setup();
//while(i<3){
//printf("%d\n",i);
//if(i==10){
//sleep(1);
//exit(0);
//}
loop(argv[1]);
//i++;
//}
  return 0;
}
 
#endif //#ifdef RaspberryPi
