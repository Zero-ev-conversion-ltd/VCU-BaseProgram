#include "mbed.h"
#include "felltenDevices.h"
#include <cstdint>
#include "can.h"


DigitalOut canNSTB(can1nstb,1); 
DigitalOut canEN(can1en,1);
CAN can1(can1rx, can1tx, 500000);       //Public CAN to Vehicle
CAN can2(can2rx, can2tx, 500000);       //Private CAN to Tesla LDU
//DigitalOut led(PA_5);
DigitalOut led(LED1);
DigitalIn canFault(can1nfault);
//DigitalOut canNSTB(can1nstb);
//DigitalOut canEN(can1en);
AnalogOut throttleOut1(dacout1);
AnalogOut throttleOut2(dacout2);
AnalogIn throttleIn1(analogin3);
AnalogIn throttleIn2(analogin4);
AnalogIn vacSensor(analogin1);
AnalogIn modeSwitch(analogin2);
AnalogIn throttle1fdbk(throttlefeedback1);
DigitalIn throttle2fdbk(throttlefeedback2);         //Needs changing back to analog in after hardware revision

#define repeatTime     100ms

void canInit(){
    wait_us(100);
    canEN = 1;
    wait_us(100);
    canNSTB = 1;
    wait_us(100);
    //can_init_freq(&cb1, can1rx, can1tx, 500000);
}

int main(){
    //canInit();
    //throttleOut1.write(1.0f);
    //throttleOut2.write(0.5f);
  
    while (true) {
        led = !led;
        ThisThread::sleep_for(repeatTime);
        //printf("Hello World\n");
    }
}