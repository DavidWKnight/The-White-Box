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
LIBS:Digital FX pedal symbols
LIBS:front panel-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MSP430FR2032 U?
U 1 1 58634AE1
P 4450 3550
F 0 "U?" H 4250 5450 60  0000 C CNN
F 1 "MSP430FR2032" H 5250 5450 60  0000 C CNN
F 2 "" H 4350 4000 60  0001 C CNN
F 3 "" H 4350 4000 60  0001 C CNN
	1    4450 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 2650 5800 2650
Wire Wire Line
	5800 2650 5800 3350
Wire Wire Line
	5800 3350 5750 3350
Wire Wire Line
	5750 3250 5800 3250
Connection ~ 5800 3250
Wire Wire Line
	5750 3150 5800 3150
Connection ~ 5800 3150
Wire Wire Line
	5750 3050 5800 3050
Connection ~ 5800 3050
Wire Wire Line
	5750 2950 5800 2950
Connection ~ 5800 2950
Wire Wire Line
	5750 2850 5800 2850
Connection ~ 5800 2850
Wire Wire Line
	5750 2750 5800 2750
Connection ~ 5800 2750
Text Notes 5850 3050 0    60   ~ 0
LCD data
Text Label 3150 2500 2    60   ~ 0
LCD_RS
Text Label 3150 2400 2    60   ~ 0
LCD_RW
Text Label 3150 2300 2    60   ~ 0
LCD_E
NoConn ~ 3150 4850
NoConn ~ 3150 1800
NoConn ~ 3150 1900
NoConn ~ 3150 2000
NoConn ~ 3150 2100
NoConn ~ 3150 2200
NoConn ~ 3150 2700
NoConn ~ 3150 2800
NoConn ~ 3150 2900
NoConn ~ 3150 3000
NoConn ~ 3150 3100
NoConn ~ 3150 3200
NoConn ~ 3150 3300
NoConn ~ 3150 3400
NoConn ~ 3150 3600
NoConn ~ 3150 3700
NoConn ~ 3150 3800
NoConn ~ 3150 3900
NoConn ~ 3150 4000
NoConn ~ 3150 4100
NoConn ~ 3150 4200
NoConn ~ 3150 4300
NoConn ~ 5750 3500
NoConn ~ 5750 3600
NoConn ~ 5750 3700
NoConn ~ 5750 3800
NoConn ~ 5750 3900
NoConn ~ 5750 4000
NoConn ~ 5750 4100
NoConn ~ 5750 4200
NoConn ~ 5750 1800
NoConn ~ 5750 1900
NoConn ~ 5750 2000
NoConn ~ 5750 2100
NoConn ~ 5750 2200
NoConn ~ 5750 2300
NoConn ~ 5750 4550
NoConn ~ 3150 4550
NoConn ~ 3150 4650
NoConn ~ 3150 4750
$Comp
L SW_PUSH SW?
U 1 1 58C70B56
P 6350 4650
F 0 "SW?" H 6500 4760 50  0000 C CNN
F 1 "SW_PUSH" H 6350 4570 50  0000 C CNN
F 2 "" H 6350 4650 50  0000 C CNN
F 3 "" H 6350 4650 50  0000 C CNN
	1    6350 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4650 6050 4650
$Comp
L GND #PWR?
U 1 1 58C70BB8
P 6700 4700
F 0 "#PWR?" H 6700 4450 50  0001 C CNN
F 1 "GND" H 6700 4550 50  0000 C CNN
F 2 "" H 6700 4700 50  0000 C CNN
F 3 "" H 6700 4700 50  0000 C CNN
	1    6700 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 4650 6700 4650
Wire Wire Line
	6700 4650 6700 4700
NoConn ~ 5750 4750
NoConn ~ 5750 4850
NoConn ~ 5750 4950
NoConn ~ 5750 5050
NoConn ~ 5750 5150
NoConn ~ 5750 5250
$Comp
L ROTARY_ENCODER SW?
U 1 1 58C70C2C
P 7400 2400
F 0 "SW?" H 7400 2660 50  0000 C CNN
F 1 "ROTARY_ENCODER" H 7400 2140 50  0000 C CNN
F 2 "" H 7300 2560 50  0001 C CNN
F 3 "" H 7400 2660 50  0001 C CNN
	1    7400 2400
	1    0    0    -1  
$EndComp
Text Label 5750 2500 0    60   ~ 0
ENC1_A
Text Label 5750 2400 0    60   ~ 0
ENC1_B
Text Label 7100 2500 2    60   ~ 0
ENC1_B
Text Label 7100 2300 2    60   ~ 0
ENC1_A
$Comp
L GND #PWR?
U 1 1 58C70D2B
P 6650 2450
F 0 "#PWR?" H 6650 2200 50  0001 C CNN
F 1 "GND" H 6650 2300 50  0000 C CNN
F 2 "" H 6650 2450 50  0000 C CNN
F 3 "" H 6650 2450 50  0000 C CNN
	1    6650 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 2400 6650 2450
Wire Wire Line
	6650 2400 7100 2400
NoConn ~ 3150 5050
NoConn ~ 3150 5150
$EndSCHEMATC
