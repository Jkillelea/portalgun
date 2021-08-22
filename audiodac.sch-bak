EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title "Portal Gun Main Board"
Date "2021-03-29"
Rev "Draft B"
Comp "Jacob Killelea"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 7600 4100 2    50   Output ~ 0
AOUT+
Text HLabel 7600 4200 2    50   Output ~ 0
AOUT-
Wire Wire Line
	7450 4200 7600 4200
Text HLabel 4850 3900 0    50   Input ~ 0
I2S_LRCIN
Text HLabel 4850 4000 0    50   Input ~ 0
I2S_BCLK
$Comp
L power:+3.3V #PWR0119
U 1 1 6029BD20
P 6850 2850
F 0 "#PWR0119" H 6850 2700 50  0001 C CNN
F 1 "+3.3V" H 6865 3023 50  0000 C CNN
F 2 "" H 6850 2850 50  0001 C CNN
F 3 "" H 6850 2850 50  0001 C CNN
	1    6850 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 602A02BF
P 7400 3250
AR Path="/602A02BF" Ref="C?"  Part="1" 
AR Path="/601DE08D/602A02BF" Ref="C3"  Part="1" 
F 0 "C3" H 7515 3296 50  0000 L CNN
F 1 "1uF" H 7515 3205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7438 3100 50  0001 C CNN
F 3 "~" H 7400 3250 50  0001 C CNN
	1    7400 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0125
U 1 1 602A0878
P 7400 3450
F 0 "#PWR0125" H 7400 3200 50  0001 C CNN
F 1 "GND" H 7405 3277 50  0000 C CNN
F 2 "" H 7400 3450 50  0001 C CNN
F 3 "" H 7400 3450 50  0001 C CNN
	1    7400 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 3450 7400 3400
$Comp
L power:GND #PWR0127
U 1 1 602A0D57
P 6800 4950
F 0 "#PWR0127" H 6800 4700 50  0001 C CNN
F 1 "GND" H 6805 4777 50  0000 C CNN
F 2 "" H 6800 4950 50  0001 C CNN
F 3 "" H 6800 4950 50  0001 C CNN
	1    6800 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 4100 7600 4100
Text HLabel 4850 3800 0    50   Input ~ 0
I2S_DIN
Wire Wire Line
	5550 4000 6350 4000
$Comp
L Connector:TestPoint TP4
U 1 1 60750D00
P 5450 4000
F 0 "TP4" V 5255 4072 50  0000 C CNN
F 1 "I2S_LRCIN_TP" V 5346 4072 50  0000 C CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 5650 4000 50  0001 C CNN
F 3 "~" H 5650 4000 50  0001 C CNN
	1    5450 4000
	0    -1   1    0   
$EndComp
Connection ~ 5550 4000
Wire Wire Line
	5550 3900 5550 4000
Wire Wire Line
	4850 3900 5550 3900
Wire Wire Line
	4850 4000 5200 4000
Wire Wire Line
	5200 4000 5200 4100
Wire Wire Line
	5200 4100 6350 4100
$Comp
L Connector:TestPoint TP5
U 1 1 6075ABC0
P 5200 4100
F 0 "TP5" V 5246 4288 50  0000 L CNN
F 1 "I2S_BCLK_TP" V 5155 4288 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 5400 4100 50  0001 C CNN
F 3 "~" H 5400 4100 50  0001 C CNN
	1    5200 4100
	0    -1   -1   0   
$EndComp
Connection ~ 5200 4100
Wire Wire Line
	4850 3800 6100 3800
$Comp
L AudioDac:MAX98357AETE U4
U 1 1 60D10E4A
P 6900 3350
F 0 "U4" H 6900 3281 50  0000 C CNN
F 1 "MAX98357AETE" H 6900 3190 50  0000 C CNN
F 2 "Package_DFN_QFN:TQFN-16-1EP_3x3mm_P0.5mm_EP1.23x1.23mm" H 6900 3350 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX98357A-MAX98357B.pdf" H 6900 3350 50  0001 C CNN
	1    6900 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 4700 6800 4850
Wire Wire Line
	6850 3600 6850 3000
Wire Wire Line
	6850 3000 7000 3000
Wire Wire Line
	7400 3000 7400 3100
Wire Wire Line
	7000 3600 7000 3000
Connection ~ 7000 3000
Wire Wire Line
	7000 3000 7400 3000
Connection ~ 6850 3000
Wire Wire Line
	6850 2850 6850 3000
Wire Wire Line
	6900 4850 6900 4700
Wire Wire Line
	6800 4850 6900 4850
Connection ~ 6800 4850
Wire Wire Line
	6800 4850 6800 4950
Wire Wire Line
	6900 4850 7000 4850
Wire Wire Line
	7000 4850 7000 4700
Connection ~ 6900 4850
Text HLabel 4850 4350 0    50   Input ~ 0
~SHUTDOWN
Wire Wire Line
	4850 4350 5100 4350
$Comp
L power:+3.3V #PWR0104
U 1 1 60D4805E
P 6300 4250
F 0 "#PWR0104" H 6300 4100 50  0001 C CNN
F 1 "+3.3V" V 6315 4378 50  0000 L CNN
F 2 "" H 6300 4250 50  0001 C CNN
F 3 "" H 6300 4250 50  0001 C CNN
	1    6300 4250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6300 4250 6350 4250
Wire Wire Line
	6100 3900 6350 3900
Wire Wire Line
	6100 3800 6100 3900
$Comp
L Connector:TestPoint TP6
U 1 1 6075DC2A
P 6100 3800
F 0 "TP6" H 6100 4125 50  0000 C CNN
F 1 "I2S_DIN_TP" H 6100 4034 50  0000 C CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 6300 3800 50  0001 C CNN
F 3 "~" H 6300 3800 50  0001 C CNN
	1    6100 3800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5450 4000 5550 4000
$Comp
L Device:R R13
U 1 1 60D8CBB8
P 5250 4350
F 0 "R13" V 5043 4350 50  0000 C CNN
F 1 "634kR" V 5134 4350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5180 4350 50  0001 C CNN
F 3 "~" H 5250 4350 50  0001 C CNN
	1    5250 4350
	0    1    1    0   
$EndComp
Text Label 5550 4350 0    50   ~ 0
~SD_MODE
Wire Wire Line
	7000 4850 7100 4850
Wire Wire Line
	7100 4850 7100 4700
Connection ~ 7000 4850
Connection ~ 6100 3800
Wire Wire Line
	5400 4350 6350 4350
Text Notes 3150 5350 0    50   ~ 0
Drive  SD_MODE high  through  a  sufficiently  large  resistor  to  select  both  the  left\nand  right  words  of  the  stereo  input  data  (left/2  +  right/2).\nRLARGE  and  RSMALL are determined by the VDDIO voltage (logic\nvoltage from control  interface)  that  is  driving  SD_MODE \naccording  to  the following two equations:\nRSMALL (kΩ) = 94.0 x VDDIO - 100\nRLARGE (kΩ) = 222.2 x VDDIO - 100
Text Notes 2700 3150 0    50   ~ 0
GAIN_SLOT
Text Notes 3400 3150 0    50   ~ 0
I2S Gain (dB)
Wire Notes Line
	2650 3200 3950 3200
Wire Notes Line
	3350 3100 3350 4100
Text Notes 2700 3400 0    50   ~ 0
Connect to GND\nthrough 100kR
Text Notes 3500 3350 0    50   ~ 0
15
Text Notes 2900 3550 0    50   ~ 0
GND
Text Notes 3500 3550 0    50   ~ 0
12
Text Notes 2900 3700 0    50   ~ 0
NC
Text Notes 3500 3700 0    50   ~ 0
9
Text Notes 2900 3850 0    50   ~ 0
VDD
Text Notes 3500 3850 0    50   ~ 0
6
Text Notes 2700 4050 0    50   ~ 0
VDD through\n100kR resitor
Text Notes 3500 4050 0    50   ~ 0
3
$EndSCHEMATC
