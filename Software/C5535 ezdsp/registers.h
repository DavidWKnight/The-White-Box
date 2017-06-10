#ifndef registers_h																		// Last Changes 2013/02/28, Max Forster (No guarantee for the correctness of information/code!)
	#define registers_h
	
	// MACROS -------------------------------------------------------
	#define sbi(PORT, BITNUM) ((PORT) |=  (1u<<(BITNUM)))
	#define cbi(PORT, BITNUM) ((PORT) &= ~(1u<<(BITNUM)))
	#define tbi(PORT, BITNUM) ((PORT) ^=  (1u<<(BITNUM)))  

	#define IOPORT_REGISTER(reg)     	(*(volatile ioport unsigned int *)(reg))		// Note: ioport register access is always 16-bit
	#define IOPORT_REGISTER_PTR(reg)	((volatile ioport unsigned int *)(reg))
	#define MMR_REGISTER(reg)			(*(volatile unsigned int *)(reg))
	
	// DEFINES ------------------------------------------------------	
	// MMR Registers (0x0000 - 0x00C0 located in data memory) -------					// -> refer to C55 CPU Ref. Guide
	#define IER0						   (MMR_REGISTER(0x0000))						// Interrupt Enable Register 0 (enables/disables interrupts 0-15)
	#define IFR0						   (MMR_REGISTER(0x0001))						// Interrupt Flag Register 0 (interrupt flags 0-15)
	#define ST0_55						   (MMR_REGISTER(0x0002))						// Status Register 0
	#define ST1_55						   (MMR_REGISTER(0x0003))						// Status Register 1
	#define C54CM							5											// C54 Compatible Mode Bit (0 = C55 code, 1 = C54 compatible mode enabled, add asm("	.C54CM_on/off"); after bit change)
	#define FRCT							6				 							// Fraction Mode
	#define SXMD							8											// Sign Extension Mode
	#define SATD							9											// Saturation Mode
	#define M40								10											// M40 Computation Mode
	#define INTM							11											// Interrupt globally enable/disable (only for maskable interrupts)
	#define XF								13											// XF general-purpose output (0 = clear output (low), 1 = set output (high))
	#define CPL								14											// Addressing Mode Select (0 = addr. relativ to data-pointer, 1 = addr. relativ to stack-pointer)
	#define ST3_55						   (MMR_REGISTER(0x0004))						// Status Register 3
	#define CLKOFF							2
	#define IER1						   (MMR_REGISTER(0x0045))						// Interrupt Enable Register 1 (enables/disables interrupts 16-31)
	#define IFR1						   (MMR_REGISTER(0x0046))						// Interrupt Flag Register 1 (interrupt flags 16-31)
	#define IVPD				           (MMR_REGISTER(0x0049))						// Interrupt Vector Pointer (for interrupts 0-15 and 24-31) 
	#define IVPH				           (MMR_REGISTER(0x004A))						// Interrupt Vector Pointer (for interrupts 16-23) 
	#define ST2_55						   (MMR_REGISTER(0x004B))						// Status Register 2
	
	// Device ID ----------------------------------------------------
	#define DIEIDR0						   (IOPORT_REGISTER(0x1C40))					// hold device ID 0
	#define DIEIDR1						   (IOPORT_REGISTER(0x1C41))					// hold device ID 1 
	#define DIEIDR2						   (IOPORT_REGISTER(0x1C42))					// hold device ID 2 
	#define DIEIDR3						   (IOPORT_REGISTER(0x1C43))					// hold device ID 3 (Bits 12-15 = Silicon Revision, 0 = Silicon 2.2)
	#define DIEIDR4						   (IOPORT_REGISTER(0x1C44))					// hold device ID 4
	#define DIEIDR5						   (IOPORT_REGISTER(0x1C45))					// hold device ID 5
	#define DIEIDR6						   (IOPORT_REGISTER(0x1C46))					// hold device ID 6
	#define DIEIDR7						   (IOPORT_REGISTER(0x1C47))					// hold device ID 7 checksum

	// System Control Registers -------------------------------------
	#define EBSR				           (IOPORT_REGISTER(0x1C00))					// External BUS Selection Register
	#define PPMODE							12
	#define PPMODE0							(0x0<<12)									// ...16Bit LCD active (LCD_EN, LCD_D[0:15], LCD_CS0, LCD_CS1, LCD_RW, LCD_RS)
	#define PPMODE1							(0x1<<12)									// ...SPI, GPIO, UART and I2S2 (SPIG, PIO[12:17], I2S2, UART)
	#define PPMODE2							(0x2<<12)									// ...8Bit LCD and GPIO (LCD_EN, LCD_D[0:7], GPIO[18:20,27:31], LCD_CS0, LCD_CS1, LCD_RW, LCD_RS)
	#define PPMODE3							(0x3<<12)									// ...8Bit LCD, SPI and I2S3 (LCD_EN, LCD_D[0:7], SPI, I2S3, LCD_CS0, LCD_CS1, LCD_RW, LCD_RS)
	#define PPMODE4							(0x4<<12)									// ...8Bit LCD, I2S2 and UART (LCD_EN, LCD_D[0:7], I2S2, UART, LCD_CS0, LCD_CS1, LCD_RW, LCD_RS)
	#define PPMODE5							(0x5<<12)									// ...8Bit LCD, SPI and UART (LCD_EN, LCD_D[0:7], SPI, UART, LCD_CS0, LCD_CS1, LCD_RW, LCD_RS)
	#define PPMODE6							(0x6<<12)									// ...SPI, I2S2, I2S3 and GPIO (SPI, I2S2, I2S3, GPIO[12:17])
	#define SP1MODE							10
	#define SP1MODE0						(0x0<<10)									// ...MMC/SD1
	#define SP1MODE1						(0x1<<10)									// ...I2S1 and GPIO (I2S1, GPIO[10:11])
	#define SP1MODE2						(0x2<<10)									// ...GPIOs (GPIO[6:11])
	#define SP0MODE							8
	#define SP0MODE0						(0x0<<8)									// ...MMC/SD0
	#define SP0MODE1						(0x1<<8)									// ...I2S0 and GPIO (I2S0, GPIO[4:5])
	#define SP0MODE2						(0x2<<8)									// ...GPIOs (GPIO[0:5])
	#define PCGCR1				           (IOPORT_REGISTER(0x1C02))					// Peripheral Clock Gating Control Register 1
	#define SYSCLKDIS						15
	#define I2S2CG							14
	#define TMR2CG							13
	#define TMR1CG							12
	#define TMR0CG							10
	#define I2S1CG							9
	#define I2S0CG							8
	#define MMCSD1CG						7
	#define I2CCG							6
	#define MMCSD0CG						4
	#define DMA0CG							3
	#define UARTCG							2
	#define SPICG							1
	#define IS23CG							0
	#define PCGCR2				           (IOPORT_REGISTER(0x1C03))					// Peripheral Clock Gating Control Register 2
	#define ANAREGCG						6
	#define DMA3CG							5
	#define DMA2CG							4
	#define DMA1CG							3
	#define USBCG							2
	#define SARCG							1
	#define LCDCG							0	
	#define CLKSTOP				           (IOPORT_REGISTER(0x1C3A))					// Peripheral Clock Stop Request/Acknowledge Register
	#define URTCLKSTPACK					5
	#define URCLKSTPREQ						4
	#define USBCLKSTPACK					3
	#define USBCLKSTPREQ					2
	//#define NMI							   (IOPORT_REGISTER(0x1C3E))				// see Chip Support Libary V3 - Timer Nested Example, unfortunately not in official TI documentation! Can be used to configure NMI.

	// Reset (Software) Control Registers ---------------------------
	#define PSRCR				           (IOPORT_REGISTER(0x1C04))					// Peripheral Software Reset Counter Register
	#define PRCR				           (IOPORT_REGISTER(0x1C05))					// Peripheral Software Reset Control Register
	#define PG4_RST							7											// reset peripheral group 4: I2S2, I2S3, UART and SPI
	#define I2S3_RST						7
	#define I2S2_RST						7
	#define UART_RST						7
	#define SPI_RST							7
	#define PG3_RST							5											// reset peripheral group 3: MMC/SD0, MMC/SD1, I2S0, I2S1
	#define MMCSD0_RST						5
	#define MMCSD1_RST						5
	#define I2S1_RST						5
	#define I2S0_RST						5
	#define DMA_RST							4
	#define USB_RST							3
	#define SAR_RST							2
	#define PG1_RST							1											// reset peripheral group 1: TIMER0,1,2
	#define TIMER_RST						1
	#define I2C_RST							0
	
	// PLL Registers ------------------------------------------------
	#define ICR							   (IOPORT_REGISTER(0x0001))					// Idle Configuration Register
	#define HWAI							9
	#define IPORTI							8
	#define MPORTI							7
	#define XPORTI							6
	#define DPORTI							5
	#define IDLECFG							(0x7<<1)									// must always set in ICR before next IDLE instruction execution!
	#define CPUI							0
	#define ISTR						   (IOPORT_REGISTER(0x0002))					// Idle Status Register
	#define HWAIS							9
	#define IPORTIS							8
	#define MPORTIS							7
	#define XPORTIS							6
	#define DPORTIS							5
	#define CPUIS							0
	#define CGCR1						   (IOPORT_REGISTER(0x1C20))					// Clock Generator Control Register 1 (MSB must be set for proper PLL operation!)
	#define PLL_ON							15
	#define PLL_PWRDN						12
	#define CGCR2						   (IOPORT_REGISTER(0x1C21))					// Clock Generator Control Register 2
	#define RDYBYPASS						15
	#define CGCR3						   (IOPORT_REGISTER(0x1C22))					// Clock Generator Control Register 3 (must set during pll init, to 0x0806 see C5505evm_pg20.gel file)
	#define EN_LOW_JIT						11											// ...only mentioned in C5505evm_pg20.gel file
	#define TESTLOCKMON						8											
	#define LONG_LK_CNT						4											
	#define EN_FASTSTART					2											
	#define CGCR4						   (IOPORT_REGISTER(0x1C23))					// Clock Generator Control Register 4
	#define OUTDIVEN						9
	#define CLKOUT						   (IOPORT_REGISTER(0x1C24))
	#define CCSSR						   (IOPORT_REGISTER(0x1C24))
	#define OUTPUT_SYSPLL					(0x0<<0)
	#define CLKOUT_HIGH						(0x1<<0)
	#define CLKOUT_LOW						(0x3<<0)
	#define OUTPUT_USBPLL					(0x7<<0)
	#define OUTPUT_SARCLK					(0x9<<0)
	#define OUTPUT_SYSCLK					(0xB<<0)
	#define ODSCR						   (IOPORT_REGISTER(0x1C16))
	#define CLKOUTSR						2
	#define CCR2						   (IOPORT_REGISTER(0x1C1F))					// Clock Configuration Register 2
	#define SYSCLKSTRC						4
	#define SYSCLK_BYPASS_RTC				(0x0<<4)
	#define SYSCLK_PLLMODE_RTC				(0x1<<4)
	#define SYSCLK_BYPASS_CLKIN				(0x2<<4)
	#define SYSCLK_PLLMODE_CLKIN			(0x3<<4)
	#define CLKSELSTAT						2
	#define SYSCLKSEL						0

	// LDO Registers ------------------------------------------------
	#define LDOCNTL						   (IOPORT_REGISTER(0x7004))					// LDO Control Register
	#define DSP_LDO_V						1
	#define DSP_LDO_EN						0
	
	// RAM Control Registers ----------------------------------------
	#define RAMSLPMDCNTLR1				   (IOPORT_REGISTER(0x1C28))					// RAM Sleep Mode Control Register 1
	#define RAMSLPMDCNTLR2				   (IOPORT_REGISTER(0x1C2A))					// RAM Sleep Mode Control Register 1
	#define RAMSLPMDCNTLR3				   (IOPORT_REGISTER(0x1C2B))					// RAM Sleep Mode Control Register 1
	#define RAMSLPMDCNTLR4				   (IOPORT_REGISTER(0x1C2C))					// RAM Sleep Mode Control Register 1
	#define RAMSLPMDCNTLR5				   (IOPORT_REGISTER(0x1C2D))					// RAM Sleep Mode Control Register 1

	// DMA Control Registers ----------------------------------------
	#define DMAIFR				   		   (IOPORT_REGISTER(0x1C30))					// DMA Interrupt Flag Register
	#define DMA3CH3IF						15
	#define DMA3CH2IF						14
	#define DMA3CH1IF						13
	#define DMA3CH0IF						12
	#define DMA2CH3IF						11
	#define DMA2CH2IF						10
	#define DMA2CH1IF						9
	#define DMA2CH0IF						8
	#define DMA1CH3IF						7
	#define DMA1CH2IF						6
	#define DMA1CH1IF						5
	#define DMA1CH0IF						4
	#define DMA0CH3IF						3
	#define DMA0CH2IF						2
	#define DMA0CH1IF						1
	#define DMA0CH0IF						0
	#define DMAIER				   		   (IOPORT_REGISTER(0x1C31))					// DMA Interrupt Enable Register
	#define DMA3CH3IE						15
	#define DMA3CH2IE						14
	#define DMA3CH1IE						13
	#define DMA3CH0IE						12
	#define DMA2CH3IE						11
	#define DMA2CH2IE						10
	#define DMA2CH1IE						9
	#define DMA2CH0IE						8
	#define DMA1CH3IE						7
	#define DMA1CH2IE						6
	#define DMA1CH1IE						5
	#define DMA1CH0IE						4
	#define DMA0CH3IE						3
	#define DMA0CH2IE						2
	#define DMA0CH1IE						1
	#define DMA0CH0IE						0
	#define DMA0CESR1			   		   (IOPORT_REGISTER(0x1C1A))					// DMA0 Channel Event Source Register 1
	#define DMA0CESR2			   		   (IOPORT_REGISTER(0x1C1B))					// DMA0 Channel Event Source Register 2
	#define DMA1CESR1			   		   (IOPORT_REGISTER(0x1C1C))					// DMA1 Channel Event Source Register 1
	#define DMA1CESR2			   		   (IOPORT_REGISTER(0x1C1D))					// DMA1 Channel Event Source Register 2
	#define DMA2CESR1			   		   (IOPORT_REGISTER(0x1C36))					// DMA2 Channel Event Source Register 1
	#define DMA2CESR2			   		   (IOPORT_REGISTER(0x1C37))					// DMA2 Channel Event Source Register 2
	#define DMA3CESR1			   		   (IOPORT_REGISTER(0x1C38))					// DMA3 Channel Event Source Register 1
	#define DMA3CESR2			   		   (IOPORT_REGISTER(0x1C39))					// DMA3 Channel Event Source Register 2
	
	#define DMA0CH0SSAL			   		   (IOPORT_REGISTER(0x0C00))					// DMA0 Source Start Address Ch0 (lower part)
	#define DMA0CH0SSAU			   		   (IOPORT_REGISTER(0x0C01))					// DMA0 Source Start Address Ch0 (upper part)
	#define DMA0CH0DSAL			   		   (IOPORT_REGISTER(0x0C02))					// DMA0 Destination Start Address Ch0 (lower part)
	#define DMA0CH0DSAU			   		   (IOPORT_REGISTER(0x0C03))					// DMA0 Destination Start Address Ch0(upper part)
	#define DMA0CH0TCR1			   		   (IOPORT_REGISTER(0x0C04))					// DMA0 Transfer Control Register Ch0 1
	#define DMA0CH0TCR2			   		   (IOPORT_REGISTER(0x0C05))					// DMA0 Transfer Control Register Ch0 2
	#define DMA0CH1SSAL			   		   (IOPORT_REGISTER(0x0C20))					// DMA0 Source Start Address Ch1 (lower part)
	#define DMA0CH1SSAU			   		   (IOPORT_REGISTER(0x0C21))					// DMA0 Source Start Address Ch1 (upper part)
	#define DMA0CH1DSAL			   		   (IOPORT_REGISTER(0x0C22))					// DMA0 Destination Start Address Ch1 (lower part)
	#define DMA0CH1DSAU			   		   (IOPORT_REGISTER(0x0C23))					// DMA0 Destination Start Address Ch1(upper part)
	#define DMA0CH1TCR1			   		   (IOPORT_REGISTER(0x0C24))					// DMA0 Transfer Control Register Ch1 1
	#define DMA0CH1TCR2			   		   (IOPORT_REGISTER(0x0C25))					// DMA0 Transfer Control Register Ch1 2
	#define DMA0CH2SSAL			   		   (IOPORT_REGISTER(0x0C40))					// DMA0 Source Start Address Ch2 (lower part)
	#define DMA0CH2SSAU			   		   (IOPORT_REGISTER(0x0C41))					// DMA0 Source Start Address Ch2 (upper part)
	#define DMA0CH2DSAL			   		   (IOPORT_REGISTER(0x0C42))					// DMA0 Destination Start Address Ch2 (lower part)
	#define DMA0CH2DSAU			   		   (IOPORT_REGISTER(0x0C43))					// DMA0 Destination Start Address Ch2(upper part)
	#define DMA0CH2TCR1			   		   (IOPORT_REGISTER(0x0C44))					// DMA0 Transfer Control Register Ch2 1
	#define DMA0CH2TCR2			   		   (IOPORT_REGISTER(0x0C45))					// DMA0 Transfer Control Register Ch2 2
	#define DMA0CH3SSAL			   		   (IOPORT_REGISTER(0x0C60))					// DMA0 Source Start Address Ch3 (lower part)
	#define DMA0CH3SSAU			   		   (IOPORT_REGISTER(0x0C61))					// DMA0 Source Start Address Ch3 (upper part)
	#define DMA0CH3DSAL			   		   (IOPORT_REGISTER(0x0C62))					// DMA0 Destination Start Address Ch3 (lower part)
	#define DMA0CH3DSAU			   		   (IOPORT_REGISTER(0x0C63))					// DMA0 Destination Start Address Ch3(upper part)
	#define DMA0CH3TCR1			   		   (IOPORT_REGISTER(0x0C64))					// DMA0 Transfer Control Register Ch3 1
	#define DMA0CH3TCR2			   		   (IOPORT_REGISTER(0x0C65))					// DMA0 Transfer Control Register Ch3 2

	#define DMA1CH0SSAL			   		   (IOPORT_REGISTER(0x0D00))					// DMA1 Source Start Address Ch0 (lower part)
	#define DMA1CH0SSAU			   		   (IOPORT_REGISTER(0x0D01))					// DMA1 Source Start Address Ch0 (upper part)
	#define DMA1CH0DSAL			   		   (IOPORT_REGISTER(0x0D02))					// DMA1 Destination Start Address Ch0 (lower part)
	#define DMA1CH0DSAU			   		   (IOPORT_REGISTER(0x0D03))					// DMA1 Destination Start Address Ch0(upper part)
	#define DMA1CH0TCR1			   		   (IOPORT_REGISTER(0x0D04))					// DMA1 Transfer Control Register Ch0 1
	#define DMA1CH0TCR2			   		   (IOPORT_REGISTER(0x0D05))					// DMA1 Transfer Control Register Ch0 2
	#define DMA1CH1SSAL			   		   (IOPORT_REGISTER(0x0D20))					// DMA1 Source Start Address Ch1 (lower part)
	#define DMA1CH1SSAU			   		   (IOPORT_REGISTER(0x0D21))					// DMA1 Source Start Address Ch1 (upper part)
	#define DMA1CH1DSAL			   		   (IOPORT_REGISTER(0x0D22))					// DMA1 Destination Start Address Ch1 (lower part)
	#define DMA1CH1DSAU			   		   (IOPORT_REGISTER(0x0D23))					// DMA1 Destination Start Address Ch1(upper part)
	#define DMA1CH1TCR1			   		   (IOPORT_REGISTER(0x0D24))					// DMA1 Transfer Control Register Ch1 1
	#define DMA1CH1TCR2			   		   (IOPORT_REGISTER(0x0D25))					// DMA1 Transfer Control Register Ch1 2
	#define DMA1CH2SSAL			   		   (IOPORT_REGISTER(0x0D40))					// DMA1 Source Start Address Ch2 (lower part)
	#define DMA1CH2SSAU			   		   (IOPORT_REGISTER(0x0D41))					// DMA1 Source Start Address Ch2 (upper part)
	#define DMA1CH2DSAL			   		   (IOPORT_REGISTER(0x0D42))					// DMA1 Destination Start Address Ch2 (lower part)
	#define DMA1CH2DSAU			   		   (IOPORT_REGISTER(0x0D43))					// DMA1 Destination Start Address Ch2(upper part)
	#define DMA1CH2TCR1			   		   (IOPORT_REGISTER(0x0D44))					// DMA1 Transfer Control Register Ch2 1
	#define DMA1CH2TCR2			   		   (IOPORT_REGISTER(0x0D45))					// DMA1 Transfer Control Register Ch2 2
	#define DMA1CH3SSAL			   		   (IOPORT_REGISTER(0x0D60))					// DMA1 Source Start Address Ch3 (lower part)
	#define DMA1CH3SSAU			   		   (IOPORT_REGISTER(0x0D61))					// DMA1 Source Start Address Ch3 (upper part)
	#define DMA1CH3DSAL			   		   (IOPORT_REGISTER(0x0D62))					// DMA1 Destination Start Address Ch3 (lower part)
	#define DMA1CH3DSAU			   		   (IOPORT_REGISTER(0x0D63))					// DMA1 Destination Start Address Ch3(upper part)
	#define DMA1CH3TCR1			   		   (IOPORT_REGISTER(0x0D64))					// DMA1 Transfer Control Register Ch3 1
	#define DMA1CH3TCR2			   		   (IOPORT_REGISTER(0x0D65))					// DMA1 Transfer Control Register Ch3 2

	#define DMA2CH0SSAL			   		   (IOPORT_REGISTER(0x0E00))					// DMA2 Source Start Address Ch0 (lower part)
	#define DMA2CH0SSAU			   		   (IOPORT_REGISTER(0x0E01))					// DMA2 Source Start Address Ch0 (upper part)
	#define DMA2CH0DSAL			   		   (IOPORT_REGISTER(0x0E02))					// DMA2 Destination Start Address Ch0 (lower part)
	#define DMA2CH0DSAU			   		   (IOPORT_REGISTER(0x0E03))					// DMA2 Destination Start Address Ch0(upper part)
	#define DMA2CH0TCR1			   		   (IOPORT_REGISTER(0x0E04))					// DMA2 Transfer Control Register Ch0 1
	#define DMA2CH0TCR2			   		   (IOPORT_REGISTER(0x0E05))					// DMA2 Transfer Control Register Ch0 2
	#define DMA2CH1SSAL			   		   (IOPORT_REGISTER(0x0E20))					// DMA2 Source Start Address Ch1 (lower part)
	#define DMA2CH1SSAU			   		   (IOPORT_REGISTER(0x0E21))					// DMA2 Source Start Address Ch1 (upper part)
	#define DMA2CH1DSAL			   		   (IOPORT_REGISTER(0x0E22))					// DMA2 Destination Start Address Ch1 (lower part)
	#define DMA2CH1DSAU			   		   (IOPORT_REGISTER(0x0E23))					// DMA2 Destination Start Address Ch1(upper part)
	#define DMA2CH1TCR1			   		   (IOPORT_REGISTER(0x0E24))					// DMA2 Transfer Control Register Ch1 1
	#define DMA2CH1TCR2			   		   (IOPORT_REGISTER(0x0E25))					// DMA2 Transfer Control Register Ch1 2
	#define DMA2CH2SSAL			   		   (IOPORT_REGISTER(0x0E40))					// DMA2 Source Start Address Ch2 (lower part)
	#define DMA2CH2SSAU			   		   (IOPORT_REGISTER(0x0E41))					// DMA2 Source Start Address Ch2 (upper part)
	#define DMA2CH2DSAL			   		   (IOPORT_REGISTER(0x0E42))					// DMA2 Destination Start Address Ch2 (lower part)
	#define DMA2CH2DSAU			   		   (IOPORT_REGISTER(0x0E43))					// DMA2 Destination Start Address Ch2(upper part)
	#define DMA2CH2TCR1			   		   (IOPORT_REGISTER(0x0E44))					// DMA2 Transfer Control Register Ch2 1
	#define DMA2CH2TCR2			   		   (IOPORT_REGISTER(0x0E45))					// DMA2 Transfer Control Register Ch2 2
	#define DMA2CH3SSAL			   		   (IOPORT_REGISTER(0x0E60))					// DMA2 Source Start Address Ch3 (lower part)
	#define DMA2CH3SSAU			   		   (IOPORT_REGISTER(0x0E61))					// DMA2 Source Start Address Ch3 (upper part)
	#define DMA2CH3DSAL			   		   (IOPORT_REGISTER(0x0E62))					// DMA2 Destination Start Address Ch3 (lower part)
	#define DMA2CH3DSAU			   		   (IOPORT_REGISTER(0x0E63))					// DMA2 Destination Start Address Ch3(upper part)
	#define DMA2CH3TCR1			   		   (IOPORT_REGISTER(0x0E64))					// DMA2 Transfer Control Register Ch3 1
	#define DMA2CH3TCR2			   		   (IOPORT_REGISTER(0x0E65))					// DMA2 Transfer Control Register Ch3 2

	#define DMA3CH0SSAL			   		   (IOPORT_REGISTER(0x0F00))					// DMA3 Source Start Address Ch0 (lower part)
	#define DMA3CH0SSAU			   		   (IOPORT_REGISTER(0x0F01))					// DMA3 Source Start Address Ch0 (upper part)
	#define DMA3CH0DSAL			   		   (IOPORT_REGISTER(0x0F02))					// DMA3 Destination Start Address Ch0 (lower part)
	#define DMA3CH0DSAU			   		   (IOPORT_REGISTER(0x0F03))					// DMA3 Destination Start Address Ch0(upper part)
	#define DMA3CH0TCR1			   		   (IOPORT_REGISTER(0x0F04))					// DMA3 Transfer Control Register Ch0 1
	#define DMA3CH0TCR2			   		   (IOPORT_REGISTER(0x0F05))					// DMA3 Transfer Control Register Ch0 2
	#define DMA3CH1SSAL			   		   (IOPORT_REGISTER(0x0F20))					// DMA3 Source Start Address Ch1 (lower part)
	#define DMA3CH1SSAU			   		   (IOPORT_REGISTER(0x0F21))					// DMA3 Source Start Address Ch1 (upper part)
	#define DMA3CH1DSAL			   		   (IOPORT_REGISTER(0x0F22))					// DMA3 Destination Start Address Ch1 (lower part)
	#define DMA3CH1DSAU			   		   (IOPORT_REGISTER(0x0F23))					// DMA3 Destination Start Address Ch1(upper part)
	#define DMA3CH1TCR1			   		   (IOPORT_REGISTER(0x0F24))					// DMA3 Transfer Control Register Ch1 1
	#define DMA3CH1TCR2			   		   (IOPORT_REGISTER(0x0F25))					// DMA3 Transfer Control Register Ch1 2
	#define DMA3CH2SSAL			   		   (IOPORT_REGISTER(0x0F40))					// DMA3 Source Start Address Ch2 (lower part)
	#define DMA3CH2SSAU			   		   (IOPORT_REGISTER(0x0F41))					// DMA3 Source Start Address Ch2 (upper part)
	#define DMA3CH2DSAL			   		   (IOPORT_REGISTER(0x0F42))					// DMA3 Destination Start Address Ch2 (lower part)
	#define DMA3CH2DSAU			   		   (IOPORT_REGISTER(0x0F43))					// DMA3 Destination Start Address Ch2(upper part)
	#define DMA3CH2TCR1			   		   (IOPORT_REGISTER(0x0F44))					// DMA3 Transfer Control Register Ch2 1
	#define DMA3CH2TCR2			   		   (IOPORT_REGISTER(0x0F45))					// DMA3 Transfer Control Register Ch2 2
	#define DMA3CH3SSAL			   		   (IOPORT_REGISTER(0x0F60))					// DMA3 Source Start Address Ch3 (lower part)
	#define DMA3CH3SSAU			   		   (IOPORT_REGISTER(0x0F61))					// DMA3 Source Start Address Ch3 (upper part)
	#define DMA3CH3DSAL			   		   (IOPORT_REGISTER(0x0F62))					// DMA3 Destination Start Address Ch3 (lower part)
	#define DMA3CH3DSAU			   		   (IOPORT_REGISTER(0x0F63))					// DMA3 Destination Start Address Ch3(upper part)
	#define DMA3CH3TCR1			   		   (IOPORT_REGISTER(0x0F64))					// DMA3 Transfer Control Register Ch3 1
	#define DMA3CH3TCR2			   		   (IOPORT_REGISTER(0x0F65))					// DMA3 Transfer Control Register Ch3 2
	
	/* DMAcCHcTCR2 */
	#define DMAEN							15
	#define STATUS							14
	#define INTEN							13
	#define AUTORLD							12
	#define DSTAMODE						8
	#define DSTAMODE_INC					(0x0<<8)
	#define DSTAMODE_CONST					(0x2<<8)
	#define SRAMODE							6
	#define SRAMODE_INC						(0x0<<6)
	#define SRAMODE_CONST					(0x2<<6)
	#define BURSTMODE						3
	#define BURSTMODE_OFF					(0x0<<3)
	#define BURSTMODE_1DOUBLEWORD			(0x0<<3)
	#define BURSTMODE_2DOUBLEWORD			(0x1<<3)
	#define BURSTMODE_4DOUBLEWORD			(0x2<<3)
	#define BURSTMODE_8DOUBLEWORD			(0x3<<3)
	#define BURSTMODE_16DOUBLEWORD			(0x4<<3)
	#define SYNCMODE						2
	#define LAST_XFER						1
	#define PING_PONG_EN					0
	
	// RTC Registers -------------------------------------------------
	#define RTCINTEN       				   (IOPORT_REGISTER(0x1900))					// RTC Interrupt Enable
	#define RTCUPDATE      				   (IOPORT_REGISTER(0x1901))					// RTC Update Register
	#define TIMEUPDT						15
	#define ALARMUPDT						14
	#define RTCMIL        				   (IOPORT_REGISTER(0x1904))					// RTC Millicseconds Register
	#define MS3								12											// ...shift values fourth decimal value
	#define MS2								8											// ...shift values third decimal value
	#define MS1								4											// ...shift values second decimal value
	#define MS0								0											// ...shift values first decimal value
	#define RTCMILA        				   (IOPORT_REGISTER(0x1905))					// RTC Millicseconds Alarm Register
	#define MSA3							12											// ...shift values fourth decimal value
	#define MSA2							8											// ...shift values third decimal value
	#define MSA1							4											// ...shift values second decimal value
	#define MSA0							0											// ...shift values first decimal value
	#define RTCSEC        				   (IOPORT_REGISTER(0x1908))					// RTC Seconds Register
	#define SEC1							4
	#define SEC0							0											// ...shift values first decimal value
	#define RTCSECA        				   (IOPORT_REGISTER(0x1909))					// RTC Seconds Alarm Register
	#define SECA1							4											// ...shift values second decimal value
	#define SECA0							0											// ...shift values first decimal value
	#define RTCMIN        				   (IOPORT_REGISTER(0x190C))					// RTC Minute Register
	#define MIN1							4											// ...shift values second decimal value
	#define MIN0							0											// ...shift values first decimal value
	#define RTCMINA        				   (IOPORT_REGISTER(0x190D))					// RTC Minute Alarm Register
	#define MINA1							4											// ...shift values second decimal value
	#define MINA0							0											// ...shift values first decimal value
	#define RTCCHOUR       				   (IOPORT_REGISTER(0x1910))					// RTC Hour Register
	#define HOUR1							4											// ...shift values second decimal value
	#define HOUR0							0											// ...shift values first decimal value
	#define RTCCHOURA      				   (IOPORT_REGISTER(0x1911))					// RTC Hour Alarm Register
	#define HOURA1							4											// ...shift values second decimal value
	#define HOURA0							0											// ...shift values first decimal value
	#define RTCDAY       				   (IOPORT_REGISTER(0x1914))					// RTC Day Register
	#define DAY1							4											// ...shift values second decimal value
	#define DAY0							0											// ...shift values first decimal value
	#define RTCDAYA       				   (IOPORT_REGISTER(0x1915))					// RTC Day Alarm Register
	#define DAYA1							4											// ...shift values second decimal value
	#define DAYA0							0											// ...shift values first decimal value
	#define RTCMONTH       				   (IOPORT_REGISTER(0x1918))					// RTC Month Register
	#define MONTH1							4											// ...shift values second decimal value
	#define MONTH0							0											// ...shift values first decimal value
	#define RTCMONTHA      				   (IOPORT_REGISTER(0x1919))					// RTC Month Alarm Register
	#define MONTHA1							4											// ...shift values second decimal value
	#define MONTHA0							0											// ...shift values first decimal value
	#define RTCYEAR        				   (IOPORT_REGISTER(0x191C))					// RTC Year Register
	#define YEAR1							4											// ...shift values second decimal value
	#define YEAR0							0											// ...shift values first decimal value
	#define RTCYEARA       				   (IOPORT_REGISTER(0x191D))					// RTC Year Alarm Register
	#define YEARA1							4											// ...shift values second decimal value
	#define YEARA0							0											// ...shift values first decimal value
	#define RTCINTFLG      				   (IOPORT_REGISTER(0x1920))					// RTC Interrupt Flag Register
	#define ALARMFL							15
	#define EXTFL							5
	#define DAYFL							4
	#define HOURFL							3
	#define MINFL							2
	#define SECFL							1
	#define MSFL							0
	#define RTCNOPWR      				   (IOPORT_REGISTER(0x1921))					// RTC Lost Power Status Register
	#define PWRUP							0
	#define RTCINTREG      				   (IOPORT_REGISTER(0x1924))					// RTC Interrupt Alarm Enable Register
	#define ALARMINTEN						15	
	#define EXTINTEN						5
	#define DAYINTEN						4
	#define HOURINTEN						3
	#define MININTEN						2
	#define SECINTEN						1
	#define MSINTEN							0
	#define RTCDRIFT      				   (IOPORT_REGISTER(0x1928))					// RTC Drift Register
	#define DRIFT							15
	#define COMP3							12
	#define COMP2							8
	#define COMP1							4
	#define COMP0							0
	#define RTCOSC      				   (IOPORT_REGISTER(0x192C))					// RTC Oscillator Register 
	#define RTCRESET						15
	#define RTCPMGT        				   (IOPORT_REGISTER(0x1930))					// RTC Power Managment Register
	#define WU_DOUT							4
	#define WU_DIR							3
	#define BG_PD							2
	#define LDO_PD							1
	#define RTCCLKOUTEN						0
	#define RTCSCR1      				   (IOPORT_REGISTER(0x1960))					// RTC LSW Scratch Register 1
	#define RTCSCR2      				   (IOPORT_REGISTER(0x1961))					// RTC MSW Scratch Register 2
	#define RTCSCR3      				   (IOPORT_REGISTER(0x1964))					// RTC LSW Scratch Register 1
	#define RTCSCR4      				   (IOPORT_REGISTER(0x1965))					// RTC MSW Scratch Register 2

	// Timer Registers ----------------------------------------------
	/* Watchdog */
	#define WDKCKLK				           (IOPORT_REGISTER(0x1880))					// Watchdog Kick Lock Register
	#define WDKICK				           (IOPORT_REGISTER(0x1882))					// Watchdog Kick Register
	#define WDSVLR				           (IOPORT_REGISTER(0x1884))					// Watchdog Start Value Lock Register
	#define WDSVR				           (IOPORT_REGISTER(0x1886))					// Watchdog Start Value Register
	#define WDENLOK				           (IOPORT_REGISTER(0x1888))					// Watchdog Enable Lock Register
	#define WDEN				           (IOPORT_REGISTER(0x188A))					// Watchdog Enable Register
	#define EN								0	
	#define WDPSLR				           (IOPORT_REGISTER(0x188C))					// Wachtdog Prescale Lock Register
	#define WDPS				           (IOPORT_REGISTER(0x188E))					// Watchdog Prescale Register
	
	/* Timer 0 */
	#define TCR0				           (IOPORT_REGISTER(0x1810))					// Timer 0 Control Register
	#define TIMPRD01			           (IOPORT_REGISTER(0x1812))					// Timer 0 Period Register (lower part)
	#define TIMPRD02			           (IOPORT_REGISTER(0x1813))					// Timer 0 Period Register (upper part)
	#define TIMCNT01			           (IOPORT_REGISTER(0x1814))					// Timer 0 Counter Register (lower part)
	#define TIMCNT02			           (IOPORT_REGISTER(0x1815))					// Timer 0 Counter Register (upper part)

	/* Timer 1 */	
	#define TCR1				           (IOPORT_REGISTER(0x1850))					// Timer 1 Control Register
	#define TIMPRD11			           (IOPORT_REGISTER(0x1852))					// Timer 1 Period Register (lower part)
	#define TIMPRD12			           (IOPORT_REGISTER(0x1853))					// Timer 1 Period Register (upper part)
	#define TIMCNT11			           (IOPORT_REGISTER(0x1854))					// Timer 1 Counter Register (lower part)
	#define TIMCNT12			           (IOPORT_REGISTER(0x1855))					// Timer 1 Counter Register (upper part)

	/* Timer 2 */	
	#define TCR2				           (IOPORT_REGISTER(0x1890))					// Timer 2 Control Register
	#define TIMPRD21			           (IOPORT_REGISTER(0x1892))					// Timer 2 Period Register (lower part)
	#define TIMPRD22			           (IOPORT_REGISTER(0x1893))					// Timer 2 Period Register (upper part)
	#define TIMCNT21			           (IOPORT_REGISTER(0x1894))					// Timer 2 Counter Register (lower part)
	#define TIMCNT22			           (IOPORT_REGISTER(0x1895))					// Timer 2 Counter Register (upper part)
	
	/* TCRx */
	#define TIMEN							15
	#define AUTORELOAD						1
	#define	START							0
	#define DIV2							(0x0<<2)									// ... Prescale Divider: SYS_CLK/2
	#define DIV4							(0x1<<2)									// ... Prescale Divider: SYS_CLK/4
	#define DIV8							(0x2<<2)									// ... Prescale Divider: SYS_CLK/8
	#define DIV16							(0x3<<2)									// ... Prescale Divider: SYS_CLK/16
	#define DIV32							(0x4<<2)									// ... Prescale Divider: SYS_CLK/32
	#define DIV64							(0x5<<2)									// ... Prescale Divider: SYS_CLK/64
	#define DIV128							(0x6<<2)									// ... Prescale Divider: SYS_CLK/128
	#define DIV256							(0x7<<2)									// ... Prescale Divider: SYS_CLK/256
	#define DIV512							(0x8<<2)									// ... Prescale Divider: SYS_CLK/512
	#define DIV1024							(0x9<<2)									// ... Prescale Divider: SYS_CLK/1024
	#define DIV2048							(0xA<<2)									// ... Prescale Divider: SYS_CLK/2048
	#define DIV4096							(0xB<<2)									// ... Prescale Divider: SYS_CLK/4096
	#define DIV8192							(0xC<<2)									// ... Prescale Divider: SYS_CLK/8192
	
	/* TIAFR */
	#define TIAFR						   (IOPORT_REGISTER(0x1C14))					// Timer Interrupt Aggregation Flag Register
	#define TIM2FLAG						2											
	#define TIM1FLAG						1
	#define TIM0FLAG						0
	#define TIMFLAG_CLEAR					0x7

	// MMC/SD Card Control Registers --------------------------------
	/* eMMC/SD0 */
	#define SD0CTL            			   (IOPORT_REGISTER(0x3A00)) 					// SD0 Control Register
	#define SD0CLK            			   (IOPORT_REGISTER(0x3A04)) 					// SD0 Memory Clock Control Register
	#define SD0ST0            			   (IOPORT_REGISTER(0x3A08)) 					// SD0 Status Register 0
	#define SD0ST1            			   (IOPORT_REGISTER(0x3A0C)) 					// SD0 Status Register 1
	#define SD0IM            			   (IOPORT_REGISTER(0x3A10)) 					// SD0 Interrupt Mask Register
	#define SD0TOR            			   (IOPORT_REGISTER(0x3A14)) 					// SD0 Response Time-Out Register
	#define SD0TOD            			   (IOPORT_REGISTER(0x3A18)) 					// SD0 Data Response Time Out Register
	#define SD0BLEN            			   (IOPORT_REGISTER(0x3A1C)) 					// SD0 Block Length Register
	#define SD0NBLK           			   (IOPORT_REGISTER(0x3A20)) 					// SD0 Number of Blocks Register
	#define SD0NBLC            			   (IOPORT_REGISTER(0x3A24)) 					// SD0 Numer of Blocks Count Register
	#define SD0DRR1            			   (IOPORT_REGISTER(0x3A28)) 					// SD0 Data Receive Register 1
	#define SD0DRR2            			   (IOPORT_REGISTER(0x3A29)) 					// SD0 Data Receive Register 2
	#define SD0DXR1            			   (IOPORT_REGISTER(0x3A2C)) 					// SD0 Data Transmit Register 1
	#define SD0DXR2            			   (IOPORT_REGISTER(0x3A2D)) 					// SD0 Data Transmit Register 2
	#define MMC0SD1            			   (IOPORT_REGISTER(0x3A30)) 					// MMC0 Command Register 1
	#define MMC0SD2            			   (IOPORT_REGISTER(0x3A31)) 					// MMC0 Command Register 2
	#define SD0ARG1            			   (IOPORT_REGISTER(0x3A34)) 					// SD0 Argument Register 1
	#define SD0ARG2            			   (IOPORT_REGISTER(0x3A35)) 					// SD0 Argument Register 2
	#define SD0RSP0            			   (IOPORT_REGISTER(0x3A38)) 					// SD0 Response Register 0
	#define SD0RSP1            			   (IOPORT_REGISTER(0x3A39)) 					// SD0 Response Register 1 
	#define SD0RSP2            			   (IOPORT_REGISTER(0x3A3C))  					// SD0 Response Register 2
	#define SD0RSP3            			   (IOPORT_REGISTER(0x3A3D))  					// SD0 Response Register 3
	#define SD0RSP4            			   (IOPORT_REGISTER(0x3A40))  					// SD0 Response Register 4
	#define SD0RSP5            			   (IOPORT_REGISTER(0x3A41))  					// SD0 Response Register 5
	#define SD0RSP6            			   (IOPORT_REGISTER(0x3A44))  					// SD0 Response Register 6
	#define SD0RSP7            			   (IOPORT_REGISTER(0x3A45))  					// SD0 Response Register 7
	#define SD0DRSP            			   (IOPORT_REGISTER(0x3A48))  					// SD0 Data Response Register
	#define SD0CIDX            			   (IOPORT_REGISTER(0x3A50)) 					// SD0 Command Index Register
	#define SD0IOCTL           			   (IOPORT_REGISTER(0x3A64)) 					// SD0 Control Register
	#define SD0IOST0           			   (IOPORT_REGISTER(0x3A68)) 					// SD0 Status Register 0
	#define SD0IOIEN           			   (IOPORT_REGISTER(0x3A6C)) 					// SD0 Interrupt Enable Register
	#define SD0IOIST            		   (IOPORT_REGISTER(0x3A70)) 					// SD0 Interrupt Status Register
	#define SD0SDFIFOCTL      			   (IOPORT_REGISTER(0x3A74)) 					// SD0 FIFO Control Register
	
	/* eMMC/SD1 */
	#define SD1CTL            			   (IOPORT_REGISTER(0x3B00)) 
	#define SD1CLK            			   (IOPORT_REGISTER(0x3B04))  					// SD1 Memory Clock Control Register
	#define SD1ST0            			   (IOPORT_REGISTER(0x3B08))  					// SD1 Status Register 0
	#define SD1ST1            			   (IOPORT_REGISTER(0x3B0C)) 					// SD1 Status Register 1
	#define SD1IM            			   (IOPORT_REGISTER(0x3B10)) 					// SD1 Interrupt Mask Register
	#define SD1TOR            			   (IOPORT_REGISTER(0x3B14)) 					// SD1 Response Time-Out Register
	#define SD1TOD            			   (IOPORT_REGISTER(0x3B18)) 					// SD1 Data Response Time Out Register
	#define SD1BLEN            			   (IOPORT_REGISTER(0x3B1C)) 					// SD1 Block Length Register
	#define SD1NBLK           			   (IOPORT_REGISTER(0x3B20)) 					// SD1 Number of Blocks Register
	#define SD1NBLC            			   (IOPORT_REGISTER(0x3B24)) 					// SD1 Numer of Blocks Count Register
	#define SD1DRR1            			   (IOPORT_REGISTER(0x3B28))  					// SD1 Data Receive Register 1
	#define SD1DRR2            			   (IOPORT_REGISTER(0x3B29))   					// SD1 Data Receive Register 2
	#define SD1DXR1            			   (IOPORT_REGISTER(0x3B2C))   					// SD1 Data Transmit Register 2
	#define SD1DXR2            			   (IOPORT_REGISTER(0x3B2D))   					// SD1 Data Transmit Register 2
	#define MMC1SD1            			   (IOPORT_REGISTER(0x3B30)) 					// MMC1 Command Register 1
	#define MMC1SD2            			   (IOPORT_REGISTER(0x3B31)) 					// MMC1 Command Register 2
	#define SD1ARG1            			   (IOPORT_REGISTER(0x3B34)) 					// SD1 Argument Register 1
	#define SD1ARG2            			   (IOPORT_REGISTER(0x3B35))					// SD1 Argument Register 1
	#define SD1RSP0            			   (IOPORT_REGISTER(0x3B38))  					// SD1 Response Register 0
	#define SD1RSP1            			   (IOPORT_REGISTER(0x3B39))  					// SD1 Response Register 1
	#define SD1RSP2            			   (IOPORT_REGISTER(0x3B3C))  					// SD1 Response Register 2
	#define SD1RSP3            			   (IOPORT_REGISTER(0x3B3D))  					// SD1 Response Register 3
	#define SD1RSP4            			   (IOPORT_REGISTER(0x3B40))  					// SD1 Response Register 4
	#define SD1RSP5            			   (IOPORT_REGISTER(0x3B41))  					// SD1 Response Register 5
	#define SD1RSP6            			   (IOPORT_REGISTER(0x3B44))  					// SD1 Response Register 6
	#define SD1RSP7            			   (IOPORT_REGISTER(0x3B45))  					// SD1 Response Register 7
	#define SD1DRSP            			   (IOPORT_REGISTER(0x3B48)) 					// SD1 Data Response Register
	#define SD1CIDX            			   (IOPORT_REGISTER(0x3B50))  					// SD1 Command Index Register
	#define SD1IOCTL           			   (IOPORT_REGISTER(0x3B64)) 					// SD1 Control Register
	#define SD1IOST0           			   (IOPORT_REGISTER(0x3B68)) 					// SD1 Status Register 0
	#define SD1IOIEN           			   (IOPORT_REGISTER(0x3B6C))  					// SD1 Interrupt Enable Register
	#define SD1IOIST            		   (IOPORT_REGISTER(0x3B70)) 					// SD1 Interrupt Status Register
	#define SD1SDFIFOCTL      			   (IOPORT_REGISTER(0x3B74)) 					// SD1 FIFO Control Register
	
	/* SDxCTL */
	#define PERMDX							10
	#define PERMDR							9
	#define DATEG							6
	#define WIDTH							2
	#define CMDRST							1
	#define DATRST							0
	
	/* SDxCLK */ 
	#define CLKEN							8
	
	/* SDxST0 */
	#define TRNDNE							12
	#define DATED							11
	#define DRRDY							10
	#define DXRDY							9
	#define CRCRS							7
	#define CRCRD							6
	#define CRCWR							5
	#define TOUTRS							4
	#define TOUTRD							3
	#define RSPDNE							2
	#define BSYDNE							1
	#define DATDNE							0
	
	/* SDxST1 */
	#define FIFOFUL							6
	#define FIFOEMP							5
	#define DAT3ST							4
	#define DRFUL							3
	#define DXEMP							2
	#define CLKSTP							1
	#define BUSY							0
	
	/* SDxIM */
	#define ETRNDNE							12
	#define EDATED							11
	#define EDRRDY							10
	#define EDXRDY							9
	#define ECRCRS							7
	#define ECRCRD							6
	#define ECRCWR							5
	#define ETOUTRS							4
	#define ETOUTRD							3
	#define ERSPDNE							2
	#define EBSYDNE							1
	#define EDATDNE							0
	
	/* MMCxSD1 */
	#define DCLR							15
	#define INITCK							14
	#define WDATX							13
	#define STRMTP							12
	#define DTRW							11
	#define RSPFMT							9												// command format type response
	#define NO_RESPONSE						(0x0<<9)										// ... no response to command	
	#define RESPONSE_48BIT_CRC				(0x1<<9)										// ... R1,R4,R5 or R6 response. 48Bits with CRC
	#define RESPONSE_136BIT_CRC				(0x2<<9)										// ... R2 response. 136Bits with CRC
	#define RESPONSE_48BIT_NOCRC			(0x3<<9)										// ... R3 response. 48Bits no CRC
	#define BSYEXP							8
	#define PPLEN							7

	/* MMCxSD2 */
	#define DMATRIG							0
	
	/* SDxCIDX */
	#define STRT							7
	#define XMIT							6

	/* SDxIOCTL */
	#define RDWTCR							1
	#define RDWTRQ							0
	
	/* SDxIOST0 */
	#define RDWTST							2
	#define INTPRD							1
	#define DAT1							0
	
	/* SDxIOIEN */
	#define RWSEN							1
	#define SDIOINTEN						0
	
	/* SDxIOIST */
	#define RWS								1
	#define IOINT							0
	
	/* SDxFIFOCTL */
	#define ACCWD							3											// access width used by FIFO to determine full/empty flag
	#define ACCESS_4BYTE					(0x0<<3)									// ... CPU/DMA access width of 4Bytes
	#define ACCESS_3BYTE					(0x1<<3)									// ... CPU/DMA access width of 3Bytes
	#define ACCESS_2BYTE					(0x2<<3)									// ... CPU/DMA access width of 2Bytes
	#define ACCESS_1BYTE					(0x3<<3)									// ... CPU/DMA access width of 1Bytes
	#define FIFOLEV							2
	#define FIFODIR							1
	#define FIFORST							0
	
	// UART Registers -----------------------------------------------
	#define RBR           				   (IOPORT_REGISTER(0x1B00)) 					// Read - UART Receive Buffer Register
	#define THR            				   (IOPORT_REGISTER(0x1B00)) 					// Write - UART Transmit Holding Register
	#define IER            				   (IOPORT_REGISTER(0x1B02)) 					// UART Interrupt Enable Register
	#define ELSI							2
	#define ETBEI							1
	#define ERBI							0
	#define IIR            				   (IOPORT_REGISTER(0x1B04)) 					// UART Interrupt Identification Register (when reading)
	#define IRQ_FIFOEN						6
	#define NON_FIFOMODE					0x0
	#define FIFOMODE						0x3
	#define INTID							1
	#define IRQ_TX_HOLDREG_EMPTY			(0x1<<1)
	#define IRQ_RX_DATA						(0x2<<1)
	#define IRQ_RX_LINESTATUS				(0x3<<1)
	#define IRQ_CHAR_TIMEOUT				(0x6<<1)
	#define IPEND							0
	#define FCR            				   (IOPORT_REGISTER(0x1B04)) 					// UART FIFO Control Register (when writing)
	#define RXFIFTL							6
	#define BYTE_1							(0x0<<6)
	#define BYTE_4							(0x1<<6)
	#define BYTE_8							(0x2<<6)
	#define BYTE_14							(0x3<<6)
	#define DMAMODE1						3
	#define TXCLR							2
	#define RXCLR							1
	#define FIFOEN							0
	#define LCR            				   (IOPORT_REGISTER(0x1B06)) 					// UART Line Control Register
	#define DLAB							7
	#define BC								6
	#define SP								5
	#define EPS								4
	#define PEN								3
	#define STB								2
	#define WLS								0
	#define BITS_5							(0x0<<0)
	#define BITS_6							(0x1<<0)
	#define BITS_7							(0x2<<0)
	#define BITS_8							(0x3<<0)
	#define MCR            				   (IOPORT_REGISTER(0x1B08)) 					// UART Modem Control Register
	#define AFE								5
	#define LOOP							4
	#define RTS								1
	#define LSR            				   (IOPORT_REGISTER(0x1B0A)) 					// UART Line Status Register
	#define RXFIFOE							7
	#define TEMT							6
	#define THRE							5
	#define BI								4
	#define FE								3
	#define PE								2
	#define OE								1
	#define DR								0
	#define MSR            				   (IOPORT_REGISTER(0x1B0C)) 					// UART Mode Status Register
	#define SCR            				   (IOPORT_REGISTER(0x1B0E)) 					// UART Scratch Register
	#define DLL            				   (IOPORT_REGISTER(0x1B10)) 					// UART Divisor Latch LSB Register
	#define DLH            				   (IOPORT_REGISTER(0x1B12)) 					// UART Divisor Latch MSB Register
	#define PID1           				   (IOPORT_REGISTER(0x1B14)) 					// UART Peripheral ID 1 Register
	#define PID2           				   (IOPORT_REGISTER(0x1B16)) 					// UART Peripheral ID 1 Register
	#define PWREMU         				   (IOPORT_REGISTER(0x1B18)) 					// UART Power Mangement and Emulation Register
	#define UTRST							14
	#define URRST							13
	#define FREE							0
	
	// SPI Registers ------------------------------------------------
	#define SPICDR          			   (IOPORT_REGISTER(0x3000)) 					// SPI Clock Divider Register
	#define SPICCR          			   (IOPORT_REGISTER(0x3001)) 					// SPI Clock Control Register
	#define SPI_CLKEN						15
	#define RST								14
	#define SPIDCR1         			   (IOPORT_REGISTER(0x3002)) 					// SPI External Device Setup Register for Chip Select 0 and 1
	#define DD1								11
	#define DELAY_05CLOCK_TOCS1				(0x0<<11)
	#define DELAY_15CLOCK_TOCS1				(0x1<<11)
	#define DELAY_25CLOCK_TOCS1				(0x2<<11)
	#define DELAY_35CLOCK_TOCS1				(0x3<<11)
	#define CKPH1							10
	#define CSP1							9
	#define CKP1							8
	#define DD0								3
	#define DELAY_05CLOCK_TOCS0				(0x0<<3)
	#define DELAY_15CLOCK_TOCS0				(0x1<<3)
	#define DELAY_25CLOCK_TOCS0				(0x2<<3)
	#define DELAY_35CLOCK_TOCS0				(0x3<<3)
	#define CKPH0							2
	#define CSP0							1
	#define CKP0							0	
	#define SPIDCR2         			   (IOPORT_REGISTER(0x3003)) 					// SPI External Device Setup Register for Chip Select 2 and 3
	#define LPBK							15
	#define DD3								11
	#define DELAY_05CLOCK_TOCS3				(0x0<<11)
	#define DELAY_15CLOCK_TOCS3				(0x1<<11)
	#define DELAY_25CLOCK_TOCS3				(0x2<<11)
	#define DELAY_35CLOCK_TOCS3				(0x3<<11)
	#define CKPH3							10
	#define CSP3							9
	#define CKP3							8
	#define DELAY_05CLOCK_TOCS2				(0x0<<3)
	#define DELAY_15CLOCK_TOCS2				(0x1<<3)
	#define DELAY_25CLOCK_TOCS2				(0x2<<3)
	#define DELAY_35CLOCK_TOCS2				(0x3<<3)
	#define CKPH2							2
	#define CSP2							1
	#define CKP2							0		
	#define SPICMD1            			   (IOPORT_REGISTER(0x3004)) 					// SPI Command 1 Register
	#define FIRQ							15
	#define CIRQ							14
	#define SPICMD2            			   (IOPORT_REGISTER(0x3005)) 					// SPI Command 2 Register
	#define CSNUM							12
	#define CS0_ACTIVE						(0x0<<12)
	#define CS1_ACTIVE						(0x1<<12)
	#define CS2_ACTIVE						(0x2<<12)
	#define CS3_ACTIVE						(0x3<<12)
	#define CLEN							3
	#define CMD								0
	#define CMD_READ						(0x1<<0)
	#define CMD_WRITE						(0x2<<0)
	#define SPISTAT1           			   (IOPORT_REGISTER(0x3006)) 					// SPI Status 1 Register
	#define FC								2
	#define CC								1
	#define BUSY							0
	#define SPISTAT2           			   (IOPORT_REGISTER(0x3007)) 					// SPI Status 2 Register
	#define SPIDAT1            			   (IOPORT_REGISTER(0x3008)) 					// SPI Data 1 Register
	#define SPIDAT2            			   (IOPORT_REGISTER(0x3009)) 					// SPI Data 2 Register

	// I2C Registers ------------------------------------------------
	#define ICOAR            			   (IOPORT_REGISTER(0x1A00)) 					// I2C Own Address Register [9:0]
	#define ICIMR             			   (IOPORT_REGISTER(0x1A04)) 					// I2C Interrupt Mask/Status Register [6:0]
	#define AAS							   	6
	#define SCD								5
	#define ICXRDY							4
	#define ICRRDY							3
	#define ARDY							2
	#define NACK							1
	#define AL								0
	#define ICSTR             			   (IOPORT_REGISTER(0x1A08)) 					// I2C Interrupt Status Register [14:0]
	#define SDIR							14
	#define NACKSNT						   	13
	#define BB								12
	#define RSFULL							11
	#define XSMT							10
	#define I2C_AAS							9
	#define AD0								8
	#define SCD								5	
	#define ICCLKL           			   (IOPORT_REGISTER(0x1A0C)) 					// I2C Clock Divider Low Register [15:0]
	#define ICCLKH           			   (IOPORT_REGISTER(0x1A10)) 					// I2C Clock Divider High Register [15:0]
	#define ICCNT            			   (IOPORT_REGISTER(0x1A14)) 					// I2C Data Count Register [15:0]
	#define ICDRR            			   (IOPORT_REGISTER(0x1A18)) 					// READ-ONLY   I2C Data Recieve Register [7:0]
	#define ICSAR            			   (IOPORT_REGISTER(0x1A1C)) 					// I2C Slave Address Register [9:0]
	#define ICDXR            			   (IOPORT_REGISTER(0x1A20)) 					// I2C Data Transmit Register [7:0]
	#define ICMDR            			   (IOPORT_REGISTER(0x1A24)) 					// I2C Mode Register [15:0]
	#define NACKMOD						   	15
	#define I2C_FREE					   	14
	#define STT								13
	#define STP								11
	#define MST								10
	#define TRX								9
	#define XA								8
	#define RM								7
	#define DLB								6
	#define IRS								5
	#define I2C_STB							4
	#define FDF								3
	#define I2C_BC							0
	#define BITCOUNT_8BITS					(0x0<<0)
	#define BITCOUNT_2BITS					(0x2<<0)
	#define BITCOUNT_3BITS					(0x3<<0)
	#define BITCOUNT_4BITS					(0x4<<0)
	#define BITCOUNT_5BITS					(0x5<<0)
	#define BITCOUNT_6BITS					(0x6<<0)
	#define BITCOUNT_7BITS					(0x7<<0)
	#define ICIVR             			    (IOPORT_REGISTER(0x1A28)) 					// I2C Interrupt Vector Register [11:0]
	#define INTCODE							0
	#define IRQ_NONE						(0x0<<0)
	#define IRQ_AL							(0x1<<0)
	#define IRQ_NACK						(0x2<<0)
	#define IRQ_ARDY						(0x3<<0)
	#define IRQ_ICRRDY						(0x4<<0)
	#define IRQ_ICXRDY						(0x5<<0)
	#define IRQ_SCD							(0x6<<0)
	#define IRQ_AAS							(0x7<<0)
	#define ICEMDR           			   (IOPORT_REGISTER(0x1A2C)) 					// I2C Extended Mode Register
	#define IGNACK						   	1
	#define BCM							   	0
	#define ICPSC            			   (IOPORT_REGISTER(0x1A30)) 					// I2C Prescaler Register (I2C clock frq = I2C input clock (=peripheral clock)/(IPSC+1)
	#define ICPID1           			   (IOPORT_REGISTER(0x1A34)) 					// READ-ONLY   I2C Pheripheral ID 1 Register [15:0]
	#define ICPID2           			   (IOPORT_REGISTER(0x1A38)) 					// READ-ONLY   I2C Pheripheral ID 2 Register [7:0]
	#define ICDMAC           			   (IOPORT_REGISTER(0x1A3C)) 					// I2C DMA Control Register [1:0] - unfortunately not in offical TI documentation!
	#define ICPFUNC          			   (IOPORT_REGISTER(0x1A48)) 					// I2C Pin Function Register [0:0] - unfortunately not in offical TI documentation!
	#define ICPDIR           			   (IOPORT_REGISTER(0x1A4C)) 					// I2C Pin Direction Register [1:0] - unfortunately not in offical TI documentation!
	#define ICPDIN           			   (IOPORT_REGISTER(0x1A50)) 					// READ-ONLY   I2C Pin Data In Register [1:0] - unfortunately not in offical TI documentation!
	#define ICPDOUT          			   (IOPORT_REGISTER(0x1A54)) 					// I2C Pin Data Out Register [1:0] - unfortunately not in offical TI documentation!
	#define ICPDSET          			   (IOPORT_REGISTER(0x1A58)) 					// I2C Pin Data Set Register [1:0] - unfortunately not in offical TI documentation!
	#define ICPDCLR         			   (IOPORT_REGISTER(0x1A5C)) 					// I2C Pin Data Clear Register [1:0] - unfortunately not in offical TI documentation!
	#define ICPDRV          			   (IOPORT_REGISTER(0x1A60)) 					// I2C Pin Driver Mode Register [1:0] - unfortunately not in offical TI documentation!
	#define ICPPDIS         			   (IOPORT_REGISTER(0x1A64)) 					// I2C Pin Pull Disable Register [1:0] - unfortunately not in offical TI documentation!
	#define ICPPSEL         			   (IOPORT_REGISTER(0x1A68)) 					// I2C Pin Pull Select Register [1:0] - unfortunately not in offical TI documentation!
	#define ICPSRS          			   (IOPORT_REGISTER(0x1A6C)) 					// I2C Pin Slew Rate Register [1:0] - unfortunately not in offical TI documentation!
	
	// I2S Registers ------------------------------------------------
	#define I2S0SCTRL					   (IOPORT_REGISTER(0x2800))					// I2S 0 Serializer Control Register
	#define I2S0SRATE					   (IOPORT_REGISTER(0x2804)) 					// I2S 0 Sample Rate Generator Register
	#define I2S0TXLT0					   (IOPORT_REGISTER(0x2808)) 					// I2S 0 Transmit Left Data 0 Register (lower part)
	#define I2S0TXLT1					   (IOPORT_REGISTER(0x2809)) 					// I2S 0 Transmit Left Data 1 Register (upper part)
	#define I2S0TXRT0					   (IOPORT_REGISTER(0x280C)) 					// I2S 0 Transmit Right Data 0 Register (lower part)
	#define I2S0TXRT1					   (IOPORT_REGISTER(0x280D)) 					// I2S 0 Transmit Right Data 1 Register (upper part)
	#define I2S0INTFL					   (IOPORT_REGISTER(0x2810))  					// I2S 0 Interrupt Flag Register
	#define I2S0INTMASK					   (IOPORT_REGISTER(0x2814))  					// I2S 0 Interrupt Mask Register
	#define I2S0RXLT0					   (IOPORT_REGISTER(0x2828))  					// I2S 0 Receive Left Data 0 Register (lower part)
	#define I2S0RXLT1					   (IOPORT_REGISTER(0x2829))  					// I2S 0 Receive Left Data 1 Register (upper part)
	#define I2S0RXRT0					   (IOPORT_REGISTER(0x282C))					// I2S 0 Receive Right Data 0 Register (lower part)  
	#define I2S0RXRT1					   (IOPORT_REGISTER(0x282D))  					// I2S 0 Receive Rigth Data 1 Register (upper part)
	
	#define I2S1SCTRL					   (IOPORT_REGISTER(0x2900))					// I2S 1 Serializer Control Register
	#define I2S1SRATE					   (IOPORT_REGISTER(0x2904)) 					// I2S 1 Sample Rate Generator Register
	#define I2S1TXLT0					   (IOPORT_REGISTER(0x2908)) 					// I2S 1 Transmit Left Data 0 Register (lower part)
	#define I2S1TXLT1					   (IOPORT_REGISTER(0x2909)) 					// I2S 1 Transmit Left Data 1 Register (upper part)
	#define I2S1TXRT0					   (IOPORT_REGISTER(0x290C)) 					// I2S 1 Transmit Right Data 0 Register (lower part)
	#define I2S1TXRT1					   (IOPORT_REGISTER(0x290D)) 					// I2S 1 Transmit Right Data 1 Register (upper part)
	#define I2S1INTFL					   (IOPORT_REGISTER(0x2910))  					// I2S 1 Interrupt Flag Register
	#define I2S1INTMASK					   (IOPORT_REGISTER(0x2914))  					// I2S 1 Interrupt Mask Register
	#define I2S1RXLT0					   (IOPORT_REGISTER(0x2928))  					// I2S 1 Receive Left Data 0 Register (lower part)
	#define I2S1RXLT1					   (IOPORT_REGISTER(0x2929))  					// I2S 1 Receive Left Data 1 Register (upper part)
	#define I2S1RXRT0					   (IOPORT_REGISTER(0x292C))					// I2S 1 Receive Right Data 0 Register (lower part)  
	#define I2S1RXRT1					   (IOPORT_REGISTER(0x292D))  					// I2S 1 Receive Rigth Data 1 Register (upper part)
	
	#define I2S2SCTRL					   (IOPORT_REGISTER(0x2A00))					// I2S 2 Serializer Control Register
	#define I2S2SRATE					   (IOPORT_REGISTER(0x2A04)) 					// I2S 2 Sample Rate Generator Register	
	#define I2S2TXLT0					   (IOPORT_REGISTER(0x2A08)) 					// I2S 2 Transmit Left Data 0 Register (lower part)
	#define I2S2TXLT1					   (IOPORT_REGISTER(0x2A09)) 					// I2S 2 Transmit Left Data 1 Register (upper part)
	#define I2S2TXRT0					   (IOPORT_REGISTER(0x2A0C)) 					// I2S 2 Transmit Right Data 0 Register (lower part)
	#define I2S2TXRT1					   (IOPORT_REGISTER(0x2A0D)) 					// I2S 2 Transmit Right Data 1 Register (upper part)
	#define I2S2INTFL					   (IOPORT_REGISTER(0x2A10))  					// I2S 2 Interrupt Flag Register
	#define I2S2INTMASK					   (IOPORT_REGISTER(0x2A14))  					// I2S 2 Interrupt Mask Register
	#define I2S2RXLT0					   (IOPORT_REGISTER(0x2A28))  					// I2S 2 Receive Left Data 0 Register (lower part)
	#define I2S2RXLT1					   (IOPORT_REGISTER(0x2A29))  					// I2S 2 Receive Left Data 1 Register (upper part)
	#define I2S2RXRT0					   (IOPORT_REGISTER(0x2A2C))					// I2S 2 Receive Right Data 0 Register (lower part)  
	#define I2S2RXRT1					   (IOPORT_REGISTER(0x2A2D))  					// I2S 2 Receive Rigth Data 1 Register (upper part)

	#define I2S3SCTRL					   (IOPORT_REGISTER(0x2B00))					// I2S 3 Serializer Control Register
	#define I2S3SRATE					   (IOPORT_REGISTER(0x2B04)) 					// I2S 3 Sample Rate Generator Register
	#define I2S3TXLT0					   (IOPORT_REGISTER(0x2B08)) 					// I2S 3 Transmit Left Data 0 Register (lower part)
	#define I2S3TXLT1					   (IOPORT_REGISTER(0x2B09)) 					// I2S 3 Transmit Left Data 1 Register (upper part)
	#define I2S3TXRT0					   (IOPORT_REGISTER(0x2B0C)) 					// I2S 3 Transmit Right Data 0 Register (lower part)
	#define I2S3TXRT1					   (IOPORT_REGISTER(0x2B0D)) 					// I2S 3 Transmit Right Data 1 Register (upper part)
	#define I2S3INTFL					   (IOPORT_REGISTER(0x2B10))  					// I2S 3 Interrupt Flag Register
	#define I2S3INTMASK					   (IOPORT_REGISTER(0x2B14))  					// I2S 3 Interrupt Mask Register
	#define I2S3RXLT0					   (IOPORT_REGISTER(0x2B28))  					// I2S 3 Receive Left Data 0 Register (lower part)
	#define I2S3RXLT1					   (IOPORT_REGISTER(0x2B29))  					// I2S 3 Receive Left Data 1 Register (upper part)
	#define I2S3RXRT0					   (IOPORT_REGISTER(0x2B2C))					// I2S 3 Receive Right Data 0 Register (lower part)  
	#define I2S3RXRT1					   (IOPORT_REGISTER(0x2B2D))  					// I2S 3 Receive Rigth Data 1 Register (upper part)

	/* I2SxSCTRL */
	#define ENABLE							15
	#define MONO							12
	#define LOOPBACK						11
	#define FSPOL							10
	#define CLKPOL							9
	#define DATADLY							8
	#define PACK							7
	#define SIGN_EXT						6
	#define WDLNGTH							2											// Serializer Word Length
	#define WDLNGTH_8BIT					(0x0<<2)									// ... 8 Bits word
	#define WDLNGTH_10BIT					(0x1<<2)									// ... 10 Bits word	
	#define WDLNGTH_12BIT					(0x2<<2)									// ... 12 Bits word
	#define WDLNGTH_14BIT					(0x3<<2)									// ... 14 Bits word
	#define WDLNGTH_16BIT					(0x4<<2)									// ... 16 Bits word
	#define WDLNGTH_18BIT					(0x5<<2)									// ... 18 Bits word
	#define WDLNGTH_20BIT					(0x6<<2)									// ... 20 Bits word
	#define WDLNGTH_24BIT					(0x7<<2)									// ... 24 Bits word
	#define WDLNGTH_32BIT					(0x8<<2)									// ... 32 Bits word
	#define I2S_MODE						1
	#define MASTER_MODE						(1u<<1)
	#define SLAVE_MODE						(0u<<1)
	#define FRMT							0
	
	/* I2SxSRATE */
	#define FSDIV							3
	#define FSDIV_8							(0x0<<3)
	#define FSDIV_16						(0x1<<3)
	#define FSDIV_32						(0x2<<3)
	#define FSDIV_64						(0x3<<3)
	#define FSDIV_128						(0x4<<3)
	#define FSDIV_256						(0x5<<3)		
	#define CLKDIV							0
	#define CLKDIV_2						(0x0<<0)
	#define CLKDIV_4						(0x1<<0)
	#define CLKDIV_8						(0x2<<0)
	#define CLKDIV_16						(0x3<<0)
	#define CLKDIV_32						(0x4<<0)
	#define CLKDIV_64						(0x5<<0)
	#define CLKDIV_128						(0x6<<0)
	#define CLKDIV_256						(0x7<<0)			
	
	/* I2SxINTFL */
	#define XMITSTFL						5
	#define CMITMONFL						4
	#define RCVSTFL							3
	#define RCVMONFL						2
	#define FERRFL							1
	#define OUERRFL							0
	
	/* I2SxINTMASK */
	#define XMITST							5
	#define XMITMON							4
	#define RCVSTMON						3
	#define RCVMON							2
	#define FERR							1
	#define OUERR							0

	// SAR Registers ------------------------------------------------
	#define SARCTRL				           (IOPORT_REGISTER(0x7012))					// SAR A/D Control Register
	#define ADCSTRT							15
	#define CHSEL							12
	#define CH0								(0x0<<12)
	#define CH1								(0x1<<12)
	#define CH2								(0x2<<12)
	#define CH3								(0x3<<12)
	#define CH4								(0x4<<12)
	#define CH5								(0x5<<12)	
	#define MULTICH							11
	#define SNGLCONV						10		
	#define SARDATA				           (IOPORT_REGISTER(0x7014))					// SAR A/D Data Register
	#define ADCBUSY							15
	#define CHAN							12
	#define SARCLKCTRL			           (IOPORT_REGISTER(0x7016))					// SAR A/D Clock Register
	#define SARPINCTRL			           (IOPORT_REGISTER(0x7018))					// SAR A/D Reference and Pin Control Register
	#define STATUSMASK						14
	#define PWRUPBIAS						13
	#define SARPWRUP						12
	#define REFBUFFEN						10
	#define REFLVSEL						9
	#define REFAVDDSEL						8
	#define TOUCHSCREENMODE					4
	#define AVDDMEAS						3
	#define GNDON							1
	#define HALF							0
	#define SARGPOCTRL			           (IOPORT_REGISTER(0x701A))					// SAR A/D GPO Control Register
	#define PENIRQ							9
	#define PENIRQEN						8
	#define GPO3EN							7
	#define GPO2EN							6
	#define GPO1EN							5
	#define GPO0EN							4
	#define GPO3							3
	#define GPO2							2
	#define GPO1							1
	#define GPO0							0
	
	// GPIO Registers -----------------------------------------------
	#define IODIR1				           (IOPORT_REGISTER(0x1C06))					// GPIO Direction Register 1 (GPIO0..15)
	#define IODIR2				           (IOPORT_REGISTER(0x1C07))					// GPIO Direction Register 2 (GPIO16..31)
	#define IOINDATA1			           (IOPORT_REGISTER(0x1C08))					// GPIO Data IN Register 1 (GPIO0..15)
	#define IOINDATA2			           (IOPORT_REGISTER(0x1C09))					// GPIO Data IN Register 2 (GPIO16..31)
	#define IODATAOUT1			           (IOPORT_REGISTER(0x1C0A))					// GPIO Data OUT Register 1 (GPIO0..15)
	#define IODATAOUT2			           (IOPORT_REGISTER(0x1C0B))					// GPIO Data OUT Register 2 (GPIO16..31)
	#define IOINTEDGE1			           (IOPORT_REGISTER(0x1C0C))					// GPIO Interrupt Edge Trigger Enable Register 1 (GPIO0..15)
	#define IOINTEDGE2			           (IOPORT_REGISTER(0x1C0D))					// GPIO Interrupt Edge Trigger Enable Register 2 (GPIO16..31)
	#define IOINTEN1			           (IOPORT_REGISTER(0x1C0E))					// GPIO Interrupt Enable Register 1 (GPIO0..15)
	#define IOINTEN2			           (IOPORT_REGISTER(0x1C0F))					// GPIO Interrupt Enable Register 2 (GPIO16.31)
	#define IOINTFLG1			           (IOPORT_REGISTER(0x1C10))					// GPIO Interrupt Flag Register 1 (GPIO0..15)
	#define IOINTFLG2			           (IOPORT_REGISTER(0x1C11))					// GPIO Interrupt Flag Register 2 (GPIO16..31)
	#define GPIO0							0
	#define GPIO1							1
	#define GPIO2							2
	#define GPIO3							3
	#define GPIO4							4
	#define GPIO5							5
	#define GPIO6							6
	#define GPIO7							7
	#define GPIO8							8
	#define GPIO9							9
	#define GPIO10							10
	#define GPIO11							11
	#define GPIO12							12
	#define GPIO13							13
	#define GPIO14							14
	#define GPIO15							15
	#define GPIO16							0
	#define GPIO17							1
	#define GPIO18							2
	#define GPIO19							3
	#define GPIO20							4
	#define GPIO27							11
	#define GPIO28							12
	#define GPIO29							13
	#define GPIO30							14
	#define GPIO31							15
	#define PDINHIBR1			           (IOPORT_REGISTER(0x1C17))					// Pull-Down Inhibit Register 1 (Serial Port0 and Serial Port1)
	#define S15PD							13
	#define S14PD							12
	#define S13PD							11
	#define S12PD							10
	#define S11PD							9
	#define S10PD							8
	#define S05PD							5
	#define S04PD							4
	#define S03PD							3
	#define S02PD							2
	#define S01PD							1
	#define S00PD							0
	#define PDINHIBR2			           (IOPORT_REGISTER(0x1C18))					// Pull-Down Inhibit Register 2 (Debug Interface)
	#define INT1PU							14
	#define INT0PU							13
	#define RESETPU							12
	#define EMU01PU							11
	#define TDIPU							10
	#define TMSPU							9
	#define TCKPU							8
	#define PDINHIBR3			           (IOPORT_REGISTER(0x1C19))					// Pull-Down Inhibit Register 3 (Parallel Port)
	#define PD15PD							15
	#define PD14PD							14
	#define PD13PD							13
	#define PD12PD							12
	#define PD11PD							11
	#define PD10PD							10
	#define PD9PD							9
	#define PD8PD							8
	#define PD7PD							7
	#define PD6PD							6
	#define PD5PD							5
	#define PD4PD							4
	#define PD3PD							3
	#define PD2PD							2		

	// USB Registers ------------------------------------------------
	// USB Control Registers
	#define USBSCR						   (IOPORT_REGISTER(0x1C32)) 					// USB System Control Register 
	#define USBPWDN							15
	#define USBSESSEND						14
	#define USBVBUSDET						13
	#define USBPLLEN						12
	#define USBDATPOL						6
	#define USBOSCBIASDIS					3
	#define USBOSCDIS						2
	#define USB_WORDACCESS					0x0
	#define USB_BYTEACCESS_HIGH				0x1
	#define USB_BYTEACCESS_LOW				0x2	
	#define REVID1						   (IOPORT_REGISTER(0x8000))					// USB Revision Identification Register 1
	#define REVID2						   (IOPORT_REGISTER(0x8001))					// USB Revision Identification Register 2
	#define CTRLR						   (IOPORT_REGISTER(0x8004))					// USB Control Register
	#define RNDIS							4
	#define UINT							3
	#define CLKFACK							1
	#define USB_RESET						0
	#define STATR						   (IOPORT_REGISTER(0x8008))					// USB Status Register
	#define DRVVBUS							0
	#define EMUR						   (IOPORT_REGISTER(0x800C))					// USB Emulation Register
	#define RT_SEL							2
	#define SOFT							1
	#define FREERUN							0
	#define MODE1						   (IOPORT_REGISTER(0x8010))					// USB Mode Register 1
	#define TX4_MODE						12
	#define TX3_MODE						8
	#define TX2_MODE						4
	#define TX1_MODE						0
	#define TRANSPARENT						0x0
	#define RNDIS_ON						0x1
	#define CDC_ON							0x2
	#define RNDIS_GENERIC					0x3
	#define MODE2						   (IOPORT_REGISTER(0x8011))					// USB Mode Register 2
	#define RX4_MODE						12
	#define RX3_MODE						8
	#define RX2_MODE						4
	#define RX1_MODE						0
	#define AUTOREQ						   (IOPORT_REGISTER(0x8014))					// USB Auto Request Register
	#define RX4_AUTOREQ						6
	#define RX3_AUTOREQ						4
	#define RX2_AUTOREQ						2
	#define RX1_AUTOREQ						0
	#define NO_AUTOREQ						0x0
	#define AUTOREQ_EXCEPT_EOP				0x1
	#define AUTOREQ_ALWAYS					0x3
	#define SRPFIXTIME1					   (IOPORT_REGISTER(0x8018))					// USB SRP Fix Time Register 1
	#define SRPFIXTIME2					   (IOPORT_REGISTER(0x8019))					// USB SRP Fix Time Register 2
	#define TEARDOWN1					   (IOPORT_REGISTER(0x801C))					// USB Teardown Register 1		
	#define TEARDOWN2					   (IOPORT_REGISTER(0x801D))					// USB Teardown Register 2
	#define INTSRCR1					   (IOPORT_REGISTER(0x8020))					// USB Interrupt Source Register 1
	#define RX4								12
	#define RX3								11
	#define RX2								10
	#define RX1								9
	#define TX4								4
	#define TX3								3
	#define TX2								2
	#define TX1								1
	#define RX1TX1							0
	#define INTSRCR2					   (IOPORT_REGISTER(0x8021))					// USB Interrupt Source Register 2
	#define VBUSERR							7
	#define SESSREQ							6
	#define DISCON							5
	#define CONN							4
	#define SOF								3
	#define RESET_BABBLE					2
	#define RESUME							1
	#define SUSPEND							0
	#define INTSETR1					   (IOPORT_REGISTER(0x8024))					// USB Interrupt Source Set Register 1
	#define INTSETR2					   (IOPORT_REGISTER(0x8025))					// USB Interrupt Source Set Register 2
	#define INTCLRR1					   (IOPORT_REGISTER(0x8028))					// USB Interrupt Source Clear Register 1
	#define INTCLRR2					   (IOPORT_REGISTER(0x8029))					// USB Interrupt Source Clear Register 2
	#define INTMSKR1					   (IOPORT_REGISTER(0x802C))					// USB Interrupt Mask Register 1
	#define INTMSKR2					   (IOPORT_REGISTER(0x802D))					// USB Interrupt Mask Register 2
	#define INTMSKSETR1					   (IOPORT_REGISTER(0x8030))					// USB Interrupt Mask Set Register 1
	#define INTMSKSETR2					   (IOPORT_REGISTER(0x8031))					// USB Interrupt Mask Set Register 2
	#define INTMSKCLRR1					   (IOPORT_REGISTER(0x8034))					// USB Interrupt Mask Clear Register 1
	#define INTMSKCLRR2					   (IOPORT_REGISTER(0x8035))					// USB Interrupt Mask Clear Register 2	
	#define INTMASKEDR1					   (IOPORT_REGISTER(0x8038))					// USB Interrupt Source Masked Register 1
	#define INTMASKEDR2					   (IOPORT_REGISTER(0x8039))					// USB Interrupt Source Masked Register 2
	#define EOIR						   (IOPORT_REGISTER(0x803C))					// USB End of Interrupt Register
	#define INTVECTR1					   (IOPORT_REGISTER(0x8040))					// USB Interrupt Vector Register 1
	#define INTVECTR2					   (IOPORT_REGISTER(0x8041))					// USB Interrupt Vector Register 2
	#define GREP1SZR1					   (IOPORT_REGISTER(0x8050))					// USB Generic RNDIS EP1Size Register 1
	#define GREP1SZR2					   (IOPORT_REGISTER(0x8051))					// USB Generic RNDIS EP1Size Register 2
	#define GREP2SZR1					   (IOPORT_REGISTER(0x8054))					// USB Generic RNDIS EP2Size Register 1
	#define GREP2SZR2					   (IOPORT_REGISTER(0x8055))					// USB Generic RNDIS EP2Size Register 2
	#define GREP3SZR1					   (IOPORT_REGISTER(0x8058))					// USB Generic RNDIS EP3Size Register 1
	#define GREP3SZR2					   (IOPORT_REGISTER(0x8059))					// USB Generic RNDIS EP3Size Register 2
	#define GREP4SZR1					   (IOPORT_REGISTER(0x805C))					// USB Generic RNDIS EP4Size Register 1
	#define GREP4SZR2					   (IOPORT_REGISTER(0x805D))					// USB Generic RNDIS EP4Size Register 2
	
	// Common USB Registers (8-Bit wide, see chapter 13.2.10, how to access high and low bytes of registers)
	#define FADDR_POWER					   (IOPORT_REGISTER(0x8401))					// USB Function Address Register or Power Managment Register
	#define ISOUPDATE						7
	#define SOFTCONN						6
	#define HSEN							5
	#define HSMODE							4
	#define USB_SOFTRESET					3
	#define USB_RESUME						2
	#define SUSPENDM						1
	#define ENSUSPM							0
	#define INTRTX						   (IOPORT_REGISTER(0x8402))					// USB Interrupt Register for Endpoint 0 and Transmit Endpoints 1 to 4
	#define EP4TX							4
	#define EP3TX							3
	#define EP2TX							2
	#define EP1TX							1
	#define EP0								0
	#define INTRRX						   (IOPORT_REGISTER(0x8405))					// USB Interrupt Register for Receive Endpoints 1 to 4
	#define EP4RX							4
	#define EP3RX							3
	#define EP2RX							2
	#define EP1RX							1
	#define INTRTXE						   (IOPORT_REGISTER(0x8406))					// USB Enable Register for INTRTX
	#define INTRRXE						   (IOPORT_REGISTER(0x8409))					// USB Enable Register for INTRRX
	#define INTRUSB_INTRUSBE			   (IOPORT_REGISTER(0x840A))					// USB Interrupt Register for Common USB Interrupts or Interrupt Enable Register
	#define FRAME						   (IOPORT_REGISTER(0x840D))					// USB Frame Number Register
	#define INDEX_TESTMODE				   (IOPORT_REGISTER(0x840E))					// USB Index Register for Selecting Endpoint Status and Control Register, Register to Enable USB 2.0 Test Modes
	#define FORCE_HOST						7
	#define FIFO_ACCESS						6
	#define FORCE_FS						5
	#define FORCE_HS						4
	#define TEST_PACKET						3
	#define TEST_K							2
	#define TEST_J							1
	#define TEST_SE0_NAK					0
	
	// Indexed USB Registers Endpoint 0 or 1..4 (8-Bit Index Registers, see chapter 13.3.32) 
	#define TXMAXP0						   (IOPORT_REGISTER(0x8411))					// USB Endpoint 0 Maximum Packet Size for Peripheral/Host Transmit 
	#define PERI_CSR					   (IOPORT_REGISTER(0x8412))					// USB Endpoint 0 Control Status Register for Peripheral Endpoint 0
	#define FLUSHFIFO						8
	#define SERV_SETUPEND					7
	#define SERV_RXPKTRDY					6
	#define SENDSTALL						5
	#define SETUPEND						4
	#define DATAEND							3
	#define SENTSTALL						2
	#define TXPKTRDY						1
	#define RXPKTRDY						0
	#define PERI_TXCSR0					   (IOPORT_REGISTER(0x8412))					// USB Endpoint 0 Control Status Register for Peripheral Tx 
	#define RXMAXP0						   (IOPORT_REGISTER(0x8415))					// USB Endpoint 0 Maximum Packet Size for Peripheral/Host Receive 
	#define PERI_RXCSR0					   (IOPORT_REGISTER(0x8416))					// USB Endpoint 0 Control Status Register for Peripheral Receive
	#define COUNT0						   (IOPORT_REGISTER(0x8419))					// USB Endpoint 0 Number of Received Byts in Endpoint 0 FIFO
	#define RXCOUNT0					   (IOPORT_REGISTER(0x8419))					// USB Endpoint 0 Number of Bytes in Host Receive Endpoint FIFO
	#define CONFIGDATA_INDC				   (IOPORT_REGISTER(0x841D))					// USB Endpoint 0 Returns details of core configuration (upper byte of 0x841D)
	#define MPRXE							7
	#define MPTXE							6
	#define BIGENDIAN						5
	#define HBRXE							4
	#define HBTXE							3
	#define DYNFIFO							2
	#define SOFTCONE						1
	#define UTMIDATAWIDTH					0

	#define TXMAXP1						   (IOPORT_REGISTER(0x8511))					// USB Endpoint 1 Maximum Packet Size for Peripheral/Host Transmit 
	#define PERI_TXCSR1					   (IOPORT_REGISTER(0x8512))					// USB Endpoint 1 Control Status Register for Peripheral Tx 
	#define RXMAXP1						   (IOPORT_REGISTER(0x8515))					// USB Endpoint 1 Maximum Packet Size for Peripheral/Host Receive 
	#define PERI_RXCSR1					   (IOPORT_REGISTER(0x8516))					// USB Endpoint 1 Control Status Register for Peripheral Receive 
	#define RXCOUNT1					   (IOPORT_REGISTER(0x8519))					// USB Endpoint 1 Number of Bytes in Host Receive Endpoint FIFO

	#define TXMAXP2						   (IOPORT_REGISTER(0x8521))					// USB Endpoint 2 Maximum Packet Size for Peripheral/Host Transmit 
	#define PERI_TXCSR2					   (IOPORT_REGISTER(0x8522))					// USB Endpoint 2 Control Status Register for Peripheral Tx 
	#define RXMAXP2						   (IOPORT_REGISTER(0x8525))					// USB Endpoint 2 Maximum Packet Size for Peripheral/Host Receive 
	#define PERI_RXCSR2					   (IOPORT_REGISTER(0x8526))					// USB Endpoint 2 Control Status Register for Peripheral Receive 
	#define RXCOUNT2					   (IOPORT_REGISTER(0x8529))					// USB Endpoint 2 Number of Bytes in Host Receive Endpoint FIFO
	
	#define TXMAXP3						   (IOPORT_REGISTER(0x8531))					// USB Endpoint 3 Maximum Packet Size for Peripheral/Host Transmit 
	#define PERI_TXCSR3					   (IOPORT_REGISTER(0x8532))					// USB Endpoint 3 Control Status Register for Peripheral Tx 
	#define RXMAXP3						   (IOPORT_REGISTER(0x8535))					// USB Endpoint 3 Maximum Packet Size for Peripheral/Host Receive 
	#define PERI_RXCSR3					   (IOPORT_REGISTER(0x8536))					// USB Endpoint 3 Control Status Register for Peripheral Receive 
	#define RXCOUNT3					   (IOPORT_REGISTER(0x8539))					// USB Endpoint 3 Number of Bytes in Host Receive Endpoint FIFO
	
	#define TXMAXP4						   (IOPORT_REGISTER(0x8541))					// USB Endpoint 4 Maximum Packet Size for Peripheral/Host Transmit 
	#define PERI_TXCSR4					   (IOPORT_REGISTER(0x8542))					// USB Endpoint 4 Control Status Register for Peripheral Tx 
	#define RXMAXP4						   (IOPORT_REGISTER(0x8545))					// USB Endpoint 4 Maximum Packet Size for Peripheral/Host Receive 
	#define PERI_RXCSR4					   (IOPORT_REGISTER(0x8546))					// USB Endpoint 4 Control Status Register for Peripheral Receive 
	#define RXCOUNT4					   (IOPORT_REGISTER(0x8549))					// USB Endpoint 4 Number of Bytes in Host Receive Endpoint FIFO

	/* PERI_RXCSRx */
	#define AUTOSET							15
	#define ISO_TX							14
	#define MODE							13
	#define DMAEN_TX						12
	#define FRCDATATOG						11
	#define DMAMODE							10
	#define CLRDATATOG_TX					6
	#define SENTSTALL_TX					5
	#define SENDSTALL_TX					4
	#define FLUSHFIF0_TX					3
	#define UNDERRUN						2
	#define FIFONOTEMPTY					1
	#define TXPKTRDY_TX						0

	/* PERI_RXCSRx */
	#define AUTOCLEAR						15
	#define ISO_RX							14
	#define DMAEN_RX						13
	#define DISNYET							12
	#define DMAOMODE_RX						11
	#define CLRDATATOG_RX					7
	#define SENTSTALL_RX					6
	#define SENDSTALL_RX					5
	#define FLUSHFIFO_RX					4
	#define DATAERROR						3
	#define OVERRUN							2
	#define FIFOFULL						1
	#define RXPKTRDY_RX						0

	// FIFO Registers
	#define FIFO0R1						   (IOPORT_REGISTER(0x8421))					// USB Transmit and Receive FIFO Register 1 for Endpoint 0
	#define FIFO0R2						   (IOPORT_REGISTER(0x8422))					// USB Transmit and Receive FIFO Register 2 for Endpoint 0
	#define FIFO1R1						   (IOPORT_REGISTER(0x8425))					// USB Transmit and Receive FIFO Register 1 for Endpoint 1
	#define FIFO1R2						   (IOPORT_REGISTER(0x8426))					// USB Transmit and Receive FIFO Register 2 for Endpoint 1
	#define FIFO2R1						   (IOPORT_REGISTER(0x8429))					// USB Transmit and Receive FIFO Register 1 for Endpoint 2
	#define FIFO2R2						   (IOPORT_REGISTER(0x842A))					// USB Transmit and Receive FIFO Register 2 for Endpoint 2
	#define FIFO3R1						   (IOPORT_REGISTER(0x842D))					// USB Transmit and Receive FIFO Register 1 for Endpoint 3
	#define FIFO3R2						   (IOPORT_REGISTER(0x842E))					// USB Transmit and Receive FIFO Register 2 for Endpoint 3
	#define FIFO4R1						   (IOPORT_REGISTER(0x8431))					// USB Transmit and Receive FIFO Register 1 for Endpoint 4
	#define FIFO4R2						   (IOPORT_REGISTER(0x8432))					// USB Transmit and Receive FIFO Register 2 for Endpoint 4
	
	// Dynamic FIFO Control Registers (8-Bit Index Registers, see chapter 13.3.32)
	//#define DEVCTL					   	   (IOPORT_REGISTER(0x8461))				// USB Device Control Register (address not in list)
	//#define BDEVICE							7
	//#define FSDEV								6
	//#define LSDEV								5
	//#define VBUS								3
	//#define BELOW_SESSION						(0x0<<3)
	//#define ABOVE_SESSION_AVALID				(0x1<<3)
	//#define BETWEEN_AVALID_VBUSVALID			(0x2<<3)
	//#define ABOVE_VBUSVALID					(0x3<<3)
	//#define HOSTMODE							2
	//#define SESSION							0
	#define TXFIFOSZ_RXFIFOSZ			   (IOPORT_REGISTER(0x8462))					// USB Transmit Endpoint FIFO Size, Receive Endpoint FIFO Size
	#define DPB								4
	#define TXFIFOADDR					   (IOPORT_REGISTER(0x8465))					// USB Transmit Endpoint FIFO Address
	#define RXFIFOADDR					   (IOPORT_REGISTER(0x8466))					// USB Receive Endpoint FIFO Address
	#define HWVERS						   (IOPORT_REGISTER(0x846D))					// USB Hardware Version Register
	
	// CPPI DMA Registers
	#define DMAREVID1					   (IOPORT_REGISTER(0x9000))					// USB CDMA Revision Identification Register 1
	#define DMAREVID2					   (IOPORT_REGISTER(0x9001))					// USB CDMA Revision Identification Register 2
	#define TDFDQ						   (IOPORT_REGISTER(0x9004))					// USB CDMA Teardown Free Description Queue Control Register
	#define DMAEMU						   (IOPORT_REGISTER(0x9008))					// USB CDMA Emulation Control Register
	#define CDMA_SOFT						1
	#define CDMA_FREE						0
	
	#define TXGCR10						   (IOPORT_REGISTER(0x9800))					// USB Transmit Channel 0 Global Configuration Register 1
	#define TXGCR20						   (IOPORT_REGISTER(0x9801))					// USB Transmit Channel 0 Global Configuration Register 2
	#define RXGCR10						   (IOPORT_REGISTER(0x9808))					// USB Receive Channel 0 Global Configuration Register 1
	#define RXGCR20						   (IOPORT_REGISTER(0x9809))					// USB Receive Channel 0 Global Configuration Register 1
	#define RXHPCR1A0					   (IOPORT_REGISTER(0x980C))					// USB Receive Channel 0 Host Packet Configuration Register 1A
	#define RXHPCR2A0					   (IOPORT_REGISTER(0x980D))					// USB Receive Channel 0 Host Packet Configuration Register 2A
	#define RXHPCR1B0					   (IOPORT_REGISTER(0x9810))					// USB Receive Channel 0 Host Packet Configuration Register 1B
	#define RXHPCR2B0					   (IOPORT_REGISTER(0x9811))					// USB Receive Channel 0 Host Packet Configuration Register 2B
	
	#define TXGCR11						   (IOPORT_REGISTER(0x9820))					// USB Transmit Channel 1 Global Configuration Register 1
	#define TXGCR21						   (IOPORT_REGISTER(0x9821))					// USB Transmit Channel 1 Global Configuration Register 2
	#define RXGCR11						   (IOPORT_REGISTER(0x9828))					// USB Receive Channel 1 Global Configuration Register 1
	#define RXGCR21						   (IOPORT_REGISTER(0x9829))					// USB Receive Channel 1 Global Configuration Register 1
	#define RXHPCR1A1					   (IOPORT_REGISTER(0x982C))					// USB Receive Channel 1 Host Packet Configuration Register 1A
	#define RXHPCR2A1					   (IOPORT_REGISTER(0x982D))					// USB Receive Channel 1 Host Packet Configuration Register 2A
	#define RXHPCR1B1					   (IOPORT_REGISTER(0x9830))					// USB Receive Channel 1 Host Packet Configuration Register 1B
	#define RXHPCR2B1					   (IOPORT_REGISTER(0x9831))					// USB Receive Channel 1 Host Packet Configuration Register 2B
	
	#define TXGCR12						   (IOPORT_REGISTER(0x9840))					// USB Transmit Channel 2 Global Configuration Register 1
	#define TXGCR22						   (IOPORT_REGISTER(0x9841))					// USB Transmit Channel 2 Global Configuration Register 2
	#define RXGCR12						   (IOPORT_REGISTER(0x9848))					// USB Receive Channel 2 Global Configuration Register 1
	#define RXGCR22						   (IOPORT_REGISTER(0x9848))					// USB Receive Channel 2 Global Configuration Register 1
	#define RXHPCR1A2					   (IOPORT_REGISTER(0x984C))					// USB Receive Channel 2 Host Packet Configuration Register 1A
	#define RXHPCR2A2					   (IOPORT_REGISTER(0x984D))					// USB Receive Channel 2 Host Packet Configuration Register 2A
	#define RXHPCR1B2					   (IOPORT_REGISTER(0x9850))					// USB Receive Channel 2 Host Packet Configuration Register 1B
	#define RXHPCR2B2					   (IOPORT_REGISTER(0x9851))					// USB Receive Channel 2 Host Packet Configuration Register 2B
	
	#define TXGCR13						   (IOPORT_REGISTER(0x9860))					// USB Transmit Channel 3 Global Configuration Register 1
	#define TXGCR23						   (IOPORT_REGISTER(0x9861))					// USB Transmit Channel 3 Global Configuration Register 2
	#define RXGCR13						   (IOPORT_REGISTER(0x9868))					// USB Receive Channel 3 Global Configuration Register 1
	#define RXGCR23						   (IOPORT_REGISTER(0x9869))					// USB Receive Channel 3 Global Configuration Register 1
	#define RXHPCR1A3					   (IOPORT_REGISTER(0x986C))					// USB Receive Channel 3 Host Packet Configuration Register 1A
	#define RXHPCR2A3					   (IOPORT_REGISTER(0x986D))					// USB Receive Channel 3 Host Packet Configuration Register 2A
	#define RXHPCR1B3					   (IOPORT_REGISTER(0x9870))					// USB Receive Channel 3 Host Packet Configuration Register 1B
	#define RXHPCR2B3					   (IOPORT_REGISTER(0x9871))					// USB Receive Channel 3 Host Packet Configuration Register 2B
	
	/* TXGCR2x */
	#define TX_ENABLE						15
	#define TX_TEARDOWN						14
	
	/* RXGCR2x */
	#define RX_ENABLE						15
	#define RX_TEARDOWN						14
	#define RX_ERROR_HANDLING				8
	
	#define DMA_SCHED_CTRL1				   (IOPORT_REGISTER(0xA000))					// USB CDMA Scheduler Control Register 1
	#define DMA_SCHED_CTRL2				   (IOPORT_REGISTER(0xA001))					// USB CDMA Scheduler Control Register 2
	#define CDMA_ENABLE						15
	#define ENTRYLSW(value)				   (IOPORT_REGISTER(0xA800+4*value))			// USB CDMA Scheduler Table Word Register LSW [0..63]
	#define ENTRY1_RXTX						15
	#define ENTRY0_RXTX						7
	#define ENTRYMSW(value)				   (IOPORT_REGISTER(0xA801+4*value))			// USB CDMA Scheduler Table Word Register MS [0..63]
	#define ENTRY3_RXTX						15
	#define ENTRY2_RXTX						7

	// Queue Manage (QMGR) Registers
	#define QMGRREVID1					   (IOPORT_REGISTER(0xC000))					// USB CDMA Scheduler Control Register 1
	#define QMGRREVID2					   (IOPORT_REGISTER(0xC001))					// USB CDMA Scheduler Control Register 1
	#define DIVERSION1				  	   (IOPORT_REGISTER(0xC008))					// USB CDMA Scheduler Control Register 1
	#define DIVERSION2				  	   (IOPORT_REGISTER(0xC009))					// USB CDMA Scheduler Control Register 1
	#define HEAD_TAIL						15
	#define FDBSC0						   (IOPORT_REGISTER(0xC020))					// USB CDMA Scheduler Control Register 1
	#define FDBSC1						   (IOPORT_REGISTER(0xC021))					// USB CDMA Scheduler Control Register 1	
	#define FDBSC2						   (IOPORT_REGISTER(0xC024))					// USB CDMA Scheduler Control Register 1	
	#define FDBSC3						   (IOPORT_REGISTER(0xC025))					// USB CDMA Scheduler Control Register 1	
	#define FDBSC4						   (IOPORT_REGISTER(0xC028))					// USB CDMA Scheduler Control Register 1	
	#define FDBSC5						   (IOPORT_REGISTER(0xC029))					// USB CDMA Scheduler Control Register 1	
	#define FDBSC6						   (IOPORT_REGISTER(0xC02C))					// USB CDMA Scheduler Control Register 1	
	#define FDBSC7						   (IOPORT_REGISTER(0xC02D))					// USB CDMA Scheduler Control Register 1
	#define LRAM0BASE1					   (IOPORT_REGISTER(0xC080))					// USB CDMA Scheduler Control Register 1	
	#define LRAM0BASE2					   (IOPORT_REGISTER(0xC081))					// USB CDMA Scheduler Control Register 1	
	#define LRAM0SIZE					   (IOPORT_REGISTER(0xC084))					// USB CDMA Scheduler Control Register 1	
	#define LRAM1BASE1					   (IOPORT_REGISTER(0xC088))					// USB CDMA Scheduler Control Register 1	
	#define LRAM1BASE2					   (IOPORT_REGISTER(0xC089))					// USB CDMA Scheduler Control Register 1	
	#define PEND0						   (IOPORT_REGISTER(0xC090))					// USB Queue Manager Pending 0
	#define PEND1						   (IOPORT_REGISTER(0xC091))					// USB Queue Manager Pending 1		
	#define PEND2						   (IOPORT_REGISTER(0xC094))					// USB Queue Manager Pending 2		
	#define PEND3						   (IOPORT_REGISTER(0xC095))					// USB Queue Manager Pending 3		
	#define PEND4						   (IOPORT_REGISTER(0xC098))					// USB Queue Manager Pending 4		
	#define PEND5						   (IOPORT_REGISTER(0xC099))					// USB Queue Manager Pending 5		
	#define QMEMRBASE1(value)			   (IOPORT_REGISTER(0xD000+(16*value)))			// USB Queue Manager Memory Region Base Address Register 1 [0..15]	
	#define QMEMRBASE2(value)			   (IOPORT_REGISTER(0xD001+(16*value)))			// USB Queue Manager Memory Region Base Address Register 2 [0..15]			
	#define QMEMRCTRL1(value)			   (IOPORT_REGISTER(0xD004+(16*value)))			// USB Queue Manager Memory Region Control Address Register 1 [0..15]
	#define DESC_SIZE						8
	#define DESC_SIZE_32					(0x0<<8)
	#define DESC_SIZE_64					(0x1<<8)
	#define DESC_SIZE_128					(0x2<<8)
	#define DESC_SIZE_256					(0x3<<8)
	#define DESC_SIZE_512					(0x4<<8)
	#define DESC_SIZE_1024					(0x5<<8)
	#define DESC_SIZE_2048					(0x6<<8)
	#define DESC_SIZE_4096					(0x7<<8)
	#define DESC_SIZE_8192					(0x8<<8)
	#define REG_SIZE						0
	#define REG_SIZE_32						(0x0<<8)
	#define REG_SIZE_64						(0x1<<8)
	#define REG_SIZE_128					(0x2<<8)
	#define REG_SIZE_256					(0x3<<8)
	#define REG_SIZE_512					(0x4<<8)
	#define REG_SIZE_1024					(0x5<<8)
	#define REG_SIZE_2048					(0x6<<8)
	#define REG_SIZE_4096					(0x7<<8)
	#define QMEMRCTRL2(value)			   (IOPORT_REGISTER(0xE005+(16*value)))			// USB Queue Manager Memory Region Control Address Register 2 [0..15]
	#define CTRL1D(value)				   (IOPORT_REGISTER(0xE00C+(16*value)))			// USB Queue Manager Memory Control Register 1 D [0..63]					
	#define CTRL2D(value)				   (IOPORT_REGISTER(0xE00D+(16*value)))			// USB Queue Manager Memory Control Register 2 D [0..63]
	#define QSTATA(value)				   (IOPORT_REGISTER(0xE800+(16*value)))			// USB Queue Manager Memory Status Register A [0..63]
	#define QSTAT1B(value)				   (IOPORT_REGISTER(0xE804+(16*value)))			// USB Queue Manager Memory Status Register 1 B [0..63]
	#define QSTAT2B(value)				   (IOPORT_REGISTER(0xE805+(16*value)))			// USB Queue Manager Memory Status Register 2 B [0..63]
	#define QSTATC(value)				   (IOPORT_REGISTER(0xE808+(16*value)))			// USB Queue Manager Memory Status Register C [0..63]

	// LCD Control Registers ----------------------------------------
	#define LCDREVMIN					   (IOPORT_REGISTER(0x2E00))					// LCD Minor Revision Register
	#define LCDREVMAJ					   (IOPORT_REGISTER(0x2E01))					// LCD Major Revision Register
	#define LCDCR						   (IOPORT_REGISTER(0x2E04))					// LCD Control Register
	#define MODESEL							0
	#define LCDSR						   (IOPORT_REGISTER(0x2E08))					// LCD Status Register
	#define EOF1							9
	#define EOF0							8
	#define DONE							0
	#define LCDLIDDCR					   (IOPORT_REGISTER(0x2E0C))					// LCD LIDD Control Register
	#define DONE_INT_EN						10
	#define DMA_CS0_CS1						9
	#define LIDD_DMA_EN						8
	#define CS1_E1_POL						7
	#define CS0_E0_POL						6
	#define WS_DIR_POL						5
	#define RS_EN_POL						4
	#define RSPOL							3
	#define LIDD_MODE_SEL					0
	#define MPU6800_SYNC_MODE				(0x0<<0)
	#define MPU6800_ASYMC_MODE				(0x1<<0)
	#define MPU80_SYNC_MODE					(0x2<<0)
	#define MPU80_ASYNC_MODE				(0x3<<0)
	#define HITACHI_ASYNC_MODE				(0x4<<0)
	#define LCDLIDDCS0CONFIG0			   (IOPORT_REGISTER(0x2E10))					// LCD LIDD CS0 Configuration Register 0
	#define LCDLIDDCS0CONFIG1			   (IOPORT_REGISTER(0x2E11))					// LCD LIDD CS0 Configuration Register 1
	#define LCDLIDDCS0ADDR				   (IOPORT_REGISTER(0x2E14))					// LCD LIDD CS0 Address Read/write Register
	#define LCDLIDDCS0DATA				   (IOPORT_REGISTER(0x2E18))					// LCD LIDD CS0 Data Read/write Register
	#define LCDLIDDCS1CONFIG0			   (IOPORT_REGISTER(0x2E1C))					// LCD LIDD CS0 Configuration Register 0
	#define LCDLIDDCS1CONFIG1			   (IOPORT_REGISTER(0x2E1D))					// LCD LIDD CS0 Configuration Register 1
	#define LCDLIDDCS1ADDR				   (IOPORT_REGISTER(0x2E20))					// LCD LIDD CS0 Address Read/write Register
	#define LCDLIDDCS1DATA				   (IOPORT_REGISTER(0x2E24))					// LCD LIDD CS0 Data Read/write Register
	#define LCDDMACR			   		   (IOPORT_REGISTER(0x2E40))					// LCD DMA Control Register
	#define BURST_SIZE						4
	#define BURST_SIZE_1					(0x0<<4)
	#define BURST_SIZE_2					(0x1<<4)
	#define BURST_SIZE_4					(0x2<<4)
	#define BURST_SIZE_8					(0x3<<4)
	#define BURST_SIZE_16					(0x4<<4)
	#define EOF_INTEN						2
	#define LCD_BIGENDIAN					1
	#define FRAME_MODE						0
	#define LCDDMAFB0BAR0				   (IOPORT_REGISTER(0x2E44))					// LCD DMA Frame Buffer 0 Base Address Register 0
	#define LCDDMAFB0BAR1				   (IOPORT_REGISTER(0x2E45))					// LCD DMA Frame Buffer 0 Base Address Register 0
	#define LCDDMAFB0CAR0				   (IOPORT_REGISTER(0x2E48))					// LCD DMA Frame Buffer 0 Ceiling Address Register 0
	#define LCDDMAFB0CAR1				   (IOPORT_REGISTER(0x2E49))					// LCD DMA Frame Buffer 0 Ceiling Address Register 0
	#define LCDDMAFB1BAR0				   (IOPORT_REGISTER(0x2E4C))					// LCD DMA Frame Buffer 1 Base Address Register 0
	#define LCDDMAFB1BAR1				   (IOPORT_REGISTER(0x2E4D))					// LCD DMA Frame Buffer 1 Base Address Register 0
	#define LCDDMAFB1CAR0				   (IOPORT_REGISTER(0x2E50))					// LCD DMA Frame Buffer 1 Ceiling Address Register 0
	#define LCDDMAFB1CAR1				   (IOPORT_REGISTER(0x2E51))					// LCD DMA Frame Buffer 1 Ceiling Address Register 0

	// PROTOTYPES ---------------------------------------------------
	void init_ebsr(unsigned int ppmode, unsigned int sp1mode, unsigned int sp0mode);
	void sw_reset_peripheral(unsigned int peripheral);

	// FUNCTIONS ----------------------------------------------------
	
#endif 

