#ifndef vcupinmapp
#define vcupinmapp

#define hardwareVCU

#ifdef hardwareVCU
    #define can1rx PB_8
    #define can1tx PB_9
    #define can1nfault PC_4
    #define can1nstb PC_5
    #define can1en PB_0
    #define can2rx PB_5
    #define can2tx PB_13
    #define statusledpin PC_13
    #define dacout1 PA_4
    #define dacout2 PA_5
    #define analogin1 PC_0
    #define analogin2 PC_1
    #define analogin3 PC_2
    #define analogin4 PC_3
    #define throttlefeedback1 PB_1      //Used for BOOT1 - conflict!!!
    #define throttlefeedback2 PB_10     //cant use PB_10 as ADC input!!!
    #define hbridge1 PA_6   //to instantiate below down
    #define hbridge2 PA_7
    #define ctrlpilot PA_0
    #define proxpilot PA_1
    #define pwmout PB_12
    #define output1 PC_9
    #define output2 PC_7
    #define output3 PC_6
    #define output4 PB_14
    #define output12stat PB_8
    #define output34stat PB_15
    #define ignwake PA_8
    #define lintx PA_9
    #define linrx PA_10
    #define linenable PA_11
    #define throt5vfdbk PA_12
    #define degitalin1 PC_10
    #define degitalin2 PC_11
    #define degitalin3 PC_12
    #define degitalin4 PD_2
    #define chargenable PB_6
    #define watchdog PB_7
#endif
#endif