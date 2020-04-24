/*
 *  vadc.c
 *
 *  Created on: May 12, 2017
 *  Author(s): Lance Gurka & Robert Valascho
 *
 */

//****************************************************************************
// @Project Includes
//****************************************************************************

#include "vadc.h"

#include "IfxSrc_reg.h"
#include "IfxPort_reg.h"
#include "IfxVadc_reg.h"
#include "IfxCcu6_reg.h"
#include "IfxPort_reg.h"

#include "IfxScuCcu.h"
//#include "../../../../4_McHal/Tricore/Cpu/Irq/IfxCpu_Irq.h"

#include "Ifx_Cfg.h"
#include "Ifx_Types.h"

#include "Compilers.h"

//****************************************************************************

#if CCU6_TRIGGER

#define CTRL_XTSEL 0	//CCU60 service request output 3
#define CTRL_GTSEL 0

#elif CCU6_TRIGGER_SYNCFIX

#define CTRL_XTSEL 0xF	//Selected gating signal is trigger
#define CTRL_GTSEL 0x3	//CCU6061 trigger output 1

#elif GTM_TRIGGER

#define CTRL_XTSEL 0xF	//Selected gating signal is trigger
#define CTRL_GTSEL 0

#elif ERU_TRIGGER

#define CTRL_XTSEL 0x7	//ERU interrupt output y
#define CTRL_GTSEL 0

#endif

IFX_INTERRUPT(ADC_SR0_Handler, 0, 31);
//IFX_INTERRUPT(ADC_SR1_Handler, 0, 32);
//IFX_INTERRUPT(ADC_SR2_Handler, 0, 33);

uint32 countSR0, countSR1, countSR2;

/*******************************************************
 *  Function: vadc_init_queue()
 * Arguments: void
 *    Return: void
 *	   Notes: Channels 0,1,2 of Group 0 are entered into the queue. Queue entries
 *	   		  are refilled so that they persist after conversion is handled. The queue source is enabled
 *	   		  for arbitration. Service requests are generated at each source event(completion of a conversion)
 ******************************************************/

void vadc_init_queue(void)
{
	countSR0 = 0;
	countSR1 = 0;
	countSR2 = 0;
	volatile unsigned int uwTemp;
	uint16  endinit_pw;
	endinit_pw = IfxScuWdt_getCpuWatchdogPassword(); //Get the password for the current CPU

	//Enable the Clock
	//-------------------------------------------------------------------------
	//Clear the Endinit Function to access the protected Registers
	IfxScuWdt_clearCpuEndinit(endinit_pw);
		//A. Enable the GTM Module:
		VADC_CLC.U   = 0x00000000;   // load clock control register
		uwTemp         = VADC_CLC.U; // dummy read to avoid pipeline effects
		while ((VADC_CLC.U & 0x00000002 )== 0x00000002);  //wait until module is enabled
		//SET the Endinit Function after access to the protected Registers
    IfxScuWdt_setCpuEndinit(endinit_pw);
	//-------------------------------------------------------------------------

    /*Configure Queue Source*/
    	//1st Enable converter
    	//2nd Set divider factor for analog internal clock and start calibration
    	//3rd Enable arbitration slot 0 (queue source) and assign priority
    	//4th Wait for calibration to complete (can be done later)
    	//5th Select triggering and gating inputs
    	//6th Enable triggering and gating
    	//7th Select channels to be considered for scan
    	//8th Map channel result to result register


	//Arbitration Configuration Register, Group x (GxARBCFG)
    //------------------------------------------------------
	//ANONC (Analog Converter Control) Converter ON/OFF
    //Notes: Converter must be started before writing to SUCAL
	VADC_G0ARBCFG.U = (0x3 /*ANONC*/);

	//Global Configuration Register (GLOBCFG)
	//---------------------------------------
	//DIVA (Divider Factor for the Analog Internal Clock)
	//DIVWC (Write Control for Divider Parameters)
	//SUCAL (Start-Up Calibration) Start calibration, status indicated by GxARBCFG.CAL
	VADC_GLOBCFG.U = (0x5     /*DIVA*/ )|
					 (0x1<<15 /*DIVWC*/);


	//Arbitration Priority Register, Group x (GxARBPR)
	//------------------------------------------------
	//PRIOx (Priority of Request Source x)
	//ASENy (Arbitration Slot y Enable) Group Queued source has slot 0
	VADC_G0ARBPR.U = (0x3       /*PRIO0*/)|
					 (0x1 << 24 /*ASEN0*/);


	VADC_GLOBCFG.U |= (0x1<<31 /*SUCAL*/);	//Begin start-up calibration

	while((VADC_G0ARBCFG.U & 0x30000000) != 0x20000000);  //Wait for start-up calibration to complete

	//Queue 0 Input Register, Group x (GxQINR0)
	//-----------------------------------------
	//Add Channels 0,1,2 to Group 0 Queue Source
	//REQCHNR (Request Channel Number)
	//RF (Refill) Reload queue entry once conversion started
	//ENSI (Enable Source Interrupt) Enable interrupt at end of conversion
	//EXTR (External Trigger) Wait for trigger to issue conversion request

	VADC_G0QINR0.U =    (0x0  /*REQCHNR*/ )|
						(0x1 << 5 /*RF*/  )|
						(0x1 << 7 /*EXTR*/);

	VADC_G0QINR0.U =    (0x1 /*REQCHNR*/)|
						(0x1 << 5 /*RF*/);

	VADC_G0QINR0.U =    (0x2 /*REQCHNR*/ )|
						(0x1 << 5 /*RF*/ )|
						(0x1 << 6 /*ENSI*/);


	//Source Control Register, Group x  (GxQCTRL0)
	//--------------------------------------------
    //SRCRESREG (Source-specific Result Register) Use GxCHCTRy.RESREG to select result register for channels in group
    //XTSEL     (External Trigger Input Selection) Use CCU60_SR3
    //XTMODE    (Trigger Operating Mode) Trigger event upon rising edge
    //XTWC      (Write Control for Trigger Configuration) Bitfields XTMODE and XTSEL can be written
	//GTSEL		(Gate Input Selection) Use CCU60_SR3
	//GTWC      (Write Control for Gate Configuration) Bitfield GTSEL can be written

	VADC_G0QCTRL0.U = 	(0x0    /*SRCRESREG*/)|
    			 (CTRL_XTSEL << 8  /*XTSEL*/ )|
    					(0x2 << 13 /*XTMODE*/)|
    					(0x1 << 15 /*XTWC*/  )|
    			 (CTRL_GTSEL << 16 /*GTSEL*/ )|
    					(0x1 << 23 /*GTWC*/  );


	//Mode Register, Group x (GxQMR0)
	//-------------------------------
	//ENGT (Enable Gate) Conversion request issued if element in queue0 register or backup register
	//ENTR (Enable External Trigger) Trigger input REQTR (selected by XTSEL) generates the trigger event

	VADC_G0QMR0.U =   (0x1      /*ENGT*/)|
					  (0x1 << 2 /*ENTR*/);


	//Channel Control Register, Group x Channel y (GxCHCTRy)
	//------------------------------------------------------
	//RESREG (Result Register) Store result from channel y to specified group result register
	//RESPOS (Result Position) Store result right-aligned
	VADC_G0CHCTR0.U = (0x0 << 16 /*RESREG*/)|
					  (0x1 << 21 /*RESPOS*/);

	VADC_G0CHCTR1.U = (0x1 << 16 /*RESREG*/)|
					  (0x1 << 21 /*RESPOS*/);

	VADC_G0CHCTR2.U = (0x2 << 16 /*RESREG*/)|
					  (0x1 << 21 /*RESPOS*/);

	//Select request line to be signaled and then configure associated interrupt.

	/*Configure Service Request*/
		//1st Map source event to service request line
		//2nd Map service request line to service request(by priority)


	//Service Event Node Pointer Register 0, Group x (GxREVNP0)
	//---------------------------------------------------------
	//SEV0NP (Service Request Node Pointer Source Event) Source 0 is an 8-stage queue source
	VADC_G0SEVNP.U = (0x0 << 0 /*SEV0NP*/); //Select service request line 0


	//Service Request Control Register (SRC)
	//--------------------------------------
	//For VADC, SRC_VADCGxSRy, Group x Request Line y
	//SRPN (Service Request Priority Number)
	//SRE  (Service Request Enable)
	//TOS  (Type of Service Control) Select handler, CPU0 or DMA
	SRC_VADCG0SR0.U = (31      /*SRPN*/) |
					  (1 << 10 /*SRE*/ ) |
					  (0 << 11 /*TOS*/ );


    //P00_IOCR0.B.PC0 = 0x10;

    //Configure P40.0 as analog input
    //Mapped to Group 0 Channel 0 by hardware
    //P40_IOCR0.B.PC0 = 0x03;

}


/******************************************************************
 *  Function: vadc_init_scan()
 * Arguments: void
 *    Return: void
 *     Notes: Channels 0,1,2 of Group 0 are set to be included in a scan sequence. Results from each channel are stored in the respective result
 *            registers. The scan source is enabled for arbitration. Service requests are generated when
 *            a new result is written (result event).
 ******************************************************************/

void vadc_init_scan(void)
{
	countSR0 = 0;
	countSR1 = 0;
	countSR2 = 0;
	volatile uint32 uwTemp;
	uint16  endinit_pw;
	endinit_pw = IfxScuWdt_getCpuWatchdogPassword(); //Get the password for the current CPU

	//Enable the Clock
	//-------------------------------------------------------------------------
	//Clear the Endinit function to access the protected registers
	IfxScuWdt_clearCpuEndinit(endinit_pw);
		//A. Enable the GTM Module:
		VADC_CLC.U   = 0x00000000;   // load clock control register
		uwTemp         = VADC_CLC.U; // dummy read to avoid pipeline effects
		while ((VADC_CLC.U & 0x00000002 )== 0x00000002);  //wait until module is enabled
		//Set the Endinit function after access to the protected registers
    IfxScuWdt_setCpuEndinit(endinit_pw);
	//-------------------------------------------------------------------------

    /*Configure Scan Source*/
    	//1st Enable converter
    	//2nd Set divider factor for analog internal clock and start calibration
    	//3rd Enable arbitration slot 1 (scan source) and assign priority
    	//4th Wait for calibration to complete (can be done later)
    	//5th Select triggering and gating inputs
    	//6th Enable triggering and gating
    	//7th Select channels to be considered for scan
    	//8th Map channel result to result register

    //Arbitration Configuration Register, Group x (GxARBCFG)
    //------------------------------------------------------
    //ANONC (Analog Converter Control) Converter ON/OFF
    //Notes: Converter must be started before writing to SUCAL
    VADC_G0ARBCFG.U = (0x3 /*ANONC*/);
    //------------------------------------------------------


    //Global Configuration Register (GLOBCFG)
    //---------------------------------------
    //DIVA (Divider Factor for the Analog Internal Clock)
    //DIVWC (Write Control for Divider Parameters)
    //SUCAL (Start-Up Calibration) Start calibration, status indicated by GxARBCFG.CAL
    VADC_GLOBCFG.U = (0x5     /*DIVA*/)|
    				 (0x1<<15 /*DIVWC*/);
    //---------------------------------------

    //Arbitration Priority Register, Group x (GxARBPR)
    //------------------------------------------------
    //PRIOx (Priority of Request Source x) Priority 0-3, 3 highest
    //ASENy (Arbitration Slot y Enable) Group Scan source has slot 1
    VADC_G0ARBPR.U = (0x3       /*PRIO0*/)|
    				 (0x1 << 25 /*ASEN1*/);
    //------------------------------------------------

    VADC_GLOBCFG.U |= (0x1<<31 /*SUCAL*/); //Begin start-up calibration

    while((VADC_G0ARBCFG.U & 0x30000000) != 0x20000000);  //Wait for start-up calibration to complete

   //Autoscan Source Control Register, Group x  (GxASCTRL)
   //-----------------------------------------------------
   //SRCRESREG (Source-specific Result Register) -- Use GxCHCTRy.RESREG to select result register for channels in group.
   //XTSEL     (External Trigger Input Selection) -- Use CCU60_SR3
   //XTMODE    (Trigger Operating Mode) -- Trigger event upon rising edge
   //XTWC      (Write Control for Trigger Configuration) -- Bitfields XTMODE and XTSEL can be written
   //GTSEL	   (Gate Input Selection) -- Use CCU60_SR3
   //GTWC      (Write Control for Gate Configuration) -- Bitfield GTSEL can be written
   VADC_G0ASCTRL.U = (0x0       /*SRCRESREG*/)|
    		  (CTRL_XTSEL << 8  /*XTSEL*/ )|
    				 (0x2 << 13 /*XTMODE*/)|
    				 (0x1 << 15 /*XTWC*/  )|
    		  (CTRL_GTSEL << 16 /*GTSEL*/ )|
    				 (0x1 << 23 /*GTWC*/);
   //-----------------------------------------------------


   //Autoscan Source Mode Register, Group x (GxASMR)
   //-----------------------------------------------
   //ENGT (Enable Gate) Issue conversion request if pending bits are set
   //ENTR (Enable External Trigger) ON/OFF, Trigger selected by XTSEL
   VADC_G0ASMR.U = (0x1 << 0 /*ENGT*/)|
   				   (0x1 << 2 /*ENTR*/);
   //-----------------------------------------------


   //Autoscan Source Channel Select Register, Group x (GxASSEL)
   //----------------------------------------------------------
   //CHSEL (Channel Selection) Set corresponding bits to include channels in scan sequence
   //Notes: Select channels 0,1,2 of Group 0 to be included in scan sequence
   VADC_G0ASSEL.U = (0x7 /*CHSEL*/);
   //----------------------------------------------------------


   //Channel Control Register, Group x Channel y (GxCHCTRy)
   //------------------------------------------------------
   //RESREG (Result Register) Store result from channel y to specified group result register
   //RESPOS (Result Position) Store result right-aligned
   VADC_G0CHCTR0.U = (0x0 << 16 /*RESREG*/)|
   				     (0x1 << 21 /*RESPOS*/);

   VADC_G0CHCTR1.U = (0x1 << 16 /*RESREG*/)|
   				     (0x1 << 21 /*RESPOS*/);

   VADC_G0CHCTR2.U = (0x2 << 16 /*RESREG*/)|
   				     (0x1 << 21 /*RESPOS*/);
   //------------------------------------------------------


   /*Select request line to be signaled and then configure associated interrupt.*/

   /*Configure Service Request*/
   	   //1st Map result event to service request line
   	   //2nd Map service request line to service request(by priority)
   	   //3rd Allow result event to generate a service request

   //Result Event Node Pointer Register 0, Group x (GxREVNP0)
   //---------------------------------------------------------
   //REVxNP (Service Request Node Pointer Result x Event) Select service request line
   VADC_G0REVNP0.U = (0x0      /*REV0NP*/)|
					 (0x1 << 4 /*REV1NP*/)|
					 (0x2 << 8 /*REV2NP*/);
   //---------------------------------------------------------


   //Service Request Control Register (SRC)
   //--------------------------------------
   //For VADC, SRC_VADCGxSRy, Group x Request Line y
   //SRPN (Service Request Priority Number)
   //SRE  (Service Request Enable)
   SRC_VADCG0SR0.U = (11      /*SRPN*/)|
   				  	 (1 << 10 /*SRE*/ );

   SRC_VADCG0SR1.U = (12      /*SRPN*/)|
   				  	 (1 << 10 /*SRE*/ );

   SRC_VADCG0SR2.U = (13      /*SRPN*/)|
   				  	 (1 << 10 /*SRE*/ );
   //-------------------------------------


   //Group 0 Result Control Register y (G0RCRy)
   //------------------------------------------
   //SRGEN (Service Request Generation Enable)
   VADC_G0RCR0.U = (0x1 << 31 /*SRGEN*/);
   VADC_G0RCR1.U = (0x1 << 31 /*SRGEN*/);
   VADC_G0RCR2.U = (0x1 << 31 /*SRGEN*/);
   //------------------------------------------

   P00_IOCR0.B.PC0 = 0x10;

   //Configure P40.0 as analog input
   //Mapped to Group 0 Channel 0 by hardware
   P40_IOCR0.B.PC0 = 0x03;

}



/******************************************************************
 *  Function: vadc_init_bgndscan()
 * Arguments: void
 *    Return: void
 *     Notes: Channels 0,1,2 of Group 0 are set to be included in a background scan sequence. Results from each channel are stored in the global result register.
 *            The background scan source is enabled for arbitration. Service requests are generated when
 *            a new result is written (result event).
 ******************************************************************/

void vadc_init_bgndscan(void)
{
	countSR0 = 0;
	countSR1 = 0;
	countSR2 = 0;
	volatile uint32 uwTemp;
	uint16  endinit_pw;
	endinit_pw     = IfxScuWdt_getCpuWatchdogPassword(); //Get the password for the current CPU

	//Enable the Clock
	//-------------------------------------------------------------------------
	//Clear the Endinit function to access the protected registers
	IfxScuWdt_clearCpuEndinit(endinit_pw);
		//A. Enable the GTM Module:
		VADC_CLC.U   = 0x00000000;   // load clock control register
		uwTemp         = VADC_CLC.U; // dummy read to avoid pipeline effects
		while ((VADC_CLC.U & 0x00000002 )== 0x00000002);  //wait until module is enabled
		//Set the Endinit function after access to the protected registers
    IfxScuWdt_setCpuEndinit(endinit_pw);
	//-------------------------------------------------------------------------

    /*Configure Scan Source*/
    	//1st Enable converter
    	//2nd Set divider factor for analog internal clock and start calibration
    	//3rd Enable arbitration slot 2 (bgnd scan source) and assign priority
    	//4th Wait for calibration to complete (can be done later)
    	//5th Select triggering and gating inputs
    	//6th Enable triggering and gating
    	//7th Select channels to be considered for scan
    	//8th Map channel result to result register


   //Arbitration Configuration Register, Group x (GxARBCFG)
   //------------------------------------------------------
   //ANONC (Analog Converter Control) Converter ON/OFF
   //Notes: Converter must be started before writing to SUCAL
   VADC_G0ARBCFG.U = (0x3 /*ANONC*/);
   //------------------------------------------------------


   //Global Configuration Register (GLOBCFG)
   //---------------------------------------
   //DIVA (Divider Factor for the Analog Internal Clock)
   //DIVWC (Write Control for Divider Parameters)
   //SUCAL (Start-Up Calibration) Start calibration, status indicated by GxARBCFG.CAL
   VADC_GLOBCFG.U = (0x5     /*DIVA*/ )|
   				    (0x1<<15 /*DIVWC*/);
   //---------------------------------------


   //Arbitration Priority Register, Group x (GxARBPR)
   //------------------------------------------------
   //PRIOx (Priority of Request Source x) Priority 0-3, 3 highest
   //ASENy (Arbitration Slot y Enable) Background Scan source has slot 2
   VADC_G0ARBPR.U = (0x3       /*PRIO0*/)|
   				 	(0x1 << 26 /*ASEN2*/);
   //------------------------------------------------

   VADC_GLOBCFG.U |= (0x1<<31 /*SUCAL*/); //Begin start-up calibration

   while((VADC_G0ARBCFG.U & 0x30000000) != 0x20000000);  //Wait for start-up calibration to complete

   //Autoscan Source Control Register (BRSCTRL)
   //------------------------------------------
   //SRCRESREG (Source-specific Result Register) -- Store in global result register 1
   //XTSEL     (External Trigger Input Selection) -- Use CCU60_SR3
   //XTMODE    (Trigger Operating Mode) -- Trigger event upon rising edge
   //XTWC      (Write Control for Trigger Configuration) -- Bitfields XTMODE and XTSEL can be written
   //GTSEL	   (Gate Input Selection) -- Use CCU60_SR3
   //GTWC      (Write Control for Gate Configuration) -- Bitfield GTSEL can be written
   VADC_BRSCTRL.U = (0x0       /*SRCRESREG*/)|
    		 (CTRL_XTSEL << 8  /*XTSEL*/ )|
    				(0x2 << 13 /*XTMODE*/)|
    				(0x1 << 15 /*XTWC*/  )|
    		 (CTRL_GTSEL << 16 /*GTSEL*/ )|
    				(0x1 << 23 /*GTWC*/  );
   //-----------------------------------------


   //Background Request Source Mode Register (BRSMR)
   //-----------------------------------------------
   //ENGT (Enable Gate) Issue conversion request if pending bits are set
   //ENTR (Enable External Trigger) ON/OFF, Trigger selected by XTSEL
   VADC_BRSMR.U = (0x1 << 0 /*ENGT*/)|
   				  (0x1 << 2 /*ENTR*/);
   //-----------------------------------------------


   //Background Request Source Channel Select Register, Group x (BRSSELx)
   //----------------------------------------------------------
   //CHSELGy (Channel y Selection) Set corresponding bits to include channels in scan sequence
   //Notes: Select channels 0,1,2 of Group 0 to be included in scan sequence
   VADC_BRSSEL0.U = (0x7 /*CHSEL*/);
   //----------------------------------------------------------


   //Channel Control Register, Group x Channel y (GxCHCTRy)
   //------------------------------------------------------
   //RESREG (Result Register) Store result from channel y to specified group result register
   //RESPOS (Result Position) Store result right-aligned
   VADC_G0CHCTR0.U = (0x1 << 20 /*RESTBS*/)|
   				     (0x1 << 21 /*RESPOS*/);

   VADC_G0CHCTR1.U = (0x1 << 20 /*RESTBS*/)|
   				     (0x1 << 21 /*RESPOS*/);

   VADC_G0CHCTR2.U = (0x1 << 20 /*RESTBS*/)|
   				     (0x1 << 21 /*RESPOS*/);
   //------------------------------------------------------


   /*Configure Service Request*/
   	   //1st map result event to service request line
   	   //2nd map service request line to service request(by priority)
   	   //3rd allow result event to generate a service request

   //Global Event Node Pointer Register (GLOBEVNP)
   //---------------------------------------------
   //REVxNP (Service Request Node Pointer Result x Event) Select service request line
   VADC_GLOBEVNP.U = (0x0 /*REV0NP*/);
   //---------------------------------------------

   //Service Request Control Register (SRC)
   //-------------------------------------
   //For VADC, SRC_VADCGxSRy, Group x Request Line y
   //SRPN (Service Request Priority Number)
   //SRE  (Service Request Enable)
   SRC_VADCCG0SR0.U = (11      /*SRPN*/)|
   				  	  (1 << 10 /*SRE*/ );
   //-------------------------------------

   //Group 0 Result Control Register y (G0RCRy)
   //------------------------------------------
   //SRGEN (Service Request Generation Enable)
   VADC_GLOBRCR.U = (0x1 << 31 /*SRGEN*/);
   //------------------------------------------

   P00_IOCR0.B.PC0 = 0x10;

   //Configure P40.0 as analog input
   //Mapped to Group 0 Channel 0 by hardware
   P40_IOCR0.B.PC0 = 0x03;

}


/******************************************************************
 *  Function: vadc_init_queue_sync()
 * Arguments: void
 *    Return: void
 *     Notes:
 ******************************************************************/

void vadc_init_queue_sync(void)
{
	countSR0 = 0;
	countSR1 = 0;
	countSR2 = 0;
	volatile uint32 uwTemp;
	uint16  endinit_pw;
	endinit_pw     = IfxScuWdt_getCpuWatchdogPassword(); //Get the password for the current CPU

	//Enable the Clock
	//-------------------------------------------------------------------------
	//Clear the Endinit function to access the protected registers
	IfxScuWdt_clearCpuEndinit(endinit_pw);
		//A. Enable the GTM Module:
		VADC_CLC.U   = 0x00000000;   // load clock control register
		uwTemp         = VADC_CLC.U; // dummy read to avoid pipeline effects
		while ((VADC_CLC.U & 0x00000002 )== 0x00000002);  //wait until module is enabled
		//Set the Endinit function after access to the protected registers
    IfxScuWdt_setCpuEndinit(endinit_pw);
	//-------------------------------------------------------------------------

#if CCU6_TRIGGER_SYNCFIX
   VADC_GLOBCFG.U |= (0x1 << 7); //Enable sync for workaround
   ADC_TC068_W4_Sync();
#endif /*CCU6_TRIGGER_SYNCFIX*/


   //Global Configuration Register (GLOBCFG)
   //---------------------------------------
   //DIVA (Divider Factor for the Analog Internal Clock)
   //DIVWC (Write Control for Divider Parameters)
   //SUCAL (Start-Up Calibration) Start calibration, status indicated by GxARBCFG.CAL
   VADC_GLOBCFG.U = (0x5     /*DIVA*/)|
   				    (0x1 << 15 /*DIVWC*/);

   //---------------------------------------


   //Arbitration Priority Register, Group x (GxARBPR)
   //------------------------------------------------
   //PRIOx (Priority of Request Source x) Priority 0-3, 3 highest
   //ASENy (Arbitration Slot y Enable) Group Queue source has slot 1
   VADC_G0ARBPR.U = (0x3       /*PRIO0*/)|
   				 	(0x1 << 24 /*ASEN0*/);
   //------------------------------------------------


   //Queue 0 Source Control Register, Group x  (GxQCTRL0)
   //-----------------------------------------------------
   //SRCRESREG (Source-specific Result Register) -- Use GxCHCTRy.RESREG to select result register for channels in group.
   //XTSEL     (External Trigger Input Selection) -- Use CCU60_SR3
   //XTMODE    (Trigger Operating Mode) -- Trigger event upon rising edge
   //XTWC      (Write Control for Trigger Configuration) -- Bitfields XTMODE and XTSEL can be written
   //GTSEL	   (Gate Input Selection) -- Use CCU60_SR3
   //GTWC      (Write Control for Gate Configuration) -- Bitfield GTSEL can be written

   VADC_G0QCTRL0.U = (0x0    /*SRCRESREG*/)|
    		  (CTRL_XTSEL << 8  /*XTSEL*/ )|
    				 (0x2 << 13 /*XTMODE*/)|
    				 (0x1 << 15 /*XTWC*/  )|
    		  (CTRL_GTSEL << 16 /*GTSEL*/ )|
    				 (0x1 << 23 /*GTWC*/  );

   //-----------------------------------------------------

	//Queue 0 Mode Register, Group x (GxQMR0)
	//-------------------------------
	//ENGT (Enable Gate) Issue conversion request if pending bits are set
	//ENTR (Enable External Trigger) ON/OFF, Trigger selected by XTSEL

	VADC_G0QMR0.U =   (0x1      /*ENGT*/)|
					  (0x1 << 2 /*ENTR*/);


	//Queue 0 Input Register, Group x (GxQINR0)
	//-----------------------------------------
	//Add Channels 0,1,2 to Group 0 Queue Source
	//REQCHNR (Request Channel Number)
	//RF (Refill) Reload queue entry once conversion started
	//ENSI (Enable Source Interrupt)

	VADC_G0QINR0.U =    (0x0  /*REQCHNR*/)|
						(0x1 << 5 /*RF*/ )|
						(0x1 << 7 /*EXTR*/);

	VADC_G0QINR0.U =    (0x1 /*REQCHNR*/)|
						(0x1 << 5 /*RF*/);

	VADC_G0QINR0.U =    (0x2 /*REQCHNR*/ )|
						(0x1 << 5 /*RF*/ )|
						(0x1 << 6 /*ENSI*/);


   //Channel Control Register, Group x Channel y (GxCHCTRy)
   //------------------------------------------------------
   //SYNC (Synchronization Request) Request a synchronized conversion (only taken into account for a master)
   //RESREG (Result Register) Store result from channel y to specified group result register
   //RESPOS (Result Position) Store result right-aligned

   VADC_G0CHCTR0.U = (0x1 << 10 /*SYNC*/  )|
		   	   	   	 (0x0 << 16 /*RESREG*/)|
		   	   	   	 (0x1 << 21 /*RESPOS*/);

   VADC_G0CHCTR1.U = (0x1 << 10 /*SYNC*/  )|
		   	   	   	 (0x1 << 16 /*RESREG*/)|
                     (0x1 << 21 /*RESPOS*/);

   VADC_G0CHCTR2.U = (0x1 << 10 /*SYNC*/  )|
		   	   	   	 (0x2 << 16 /*RESREG*/)|
   				     (0x1 << 21 /*RESPOS*/);


   VADC_G1CHCTR0.U = (0x0 << 16 /*RESREG*/)|
		  	   	   	 (0x1 << 21 /*RESPOS*/);

   VADC_G1CHCTR1.U = (0x1 << 16 /*RESREG*/)|
                     (0x1 << 21 /*RESPOS*/);

   VADC_G1CHCTR2.U = (0x2 << 16 /*RESREG*/)|
   				     (0x1 << 21 /*RESPOS*/);


   VADC_G2CHCTR0.U = (0x0 << 16 /*RESREG*/)|
		   	   	   	 (0x1 << 21 /*RESPOS*/);

   VADC_G2CHCTR1.U = (0x1 << 16 /*RESREG*/)|
                     (0x1 << 21 /*RESPOS*/);

   VADC_G2CHCTR2.U = (0x2 << 16 /*RESREG*/)|
   				     (0x1 << 21 /*RESPOS*/);

   //------------------------------------------------------


   //Synchronization Control Register, Group x (GxSYNCTR)
   //----------------------------------------------------
   //STSEL  (Start Selection)
   //EVALRx (Evaluate Ready Input R x)
   VADC_G0SYNCTR.U = (0x0       /*STSEL*/)|
		   	   	   	 (0x1 << 4 /*EVALR1*/)|
		   	   	   	 (0x1 << 5 /*EVALR2*/);

   VADC_G1SYNCTR.U = (0x1       /*STSEL*/)|
                     (0x1 << 4 /*EVALR1*/)|
                     (0x1 << 5 /*EVALR2*/);

   VADC_G2SYNCTR.U = (0x1       /*STSEL*/)|
                     (0x1 << 4 /*EVALR1*/)|
                     (0x1 << 5 /*EVALR2*/);

   //----------------------------------------------------

   /*Select request line to be signaled and then configure associated interrupt.*/

   /*Configure Service Request*/
		//1st Map source event to service request line
		//2nd Map service request line to service request(by priority)


   //Service Event Node Pointer Register 0, Group x (GxREVNP0)
   //---------------------------------------------------------
   //SEV0NP (Service Request Node Pointer Source Event) Source 0 is an 8-stage queue source
   VADC_G0SEVNP.U = (0x0 << 0 /*SEV0NP*/); //Select group 0 service request line 0


   //Service Request Control Register (SRC)
   //--------------------------------------
   //For VADC, SRC_VADCGxSRy, Group x Request Line y
   //SRPN (Service Request Priority Number)
   //SRE  (Service Request Enable)
   //TOS  (Type of Service Control) Select handler, CPU0 or DMA
   SRC_VADCG0SR0.U = (11      /*SRPN*/)|
		   	   	   	 (1 << 10 /*SRE*/ )|
				     (0 << 11 /*TOS*/ );

   //Configure P40.0 as analog input
   P40_IOCR0.B.PC0 = 0x03;

   VADC_G0ARBCFG.U |= (0x3 /*ANONC*/);	//Enable G0 converter
   VADC_GLOBCFG.U |= (0x1 << 31); //Start calibration
   while((VADC_G0ARBCFG.U & 0x30000000) != 0x20000000);  //Wait for start-up calibration to complete
}

void ADC_TC068_W4_Sync()
{
	//Provide a 20 MHz synchronization signal @fSPB = 100 MHz

		uint16 endinit_pw;
		endinit_pw = IfxScuWdt_getCpuWatchdogPassword(); //Get the password for the current CPU

		//Enable the Clock
		//-------------------------------------------------------------------------
		//Clear the Endinit Function to access the protected Registers
		IfxScuWdt_clearCpuEndinit(endinit_pw);

		while(CCU61_CLC.B.DISS == 0x1)
		{
			CCU61_CLC.B.DISR = 0x0;
		}

		while(CCU60_CLC.B.DISS == 0x1)
		{
			CCU60_CLC.B.DISR = 0x0;
		}

		IfxScuWdt_setCpuEndinit(endinit_pw);
		//-------------------------------------------------------------------------

		//Timer 13 Period Register (T12PR)
		//--------------------------------
		//T13PV (T13 Period Value)
		//--------------------------------
		CCU61_T13PR.U = (0x4 /*T13PV*/);
		//--------------------------------

		//Compare Shadow Register for T13
		//-------------------------------
		//CCS (Shadow Register for Channel CC63 Compare Value)
		//-------------------------------
		CCU61_CC63SR.U = (0x1 /*CCS*/);
		//-------------------------------

		//Passive State Level Register
		//----------------------------
		//PSL63 (Passive State Level of Output COUT63)
		//----------------------------
		CCU61_PSLR.U |= (0x1 << 7 /*PSL63*/);
		//----------------------------

		//Modulation Control Register
		//---------------------------
		//ECT130 (Enable Compare Timer T13 Output)
		//---------------------------
		CCU61_MODCTR.U |= (0x1 << 15 /*ECT130*/);
		//---------------------------

		//Timer Control Register 4 (TCTR4)
		//--------------------------------
		//T13STR (Timer 13 Shadow Transfer Request) Request to update Compare and Period values
		//--------------------------------
		CCU61_TCTR4.U |= (0x1 << 14 /*T13STR*/);
		//--------------------------------

		//CCU60 Module Output Selection Register
		//--------------------------------------
		//TRIGxSEL (Output Trigger Selection for CCU6061 TRIGx)
		//--------------------------------------
		CCU60_MOSEL.U |= (0x1 << 3 /*TRIG1SEL*/); //CCU61_COUT63 is selected
		//--------------------------------------

		//Timer Control Register 4 (TCTR4)
		//--------------------------------
		//T13RS (Timer 13 Run Set)
		//--------------------------------
		CCU61_TCTR4.U |= (0x1 << 9 /*T13RS*/); //Start T13
		//--------------------------------
}

void ADC_SR0_Handler()
{
	VADC_G0REFCLR.U |= 0x1; //Clear REV0 flag
	uint32 result = VADC_G0RES0.U & 0xFFFF; //Group 0 Result 0
	countSR0++;
}
//
//void ADC_SR1_Handler()
//{
//	VADC_G0REFCLR.U |= 0x2; //Clear REV1 flag
//	uint32 result = VADC_G0RES1.U; //Group 0 Result 1
//	countSR1++;
//}
//
//void ADC_SR2_Handler()
//{
//	VADC_G0REFCLR.U |= 0x4; //Clear REV2 flag
//	uint32 result = VADC_G0RES2.U; //Group 0 Result 2
//	countSR2++;
//}
