/*
Usage: ./codesend decimalcode [protocol] [pulselength]
decimalcode - As decoded by RFSniffer
protocol    - According to rc-switch definitions
pulselength - pulselength in microseconds

 'codesend' hacked from 'send' by @justy
 
 - The provided rc_switch 'send' command uses the form systemCode, unitCode, command
   which is not suitable for our purposes.  Instead, we call 
   send(code, length); // where length is always 24 and code is simply the code
   we find using the RF_sniffer.ino Arduino sketch.

(Use RF_Sniffer.ino to check that RF signals are being produced by the RPi's transmitter 
or your remote control)
*/
#include "../rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
     

int main(int argc, char *argv[]) {
    
    // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/ for more information.
    // PIN 7 is the GPIO 4 which corresponds to Driver 1 on Google Voice AIY
    int PIN = 7;
    
    // Parse the first parameter to this command as an integer
    int protocol = 1; //Is the protocol in use
    int pulseLength = 318; 

    // If no command line argument is given, print the help text
    if (argc == 1) {
        printf("Usage: %s decimalcode [protocol] [pulselength]\n", argv[0]);
        printf("decimalcode\t- As decoded by RFSniffer\n");
        printf("protocol\t- According to rc-switch definitions\n");
        printf("pulselength\t- pulselength in microseconds\n");
        return -1;
    }

    // Change protocol and pulse length accroding to parameters
    int code = atoi(argv[1]);
    if (argc >= 3) protocol = atoi(argv[2]);
    if (argc >= 4) pulseLength = atoi(argv[3]);
    
    if (wiringPiSetup () == -1) return 1;
    printf("sending code[%i]\n", code);
    RCSwitch mySwitch = RCSwitch();
    if (protocol != 0) mySwitch.setProtocol(protocol);
    if (pulseLength != 0) mySwitch.setPulseLength(pulseLength);
    mySwitch.enableTransmit(PIN);
    
    mySwitch.send(code, 24);
    
    return 0;

}
