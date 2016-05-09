/*
  RFSniffer

  Usage: ./RFSniffer [<pulseLength>]
  [] = optional

  Hacked from http://code.google.com/p/rc-switch/
  by @justy to provide a handy RF code sniffer
*/

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
     
     
RCSwitch mySwitch;
 


int main(int argc, char *argv[]) {
	
	pinMode (20, OUTPUT);
	pinMode (21, OUTPUT);
	pinMode (16, OUTPUT);
	
	digitalWrite (16, HIGH);
   	delay(5000);
   	digitalWrite (16, LOW);
	
	digitalWrite (21, HIGH);
   	delay(5000);
   	digitalWrite (21, LOW);
   	
   	digitalWrite (16, HIGH);
	 
     // This pin is not the first pin on the RPi GPIO header!
     // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     // for more information.
     int PIN = 2;
     
     if(wiringPiSetup() == -1) {
       printf("wiringPiSetup failed, exiting...");
       return 0;
     }
     pinMode (3, OUTPUT);
     int pulseLength = 0;
     if (argv[1] != NULL) pulseLength = atoi(argv[1]);

     mySwitch = RCSwitch();
	 if (pulseLength != 0) mySwitch.setPulseLength(pulseLength);
     mySwitch.enableReceive(PIN);  // Receiver on interrupt 0 => that is pin #2
     
    
     while(1) {
  
      if (mySwitch.available()) {
    
        int value = mySwitch.getReceivedValue();
    
        if (value == 0) {
          printf("Unknown encoding\n");
        } else {    
   		if(mySwitch.getReceivedValue() == 11466866)
   		{
   			
   			digitalWrite (3, HIGH);
   			delay(2000);
   			digitalWrite (3, LOW);
   		}
          printf("Received %i\n", mySwitch.getReceivedValue() );
        }
    
        mySwitch.resetAvailable();
    
      }
      
     
  
  }

  exit(0);


}

