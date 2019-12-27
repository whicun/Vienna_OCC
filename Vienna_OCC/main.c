
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"

#include "ADC_config.h"
#include "PWM_config.h"
#include "sci.h"
#include "Spi.h"
interrupt void  adc_isr(void);

/*******************************************����ֵ�����******************************/
Uint16  AC_Current1,AC_Current2,AC_Current3,DC_Voltage1,DC_Voltage2;
float32 ia,ib,ic,Vc1,Vc2,Vdc,deltaVc;
float32 imax,imin,i3rd,deltaVm,Vm,abs_ia,abs_ib,abs_ic;
float32 da,db,dc;  //ռ�ձ�
Uint16  a1,a2,a3;  //PWM�Ƚ�ֵ

float32 graph1buffer[1600];  //graphʹ�õ�����
float32 graph2buffer[1600];
float32 graph3buffer[1600];
float32 graph4buffer[1600];
Uint16  count=0;

Uint16  sdata=0;  // SPI send data
float32 sdd=0;
/***************************************PI����************************************/
float32 PI_deltaVm(float32 IN1,float32 SET1);
float32 PI_Vm(float32 IN2,float32 SET2);  //������PI
float32 e0=0,e1=0,ee0=0,P0=0;   // ������d
float32 e2=0,e3=0,ee1=0,P1=0; //������q
float32 deltaUm=0; //Um=0
float32 KP1=0.1,KI1=0.05;
float32 KP2=0.5,KI2=0.02;

/*************************************��ʼֵ�����***********************************/
float32 TPR=3750;   // 150000/2fs ��ʱfs=20k
float32 Vdc_ref=1;  // ʵ��Vdc=800V ��Ӧ8
float32 deltaVdc_ref=0;


/*********************************main function**********************************/
void main(void)
{
	// ----Step 1. Initialize System Control:
	// PLL, WatchDog, enable Peripheral Clocks
	// This example function is found in the DSP2833x_SysCtrl.c file.
	   InitSysCtrl();   //ϵͳ��ʼ��  �ϵ�

	   EALLOW;
	   SysCtrlRegs.HISPCP.all = ADC_MODCLK;
	   EDIS;

	   InitGpio();     // GPIO������ ��ʼ��
	   EALLOW;
	   GpioCtrlRegs.GPAMUX1.all=0x00005555;//����GPIO0-GPIO7��ΪEPWM1234ģʽ
	   GpioCtrlRegs.GPADIR.all=0xFFFFFFFF;//����GPIO0-GPIO31��Ϊ���
	   GpioCtrlRegs.GPAQSEL1.all=0x00000000;//��ϵͳʱ��ͬ����32λ��ÿ��GPIOռ����λ
	   GpioCtrlRegs.GPAPUD.all=0x00000000;//ÿGPIO��ռ��һλ��ʹ���ڲ�����GPIO
	   GpioCtrlRegs.GPACTRL.all=0x00000000;//�������ڵ���ϵͳʱ��
	   GpioDataRegs.GPADAT.all = 0x00000000;//����Ӧ������������
	   InitScicGpio();      // SCI IO��ʼ��
	   InitSpiaGpio();      // SPI IO init
	   EDIS;
	// Initialize PIE control registers to their default state.
	// The default state is all PIE interrupts disabled and flags are cleared.
	// This function is found in the DSP2833x_PieCtrl.c file.
	   InitPieCtrl();             // �жϳ�ʼ�� ����
	// Disable CPU interrupts and clear all CPU interrupt flags:
	   IER = 0x0000;             // �ж�ʹ������ ���ж�
	   IFR = 0x0000;
	// Initialize the PIE vector table with pointers to the shell Interrupt Service Routines (ISR).
	// This will populate the entire table, even if the interrupt is not used in this example.  This is useful for debug purposes.
	// The shell ISR routines are found in DSP2833x_DefaultIsr.c.  This function is found in DSP2833x_PieVect.c.
	   InitPieVectTable();       // �����ж�������

	    EALLOW;  // This is needed to write to EALLOW protected registers
//		PieVectTable.EPWM1_INT = &epwm1_isr;    //  �жϵ�ַ��ֵ
		PieVectTable.ADCINT = &adc_isr;
	    PieVectTable.SCIRXINTC = &uartIsr;
	    PieVectTable.SCITXINTC = &uart_send;
	    EDIS;    // This is needed to disable write to EALLOW protected registers

	    EALLOW;
	    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
	    EDIS;
	    InitEPwm1Example();  // ePWMģ���ʼ��
        InitEPwm2Example();
	    InitEPwm3Example();
	    InitEPwm4Example();
	    InitAdc();  // USE DSP ADC

		adc_config();       // AD��ʼ��
		sci_init();        //SCI��ʼ��
	    spi_init();		  // init SPI
	    EALLOW;
	    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
	    EDIS;

		IER |= M_INT1;//Enable ADCINT in PIE
//		IER |= M_INT3;//PWM
		IER|=M_INT8; //Enable SCI in PIE
		// Enable INTn in the PIE: Group 3 interrupt 1-6
//		PieCtrlRegs.PIEIER3.bit.INTx1 = 1;//PWM1      // ���ж�ʹ��
		PieCtrlRegs.PIEIER1.bit.INTx6 = 1;//ADC
	    PieCtrlRegs.PIEIER8.bit.INTx5=1;  //SCI
	    PieCtrlRegs.PIEIER8.bit.INTx6=1;
		// Enable global Interrupts and higher priority real-time debug events:
		EINT;   // Enable Global interrupt INTM
		ERTM;   // Enable Global realtime interrupt DBGM
		// Step 5. User specific code:
//		AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
    	while(1)
	     { }
}

interrupt void  adc_isr(void)    // AD�ж�
{
	AC_Current1=AdcRegs.ADCRESULT0 >>4;    // 35clock
	AC_Current2=AdcRegs.ADCRESULT1 >>4;
//	AC_Current3=AdcRegs.ADCRESULT2 >>4;
	DC_Voltage1=AdcRegs.ADCRESULT2 >>4;
    DC_Voltage2=AdcRegs.ADCRESULT3 >>4;

	ib=AC_Current2*0.01221-25.1630;
	ic=AC_Current3*0.01221-25.0755; //-ia-ib;
    ia=-ib-ic;
	Vc1=DC_Voltage1*0.246-500.0048;
    Vc2=DC_Voltage2*0.246-500.4558;

	Vdc=0.01*(Vc1+Vc2);        // ��ʱ��ѹ����ϵ������Ϊ0.01
	deltaVc=0.1*(Vc1-Vc2);

	    GpioDataRegs.GPACLEAR.bit.GPIO24=1;        // set low for DAC7311 sync signal
	    while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG ==1) {}
	//    SpiaRegs.SPITXBUF=sdata;                     // Transmit data
	    spi_xmit(sdata);
	    while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG ==1) {}
	    // Check against sent data

	if(ia>ib)            //197clock
	 {
		imax=ia;
		imin=ib;
		if(imax<ic)
	        imax=ic;
		else if(imin>ic)
			imin=ic;
	 }
	else
	{
		imax=ib;
		imin=ia;
		if(imax<ic)
	        imax=ic;
		else if(imin>ic)
			imin=ic;
	}

    i3rd=-0.5*(imax+imin);
    deltaVm=0; //PI_deltaVm(deltaVc,deltaVdc_ref);

    abs_ia=fabs(ia+i3rd+deltaVm);   // 3��fabs=343clock
    abs_ib=fabs(ib+i3rd+deltaVm);
    abs_ic=fabs(ic+i3rd+deltaVm);
    Vm=PI_Vm(Vdc,Vdc_ref);          // 827clock

    da=1-abs_ia/Vm;       //1213clock
    db=1-abs_ib/Vm;
    dc=1-abs_ic/Vm;

	if(da>1)       da=1;  // ռ�ձ�da,db,dc�޷�   366clock
	else if(da<0)  da=0;    //0.055
	if(db>1)       db=1;
	else if(db<0)  db=0;
	if(dc>1)       dc=1;
	else if(dc<0)  dc=0;

	a1=da*3750+0.5;       // 949clock
	a2=db*3750+0.5;
	a3=dc*3750+0.5;
    EPwm1Regs.CMPA.half.CMPA=a1;
    EPwm2Regs.CMPA.half.CMPA=a2;
    EPwm3Regs.CMPA.half.CMPA=a3;
/***tiaoshiyong
	if(count<1600)                 // graph�õ�����  40clock
	   {
		graph1buffer[count]=ib; //abs_ia;
		graph2buffer[count]=ic; //deltaVm;
		graph3buffer[count]=ia;//deltaVc;
		graph4buffer[count++]=Vc2;//db;
	   }
	else
		count=0;  */

	GpioDataRegs.GPASET.bit.GPIO24 = 1;
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
//	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;         // Reset SEQ1  (��ͣģʽ)
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
	return;

}
 float32 PI_deltaVm(float32 IN1,float32 SET1)   //�е��λƽ�⻷PI������
{
	e0= SET1 - IN1;
	ee0= e0 - e1;
	P0 = KP1*ee0 + KI1*e0;
	e1 =e0;
	deltaUm=P0+deltaUm;
	if(deltaUm>2)
		deltaUm=2;
	else if(deltaUm<-2)
		deltaUm=-2;
	return deltaUm;
}

float32 PI_Vm(float32 IN2,float32 SET2)   //��ѹ�⻷PI������
{
	e2 = SET2 - IN2;
	ee1 = e2 - e3;
	P1 = KP2*ee1 + KI2*e2;
//	P1=  KP2*ee1+0.000025*KI2*e2+0.000025*KI2*e3;
/*	  if(P1>1)
		P1=1;
	  else if(P1<-0.8)
	 P1= -0.8;*/
	e3 =e2;
	Um=P1+Um;                       //Um��ֵ�޶����������iabc������ֵ
	if(Um>10)
			Um=10;
	else if(Um<0)
		    Um=0.01;
	return Um;
}
