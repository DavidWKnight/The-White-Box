EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Main Board
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 8925 650  1275 950 
U 586C91C8
F0 "Power" 60
F1 "Power.sch" 60
$EndSheet
Wire Wire Line
	3300 1050 3250 1050
Wire Wire Line
	3250 1350 3300 1350
Wire Wire Line
	3300 1150 3250 1150
Connection ~ 3250 1150
$Comp
L GNDD #PWR01
U 1 1 586E05CE
P 3250 1400
F 0 "#PWR01" H 3250 1150 50  0001 C CNN
F 1 "GNDD" H 3250 1250 50  0000 C CNN
F 2 "" H 3250 1400 50  0000 C CNN
F 3 "" H 3250 1400 50  0000 C CNN
	1    3250 1400
	1    0    0    -1  
$EndComp
Connection ~ 3250 1350
NoConn ~ 3300 1700
NoConn ~ 3300 1800
NoConn ~ 3300 1900
NoConn ~ 3300 2000
$Comp
L Crystal Y1
U 1 1 586E0B81
P 3100 2400
F 0 "Y1" H 3100 2550 50  0000 C CNN
F 1 "32.768k" H 3100 2250 50  0000 C CNN
F 2 "" H 3100 2400 50  0000 C CNN
F 3 "" H 3100 2400 50  0000 C CNN
	1    3100 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	2900 2600 3300 2600
Wire Wire Line
	3100 2600 3100 2550
Wire Wire Line
	3100 2250 3100 2200
Wire Wire Line
	2900 2200 3300 2200
$Comp
L C C3
U 1 1 586E0D2C
P 2750 2200
F 0 "C3" V 2600 2150 50  0000 L CNN
F 1 "33pF" V 2700 1950 50  0000 L CNN
F 2 "" H 2788 2050 50  0000 C CNN
F 3 "" H 2750 2200 50  0000 C CNN
	1    2750 2200
	0    1    1    0   
$EndComp
$Comp
L C C4
U 1 1 586E0D80
P 2750 2600
F 0 "C4" V 2600 2550 50  0000 L CNN
F 1 "33pF" V 2700 2350 50  0000 L CNN
F 2 "" H 2788 2450 50  0000 C CNN
F 3 "" H 2750 2600 50  0000 C CNN
	1    2750 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	2450 2750 3300 2750
Wire Wire Line
	2450 2200 2450 2750
Wire Wire Line
	2450 2200 2600 2200
Wire Wire Line
	2450 2600 2600 2600
Connection ~ 2450 2600
Connection ~ 3100 2600
Connection ~ 3100 2200
NoConn ~ 3300 3100
NoConn ~ 3300 3200
NoConn ~ 3300 3300
$Comp
L CONN_02X07 P1
U 1 1 586E133A
P 1300 3200
F 0 "P1" H 1300 3600 50  0000 C CNN
F 1 "CONN_02X07" V 1300 3200 50  0000 C CNN
F 2 "" H 1300 2000 50  0000 C CNN
F 3 "" H 1300 2000 50  0000 C CNN
	1    1300 3200
	1    0    0    -1  
$EndComp
Text Label 1550 2900 0    60   ~ 0
DSP_nTRST
Text Label 1550 3000 0    60   ~ 0
DSP_TDIS
Text Label 1550 3100 0    60   ~ 0
DSP_KEY
$Comp
L GNDD #PWR02
U 1 1 586E13C8
P 2100 3450
F 0 "#PWR02" H 2100 3200 50  0001 C CNN
F 1 "GNDD" H 2100 3300 50  0000 C CNN
F 2 "" H 2100 3450 50  0000 C CNN
F 3 "" H 2100 3450 50  0000 C CNN
	1    2100 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 3200 2100 3200
Wire Wire Line
	1550 3300 2100 3300
Wire Wire Line
	2100 3400 1550 3400
Text Label 1550 3500 0    60   ~ 0
DSP_EMU1
Wire Wire Line
	2100 3200 2100 3450
Connection ~ 2100 3300
Connection ~ 2100 3400
Text Label 1050 2900 2    60   ~ 0
DSP_TMS
Text Label 1050 3000 2    60   ~ 0
DSP_TDI
Text Label 1050 3100 2    60   ~ 0
DSP_VTRef
Text Label 1050 3200 2    60   ~ 0
DSP_TDO
Text Label 1050 3300 2    60   ~ 0
DSP_RTCK
Text Label 1050 3400 2    60   ~ 0
DSP_TCK
Text Label 1050 3500 2    60   ~ 0
DSP_EMU0
Text Label 3300 3600 2    60   ~ 0
DSP_nTRST
Text Label 3300 3700 2    60   ~ 0
DSP_TMS
Text Label 3300 3800 2    60   ~ 0
DSP_TDI
Text Label 3300 3900 2    60   ~ 0
DSP_TDO
Text Label 3300 4000 2    60   ~ 0
DSP_TCK
Text Label 3300 4100 2    60   ~ 0
DSP_EMU0
Text Label 3300 4200 2    60   ~ 0
DSP_EMU1
Wire Wire Line
	1750 4700 3300 4700
NoConn ~ 3300 4900
NoConn ~ 3300 4800
$Comp
L C C2
U 1 1 586E1BE8
P 2000 4900
F 0 "C2" H 2025 5000 50  0000 L CNN
F 1 ".1uF" H 2025 4800 50  0000 L CNN
F 2 "" H 2038 4750 50  0000 C CNN
F 3 "" H 2000 4900 50  0000 C CNN
	1    2000 4900
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 586E1C63
P 1750 4900
F 0 "C1" H 1775 5000 50  0000 L CNN
F 1 "1uF" H 1775 4800 50  0000 L CNN
F 2 "" H 1788 4750 50  0000 C CNN
F 3 "" H 1750 4900 50  0000 C CNN
	1    1750 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 4700 2000 4750
Wire Wire Line
	1750 4550 1750 4750
$Comp
L GNDD #PWR03
U 1 1 586E1D1E
P 2000 5150
F 0 "#PWR03" H 2000 4900 50  0001 C CNN
F 1 "GNDD" H 2000 5000 50  0000 C CNN
F 2 "" H 2000 5150 50  0000 C CNN
F 3 "" H 2000 5150 50  0000 C CNN
	1    2000 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 5050 2000 5150
Wire Wire Line
	2000 5100 1750 5100
Wire Wire Line
	1750 5100 1750 5050
Connection ~ 2000 5100
Connection ~ 2000 4700
Connection ~ 1750 4700
NoConn ~ 3300 5200
Text Label 3300 5500 2    60   ~ 0
DSP_RDY
Text Label 3300 5300 2    60   ~ 0
~DSP_FX_DATA_SEND
$Comp
L R R1
U 1 1 586E26C3
P 1050 4950
F 0 "R1" V 1130 4950 50  0000 C CNN
F 1 "47k" V 1050 4950 50  0000 C CNN
F 2 "" V 980 4950 50  0000 C CNN
F 3 "" H 1050 4950 50  0000 C CNN
	1    1050 4950
	1    0    0    -1  
$EndComp
$Comp
L SPST SW1
U 1 1 586E274A
P 1050 5700
F 0 "SW1" H 1050 5800 50  0000 C CNN
F 1 "SPST" H 1050 5600 50  0000 C CNN
F 2 "" H 1050 5700 50  0000 C CNN
F 3 "" H 1050 5700 50  0000 C CNN
	1    1050 5700
	0    1    1    0   
$EndComp
Wire Wire Line
	1050 5100 1050 5200
$Comp
L +3.3V #PWR04
U 1 1 586E2843
P 1050 4700
F 0 "#PWR04" H 1050 4550 50  0001 C CNN
F 1 "+3.3V" H 1050 4840 50  0000 C CNN
F 2 "" H 1050 4700 50  0000 C CNN
F 3 "" H 1050 4700 50  0000 C CNN
	1    1050 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 4800 1050 4700
Wire Wire Line
	1050 5150 1150 5150
Connection ~ 1050 5150
$Comp
L GNDD #PWR05
U 1 1 586E28ED
P 1050 6250
F 0 "#PWR05" H 1050 6000 50  0001 C CNN
F 1 "GNDD" H 1050 6100 50  0000 C CNN
F 2 "" H 1050 6250 50  0000 C CNN
F 3 "" H 1050 6250 50  0000 C CNN
	1    1050 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 6250 1050 6200
Text Label 1150 5150 0    60   ~ 0
DSP_Reset
Text Label 3300 5400 2    60   ~ 0
DSP_Reset
$Comp
L GNDD #PWR06
U 1 1 586E2E28
P 5850 1550
F 0 "#PWR06" H 5850 1300 50  0001 C CNN
F 1 "GNDD" H 5850 1400 50  0000 C CNN
F 2 "" H 5850 1550 50  0000 C CNN
F 3 "" H 5850 1550 50  0000 C CNN
	1    5850 1550
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 586E2E6B
P 6000 1400
F 0 "R2" V 6080 1400 50  0000 C CNN
F 1 "R" V 6000 1400 50  0000 C CNN
F 2 "" V 5930 1400 50  0000 C CNN
F 3 "" H 6000 1400 50  0000 C CNN
	1    6000 1400
	0    1    1    0   
$EndComp
$Comp
L GNDD #PWR07
U 1 1 586E2ED0
P 6200 1450
F 0 "#PWR07" H 6200 1200 50  0001 C CNN
F 1 "GNDD" H 6200 1300 50  0000 C CNN
F 2 "" H 6200 1450 50  0000 C CNN
F 3 "" H 6200 1450 50  0000 C CNN
	1    6200 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 1500 5850 1500
Wire Wire Line
	5850 1500 5850 1550
Wire Wire Line
	5750 1400 5850 1400
Wire Wire Line
	6150 1400 6200 1400
Wire Wire Line
	6200 1250 6200 1450
Wire Wire Line
	5750 1050 5800 1050
Wire Wire Line
	5800 1050 5800 1250
Wire Wire Line
	5750 1250 6200 1250
Wire Wire Line
	5750 1150 5800 1150
Connection ~ 5800 1150
Connection ~ 6200 1400
Connection ~ 5800 1250
$Comp
L TMS320C5535 U1
U 1 1 586E057F
P 4500 2450
F 0 "U1" H 3550 4050 60  0000 C CNN
F 1 "TMS320C5535" H 5300 4050 60  0000 C CNN
F 2 "" H 8600 3850 60  0000 C CNN
F 3 "" H 8600 3850 60  0000 C CNN
	1    4500 2450
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X17 P2
U 1 1 586E3520
P 8250 2850
F 0 "P2" H 8250 3750 50  0000 C CNN
F 1 "CONN_02X17" V 8250 2850 50  0000 C CNN
F 2 "" H 8250 1750 50  0000 C CNN
F 3 "" H 8250 1750 50  0000 C CNN
	1    8250 2850
	1    0    0    -1  
$EndComp
Text Label 8000 2050 2    60   ~ 0
FX_Data0
Text Label 8000 2150 2    60   ~ 0
FX_Data1
Text Label 8000 2250 2    60   ~ 0
FX_Data2
Text Label 8000 2350 2    60   ~ 0
FX_Data3
Text Label 8000 2450 2    60   ~ 0
FX_Data4
Text Label 8000 2550 2    60   ~ 0
FX_Data5
Text Label 8000 2650 2    60   ~ 0
FX_Data6
Text Label 8000 2750 2    60   ~ 0
FX_Data7
Text Label 8500 2050 0    60   ~ 0
FX_Pot_Sel0
Text Label 8500 2150 0    60   ~ 0
FX_Pot_Sel1
Text Label 8500 2250 0    60   ~ 0
FX_effect_Sel0
Text Label 8500 2350 0    60   ~ 0
FX_effect_Sel1
Text Label 8500 2450 0    60   ~ 0
FX_effect_Sel2
Text Label 8500 2550 0    60   ~ 0
~DSP_FX_DATA_SEND
Text Label 8500 2650 0    60   ~ 0
DSP_RDY
Wire Wire Line
	8000 3550 7950 3550
Wire Wire Line
	7950 3550 7950 3650
Wire Wire Line
	7950 3650 8000 3650
Wire Wire Line
	8500 3550 8550 3550
Wire Wire Line
	8550 3550 8550 3650
Wire Wire Line
	8550 3650 8500 3650
$Comp
L +3.3V #PWR08
U 1 1 586E3F5F
P 7850 3550
F 0 "#PWR08" H 7850 3400 50  0001 C CNN
F 1 "+3.3V" H 7850 3690 50  0000 C CNN
F 2 "" H 7850 3550 50  0000 C CNN
F 3 "" H 7850 3550 50  0000 C CNN
	1    7850 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 3600 7850 3600
Wire Wire Line
	7850 3600 7850 3550
Connection ~ 7950 3600
$Comp
L GNDD #PWR09
U 1 1 586E3FE0
P 8650 3650
F 0 "#PWR09" H 8650 3400 50  0001 C CNN
F 1 "GNDD" H 8650 3500 50  0000 C CNN
F 2 "" H 8650 3650 50  0000 C CNN
F 3 "" H 8650 3650 50  0000 C CNN
	1    8650 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 3600 8650 3600
Wire Wire Line
	8650 3600 8650 3650
Connection ~ 8550 3600
Text Label 5750 1850 0    60   ~ 0
FX_Data0
Text Label 5750 1950 0    60   ~ 0
FX_Data1
Text Label 5750 2050 0    60   ~ 0
FX_Data2
Text Label 5750 2150 0    60   ~ 0
FX_Data3
Text Label 5750 2250 0    60   ~ 0
FX_Data4
Text Label 5750 2350 0    60   ~ 0
FX_Data5
Text Label 5750 2600 0    60   ~ 0
FX_Data6
Text Label 5750 2700 0    60   ~ 0
FX_Data7
Text Label 5750 3500 0    60   ~ 0
FX_Pot_Sel0
Text Label 5750 3600 0    60   ~ 0
FX_Pot_Sel1
Text Label 5750 2800 0    60   ~ 0
FX_effect_Sel0
Text Label 5750 2900 0    60   ~ 0
FX_effect_Sel1
Text Label 5750 3000 0    60   ~ 0
FX_effect_Sel2
Text Label 5750 3300 0    60   ~ 0
SPI_RX
Text Label 5750 3400 0    60   ~ 0
SPI_TX
Text Label 5750 4000 0    60   ~ 0
Bypass_en
Text Label 5750 4200 0    60   ~ 0
I2S2_CLK
Text Label 5750 4300 0    60   ~ 0
I2S2_FS
Text Label 5750 4400 0    60   ~ 0
I2S2_RX
Text Label 5750 4500 0    60   ~ 0
I2S2_DX
Text Label 5750 4600 0    60   ~ 0
UART_RTS
Text Label 5750 4700 0    60   ~ 0
UART_CTS
Text Label 5750 4800 0    60   ~ 0
UART_RXD
Text Label 5750 4900 0    60   ~ 0
UART_TXD
Text Label 5750 5100 0    60   ~ 0
SPI_CLK
Text Label 5750 5200 0    60   ~ 0
SPI_CS0
Text Label 5750 5300 0    60   ~ 0
SPI_CS1
Text Label 5750 5400 0    60   ~ 0
SPI_CS2
Text Label 5750 5500 0    60   ~ 0
SPI_CS3
NoConn ~ 5750 5700
NoConn ~ 5750 5800
$Sheet
S 9650 4650 1000 1600
U 586E795B
F0 "Peripherals" 60
F1 "Peripherals.sch" 60
F2 "SPI_RX" I L 9650 4850 60 
F3 "SPI_TX" I L 9650 4950 60 
F4 "SPI_CLK" I L 9650 5100 60 
F5 "SPI_CS0" I L 9650 5200 60 
F6 "SPI_CS1" I L 9650 5300 60 
F7 "SPI_CS2" I L 9650 5400 60 
F8 "SPI_CS3" I L 9650 5500 60 
F9 "Bypass_en" I L 9650 5800 60 
$EndSheet
Text Label 9500 5100 2    60   ~ 0
SPI_CLK
Text Label 9500 5200 2    60   ~ 0
SPI_CS0
Text Label 9500 5300 2    60   ~ 0
SPI_CS1
Text Label 9500 5400 2    60   ~ 0
SPI_CS2
Text Label 9500 5500 2    60   ~ 0
SPI_CS3
Wire Wire Line
	9650 5100 9500 5100
Wire Wire Line
	9650 5200 9500 5200
Wire Wire Line
	9650 5300 9500 5300
Wire Wire Line
	9650 5400 9500 5400
Wire Wire Line
	9650 5500 9500 5500
Text Label 9500 5800 2    60   ~ 0
Bypass_en
Wire Wire Line
	9500 5800 9650 5800
Text Label 9500 4850 2    60   ~ 0
SPI_RX
Text Label 9500 4950 2    60   ~ 0
SPI_TX
Wire Wire Line
	9500 4850 9650 4850
Wire Wire Line
	9500 4950 9650 4950
NoConn ~ 5750 3100
NoConn ~ 5750 3700
NoConn ~ 5750 3800
NoConn ~ 5750 3900
Wire Wire Line
	3300 4600 3250 4600
Wire Wire Line
	3250 4600 3250 4700
Connection ~ 3250 4700
NoConn ~ 8500 2750
NoConn ~ 8500 2850
NoConn ~ 8500 2950
NoConn ~ 8500 3050
NoConn ~ 8500 3150
NoConn ~ 8500 3250
NoConn ~ 8500 3350
NoConn ~ 8500 3450
NoConn ~ 8000 2850
NoConn ~ 8000 2950
NoConn ~ 8000 3050
NoConn ~ 8000 3150
NoConn ~ 8000 3250
NoConn ~ 8000 3350
NoConn ~ 8000 3450
NoConn ~ 5750 4200
NoConn ~ 5750 4300
NoConn ~ 5750 4400
NoConn ~ 5750 4500
NoConn ~ 5750 4600
NoConn ~ 5750 4700
NoConn ~ 5750 4800
NoConn ~ 5750 4900
NoConn ~ 1550 3000
NoConn ~ 1550 3100
NoConn ~ 1050 3100
NoConn ~ 1050 3300
$Comp
L +1V35 #PWR010
U 1 1 5870A122
P 1750 4550
F 0 "#PWR010" H 1750 4400 50  0001 C CNN
F 1 "+1V35" H 1750 4690 50  0000 C CNN
F 2 "" H 1750 4550 50  0000 C CNN
F 3 "" H 1750 4550 50  0000 C CNN
	1    1750 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 4500 3300 4500
$Comp
L C C10
U 1 1 58732BCE
P 2000 4200
F 0 "C10" H 2025 4300 50  0000 L CNN
F 1 ".1uF" H 2025 4100 50  0000 L CNN
F 2 "" H 2038 4050 50  0000 C CNN
F 3 "" H 2000 4200 50  0000 C CNN
	1    2000 4200
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR011
U 1 1 58732CC6
P 2000 4400
F 0 "#PWR011" H 2000 4150 50  0001 C CNN
F 1 "GNDD" H 2000 4250 50  0000 C CNN
F 2 "" H 2000 4400 50  0000 C CNN
F 3 "" H 2000 4400 50  0000 C CNN
	1    2000 4400
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR012
U 1 1 58732E3D
P 2000 3950
F 0 "#PWR012" H 2000 3800 50  0001 C CNN
F 1 "+3.3V" H 2000 4090 50  0000 C CNN
F 2 "" H 2000 3950 50  0000 C CNN
F 3 "" H 2000 3950 50  0000 C CNN
	1    2000 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 3950 2000 4050
Wire Wire Line
	2200 4000 2200 4500
Wire Wire Line
	2000 4000 2200 4000
Connection ~ 2000 4000
Wire Wire Line
	2350 4200 3300 4200
Wire Wire Line
	2350 3900 2350 4200
Wire Wire Line
	2550 4100 3300 4100
Wire Wire Line
	2550 3900 2550 4100
$Comp
L R R17
U 1 1 58733955
P 2350 3750
F 0 "R17" V 2430 3750 50  0000 C CNN
F 1 "10k" V 2350 3750 50  0000 C CNN
F 2 "" V 2280 3750 50  0000 C CNN
F 3 "" H 2350 3750 50  0000 C CNN
	1    2350 3750
	1    0    0    -1  
$EndComp
$Comp
L R R18
U 1 1 58733A32
P 2550 3750
F 0 "R18" V 2630 3750 50  0000 C CNN
F 1 "10k" V 2550 3750 50  0000 C CNN
F 2 "" V 2480 3750 50  0000 C CNN
F 3 "" H 2550 3750 50  0000 C CNN
	1    2550 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 3600 2350 3500
Wire Wire Line
	2350 3500 2550 3500
Wire Wire Line
	2550 3500 2550 3600
Wire Wire Line
	2450 3500 2450 3450
Connection ~ 2450 3500
$Comp
L +3.3V #PWR013
U 1 1 58733DC4
P 2450 3450
F 0 "#PWR013" H 2450 3300 50  0001 C CNN
F 1 "+3.3V" H 2450 3590 50  0000 C CNN
F 2 "" H 2450 3450 50  0000 C CNN
F 3 "" H 2450 3450 50  0000 C CNN
	1    2450 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 1050 3250 1400
NoConn ~ 3300 1250
Wire Wire Line
	2000 4400 2000 4350
$EndSCHEMATC