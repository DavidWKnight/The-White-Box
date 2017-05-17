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
LIBS:switches
LIBS:Main Board
LIBS:Main Board-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
Title "The White Box"
Date "2017-02-23"
Rev "1.1"
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
NoConn ~ 3300 1700
NoConn ~ 3300 1800
NoConn ~ 3300 1900
NoConn ~ 3300 2000
$Comp
L Crystal Y1
U 1 1 586E0B81
P 3100 2400
F 0 "Y1" H 3100 2550 50  0000 C CNN
F 1 "32.768KHz" H 3100 2250 50  0000 C CNN
F 2 "" H 3100 2400 50  0000 C CNN
F 3 "" H 3100 2400 50  0000 C CNN
	1    3100 2400
	0    1    1    0   
$EndComp
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
Text Label 1550 3500 0    60   ~ 0
DSP_EMU1
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
NoConn ~ 3300 4900
NoConn ~ 3300 4800
NoConn ~ 3300 5200
$Comp
L GNDD #PWR05
U 1 1 586E2E28
P 5850 1550
F 0 "#PWR05" H 5850 1300 50  0001 C CNN
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
F 1 "10k" V 6000 1400 50  0000 C CNN
F 2 "" V 5930 1400 50  0000 C CNN
F 3 "" H 6000 1400 50  0000 C CNN
	1    6000 1400
	0    1    1    0   
$EndComp
$Comp
L GNDD #PWR06
U 1 1 586E2ED0
P 6200 1450
F 0 "#PWR06" H 6200 1200 50  0001 C CNN
F 1 "GNDD" H 6200 1300 50  0000 C CNN
F 2 "" H 6200 1450 50  0000 C CNN
F 3 "" H 6200 1450 50  0000 C CNN
	1    6200 1450
	1    0    0    -1  
$EndComp
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
Text Label 5750 3300 0    60   ~ 0
SPI_RX
Text Label 5750 3400 0    60   ~ 0
SPI_TX
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
Text Label 9500 5100 2    60   ~ 0
SPI_CLK
Text Label 9500 5200 2    60   ~ 0
SPI_CS0
Text Label 9500 5300 2    60   ~ 0
SPI_CS1
Text Label 9500 5400 2    60   ~ 0
SPI_CS2
Text Label 9500 4850 2    60   ~ 0
SPI_RX
Text Label 9500 4950 2    60   ~ 0
SPI_TX
NoConn ~ 5750 3100
NoConn ~ 5750 3700
NoConn ~ 5750 3800
NoConn ~ 5750 3900
NoConn ~ 5750 4600
NoConn ~ 5750 4700
NoConn ~ 5750 4800
NoConn ~ 5750 4900
NoConn ~ 1550 3000
NoConn ~ 1550 3100
NoConn ~ 1050 3100
NoConn ~ 1050 3300
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
L GNDD #PWR07
U 1 1 58732CC6
P 2000 4400
F 0 "#PWR07" H 2000 4150 50  0001 C CNN
F 1 "GNDD" H 2000 4250 50  0000 C CNN
F 2 "" H 2000 4400 50  0000 C CNN
F 3 "" H 2000 4400 50  0000 C CNN
	1    2000 4400
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR08
U 1 1 58732E3D
P 2000 3950
F 0 "#PWR08" H 2000 3800 50  0001 C CNN
F 1 "+3.3V" H 2000 4090 50  0000 C CNN
F 2 "" H 2000 3950 50  0000 C CNN
F 3 "" H 2000 3950 50  0000 C CNN
	1    2000 3950
	1    0    0    -1  
$EndComp
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
$Comp
L +3.3V #PWR09
U 1 1 58733DC4
P 2450 3450
F 0 "#PWR09" H 2450 3300 50  0001 C CNN
F 1 "+3.3V" H 2450 3590 50  0000 C CNN
F 2 "" H 2450 3450 50  0000 C CNN
F 3 "" H 2450 3450 50  0000 C CNN
	1    2450 3450
	1    0    0    -1  
$EndComp
NoConn ~ 3300 1250
$Comp
L CONN_02X07 P2
U 1 1 58C4F88D
P 8400 2900
F 0 "P2" H 8400 3300 50  0000 C CNN
F 1 "CONN_02X07" V 8400 2900 50  0000 C CNN
F 2 "" H 8400 1700 50  0000 C CNN
F 3 "" H 8400 1700 50  0000 C CNN
	1    8400 2900
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR010
U 1 1 58C4FB73
P 8700 3250
F 0 "#PWR010" H 8700 3000 50  0001 C CNN
F 1 "GNDD" H 8700 3100 50  0000 C CNN
F 2 "" H 8700 3250 50  0000 C CNN
F 3 "" H 8700 3250 50  0000 C CNN
	1    8700 3250
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR011
U 1 1 58C4FDC7
P 8100 3250
F 0 "#PWR011" H 8100 3100 50  0001 C CNN
F 1 "+3.3V" H 8100 3390 50  0000 C CNN
F 2 "" H 8100 3250 50  0000 C CNN
F 3 "" H 8100 3250 50  0000 C CNN
	1    8100 3250
	-1   0    0    1   
$EndComp
Text Label 8150 2600 2    60   ~ 0
SPI_RX
Text Label 8150 2700 2    60   ~ 0
SPI_TX
Text Label 8150 2800 2    60   ~ 0
SPI_CLK
Text Label 8150 2900 2    60   ~ 0
SPI_CS3
NoConn ~ 5750 3500
NoConn ~ 5750 3600
NoConn ~ 5750 3000
NoConn ~ 5750 2900
NoConn ~ 5750 2800
NoConn ~ 5750 2700
NoConn ~ 5750 2600
NoConn ~ 5750 1850
NoConn ~ 5750 1950
NoConn ~ 5750 2050
NoConn ~ 5750 2150
NoConn ~ 5750 2250
NoConn ~ 5750 2350
$Comp
L CP C2
U 1 1 58C3BF33
P 2450 4900
F 0 "C2" H 2475 5000 50  0000 L CNN
F 1 ".1uF" H 2475 4800 50  0000 L CNN
F 2 "" H 2488 4750 50  0000 C CNN
F 3 "" H 2450 4900 50  0000 C CNN
	1    2450 4900
	1    0    0    -1  
$EndComp
$Comp
L CP C1
U 1 1 58C3BFDB
P 2150 4900
F 0 "C1" H 2175 5000 50  0000 L CNN
F 1 ".1uF" H 2175 4800 50  0000 L CNN
F 2 "" H 2188 4750 50  0000 C CNN
F 3 "" H 2150 4900 50  0000 C CNN
	1    2150 4900
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR012
U 1 1 58C3C053
P 2300 5150
F 0 "#PWR012" H 2300 4900 50  0001 C CNN
F 1 "GNDD" H 2300 5000 50  0000 C CNN
F 2 "" H 2300 5150 50  0000 C CNN
F 3 "" H 2300 5150 50  0000 C CNN
	1    2300 5150
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 58C3C752
P 1700 4500
F 0 "R5" V 1780 4500 50  0000 C CNN
F 1 "10k" V 1700 4500 50  0000 C CNN
F 2 "" V 1630 4500 50  0000 C CNN
F 3 "" H 1700 4500 50  0000 C CNN
	1    1700 4500
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 58C3C806
P 1700 4900
F 0 "R7" V 1780 4900 50  0000 C CNN
F 1 "6.5k" V 1700 4900 50  0000 C CNN
F 2 "" V 1630 4900 50  0000 C CNN
F 3 "" H 1700 4900 50  0000 C CNN
	1    1700 4900
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR013
U 1 1 58C3CEE5
P 1700 5100
F 0 "#PWR013" H 1700 4850 50  0001 C CNN
F 1 "GNDD" H 1700 4950 50  0000 C CNN
F 2 "" H 1700 5100 50  0000 C CNN
F 3 "" H 1700 5100 50  0000 C CNN
	1    1700 5100
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR014
U 1 1 58C3CFCC
P 1700 4300
F 0 "#PWR014" H 1700 4150 50  0001 C CNN
F 1 "+3.3V" H 1700 4440 50  0000 C CNN
F 2 "" H 1700 4300 50  0000 C CNN
F 3 "" H 1700 4300 50  0000 C CNN
	1    1700 4300
	1    0    0    -1  
$EndComp
NoConn ~ 3300 5500
NoConn ~ 3300 5300
NoConn ~ 8650 2600
NoConn ~ 8650 2700
NoConn ~ 8650 2800
NoConn ~ 8650 2900
NoConn ~ 8650 3000
NoConn ~ 8650 3100
NoConn ~ 8150 3000
NoConn ~ 8150 3100
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
F8 "I2S2_CLK" I L 9650 5600 60 
F9 "I2S2_FS" I L 9650 5700 60 
F10 "I2S2_RX" I L 9650 5800 60 
F11 "I2S2_DX" I L 9650 5900 60 
F12 "I2C_SCL" I L 9650 6050 60 
F13 "I2C_SDA" I L 9650 6150 60 
$EndSheet
NoConn ~ 5750 4000
Text Label 9500 5600 2    60   ~ 0
I2S2_CLK
Text Label 9500 5700 2    60   ~ 0
I2S2_FS
Text Label 9500 5800 2    60   ~ 0
I2S2_RX
Text Label 9500 5900 2    60   ~ 0
I2S2_DX
Text Label 6650 5700 0    60   ~ 0
I2C_SCL
Text Label 6650 5800 0    60   ~ 0
I2C_SDA
Text Label 9500 6050 2    60   ~ 0
I2C_SCL
Text Label 9500 6150 2    60   ~ 0
I2C_SDA
$Comp
L +3.3V #PWR015
U 1 1 591C9A5F
P 6300 5200
F 0 "#PWR015" H 6300 5050 50  0001 C CNN
F 1 "+3.3V" H 6300 5340 50  0000 C CNN
F 2 "" H 6300 5200 50  0000 C CNN
F 3 "" H 6300 5200 50  0000 C CNN
	1    6300 5200
	1    0    0    -1  
$EndComp
$Comp
L R R20
U 1 1 591CA86D
P 6300 5450
F 0 "R20" V 6380 5450 50  0000 C CNN
F 1 "10k" V 6300 5450 50  0000 C CNN
F 2 "" V 6230 5450 50  0001 C CNN
F 3 "" H 6300 5450 50  0001 C CNN
	1    6300 5450
	1    0    0    -1  
$EndComp
$Comp
L R R21
U 1 1 591CB100
P 6500 5450
F 0 "R21" V 6580 5450 50  0000 C CNN
F 1 "10k" V 6500 5450 50  0000 C CNN
F 2 "" V 6430 5450 50  0001 C CNN
F 3 "" H 6500 5450 50  0001 C CNN
	1    6500 5450
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG016
U 1 1 591D7F30
P 1450 4550
F 0 "#FLG016" H 1450 4625 50  0001 C CNN
F 1 "PWR_FLAG" H 1450 4700 50  0000 C CNN
F 2 "" H 1450 4550 50  0001 C CNN
F 3 "" H 1450 4550 50  0001 C CNN
	1    1450 4550
	1    0    0    -1  
$EndComp
NoConn ~ 5750 5400
Wire Wire Line
	3300 1050 3250 1050
Wire Wire Line
	3250 1350 3300 1350
Wire Wire Line
	3300 1150 3250 1150
Connection ~ 3250 1150
Connection ~ 3250 1350
Wire Wire Line
	2900 2600 3300 2600
Wire Wire Line
	3100 2600 3100 2550
Wire Wire Line
	3100 2250 3100 2200
Wire Wire Line
	2900 2200 3300 2200
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
Wire Wire Line
	1550 3200 2100 3200
Wire Wire Line
	1550 3300 2100 3300
Wire Wire Line
	2100 3400 1550 3400
Wire Wire Line
	2100 3200 2100 3450
Connection ~ 2100 3300
Connection ~ 2100 3400
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
Wire Wire Line
	9650 5100 9500 5100
Wire Wire Line
	9650 5200 9500 5200
Wire Wire Line
	9650 5300 9500 5300
Wire Wire Line
	9650 5400 9500 5400
Wire Wire Line
	9500 4850 9650 4850
Wire Wire Line
	9500 4950 9650 4950
Wire Wire Line
	3300 4600 3250 4600
Wire Wire Line
	3250 4600 3250 4700
Connection ~ 3250 4700
Wire Wire Line
	2200 4500 3300 4500
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
Wire Wire Line
	2350 3600 2350 3500
Wire Wire Line
	2350 3500 2550 3500
Wire Wire Line
	2550 3500 2550 3600
Wire Wire Line
	2450 3500 2450 3450
Connection ~ 2450 3500
Wire Wire Line
	3250 1050 3250 1400
Wire Wire Line
	2000 4400 2000 4350
Wire Wire Line
	8650 3200 8700 3200
Wire Wire Line
	8700 3200 8700 3250
Wire Wire Line
	8100 3250 8100 3200
Wire Wire Line
	8100 3200 8150 3200
Wire Wire Line
	2150 5050 2150 5100
Wire Wire Line
	2150 5100 2450 5100
Wire Wire Line
	2450 5100 2450 5050
Wire Wire Line
	2300 5150 2300 5100
Connection ~ 2300 5100
Wire Wire Line
	1450 4700 3300 4700
Wire Wire Line
	2150 4750 2150 4700
Wire Wire Line
	2450 4750 2450 4700
Connection ~ 2450 4700
Wire Wire Line
	1700 4650 1700 4750
Connection ~ 2150 4700
Connection ~ 1700 4700
Wire Wire Line
	1700 5100 1700 5050
Wire Wire Line
	1700 4350 1700 4300
Wire Wire Line
	9650 5600 9500 5600
Wire Wire Line
	9650 5700 9500 5700
Wire Wire Line
	9650 5800 9500 5800
Wire Wire Line
	9650 5900 9500 5900
Wire Wire Line
	9500 6050 9650 6050
Wire Wire Line
	9500 6150 9650 6150
Wire Wire Line
	5750 5700 6650 5700
Wire Wire Line
	5750 5800 6650 5800
Connection ~ 6300 5700
Wire Wire Line
	6300 5700 6300 5600
Wire Wire Line
	6300 5300 6300 5200
Wire Wire Line
	6500 5800 6500 5600
Connection ~ 6500 5800
Wire Wire Line
	6500 5300 6500 5250
Wire Wire Line
	6500 5250 6300 5250
Connection ~ 6300 5250
Wire Wire Line
	1450 4700 1450 4550
Text GLabel 3200 5400 0    60   Input ~ 0
PGOOD
Wire Wire Line
	3200 5400 3300 5400
$EndSCHEMATC
