//###########################################################################
// $TI Release: DSP281x C/C++ Header Files V1.20 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "global.h"
#include "main.h"

//#define             FLASH         1


// Functions that will be run from RAM need to be assigned to
// a different section.  This section will then be mapped using
// the linker cmd file.
// #pragma CODE_SECTION(eva_timer1_isr, "ramfuncs");
#ifdef  FLASH

extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;

#endif
#define                     INPUT             0

Uint16 sdataA[8];    // Send data for SCI-A
Uint16 sdataB[8];    // Send data for SCI-B
Uint16 rdataA[8];    // Received data for SCI-A
Uint16 rdataB[8];    // Received data for SCI-A
Uint16 rdata_pointA; // Used for checking the received data
Uint16 rdata_pointB;
AS608   *as608_p, as608;
Uint16 id_flag = false;
uint16  error_count;
void main(void)
{
    Uint32 k;
    Uint16 i, n,ensure, msg_str[40];
    Uint16 count = 0;
    Uint16 addr=0;
    as608_p  =    &as608;
    // Step 1. Initialize System Control:-
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP281x_SysCtrl.c file.
    InitSysCtrl();

    // Step 2. Initalize GPIO:
    // This example function is found in the DSP281x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    InitGpio();  // Skipped for this example

    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    DINT;

    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP281x_PieCtrl.c file.
    InitPieCtrl();

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in DSP281x_DefaultIsr.c.
    // This function is found in DSP281x_PieVect.c.
    InitPieVectTable();

    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.SCIRXINTA = &sciaRxFifoIsr;
    PieVectTable.SCIRXINTB = &scibRxFifoIsr;
    PieVectTable.SCIRXINTC = &scicRxFifoIsr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

    // Step 4. Initialize all the Device Peripherals:
    // This function is found in DSP281x_InitPeripherals.c
    // InitPeripherals(); // Not required for this example


    AS608_INIT( as608_p );
    // Step 5. User specific code, enable interrupts:

    // Init send data.  After each transmission this data
    // will be updated for the next transmission
    // ���� 4.��ʼ��Ƭ������:
    InitCpuTimers();   // ��������Ҫ��ʼ��CPU��ʱ��
    DELAY_US(2000);
    // Copy time critical code and Flash setup code to RAM
    // This includes the following ISR functions: EvaTimer1(), EvaTimer2()
    // EvbTimer3 and and InitFlash();
    // The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
    // symbols are created by the linker. Refer to the F2812.cmd file.
#ifdef  FLASH
    MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);

    // Call Flash Initialization to setup flash waitstates
    // This function must reside in RAM
    InitFlash();
#endif
    // Enable interrupts required for this example
    PieCtrlRegs.PIEIER9.bit.INTx1   =1;     // PIE Group 9, INT1
    PieCtrlRegs.PIEIER9.bit.INTx3   =1;     // PIE Group 9, INT1
    IER |= M_INT9; // Enable CPU INT

    scic_msg("scic: �豸���ڳ�ʼ�����������������.... \n\r");

    DELAY_MS(2000);
    SCI_INIT();
    ERTM;   // Enable Global realtime interrupt DBGM
    // Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    // Step 6. IDLE loop. Just sit and loop forever:
    scic_msg("scic: ��ʼ���������ź�.... \n\r");
    scic_msg("scic: ������������źų�ʱ��û��Ӧ���밴�����ϵĺ�ɫ��λ���������� \n\r");
    while( !as608_p->hand_shake(as608_p, as608_p->device_address )  );
    //printf("debug:�豸�������\n");
    DELAY_MS(100);

    scic_msg("scic: ��ȡ�豸ָ�Ƹ���....\n\r");
    ensure = as608_p->valid_templete_num( as608_p, &n );
    if( ensure != 0x00 ) {
        as608_p->ensure_message( as608_p, ensure );
    }
    DELAY_MS(100);
    scic_msg("scic: ��ȡ�豸����....\n\r");
    ensure = as608_p->read_sys_para( as608_p, &as608_p->system_para );

    if ( ensure == 0x00 ) {
        memset(msg_str, 0,50);
        sprintf( msg_str, "scic: current num: %d, level: %d\n\r" ,as608_p->system_para.PS_max, as608_p->system_para.PS_level);
        scic_msg( msg_str );
    }else {
        as608_p->ensure_message( as608_p, ensure );
    }
#if INPUT
    DELAY_MS(1000);
    as608_p->add_finger( as608_p );
#endif
    k = 0;
    while(1) {
#if !INPUT
        if( TOUCH ==  as608_p->read_state( as608_p ) ) {
            k++;
            if (k >= 600000) {
                as608_p->press_finger( as608_p );
                k = 0;
            }
        }
#endif

    }
}
/*------------------------------------------*/
/*��ʽ������void                            */
/*����ֵ:void                              */
/*��������:��ʱ��CPU0�жϷ����ӳ���         */
/*------------------------------------------*/

void Delay(Uint16 t)                                                        //��ʱ����
{
    Uint32 i=0;
    Uint32 gain = 300000;                                                   //��ʱ����
    Uint32 base=0;
    base=gain*t;
    for(i=0;i<=base;i++);
}





//===========================================================================
// No more.
//===========================================================================
