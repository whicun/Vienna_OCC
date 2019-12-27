/*
 * PWM_config.c
 *
 */
#include "DSP28x_Project.h"

void InitEPwm1Example(void)
{
	//----------------- Initialize ePWM1-------------------
/*	   EALLOW;
	   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
	   EDIS;
*/
	   EPwm1Regs.TBPHS.half.TBPHS = 0x0000;   	//��λ�Ĵ���ֵΪ0
	   EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;	// Up_down_count mode,����ԳƲ���,�Ҹ�����ģʽ����ģʽ
	   EPwm1Regs.TBCTL.bit.PHSEN = 0; 	// ��λװ�ؽ�ֹ
	   EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW; 	// enable the shadow register ,ʹ��ӳ��Ĵ���
	   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;	//TBCLK=SYSCLKOUT
	   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;	//TBCLK=SYSCLKOUT

	   EPwm1Regs.TBCTL.bit.SYNCOSEL =TB_CTR_ZERO;   	// master module
	   EPwm1Regs.TBPRD = 3750;             //      150/(2*fs)

	   EPwm1Regs.CMPA.half.CMPA=1000;
	   EPwm1Regs.CMPB=1000;

	   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; 		// shadow mode
	   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW; 		// shadow mode

	   EPwm1Regs.CMPCTL.bit.LOADAMODE =CC_CTR_ZERO; 	// ����ʱ����
	   EPwm1Regs.CMPCTL.bit.LOADBMODE =CC_CTR_ZERO; 	// ����ʱ����

	// EPwm1Regs.ETSEL.bit.INTSEL = 0x001;     	// Select INT on Zero event�������жϣ�
	// EPwm1Regs.ETSEL.bit.INTSEL = 0x002;     	// �����ж�
	// EPwm1Regs.ETSEL.bit.INTEN = 1;  			// Enable INT  ò��û���õ����жϣ�Ĭ�ϵ�����ѡ����?
	// EPwm1Regs.ETPS.bit.INTPRD = 0x01; 		// Generate INT on 1st event

	   EPwm1Regs.AQCTLA.bit.CAD =AQ_SET ;     //PWMA�������Ч
	   EPwm1Regs.AQCTLA.bit.CAU =AQ_CLEAR;
       EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR ;    //PWMB�������Ч
	   EPwm1Regs.AQCTLB.bit.CBU =AQ_SET ;
	 //EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;//����ʹ��
	 //EPwm1Regs.DBCTL.bit.IN_MODE =0;  //EPWMxA��Ϊ��ʱ�ź�Դ��
	 //EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_LOC	;  //�͵�ƽ��Ч�������,��������11.24
	 //EPwm1Regs.DBCTL.bit.POLSEL =DB_ACTV_HIC	;  //�ߵ�ƽ��Ч�������,ͬ������2
/*	   EALLOW;
	   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
	   EDIS;
*/	//----------- Initialize ePWM1-------------------
}


void InitEPwm2Example(void)
{
	//----------------- Initialize ePWM2-------------------
/*	   EALLOW;
	   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
	   EDIS;
*/
	   EPwm2Regs.TBPHS.half.TBPHS = 0x0000;   	//��λ�Ĵ���ֵΪ0
	   EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;	// Up_down_count mode,����ԳƲ���,�Ҹ�����ģʽ����ģʽ
	   EPwm2Regs.TBCTL.bit.PHSEN = 0; 	// ��λװ�ؽ�ֹ
	   EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW; 	// enable the shadow register ,ʹ��ӳ��Ĵ���
	   EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;	//TBCLK=SYSCLKOUT
	   EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;	//TBCLK=SYSCLKOUT

	   EPwm2Regs.TBCTL.bit.SYNCOSEL =TB_CTR_ZERO;   	// master module
	   EPwm2Regs.TBPRD = 3750;

	   EPwm2Regs.CMPA.half.CMPA=1000;
	   EPwm2Regs.CMPB=1000;

	   EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; 		// shadow mode
	   EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW; 		// shadow mode

	   EPwm2Regs.CMPCTL.bit.LOADAMODE =CC_CTR_ZERO; 	// ����ʱ����
	   EPwm2Regs.CMPCTL.bit.LOADBMODE =CC_CTR_ZERO; 	// ����ʱ����

	 /*EPwm2Regs.ETSEL.bit.INTSEL = 0x001;     	// Select INT on Zero event�������жϣ�
	   EPwm2Regs.ETSEL.bit.INTSEL = 0x002;     	// �����ж�
	   EPwm2Regs.ETSEL.bit.INTEN = 1;  			// Enable INT
	   EPwm2Regs.ETPS.bit.INTPRD = 0x01; 		// Generate INT on 1st event
	*/
	   EPwm2Regs.AQCTLA.bit.CAD =AQ_SET;     //PWMA�������Ч
	   EPwm2Regs.AQCTLA.bit.CAU =AQ_CLEAR;
	   EPwm2Regs.AQCTLB.bit.CBD = AQ_CLEAR ;    //PWMB�������Ч
	   EPwm2Regs.AQCTLB.bit.CBU =AQ_SET ;
	 //EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;//����ʹ��
	 //EPwm2Regs.DBCTL.bit.IN_MODE =0;  //EPWMxA��Ϊ��ʱ�ź�Դ��
	 //EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_LOC	;  //�͵�ƽ��Ч�������,��������11.24
	 //EPwm2Regs.DBCTL.bit.POLSEL =DB_ACTV_HIC	;  //�ߵ�ƽ��Ч�������,ͬ������2
/*	   EALLOW;
	   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
       EDIS;
*/	//----------- Initialize ePWM2-------------------
}


void InitEPwm3Example(void)
{
	//----------------- Initialize ePWM3-------------------
/*	   EALLOW;
	   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
	   EDIS;
*/
	   EPwm3Regs.TBPHS.half.TBPHS = 0x0000;   	//��λ�Ĵ���ֵΪ0
	   EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;	// Up_down_count mode,����ԳƲ���,�Ҹ�����ģʽ����ģʽ
	   EPwm3Regs.TBCTL.bit.PHSEN = 0; 	// ��λװ�ؽ�ֹ
	   EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW; 	// enable the shadow register ,ʹ��ӳ��Ĵ���
	   EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;	//TBCLK=SYSCLKOUT
	   EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;	//TBCLK=SYSCLKOUT

	   EPwm3Regs.TBCTL.bit.SYNCOSEL =TB_CTR_ZERO;   	// master module
	   EPwm3Regs.TBPRD = 3750;

	   EPwm3Regs.CMPA.half.CMPA=1000;
	   EPwm3Regs.CMPB=1000;

	   EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; 		// shadow mode
	   EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW; 		// shadow mode

	   EPwm3Regs.CMPCTL.bit.LOADAMODE =CC_CTR_ZERO; 	// ����ʱ����
	   EPwm3Regs.CMPCTL.bit.LOADBMODE =CC_CTR_ZERO; 	// ����ʱ����

	 /*EPwm3Regs.ETSEL.bit.INTSEL = 0x001;     	// Select INT on Zero event�������жϣ�
	   EPwm3Regs.ETSEL.bit.INTSEL = 0x002;     	// �����ж�
	   EPwm3Regs.ETSEL.bit.INTEN = 1;  			// Enable INT
	   EPwm3Regs.ETPS.bit.INTPRD = 0x01; 		// Generate INT on 1st event
	*/

	   EPwm3Regs.AQCTLA.bit.CAD =AQ_SET ;    //PWMA�������Ч
	   EPwm3Regs.AQCTLA.bit.CAU =AQ_CLEAR;
	   EPwm3Regs.AQCTLB.bit.CBD = AQ_CLEAR;    //PWMB�������Ч
	   EPwm3Regs.AQCTLB.bit.CBU =AQ_SET ;
	 //EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;//����ʹ��
	 //EPwm3Regs.DBCTL.bit.IN_MODE =0;  //EPWMxA��Ϊ��ʱ�ź�Դ��
	 //EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_LOC	;  //�͵�ƽ��Ч�������,��������11.24
	 //EPwm3Regs.DBCTL.bit.POLSEL =DB_ACTV_HIC	;  //�ߵ�ƽ��Ч�������,ͬ������2
/*	   EALLOW;
	   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
	   EDIS;
*/
	//----------- Initialize ePWM3-------------------
 }


void InitEPwm4Example(void)
{
	//----------------- Initialize ePWM5-------------------
/*	   EALLOW;
	   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
	   EDIS;
*/
	   EPwm4Regs.TBPHS.half.TBPHS = 0x0000;   	//��λ�Ĵ���ֵΪ0
	   EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;	// Up_count mode,����ԳƲ���,�Ҹ�����ģʽ����ģʽ
	   EPwm4Regs.TBCTL.bit.PHSEN = 0; 	// ��λװ�ؽ�ֹ
	   EPwm4Regs.TBCTL.bit.PRDLD = TB_SHADOW; 	// enable the shadow register ,ʹ��ӳ��Ĵ���
	   EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;	//TBCLK=SYSCLKOUT
	   EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;	//TBCLK=SYSCLKOUT

	   EPwm4Regs.TBCTL.bit.SYNCOSEL =TB_CTR_ZERO;   	// master module
	   EPwm4Regs.TBPRD =3750;             // 150M/fs  20k=3750  40k=1875
	   EPwm4Regs.CMPA.half.CMPA=1000;
	   EPwm4Regs.CMPB=1000;

	   EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; 		// shadow mode
	   EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW; 		// shadow mode
	   EPwm4Regs.CMPCTL.bit.LOADAMODE =CC_CTR_ZERO; 	// ����ʱ����
	   EPwm4Regs.CMPCTL.bit.LOADBMODE =CC_CTR_ZERO; 	// ����ʱ����

	   EPwm4Regs.AQCTLA.bit.CAD =AQ_SET ;    //PWMA�������Ч
	   EPwm4Regs.AQCTLA.bit.CAU =AQ_CLEAR;
	   EPwm4Regs.AQCTLB.bit.CBD =AQ_SET;   //PWMB�������Ч
	   EPwm4Regs.AQCTLB.bit.CBU =AQ_CLEAR ;
/*
	   EPwm5Regs.ETSEL.bit.SOCAEN = 1;        // Enable SOC on A group
	   EPwm5Regs.ETSEL.bit.SOCASEL = 4;       // Select SOC from from CPMA on upcount
	   EPwm5Regs.ETPS.bit.SOCAPRD = 1;        // Generate pulse on 1st event

       EALLOW;
	   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
	   EDIS;
*/
	//----------- Initialize ePWM5-------------------
 }




