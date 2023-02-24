#include "mbed.h"
#include "vcupinmapp.h"
#include <cstdint>
#include "can.h"

//DigitalOut led(PA_5);
DigitalOut led(LED1);
DigitalIn canFault(can1nfault);
DigitalOut canNSTB(can1nstb,1); 
DigitalOut canEN(can1en,1);
AnalogOut throttleOut1(dacout1);
AnalogOut throttleOut2(dacout2);
AnalogIn throttleIn1(analogin3);
AnalogIn throttleIn2(analogin4);
AnalogIn vacSensor(analogin1);
AnalogIn modeSwitch(analogin2);
AnalogIn throttle1fdbk(throttlefeedback1);
DigitalIn throttle2fdbk(throttlefeedback2);         //Needs changing back to analog in after hardware revision
DigitalOut hbridge1out(hbridge1);
DigitalOut hbridge2out(hbridge2);
DigitalIn ctrlpilotin(ctrlpilot);
DigitalIn proxpilotin(proxpilot);
DigitalOut pwmoutput(pwmout);
DigitalOut output1out(output1);
DigitalOut output2out(output2);
DigitalOut output3out(output3);
DigitalOut output4out(output4);
DigitalIn output12statin(output12stat);
DigitalIn output34statin(output34stat);
DigitalIn ignwakein(ignwake);
DigitalOut linenableout(linenable);
DigitalIn throt5vfdbkin(throt5vfdbk);
DigitalIn degitalin1in(degitalin1);
DigitalIn degitalin2in(degitalin2);
DigitalIn degitalin3in(degitalin3);
DigitalIn degitalin4in(degitalin4);
DigitalOut chargenableout(chargenable);
DigitalOut watchdogout(watchdog);

uint16_t analoginthrot1mv, analoginthrot2mv = 0;


CAN can1(can1rx, can1tx, 500000);       //Public CAN to Vehicle
CAN can2(can2rx, can2tx, 500000);       //Private CAN to Tesla LDU


#define repeatTime     100ms

void flashled(){
    led = !led;
}

void testDAC(){
    if (throt5vfdbkin) {
        throttleOut1.write(0.757f);     //full range
        throttleOut2.write(0.3785f);    //half range
    } else {
        throttleOut1.write(0.0);
        throttleOut2.write(0.0);
    }
}

void testUART(){
    printf("CU Stat:\r\n");
    printf("Throt in 1: %d\r\n", analoginthrot1mv);
    printf("Throt in 2: %d\r\n", analoginthrot2mv);
}

void testADC(){
    analoginthrot1mv = throttleIn1.read_u16();
    analoginthrot2mv = throttleIn2.read_u16();
    analoginthrot1mv= analoginthrot1mv * 0.0763;        //5000mV full scale = 65535 * 0.0763
    analoginthrot2mv= analoginthrot2mv * 0.0763;        //5000mV full scale = 65535 * 0.0763
}

void testECUfunctionality(){
    flashled();
    testDAC();
    testUART();
    testADC();
}

int main(){
    while (true) {
        ThisThread::sleep_for(repeatTime);
        testECUfunctionality();
    }
}