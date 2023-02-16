#include "mbed.h"

#define can1rx PB_8
#define can1tx PB_9
#define can1nfault PC_4
#define can1nstb PC_5
#define can1en PB_0
#define can2rx PB_5
#define can2tx PB_13
#define statusledpin PC_13       //old PA_5 new PC_13
#define dacout1 PA_4
#define dacout2 PA_5
#define analogin1 PC_0
#define analogin2 PC_1
#define analogin3 PC_2
#define analogin4 PC_3
#define throttlefeedback1 PB_1      //Used for BOOT1 - conflict!!!
#define throttlefeedback2 PB_10     //cant use PB_10 as ADC input!!!
#define hbrdige1 PA_6   //to instantiate
#define hbridge2 PA_7   //to instantiate
#define output4 PB_14   //to instantiate

CAN can1(can1rx, can1tx, 500000);       //Public CAN to Vehicle
CAN can2(can2rx, can2tx, 500000);       //Private CAN to Tesla LDU
DigitalOut led(statusledpin);
DigitalIn canFault(can1nfault);
DigitalOut canNSTB(can1nstb);
DigitalOut canEN(can1en);
AnalogOut throttleOut1(dacout1);
AnalogOut throttleOut2(dacout2);
AnalogIn throttleIn1(analogin3);
AnalogIn throttleIn2(analogin4);
AnalogIn vacSensor(analogin1);
AnalogIn modeSwitch(analogin2);
AnalogIn throttle1fdbk(throttlefeedback1);
DigitalIn throttle2fdbk(throttlefeedback2);         //Needs changing back to analog in after hardware revision

#define repeatTime     100ms

int main(){
    throttleOut1.write(1.0f);
    throttleOut2.write(0.5f);
    while (true) {
        led = !led;
        ThisThread::sleep_for(repeatTime);
    }
}