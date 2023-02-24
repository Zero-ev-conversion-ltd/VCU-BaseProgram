#include "mbed.h"
#include "canmessage-mbed.h"
#include "vcupinmapp.h"
#include <cstdint>
#include "mbed_events.h"
using namespace std::chrono_literals;

#define LSB 0
#define MSB 1
#define UNSIGNED 0
#define SIGNED 1

CAN_message_t outMsg;
CANMessage inMsg;

Thread ms200;



DigitalOut led(LED1);
DigitalIn canFault(M_CAN1_NFAULT);
DigitalOut canNSTB(M_CAN1_NSTB,1); 
DigitalOut canEN(M_CAN1_EN,1);
AnalogOut throttleOut1(M_DAC_OUT_1);
AnalogOut throttleOut2(M_DAC_OUT_2);
AnalogIn throttleIn1(M_ANA_IN_3);
AnalogIn throttleIn2(M_ANA_IN_4);
AnalogIn analogin1(M_ANA_IN_1);
AnalogIn analogin2(M_ANA_IN_2);
AnalogIn throttle1fdbk(M_DAC_FDBK_1);
DigitalIn throttle2fdbk(M_DAC_FDBK_2);         //Needs changing back to analog in after hardware revision
DigitalOut hbridge1(H_BRIDGE_IN_1);
DigitalOut hbridge2(H_BRIDGE_IN_2);
DigitalIn ctrlpilot(M_CTRL_PILOT);
DigitalIn proxpilot(M_PROX_PILOT);
DigitalOut pwmout(M_PWM_OUT);
DigitalOut output1(OUT1_EN);
DigitalOut output2(OUT2_EN);
DigitalOut output3(OUT3_EN);
DigitalOut output4(OUT4_EN);
DigitalIn output12stat(OUT1_2_STAT);
DigitalIn output34stat(OUT3_4_STAT);
DigitalIn ignwake(M_IGN_WAKE);
DigitalOut linenable(M_LIN_EN);
DigitalIn throt5vfdbkin(M_THROT_5V);
DigitalIn degitalin1(M_DIG_IN_1);
DigitalIn degitalin2(M_DIG_IN_2);
DigitalIn degitalin3(M_DIG_IN_3);
DigitalIn degitalin4(M_DIG_IN_4);
DigitalOut chargenable(CHRG_EN);
DigitalOut watchdog(WDI);

uint16_t analoginthrot1mv, analoginthrot2mv = 0;
uint16_t dacout1mv = 2500;
uint16_t dacout2mv = 5000;

CAN can1(M_CAN_RXD, M_CAN_TXD, 500000);       //Public CAN to Vehicle
CAN can2(M_CAN2_RXD, M_CAN2_TXD, 500000);     //Private CAN to Tesla LDU

#define repeatTime     100ms

void flashled(){
    led = !led;
}

void testDAC(){
    if (throt5vfdbkin) {
        throttleOut1.write_u16(dacout1mv * 6.5534);         //65535 (full 16 bit) devided by 2 due to dac ration of double
        throttleOut2.write_u16(dacout2mv * 6.5534);         //(65535/2)/5000 = 6.5534
        //throttleOut1.write(0.757f);     //full range (5v out)
        //throttleOut2.write(0.3785f);    //half range (2.5v out)
    } else {
        throttleOut1.write_u16(0 * 6.5534);
        throttleOut2.write_u16(0 * 6.5534);
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

bool send_can1(){   
    outMsg.id  = 0x1;
    outMsg.len = 8;
    for (int i = 0; i < outMsg.len; i++) {outMsg.Data[i] = 0x00;}
    if(can1.write(CANMessage(outMsg.id, outMsg.Data, outMsg.len, CANData, CANStandard))){return true;}
    else{return false;}
}

bool send_can2(){   
    outMsg.id  = 0x2;
    outMsg.len = 8;
    for (int i = 0; i < outMsg.len; i++) {outMsg.Data[i] = 0x00;}
    if(can2.write(CANMessage(outMsg.id, outMsg.Data, outMsg.len, CANData, CANStandard))){return true;}
    else{return false;}
}

void can1Read(CANMessage inMsg){
  printf("CAN 1 Receive\r\n");
  switch (inMsg.id) {
    case 0x3:
      //variable = CAN_decode(&inMsg, 32, 16, LSB, SIGNED, 1, 0);
    break;
    default:
      break;
  }
}

void can2Read(CANMessage inMsg){
  flashled();
  printf("CAN 2 Receive\r\n");
  switch (inMsg.id) {
    case 0x3:
      //variable = CAN_decode(&inMsg, 32, 16, LSB, SIGNED, 1, 0);
    break;
    default:
      break;
  }
}

void testECUfunctionality(){
    while (true){
        //flashled();
        testDAC();
        testUART();
        testADC();
        send_can1();
        send_can2();
        ThisThread::sleep_for(200ms);
    }
}

void testECUfunctionality2(){
        //flashled();
        testDAC();
        testUART();
        testADC();
        send_can1();
        send_can2();
        return;
}

void checkcan(){
    if(can1.read(inMsg)){can1Read(inMsg);}
    if(can2.read(inMsg)){can2Read(inMsg);}
}

EventQueue queue;
Event<void()> event1(&queue, testECUfunctionality2);
Event<void()> event2(&queue, flashled);

void post_events(void){
    event1.post();      // Event1 with a value of 1
    event2.post();      // Event1 with a value of 2
}

int main(){

    //EventQueue queue;

    //queue.call_every(200ms, &testECUfunctionality);
    //queue.call_every(1ms, &checkcan);
    //queue.call_every(500ms, &testUART);
    //queue.dispatch_forever();

    //ms200.start(testECUfunctionality);

    Thread event_thread;

    event1.delay(10ms);       // Starting delay - 100 msec
    event1.period(200ms);      // Delay between each event - 200msec

    event2.delay(20ms);           // Starting delay - 400 msec
    event2.period(100ms);   // Single non periodic event

    event_thread.start(callback(post_events));
    event_thread.join();
    bool dispatchonce = false;

    //Need to poll canbus as mbed ran rx interrupts are broken
    while(true){
        if(can1.read(inMsg)){can1Read(inMsg);}
        if(can2.read(inMsg)){can2Read(inMsg);}
        if(!dispatchonce){
            queue.dispatch_forever();
            dispatchonce = false;
        }
    }
}