#ifndef vcupinmapp
#define vcupinmapp

#define hardwareVCU

#ifdef hardwareVCU
    #define M_CAN_RXD PB_8
    #define M_CAN_TXD PB_9
    #define M_CAN1_NFAULT PC_4
    #define M_CAN1_NSTB PC_5
    #define M_CAN1_EN PB_0
    #define M_CAN2_RXD PB_5
    #define M_CAN2_TXD PB_13
    #define statusledpin PC_13
    #define M_DAC_OUT_1 PA_4
    #define M_DAC_OUT_2 PA_5
    #define M_ANA_IN_1 PC_0
    #define M_ANA_IN_2 PC_1
    #define M_ANA_IN_3 PC_2
    #define M_ANA_IN_4 PC_3
    #define M_DAC_FDBK_1 PB_1      //Used for BOOT1 - conflict!!!
    #define M_DAC_FDBK_2 PB_10     //cant use PB_10 as ADC input!!!
    #define H_BRIDGE_IN_1 PA_6   //to instantiate below down
    #define H_BRIDGE_IN_2 PA_7
    #define M_CTRL_PILOT PA_0
    #define M_PROX_PILOT PA_1
    #define M_PWM_OUT PB_12
    #define OUT1_EN PC_9
    #define OUT2_EN PC_7
    #define OUT3_EN PC_6
    #define OUT4_EN PB_14
    #define OUT1_2_STAT PB_8
    #define OUT3_4_STAT PB_15
    #define M_IGN_WAKE PA_8
    #define M_LIN_TXD PA_9
    #define M_LIN_RXD PA_10
    #define M_LIN_EN PA_11
    #define M_THROT_5V PA_12
    #define M_DIG_IN_1 PC_10
    #define M_DIG_IN_2 PC_11
    #define M_DIG_IN_3 PC_12
    #define M_DIG_IN_4 PD_2
    #define CHRG_EN PB_6
    #define WDI PB_7
#endif
#endif