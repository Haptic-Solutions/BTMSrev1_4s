EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "Battery Controller"
Date "2021-06-16"
Rev "1"
Comp "N/A"
Comment1 "Jarrett Cigainero"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:Q_NMOS_GDS Q1
U 1 1 5E10B7E4
P 1800 1800
F 0 "Q1" H 2004 1846 50  0000 L CNN
F 1 "PSMN5R6-100BS" H 2004 1755 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:TO-263-2" H 2000 1900 50  0001 C CNN
F 3 "~" H 1800 1800 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/nexperia-usa-inc/PSMN5R6-100BS-118/3131570" H 1800 1800 50  0001 C CNN "DK_Detail_Page"
F 5 "1727-7125-1-ND" H 1800 1800 50  0001 C CNN "Digi-Key_PN"
	1    1800 1800
	-1   0    0    1   
$EndComp
Text Label 1300 1200 2    50   ~ 0
CH+
Text Label 1300 1500 2    50   ~ 0
CH-
$Comp
L Device:R R8
U 1 1 5E10CB3C
P 2450 800
F 0 "R8" H 2520 846 50  0000 L CNN
F 1 "10K" H 2520 755 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 2380 800 50  0001 C CNN
F 3 "~" H 2450 800 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/ESR03EZPJ103/1762722" H 2450 800 50  0001 C CNN "DK_Detail_Page"
F 5 "RHM10KDCT-ND" H 2450 800 50  0001 C CNN "Digi-Key_PN"
	1    2450 800 
	-1   0    0    1   
$EndComp
$Comp
L Device:D_Zener D1
U 1 1 5E10E01D
P 2100 1650
F 0 "D1" V 2054 1729 50  0000 L CNN
F 1 "15V" V 2145 1729 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 2100 1650 50  0001 C CNN
F 3 "~" H 2100 1650 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 2100 1650 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 2100 1650 50  0001 C CNN "Digi-Key_PN"
	1    2100 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2000 1800 2100 1800
Wire Wire Line
	2100 1500 1700 1500
Wire Wire Line
	1700 1500 1700 1600
Wire Wire Line
	1300 1500 1500 1500
Connection ~ 1700 1500
Wire Wire Line
	2450 1200 1500 1200
$Comp
L Device:R R6
U 1 1 5E1209BF
P 3100 1800
F 0 "R6" H 3170 1846 50  0000 L CNN
F 1 "8" H 3170 1755 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 3030 1800 50  0001 C CNN
F 3 "~" H 3100 1800 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/vishay-dale/CRCW06038R06FKEAHP/2225948" H 3100 1800 50  0001 C CNN "DK_Detail_Page"
F 5 "541-8.06SCT-ND" H 3100 1800 50  0001 C CNN "Digi-Key_PN"
	1    3100 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	3350 1800 3250 1800
Wire Wire Line
	2450 1200 2450 2000
Wire Wire Line
	2950 1800 2100 1800
Connection ~ 2100 1800
Wire Wire Line
	3350 2100 2800 2100
Wire Wire Line
	2800 2100 2800 1500
Wire Wire Line
	2800 1500 2100 1500
Connection ~ 2100 1500
Text Label 1300 3800 2    50   ~ 0
B+
Text Label 1300 3150 2    50   ~ 0
BC-
Text Label 1300 3450 2    50   ~ 0
BP-
Wire Wire Line
	2900 1500 2800 1500
Connection ~ 2800 1500
Connection ~ 2450 2000
$Comp
L Device:D_Zener D5
U 1 1 5E12E723
P 3050 600
F 0 "D5" V 3000 450 50  0000 L CNN
F 1 "15V" V 3150 400 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 3050 600 50  0001 C CNN
F 3 "~" H 3050 600 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 3050 600 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 3050 600 50  0001 C CNN "Digi-Key_PN"
	1    3050 600 
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 600  3300 600 
Wire Wire Line
	2900 600  2800 600 
Text Label 1300 4400 2    50   ~ 0
M+
Text Label 1300 4700 2    50   ~ 0
M-
Wire Wire Line
	1300 4400 1400 4400
$Comp
L Device:C C8
U 1 1 5E138407
P 5000 3950
F 0 "C8" H 5115 3996 50  0000 L CNN
F 1 "0.1uf film" H 5115 3905 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5038 3800 50  0001 C CNN
F 3 "~" H 5000 3950 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 5000 3950 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 5000 3950 50  0001 C CNN "Digi-Key_PN"
	1    5000 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 3900 3550 3900
$Comp
L Device:Q_NMOS_GDS Q2
U 1 1 5E13E9AF
P 2050 5900
F 0 "Q2" H 2254 5946 50  0000 L CNN
F 1 "PSMN5R6-100BS" H 2000 6150 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:TO-263-2" H 2250 6000 50  0001 C CNN
F 3 "~" H 2050 5900 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/nexperia-usa-inc/PSMN5R6-100BS-118/3131570" H 2050 5900 50  0001 C CNN "DK_Detail_Page"
F 5 "1727-7125-1-ND" H 2050 5900 50  0001 C CNN "Digi-Key_PN"
	1    2050 5900
	-1   0    0    -1  
$EndComp
$Comp
L Device:D_Zener D2
U 1 1 5E1409D2
P 2250 6050
F 0 "D2" V 2204 6129 50  0000 L CNN
F 1 "15V" V 2295 6129 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 2250 6050 50  0001 C CNN
F 3 "~" H 2250 6050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 2250 6050 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 2250 6050 50  0001 C CNN "Digi-Key_PN"
	1    2250 6050
	0    -1   1    0   
$EndComp
Wire Wire Line
	1300 4700 1400 4700
$Comp
L power:GND #PWR01
U 1 1 5E14B309
P 1950 6200
F 0 "#PWR01" H 1950 5950 50  0001 C CNN
F 1 "GND" H 1955 6027 50  0000 C CNN
F 2 "" H 1950 6200 50  0001 C CNN
F 3 "" H 1950 6200 50  0001 C CNN
	1    1950 6200
	1    0    0    -1  
$EndComp
Text Label 5350 850  0    50   ~ 0
B+
$Comp
L Device:R R12
U 1 1 5E15D51B
P 4450 1500
F 0 "R12" H 4520 1546 50  0000 L CNN
F 1 "500" H 4520 1455 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 4380 1500 50  0001 C CNN
F 3 "~" H 4450 1500 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 4450 1500 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 4450 1500 50  0001 C CNN "Digi-Key_PN"
	1    4450 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	4150 1500 4300 1500
Wire Wire Line
	4150 2100 4300 2100
Text Label 2450 3150 2    50   ~ 0
IntBus
Wire Wire Line
	4750 1500 4600 1500
$Comp
L Driver_FET:HCPL-3120 U5
U 1 1 5E18609E
P 3750 1800
F 0 "U5" H 3750 2317 50  0000 C CNN
F 1 "HCPL-3120" H 3750 2226 50  0000 C CNN
F 2 "SMD_Packages:DIP-8_SMD" H 3750 1400 50  0001 C CIN
F 3 "https://docs.broadcom.com/docs/AV02-0161EN" H 3660 1805 50  0001 L CNN
F 4 "https://www.digikey.com/en/products/detail/broadcom-limited/HCPL-3120-500E/1966495" H 3750 1800 50  0001 C CNN "DK_Detail_Page"
F 5 "516-1789-1-ND" H 3750 1800 50  0001 C CNN "Digi-Key_PN"
	1    3750 1800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3350 1700 3350 1800
Wire Wire Line
	3350 1900 3350 1800
Connection ~ 3350 1800
$Comp
L Isolator:LTV-817S U7
U 1 1 5E18D2A5
P 4350 2500
F 0 "U7" H 4450 2700 50  0000 C CNN
F 1 "LTV-817S" H 4350 2300 50  0000 C CNN
F 2 "Housings_SOIC:SO-4_7.6x3.6mm_Pitch2.54mm" H 4350 2200 50  0001 C CNN
F 3 "http://www.us.liteon.com/downloads/LTV-817-827-847.PDF" H 4000 2800 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/lite-on-inc/LTV-817S/385837" H 4350 2500 50  0001 C CNN "DK_Detail_Page"
F 5 "160-1367-5-ND" H 4350 2500 50  0001 C CNN "Digi-Key_PN"
	1    4350 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 2400 2650 2400
Wire Wire Line
	2800 2100 2800 2600
Connection ~ 2800 2100
$Comp
L Device:R R4
U 1 1 5E1BCE7F
P 3100 7100
F 0 "R4" H 3170 7146 50  0000 L CNN
F 1 "8" H 3170 7055 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 3030 7100 50  0001 C CNN
F 3 "~" H 3100 7100 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/vishay-dale/CRCW06038R06FKEAHP/2225948" H 3100 7100 50  0001 C CNN "DK_Detail_Page"
F 5 "541-8.06SCT-ND" H 3100 7100 50  0001 C CNN "Digi-Key_PN"
	1    3100 7100
	0    1    1    0   
$EndComp
$Comp
L Device:Q_NMOS_GDS Q3
U 1 1 5E1BCE85
P 2450 7100
F 0 "Q3" H 2654 7146 50  0000 L CNN
F 1 "PSMN5R6-100BS" H 2654 7055 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:TO-263-2" H 2650 7200 50  0001 C CNN
F 3 "~" H 2450 7100 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/nexperia-usa-inc/PSMN5R6-100BS-118/3131570" H 2450 7100 50  0001 C CNN "DK_Detail_Page"
F 5 "1727-7125-1-ND" H 2450 7100 50  0001 C CNN "Digi-Key_PN"
	1    2450 7100
	-1   0    0    -1  
$EndComp
$Comp
L Device:D_Zener D3
U 1 1 5E1BCE8B
P 2800 7250
F 0 "D3" V 2754 7329 50  0000 L CNN
F 1 "15V" V 2845 7329 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 2800 7250 50  0001 C CNN
F 3 "~" H 2800 7250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 2800 7250 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 2800 7250 50  0001 C CNN "Digi-Key_PN"
	1    2800 7250
	0    -1   1    0   
$EndComp
Wire Wire Line
	2650 7100 2800 7100
Wire Wire Line
	2800 7100 2950 7100
Connection ~ 2800 7100
Wire Wire Line
	2350 7300 2350 7400
Wire Wire Line
	2350 7400 2800 7400
Wire Wire Line
	3350 7100 3250 7100
$Comp
L power:GND #PWR02
U 1 1 5E1BCE99
P 2350 7400
F 0 "#PWR02" H 2350 7150 50  0001 C CNN
F 1 "GND" H 2355 7227 50  0000 C CNN
F 2 "" H 2350 7400 50  0001 C CNN
F 3 "" H 2350 7400 50  0001 C CNN
	1    2350 7400
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR05
U 1 1 5E1BCEA6
P 2750 6500
F 0 "#PWR05" H 2750 6350 50  0001 C CNN
F 1 "+12V" H 2765 6673 50  0000 C CNN
F 2 "" H 2750 6500 50  0001 C CNN
F 3 "" H 2750 6500 50  0001 C CNN
	1    2750 6500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 5E1BCEB2
P 4250 7200
F 0 "R10" H 4320 7246 50  0000 L CNN
F 1 "500" H 4320 7155 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 4180 7200 50  0001 C CNN
F 3 "~" H 4250 7200 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 4250 7200 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 4250 7200 50  0001 C CNN "Digi-Key_PN"
	1    4250 7200
	0    1    1    0   
$EndComp
Wire Wire Line
	3950 7200 4100 7200
$Comp
L dk_PMIC-Gate-Drivers:FAN3111ESX U4
U 1 1 5E1BCECA
P 3650 7100
F 0 "U4" H 3900 7450 60  0000 C CNN
F 1 "FAN3111ESX" H 3200 6650 60  0000 C CNN
F 2 "digikey-footprints:SOT-753" H 3850 7300 60  0001 L CNN
F 3 "https://www.onsemi.com/pub/Collateral/FAN3111E-D.pdf" H 3850 7400 60  0001 L CNN
F 4 "FAN3111ESXCT-ND" H 3850 7500 60  0001 L CNN "Digi-Key_PN"
F 5 "FAN3111ESX" H 3850 7600 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 3850 7700 60  0001 L CNN "Category"
F 7 "PMIC - Gate Drivers" H 3850 7800 60  0001 L CNN "Family"
F 8 "https://www.onsemi.com/pub/Collateral/FAN3111E-D.pdf" H 3850 7900 60  0001 L CNN "DK_Datasheet_Link"
F 9 "https://www.digikey.com/en/products/detail/on-semiconductor/FAN3111ESX/2036891?s=N4IgTCBcDaIGIEEByBmAjBgogZQBogF0BfIA" H 3850 8000 60  0001 L CNN "DK_Detail_Page"
F 10 "IC GATE DVR SGL 1A EXTER SOT23-5" H 3850 8100 60  0001 L CNN "Description"
F 11 "ON Semiconductor" H 3850 8200 60  0001 L CNN "Manufacturer"
F 12 "Active" H 3850 8300 60  0001 L CNN "Status"
	1    3650 7100
	-1   0    0    -1  
$EndComp
$Comp
L power:+12V #PWR013
U 1 1 5E1BCED1
P 3650 6800
F 0 "#PWR013" H 3650 6650 50  0001 C CNN
F 1 "+12V" H 3500 6900 50  0000 C CNN
F 2 "" H 3650 6800 50  0001 C CNN
F 3 "" H 3650 6800 50  0001 C CNN
	1    3650 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 7400 3650 7450
Text Label 1300 6900 2    50   ~ 0
Heater-
Wire Notes Line
	1300 650  1300 7650
Text Label 1300 6400 2    50   ~ 0
Heater+
$Comp
L Device:Fuse F1
U 1 1 5E1C726D
P 1550 6400
F 0 "F1" V 1353 6400 50  0000 C CNN
F 1 "2A" V 1444 6400 50  0000 C CNN
F 2 "Resistors_ThroughHole:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1480 6400 50  0001 C CNN
F 3 "~" H 1550 6400 50  0001 C CNN
	1    1550 6400
	0    1    1    0   
$EndComp
Text Label 1300 8900 2    50   ~ 0
IntBus
Wire Wire Line
	1800 6400 1700 6400
Wire Wire Line
	1400 6400 1350 6400
Wire Wire Line
	2450 3150 2450 3800
Wire Wire Line
	2750 3800 2450 3800
Wire Wire Line
	2750 4000 2200 4000
Wire Wire Line
	2200 4000 2200 3800
Wire Wire Line
	3350 2400 4050 2400
Wire Wire Line
	2800 2600 4050 2600
$Comp
L Device:R R13
U 1 1 5E13B1FD
P 4900 2600
F 0 "R13" H 4970 2646 50  0000 L CNN
F 1 "10K" H 4970 2555 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 4830 2600 50  0001 C CNN
F 3 "~" H 4900 2600 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/ESR03EZPJ103/1762722" H 4900 2600 50  0001 C CNN "DK_Detail_Page"
F 5 "RHM10KDCT-ND" H 4900 2600 50  0001 C CNN "Digi-Key_PN"
	1    4900 2600
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR021
U 1 1 5E13BE26
P 4650 2300
F 0 "#PWR021" H 4650 2150 50  0001 C CNN
F 1 "+5V" H 4665 2473 50  0000 C CNN
F 2 "" H 4650 2300 50  0001 C CNN
F 3 "" H 4650 2300 50  0001 C CNN
	1    4650 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 2300 4650 2400
Wire Wire Line
	4750 2600 4700 2600
Wire Wire Line
	5050 2700 5050 2600
Wire Wire Line
	4700 2600 4700 2450
Wire Wire Line
	4700 2450 5100 2450
Connection ~ 4700 2600
Wire Wire Line
	4700 2600 4650 2600
Text Label 4750 1500 0    50   ~ 0
CHctrl
Text Label 5100 2450 0    50   ~ 0
CHdetect
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5E159150
P 800 1200
F 0 "H1" V 1037 1203 50  0000 C CNN
F 1 "Charge+" V 946 1203 50  0000 C CNN
F 2 "Connect:1pin" H 800 1200 50  0001 C CNN
F 3 "~" H 800 1200 50  0001 C CNN
	1    800  1200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1500 1200 1500 1150
Connection ~ 1500 1200
Wire Wire Line
	1500 1200 1300 1200
$Comp
L Mechanical:MountingHole_Pad H9
U 1 1 5E15F0FF
P 800 1500
F 0 "H9" V 1037 1503 50  0000 C CNN
F 1 "Charge-" V 946 1503 50  0000 C CNN
F 2 "Connect:1pin" H 800 1500 50  0001 C CNN
F 3 "~" H 800 1500 50  0001 C CNN
	1    800  1500
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5E15F414
P 750 3150
F 0 "H2" V 987 3153 50  0000 C CNN
F 1 "BatteryC-" V 896 3153 50  0000 C CNN
F 2 "Connect:1pin" H 750 3150 50  0001 C CNN
F 3 "~" H 750 3150 50  0001 C CNN
	1    750  3150
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 5E15FCED
P 750 3450
F 0 "H3" V 987 3453 50  0000 C CNN
F 1 "BatteryP-" V 896 3453 50  0000 C CNN
F 2 "Connect:1pin" H 750 3450 50  0001 C CNN
F 3 "~" H 750 3450 50  0001 C CNN
	1    750  3450
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 5E160167
P 750 3800
F 0 "H4" V 987 3803 50  0000 C CNN
F 1 "Battery+" V 896 3803 50  0000 C CNN
F 2 "Connect:1pin" H 750 3800 50  0001 C CNN
F 3 "~" H 750 3800 50  0001 C CNN
	1    750  3800
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H5
U 1 1 5E1605A9
P 750 4400
F 0 "H5" V 987 4403 50  0000 C CNN
F 1 "Out+" V 896 4403 50  0000 C CNN
F 2 "Connect:1pin" H 750 4400 50  0001 C CNN
F 3 "~" H 750 4400 50  0001 C CNN
	1    750  4400
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H6
U 1 1 5E1609D4
P 750 4700
F 0 "H6" V 987 4703 50  0000 C CNN
F 1 "Out-" V 896 4703 50  0000 C CNN
F 2 "Connect:1pin" H 750 4700 50  0001 C CNN
F 3 "~" H 750 4700 50  0001 C CNN
	1    750  4700
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H7
U 1 1 5E160DD1
P 750 6400
F 0 "H7" V 987 6403 50  0000 C CNN
F 1 "Heater+" V 896 6403 50  0000 C CNN
F 2 "Connect:1pin" H 750 6400 50  0001 C CNN
F 3 "~" H 750 6400 50  0001 C CNN
	1    750  6400
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H8
U 1 1 5E1620A1
P 750 6900
F 0 "H8" V 987 6903 50  0000 C CNN
F 1 "Heater-" V 896 6903 50  0000 C CNN
F 2 "Connect:1pin" H 750 6900 50  0001 C CNN
F 3 "~" H 750 6900 50  0001 C CNN
	1    750  6900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1500 1150 900  1150
Wire Wire Line
	900  1150 900  1200
Wire Wire Line
	900  1500 900  1450
Wire Wire Line
	900  1450 1500 1450
Wire Wire Line
	1500 1450 1500 1500
Connection ~ 1500 1500
Wire Wire Line
	1500 1500 1700 1500
Wire Wire Line
	850  3150 850  3100
Wire Wire Line
	1400 3100 1400 3150
Wire Wire Line
	850  3450 850  3400
Wire Wire Line
	850  3400 1400 3400
Wire Wire Line
	1400 3400 1400 3450
Wire Wire Line
	1400 3450 1300 3450
Wire Wire Line
	850  3800 850  3750
Wire Wire Line
	850  3750 1400 3750
Wire Wire Line
	1400 3750 1400 3800
Connection ~ 1400 3800
Wire Wire Line
	1400 3800 1300 3800
Wire Wire Line
	850  4400 850  4350
Wire Wire Line
	850  4350 1400 4350
Wire Wire Line
	1400 4350 1400 4400
Wire Wire Line
	850  4700 850  4650
Wire Wire Line
	850  4650 1400 4650
Wire Wire Line
	1400 4650 1400 4700
Wire Wire Line
	850  6400 850  6350
Wire Wire Line
	850  6350 1350 6350
Wire Wire Line
	1350 6350 1350 6400
Connection ~ 1350 6400
Wire Wire Line
	1350 6400 1300 6400
Wire Wire Line
	850  6900 850  6850
Wire Wire Line
	850  6850 1350 6850
Wire Wire Line
	1350 6850 1350 6900
Connection ~ 1350 6900
Wire Wire Line
	1350 6900 1300 6900
Wire Wire Line
	1400 3800 2200 3800
$Comp
L Device:D_Zener D7
U 1 1 5E1383EA
P 6650 10300
F 0 "D7" V 6604 10379 50  0000 L CNN
F 1 "15V" V 6695 10379 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 6650 10300 50  0001 C CNN
F 3 "~" H 6650 10300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 6650 10300 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 6650 10300 50  0001 C CNN "Digi-Key_PN"
	1    6650 10300
	0    -1   1    0   
$EndComp
Wire Wire Line
	6650 10450 6200 10450
Wire Wire Line
	6200 10450 6200 10350
Wire Wire Line
	6650 10150 6500 10150
$Comp
L dk_Rectangular-Connectors-Headers-Male-Pins:22-23-2021 J1
U 1 1 5E148841
P 4850 9500
F 0 "J1" V 4625 9508 50  0000 C CNN
F 1 "fan" V 4716 9508 50  0000 C CNN
F 2 "digikey-footprints:PinHeader_1x2_P2.54mm_Drill1.02mm" H 5050 9700 60  0001 L CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 5050 9800 60  0001 L CNN
F 4 "" H 5050 9900 60  0001 L CNN "Digi-Key_PN"
F 5 "22-23-2021" H 5050 10000 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 5050 10100 60  0001 L CNN "Category"
F 7 "Rectangular Connectors - Headers, Male Pins" H 5050 10200 60  0001 L CNN "Family"
F 8 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 5050 10300 60  0001 L CNN "DK_Datasheet_Link"
F 9 "" H 5050 10400 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN HEADER VERT 2POS 2.54MM" H 5050 10500 60  0001 L CNN "Description"
F 11 "Molex" H 5050 10600 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5050 10700 60  0001 L CNN "Status"
	1    4850 9500
	-1   0    0    1   
$EndComp
$Comp
L power:+12V #PWR0102
U 1 1 5E151692
P 5200 9700
F 0 "#PWR0102" H 5200 9550 50  0001 C CNN
F 1 "+12V" H 5215 9873 50  0000 C CNN
F 2 "" H 5200 9700 50  0001 C CNN
F 3 "" H 5200 9700 50  0001 C CNN
	1    5200 9700
	1    0    0    -1  
$EndComp
Text Label 6800 9950 2    50   ~ 0
CoolCTRL
Wire Wire Line
	5700 9650 5400 9650
Wire Wire Line
	5400 9650 5400 9700
Wire Wire Line
	5400 9700 5200 9700
Wire Wire Line
	13400 8800 13400 8950
$Comp
L Device:C C17
U 1 1 5E15224D
P 12600 6050
F 0 "C17" H 12650 6150 50  0000 L CNN
F 1 "0.1uf film" H 12600 5800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 12638 5900 50  0001 C CNN
F 3 "~" H 12600 6050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 12600 6050 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 12600 6050 50  0001 C CNN "Digi-Key_PN"
	1    12600 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C18
U 1 1 5E152EDA
P 12850 6050
F 0 "C18" H 12900 6150 50  0000 L CNN
F 1 "0.1uf film" H 12900 6300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 12888 5900 50  0001 C CNN
F 3 "~" H 12850 6050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 12850 6050 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 12850 6050 50  0001 C CNN "Digi-Key_PN"
	1    12850 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C16
U 1 1 5E153220
P 12350 6050
F 0 "C16" H 12400 6150 50  0000 L CNN
F 1 "0.1uf film" H 12400 6300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 12388 5900 50  0001 C CNN
F 3 "~" H 12350 6050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 12350 6050 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 12350 6050 50  0001 C CNN "Digi-Key_PN"
	1    12350 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C15
U 1 1 5E15368D
P 12100 6050
F 0 "C15" H 12150 6150 50  0000 L CNN
F 1 "0.1uf film" H 11900 6400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 12138 5900 50  0001 C CNN
F 3 "~" H 12100 6050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 12100 6050 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 12100 6050 50  0001 C CNN "Digi-Key_PN"
	1    12100 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	12100 6200 12350 6200
Connection ~ 12350 6200
Wire Wire Line
	12600 6200 12850 6200
Connection ~ 12600 6200
Wire Wire Line
	12350 5900 12600 5900
Connection ~ 12350 5900
Wire Wire Line
	12600 5900 12850 5900
Connection ~ 12600 5900
$Comp
L power:+5V #PWR025
U 1 1 5E1BC9DC
P 15700 2050
F 0 "#PWR025" H 15700 1900 50  0001 C CNN
F 1 "+5V" H 15715 2223 50  0000 C CNN
F 2 "" H 15700 2050 50  0001 C CNN
F 3 "" H 15700 2050 50  0001 C CNN
	1    15700 2050
	1    0    0    -1  
$EndComp
Text Label 11550 7350 2    50   ~ 0
CHctrl
Text Label 15550 7250 0    50   ~ 0
CHdetect
Text Label 11550 8150 2    50   ~ 0
BCsense
Text Label 11550 8050 2    50   ~ 0
BVsense
Text Label 11550 7150 2    50   ~ 0
Mctrl+
Text Label 11550 7750 2    50   ~ 0
Hctrl
Text Label 11550 7050 2    50   ~ 0
CoolCTRL
Wire Wire Line
	11650 7150 11550 7150
Wire Wire Line
	11550 7350 11650 7350
Wire Wire Line
	11650 7750 11550 7750
Wire Wire Line
	11650 7050 11550 7050
Wire Wire Line
	11550 8050 11600 8050
Wire Wire Line
	11650 8150 11550 8150
Text Label 11550 8250 2    50   ~ 0
Btemp
Wire Wire Line
	11650 8250 11550 8250
Text Label 11550 8350 2    50   ~ 0
cTemp
Wire Wire Line
	11650 8350 11550 8350
Wire Wire Line
	15550 7250 15450 7250
Text Label 11650 6950 2    50   ~ 0
__PwrKey
$Comp
L Device:R R14
U 1 1 5E157224
P 11000 7500
F 0 "R14" H 11070 7546 50  0000 L CNN
F 1 "10K" H 11070 7455 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 10930 7500 50  0001 C CNN
F 3 "~" H 11000 7500 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/ESR03EZPJ103/1762722" H 11000 7500 50  0001 C CNN "DK_Detail_Page"
F 5 "RHM10KDCT-ND" H 11000 7500 50  0001 C CNN "Digi-Key_PN"
	1    11000 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	11650 7950 11000 7950
$Comp
L power:+5C #PWR0104
U 1 1 5E1645FA
P 13400 6200
F 0 "#PWR0104" H 13400 6050 50  0001 C CNN
F 1 "+5C" H 13415 6373 50  0000 C CNN
F 2 "" H 13400 6200 50  0001 C CNN
F 3 "" H 13400 6200 50  0001 C CNN
	1    13400 6200
	1    0    0    -1  
$EndComp
$Comp
L power:+5C #PWR0105
U 1 1 5E186358
P 11000 7350
F 0 "#PWR0105" H 11000 7200 50  0001 C CNN
F 1 "+5C" H 11015 7523 50  0000 C CNN
F 2 "" H 11000 7350 50  0001 C CNN
F 3 "" H 11000 7350 50  0001 C CNN
	1    11000 7350
	1    0    0    -1  
$EndComp
Text Label 11550 6650 2    50   ~ 0
PGMC
Text Label 15550 6650 0    50   ~ 0
PGMD
Wire Wire Line
	15550 6650 15450 6650
Wire Wire Line
	11650 6650 11550 6650
Text Label 11000 8100 2    50   ~ 0
MCLR
Wire Wire Line
	11000 7950 11000 8100
$Comp
L Device:D_Zener D14
U 1 1 5E15D833
P 3650 9650
F 0 "D14" V 3604 9729 50  0000 L CNN
F 1 "15V" V 3695 9729 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 3650 9650 50  0001 C CNN
F 3 "~" H 3650 9650 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 3650 9650 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 3650 9650 50  0001 C CNN "Digi-Key_PN"
	1    3650 9650
	0    -1   1    0   
$EndComp
Wire Wire Line
	3650 9800 3200 9800
Wire Wire Line
	3200 9800 3200 9700
Wire Wire Line
	3650 9500 3500 9500
$Comp
L power:+12V #PWR0107
U 1 1 5E15D853
P 2250 9050
F 0 "#PWR0107" H 2250 8900 50  0001 C CNN
F 1 "+12V" H 2265 9223 50  0000 C CNN
F 2 "" H 2250 9050 50  0001 C CNN
F 3 "" H 2250 9050 50  0001 C CNN
	1    2250 9050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 9000 2450 9000
Wire Wire Line
	2450 9000 2450 9050
Wire Wire Line
	2450 9050 2250 9050
Wire Wire Line
	5500 1300 5350 1300
Text Label 6000 1300 0    50   ~ 0
BVsense
Wire Wire Line
	5350 1600 5350 1650
Wire Wire Line
	5350 1250 5350 1300
Wire Wire Line
	5350 850  5350 950 
$Comp
L Device:R R2
U 1 1 5E14F6FC
P 5350 1450
F 0 "R2" H 5420 1496 50  0000 L CNN
F 1 "16K" H 5420 1405 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 5280 1450 50  0001 C CNN
F 3 "~" H 5350 1450 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/vishay-dale/CRCW060316K0FKEAHP/2226306" H 5350 1450 50  0001 C CNN "DK_Detail_Page"
F 5 "541-CRCW060316K0FKEAHPCT-ND" H 5350 1450 50  0001 C CNN "Digi-Key_PN"
	1    5350 1450
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 5E14F459
P 5350 1100
F 0 "R1" H 5420 1146 50  0000 L CNN
F 1 "200K" H 5420 1055 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 5280 1100 50  0001 C CNN
F 3 "~" H 5350 1100 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ERJ-PA3F2003V/5035886" H 5350 1100 50  0001 C CNN "DK_Detail_Page"
F 5 "P200KBYCT-ND" H 5350 1100 50  0001 C CNN "Digi-Key_PN"
	1    5350 1100
	-1   0    0    1   
$EndComp
Text Label 15550 6750 0    50   ~ 0
chargeRLY
Wire Wire Line
	15550 6750 15450 6750
Text Label 15550 7150 0    50   ~ 0
mainContactor
Wire Wire Line
	15550 7050 15450 7050
$Comp
L Device:D_Zener D13
U 1 1 5E20EA77
P 3650 8500
F 0 "D13" V 3604 8579 50  0000 L CNN
F 1 "15V" V 3695 8579 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 3650 8500 50  0001 C CNN
F 3 "~" H 3650 8500 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 3650 8500 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 3650 8500 50  0001 C CNN "Digi-Key_PN"
	1    3650 8500
	0    -1   1    0   
$EndComp
Wire Wire Line
	3650 8650 3200 8650
Wire Wire Line
	3650 8350 3500 8350
$Comp
L power:+12V #PWR0109
U 1 1 5E20EA97
P 2250 7900
F 0 "#PWR0109" H 2250 7750 50  0001 C CNN
F 1 "+12V" H 2265 8073 50  0000 C CNN
F 2 "" H 2250 7900 50  0001 C CNN
F 3 "" H 2250 7900 50  0001 C CNN
	1    2250 7900
	1    0    0    -1  
$EndComp
Text Label 3800 8150 2    50   ~ 0
HeatRLY
Wire Wire Line
	2750 7850 2450 7850
Wire Wire Line
	2450 7850 2450 7900
Wire Wire Line
	2450 7900 2250 7900
Wire Wire Line
	15550 7750 15450 7750
Text Label 15550 6850 0    50   ~ 0
TACinput
Wire Wire Line
	15550 6850 15450 6850
$Comp
L Device:R R15
U 1 1 5E2536FE
P 3650 8250
F 0 "R15" H 3720 8296 50  0000 L CNN
F 1 "500" V 3650 8150 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 3580 8250 50  0001 C CNN
F 3 "~" H 3650 8250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 3650 8250 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 3650 8250 50  0001 C CNN "Digi-Key_PN"
	1    3650 8250
	0    1    1    0   
$EndComp
$Comp
L Device:R R16
U 1 1 5E254075
P 3650 9400
F 0 "R16" H 3720 9446 50  0000 L CNN
F 1 "500" H 3720 9355 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 3580 9400 50  0001 C CNN
F 3 "~" H 3650 9400 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 3650 9400 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 3650 9400 50  0001 C CNN "Digi-Key_PN"
	1    3650 9400
	0    1    1    0   
$EndComp
$Comp
L Device:R R17
U 1 1 5E2544CF
P 6650 10050
F 0 "R17" H 6720 10096 50  0000 L CNN
F 1 "500" H 6720 10005 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 6580 10050 50  0001 C CNN
F 3 "~" H 6650 10050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 6650 10050 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 6650 10050 50  0001 C CNN "Digi-Key_PN"
	1    6650 10050
	0    1    1    0   
$EndComp
Wire Wire Line
	3500 8250 3500 8350
Wire Wire Line
	3800 8250 3800 8150
Wire Wire Line
	3500 9400 3500 9500
Wire Wire Line
	3800 9400 3800 9300
Wire Wire Line
	6500 10050 6500 10150
Wire Wire Line
	6800 10050 6800 9950
Wire Wire Line
	15550 7950 15450 7950
$Comp
L Device:R R19
U 1 1 5E18E44A
P 10800 6850
F 0 "R19" H 10870 6896 50  0000 L CNN
F 1 "10K" H 10870 6805 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 10730 6850 50  0001 C CNN
F 3 "~" H 10800 6850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/ESR03EZPJ103/1762722" H 10800 6850 50  0001 C CNN "DK_Detail_Page"
F 5 "RHM10KDCT-ND" H 10800 6850 50  0001 C CNN "Digi-Key_PN"
	1    10800 6850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R18
U 1 1 5E18E6FB
P 10600 6850
F 0 "R18" H 10670 6896 50  0000 L CNN
F 1 "10K" H 10670 6805 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 10530 6850 50  0001 C CNN
F 3 "~" H 10600 6850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/ESR03EZPJ103/1762722" H 10600 6850 50  0001 C CNN "DK_Detail_Page"
F 5 "RHM10KDCT-ND" H 10600 6850 50  0001 C CNN "Digi-Key_PN"
	1    10600 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 6700 10600 6700
Wire Wire Line
	10800 6700 10600 6700
Wire Wire Line
	10800 7000 10800 7050
Wire Wire Line
	11300 7450 11650 7450
Wire Wire Line
	11650 7850 11250 7850
Wire Wire Line
	10600 7100 10600 7000
$Comp
L Device:C C19
U 1 1 5E213BBA
P 11050 8300
F 0 "C19" H 11165 8346 50  0000 L CNN
F 1 "0.1uf film" H 11165 8255 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 11088 8150 50  0001 C CNN
F 3 "~" H 11050 8300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 11050 8300 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 11050 8300 50  0001 C CNN "Digi-Key_PN"
	1    11050 8300
	1    0    0    -1  
$EndComp
Wire Wire Line
	11050 8150 11050 8000
Wire Wire Line
	11050 8000 11600 8000
Wire Wire Line
	11600 8000 11600 8050
Connection ~ 11600 8050
Wire Wire Line
	11600 8050 11650 8050
$Comp
L Device:Fuse F2
U 1 1 5E28B1F1
P 2800 3150
F 0 "F2" V 2603 3150 50  0000 C CNN
F 1 "Fuse1A" V 2694 3150 50  0000 C CNN
F 2 "Resistors_ThroughHole:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2730 3150 50  0001 C CNN
F 3 "~" H 2800 3150 50  0001 C CNN
	1    2800 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	2650 3150 2450 3150
$Comp
L dk_Rectangular-Connectors-Headers-Male-Pins:B5B-XH-A_LF__SN_ J5
U 1 1 5E163883
P 9100 1100
F 0 "J5" V 9341 972 50  0000 R CNN
F 1 "ICSP" V 8950 1250 50  0000 R CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 9300 1300 60  0001 L CNN
F 3 "http://www.jst-mfg.com/product/pdf/eng/eXH.pdf" H 9300 1400 60  0001 L CNN
F 4 "" H 9300 1500 60  0001 L CNN "Digi-Key_PN"
F 5 "B5B-XH-A(LF)(SN)" H 9300 1600 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 9300 1700 60  0001 L CNN "Category"
F 7 "Rectangular Connectors - Headers, Male Pins" H 9300 1800 60  0001 L CNN "Family"
F 8 "http://www.jst-mfg.com/product/pdf/eng/eXH.pdf" H 9300 1900 60  0001 L CNN "DK_Datasheet_Link"
F 9 "" H 9300 2000 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN HEADER VERT 5POS 2.5MM" H 9300 2100 60  0001 L CNN "Description"
F 11 "JST Sales America Inc." H 9300 2200 60  0001 L CNN "Manufacturer"
F 12 "Active" H 9300 2300 60  0001 L CNN "Status"
	1    9100 1100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9000 900  8750 900 
Wire Wire Line
	8750 900  8750 1250
Text Label 8500 1100 2    50   ~ 0
MCLR
Text Label 8500 700  2    50   ~ 0
PGMC
Text Label 8500 800  2    50   ~ 0
PGMD
Wire Wire Line
	9000 1000 8600 1000
Wire Wire Line
	9000 1100 8500 1100
Wire Wire Line
	8500 700  9000 700 
Wire Wire Line
	9000 800  8500 800 
$Comp
L Device:R R22
U 1 1 5E166531
P 15100 8650
F 0 "R22" H 15170 8696 50  0000 L CNN
F 1 "1K" H 15170 8605 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 15030 8650 50  0001 C CNN
F 3 "~" H 15100 8650 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 15100 8650 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 15100 8650 50  0001 C CNN "Digi-Key_PN"
	1    15100 8650
	0    1    1    0   
$EndComp
$Comp
L Device:R R23
U 1 1 5E166AF3
P 15100 8900
F 0 "R23" H 15170 8946 50  0000 L CNN
F 1 "1K" H 15170 8855 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 15030 8900 50  0001 C CNN
F 3 "~" H 15100 8900 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 15100 8900 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 15100 8900 50  0001 C CNN "Digi-Key_PN"
	1    15100 8900
	0    1    1    0   
$EndComp
$Comp
L Device:R R24
U 1 1 5E1672C1
P 15100 9150
F 0 "R24" H 15170 9196 50  0000 L CNN
F 1 "1K" H 15170 9105 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 15030 9150 50  0001 C CNN
F 3 "~" H 15100 9150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 15100 9150 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 15100 9150 50  0001 C CNN "Digi-Key_PN"
	1    15100 9150
	0    1    1    0   
$EndComp
Wire Wire Line
	15250 8650 15500 8650
Wire Wire Line
	15500 8650 15500 8350
Wire Wire Line
	15500 8350 15450 8350
Wire Wire Line
	15250 8900 15550 8900
Wire Wire Line
	15550 8900 15550 8250
Wire Wire Line
	15550 8250 15450 8250
Wire Wire Line
	15250 9150 15600 9150
Wire Wire Line
	15600 9150 15600 8150
Wire Wire Line
	15600 8150 15450 8150
$Comp
L Device:LED D17
U 1 1 5E1A0149
P 14700 8650
F 0 "D17" H 14693 8866 50  0000 C CNN
F 1 "chgDetect" H 14693 8775 50  0000 C CNN
F 2 "LEDs:LED_0603" H 14700 8650 50  0001 C CNN
F 3 "~" H 14700 8650 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/vishay-semiconductor-opto-division/VLMB1310-GS08/2813355" H 14700 8650 50  0001 C CNN "DK_Detail_Page"
F 5 "VLMB1310-GS08CT-ND" H 14700 8650 50  0001 C CNN "Digi-Key_PN"
	1    14700 8650
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D18
U 1 1 5E1A108A
P 14700 8900
F 0 "D18" H 14693 9116 50  0000 C CNN
F 1 "Error" H 14693 9025 50  0000 C CNN
F 2 "LEDs:LED_0603" H 14700 8900 50  0001 C CNN
F 3 "~" H 14700 8900 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/w%C3%BCrth-elektronik/150060RS75000/4489901" H 14700 8900 50  0001 C CNN "DK_Detail_Page"
F 5 "732-4978-1-ND" H 14700 8900 50  0001 C CNN "Digi-Key_PN"
	1    14700 8900
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D19
U 1 1 5E1A1385
P 14700 9150
F 0 "D19" H 14693 9366 50  0000 C CNN
F 1 "CPUact" H 14693 9275 50  0000 C CNN
F 2 "LEDs:LED_0603" H 14700 9150 50  0001 C CNN
F 3 "~" H 14700 9150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/qt-brightek-qtb/QBLP601-IG/4814653" H 14700 9150 50  0001 C CNN "DK_Detail_Page"
F 5 "1516-1055-1-ND" H 14700 9150 50  0001 C CNN "Digi-Key_PN"
	1    14700 9150
	1    0    0    -1  
$EndComp
Wire Wire Line
	14550 9250 14550 9150
Wire Wire Line
	14550 8900 14550 9150
Connection ~ 14550 9150
Wire Wire Line
	14550 8650 14550 8900
Connection ~ 14550 8900
Wire Wire Line
	14850 8650 14950 8650
Wire Wire Line
	14950 8900 14850 8900
Wire Wire Line
	14850 9150 14950 9150
$Comp
L dk_Rectangular-Connectors-Headers-Male-Pins:22-23-2021 J9
U 1 1 5E26187E
P 13250 2000
F 0 "J9" V 13025 2008 50  0000 C CNN
F 1 "key" V 13116 2008 50  0000 C CNN
F 2 "digikey-footprints:PinHeader_1x2_P2.54mm_Drill1.02mm" H 13450 2200 60  0001 L CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 13450 2300 60  0001 L CNN
F 4 "" H 13450 2400 60  0001 L CNN "Digi-Key_PN"
F 5 "22-23-2021" H 13450 2500 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 13450 2600 60  0001 L CNN "Category"
F 7 "Rectangular Connectors - Headers, Male Pins" H 13450 2700 60  0001 L CNN "Family"
F 8 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 13450 2800 60  0001 L CNN "DK_Datasheet_Link"
F 9 "" H 13450 2900 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN HEADER VERT 2POS 2.54MM" H 13450 3000 60  0001 L CNN "Description"
F 11 "Molex" H 13450 3100 60  0001 L CNN "Manufacturer"
F 12 "Active" H 13450 3200 60  0001 L CNN "Status"
	1    13250 2000
	0    1    1    0   
$EndComp
$Comp
L Device:R R28
U 1 1 5E261D22
P 14050 1850
F 0 "R28" H 14120 1896 50  0000 L CNN
F 1 "10K" H 14120 1805 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 13980 1850 50  0001 C CNN
F 3 "~" H 14050 1850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/ESR03EZPJ103/1762722" H 14050 1850 50  0001 C CNN "DK_Detail_Page"
F 5 "RHM10KDCT-ND" H 14050 1850 50  0001 C CNN "Digi-Key_PN"
	1    14050 1850
	1    0    0    -1  
$EndComp
Text Label 10750 1050 0    50   ~ 0
TACinput
$Comp
L Device:R R31
U 1 1 5E2B84BE
P 10650 900
F 0 "R31" H 10720 946 50  0000 L CNN
F 1 "10K" H 10720 855 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 10580 900 50  0001 C CNN
F 3 "~" H 10650 900 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/ESR03EZPJ103/1762722" H 10650 900 50  0001 C CNN "DK_Detail_Page"
F 5 "RHM10KDCT-ND" H 10650 900 50  0001 C CNN "Digi-Key_PN"
	1    10650 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	10750 1050 10650 1050
Wire Wire Line
	10250 950  10100 950 
Connection ~ 10650 1050
$Comp
L dk_Rectangular-Connectors-Headers-Male-Pins:640456-3 J13
U 1 1 5E446C7B
P 10000 1550
F 0 "J13" V 9775 1558 50  0000 C CNN
F 1 "IntBTemp" V 9900 1350 50  0000 C CNN
F 2 "digikey-footprints:PinHeader_1x3_P2.54_Drill1.1mm" H 10200 1750 60  0001 L CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=640456&DocType=Customer+Drawing&DocLang=English" H 10200 1850 60  0001 L CNN
F 4 "" H 10200 1950 60  0001 L CNN "Digi-Key_PN"
F 5 "640456-3" H 10200 2050 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 10200 2150 60  0001 L CNN "Category"
F 7 "Rectangular Connectors - Headers, Male Pins" H 10200 2250 60  0001 L CNN "Family"
F 8 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=640456&DocType=Customer+Drawing&DocLang=English" H 10200 2350 60  0001 L CNN "DK_Datasheet_Link"
F 9 "" H 10200 2450 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN HEADER VERT 3POS 2.54MM" H 10200 2550 60  0001 L CNN "Description"
F 11 "TE Connectivity AMP Connectors" H 10200 2650 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10200 2750 60  0001 L CNN "Status"
	1    10000 1550
	0    1    1    0   
$EndComp
Text Label 10550 1550 0    50   ~ 0
Btemp
Wire Wire Line
	10200 1850 10200 1650
Wire Wire Line
	10200 1650 10100 1650
Wire Wire Line
	10100 1450 10100 1550
$Comp
L Device:R R29
U 1 1 5E474D16
P 10400 1550
F 0 "R29" H 10470 1596 50  0000 L CNN
F 1 "1K" H 10470 1505 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 10330 1550 50  0001 C CNN
F 3 "~" H 10400 1550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 10400 1550 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 10400 1550 50  0001 C CNN "Digi-Key_PN"
	1    10400 1550
	0    1    1    0   
$EndComp
$Comp
L Device:C C20
U 1 1 5E4750EA
P 10550 1700
F 0 "C20" H 10665 1746 50  0000 L CNN
F 1 "0.1uf film" H 10665 1655 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 10588 1550 50  0001 C CNN
F 3 "~" H 10550 1700 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 10550 1700 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 10550 1700 50  0001 C CNN "Digi-Key_PN"
	1    10550 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 1550 10250 1750
Wire Wire Line
	10250 1750 10100 1750
$Comp
L dk_Rectangular-Connectors-Headers-Male-Pins:640456-3 J14
U 1 1 5E4FCF79
P 10000 2250
F 0 "J14" V 9775 2258 50  0000 C CNN
F 1 "ctrlTemp" V 9900 2050 50  0000 C CNN
F 2 "digikey-footprints:PinHeader_1x3_P2.54_Drill1.1mm" H 10200 2450 60  0001 L CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=640456&DocType=Customer+Drawing&DocLang=English" H 10200 2550 60  0001 L CNN
F 4 "" H 10200 2650 60  0001 L CNN "Digi-Key_PN"
F 5 "640456-3" H 10200 2750 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 10200 2850 60  0001 L CNN "Category"
F 7 "Rectangular Connectors - Headers, Male Pins" H 10200 2950 60  0001 L CNN "Family"
F 8 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=640456&DocType=Customer+Drawing&DocLang=English" H 10200 3050 60  0001 L CNN "DK_Datasheet_Link"
F 9 "" H 10200 3150 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN HEADER VERT 3POS 2.54MM" H 10200 3250 60  0001 L CNN "Description"
F 11 "TE Connectivity AMP Connectors" H 10200 3350 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10200 3450 60  0001 L CNN "Status"
	1    10000 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	10200 2550 10200 2350
Wire Wire Line
	10200 2350 10100 2350
Wire Wire Line
	10100 2150 10100 2250
$Comp
L Device:R R30
U 1 1 5E4FCF89
P 10400 2250
F 0 "R30" H 10470 2296 50  0000 L CNN
F 1 "1K" H 10470 2205 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 10330 2250 50  0001 C CNN
F 3 "~" H 10400 2250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 10400 2250 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 10400 2250 50  0001 C CNN "Digi-Key_PN"
	1    10400 2250
	0    1    1    0   
$EndComp
$Comp
L Device:C C21
U 1 1 5E4FCF8F
P 10550 2400
F 0 "C21" H 10665 2446 50  0000 L CNN
F 1 "0.1uf film" H 10665 2355 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 10588 2250 50  0001 C CNN
F 3 "~" H 10550 2400 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 10550 2400 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 10550 2400 50  0001 C CNN "Digi-Key_PN"
	1    10550 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 2250 10250 2450
Wire Wire Line
	10250 2450 10100 2450
Text Label 10550 2250 0    50   ~ 0
cTemp
$Comp
L power:+5C #PWR0129
U 1 1 5E515361
P 12850 5900
F 0 "#PWR0129" H 12850 5750 50  0001 C CNN
F 1 "+5C" H 12865 6073 50  0000 C CNN
F 2 "" H 12850 5900 50  0001 C CNN
F 3 "" H 12850 5900 50  0001 C CNN
	1    12850 5900
	1    0    0    -1  
$EndComp
Connection ~ 12850 5900
Text Label 15550 8050 0    50   ~ 0
brdTemp
Wire Wire Line
	15550 8050 15450 8050
$Comp
L dk_Rectangular-Connectors-Headers-Male-Pins:640456-3 J10
U 1 1 5E5ECD2B
P 13300 750
F 0 "J10" V 13075 758 50  0000 C CNN
F 1 "U1COMMS" V 13200 550 50  0000 C CNN
F 2 "digikey-footprints:PinHeader_1x3_P2.54_Drill1.1mm" H 13500 950 60  0001 L CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=640456&DocType=Customer+Drawing&DocLang=English" H 13500 1050 60  0001 L CNN
F 4 "" H 13500 1150 60  0001 L CNN "Digi-Key_PN"
F 5 "640456-3" H 13500 1250 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 13500 1350 60  0001 L CNN "Category"
F 7 "Rectangular Connectors - Headers, Male Pins" H 13500 1450 60  0001 L CNN "Family"
F 8 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=640456&DocType=Customer+Drawing&DocLang=English" H 13500 1550 60  0001 L CNN "DK_Datasheet_Link"
F 9 "" H 13500 1650 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN HEADER VERT 3POS 2.54MM" H 13500 1750 60  0001 L CNN "Description"
F 11 "TE Connectivity AMP Connectors" H 13500 1850 60  0001 L CNN "Manufacturer"
F 12 "Active" H 13500 1950 60  0001 L CNN "Status"
	1    13300 750 
	0    1    1    0   
$EndComp
$Comp
L dk_Rectangular-Connectors-Headers-Male-Pins:640456-3 J11
U 1 1 5E5ED11B
P 11900 750
F 0 "J11" V 11675 758 50  0000 C CNN
F 1 "U2COMMS" V 11800 550 50  0000 C CNN
F 2 "digikey-footprints:PinHeader_1x3_P2.54_Drill1.1mm" H 12100 950 60  0001 L CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=640456&DocType=Customer+Drawing&DocLang=English" H 12100 1050 60  0001 L CNN
F 4 "" H 12100 1150 60  0001 L CNN "Digi-Key_PN"
F 5 "640456-3" H 12100 1250 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 12100 1350 60  0001 L CNN "Category"
F 7 "Rectangular Connectors - Headers, Male Pins" H 12100 1450 60  0001 L CNN "Family"
F 8 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=640456&DocType=Customer+Drawing&DocLang=English" H 12100 1550 60  0001 L CNN "DK_Datasheet_Link"
F 9 "" H 12100 1650 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN HEADER VERT 3POS 2.54MM" H 12100 1750 60  0001 L CNN "Description"
F 11 "TE Connectivity AMP Connectors" H 12100 1850 60  0001 L CNN "Manufacturer"
F 12 "Active" H 12100 1950 60  0001 L CNN "Status"
	1    11900 750 
	0    1    1    0   
$EndComp
Wire Wire Line
	12200 1050 12200 850 
Wire Wire Line
	12200 850  12000 850 
Wire Wire Line
	13600 1050 13600 850 
Wire Wire Line
	13600 850  13400 850 
Text Label 11550 6850 2    50   ~ 0
U2RX
Text Label 11550 6750 2    50   ~ 0
U2TX
Text Label 15550 7650 0    50   ~ 0
U1TX
Text Label 15550 7350 0    50   ~ 0
U1RX
Wire Wire Line
	11550 6750 11650 6750
Wire Wire Line
	11650 6850 11550 6850
Wire Wire Line
	15550 7350 15450 7350
Wire Wire Line
	15450 7650 15550 7650
Text Label 12550 750  0    50   ~ 0
U1RX
Text Label 12550 950  0    50   ~ 0
U1TX
Text Label 13950 950  0    50   ~ 0
U2TX
Text Label 13950 750  0    50   ~ 0
U2RX
Wire Wire Line
	13650 750  13400 750 
Wire Wire Line
	13650 950  13400 950 
Wire Wire Line
	12250 750  12000 750 
Wire Wire Line
	12250 950  12000 950 
$Comp
L Device:C C22
U 1 1 5E17EEBF
P 7600 1850
F 0 "C22" H 7715 1896 50  0000 L CNN
F 1 "0.1uf film" H 7715 1805 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 7638 1700 50  0001 C CNN
F 3 "~" H 7600 1850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 7600 1850 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 7600 1850 50  0001 C CNN "Digi-Key_PN"
	1    7600 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C23
U 1 1 5E17F868
P 8250 1850
F 0 "C23" H 8365 1896 50  0000 L CNN
F 1 "0.1uf film" H 8365 1805 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 8288 1700 50  0001 C CNN
F 3 "~" H 8250 1850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 8250 1850 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 8250 1850 50  0001 C CNN "Digi-Key_PN"
	1    8250 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R34
U 1 1 5E17FB93
P 8100 1700
F 0 "R34" H 8170 1746 50  0000 L CNN
F 1 "1K" H 8170 1655 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 8030 1700 50  0001 C CNN
F 3 "~" H 8100 1700 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 8100 1700 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 8100 1700 50  0001 C CNN "Digi-Key_PN"
	1    8100 1700
	0    1    1    0   
$EndComp
Text Label 8250 1700 0    50   ~ 0
brdTemp
$Comp
L Device:Q_NMOS_GDS U9
U 1 1 5E1B40A7
P 7700 1450
F 0 "U9" H 7905 1496 50  0000 L CNN
F 1 "LM62CIM3/NOPB" H 7905 1405 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 7900 1550 50  0001 C CNN
F 3 "~" H 7700 1450 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/texas-instruments/LM62CIM3-NOPB/364229" H 7700 1450 50  0001 C CNN "DK_Detail_Page"
F 5 "LM62CIM3/NOPBCT-ND" H 7700 1450 50  0001 C CNN "Digi-Key_PN"
	1    7700 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 1650 7800 2000
Connection ~ 7800 2000
Wire Wire Line
	7800 2000 7600 2000
Wire Wire Line
	7800 1250 7950 1250
Wire Wire Line
	7950 1250 7950 1700
Wire Wire Line
	7600 1700 7500 1700
Wire Wire Line
	7500 1700 7500 1450
$Comp
L Device:D_Schottky_AAK D4
U 1 1 5E18D9F4
P 2450 2200
F 0 "D4" V 2521 2112 50  0000 R CNN
F 1 "D_Schottky_AAK" V 2430 2112 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:TO-277A" H 2450 2200 50  0001 C CNN
F 3 "~" H 2450 2200 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/on-semiconductor/FSV20100V/5306682" H 2450 2200 50  0001 C CNN "DK_Detail_Page"
F 5 "FSV20100VCT-ND" H 2450 2200 50  0001 C CNN "Digi-Key_PN"
	1    2450 2200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2450 2000 2350 2000
$Comp
L Mechanical:MountingHole_Pad H11
U 1 1 5E35B333
P 800 5300
F 0 "H11" V 1037 5303 50  0000 C CNN
F 1 "mnt" V 946 5303 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_2.7mm" H 800 5300 50  0001 C CNN
F 3 "~" H 800 5300 50  0001 C CNN
	1    800  5300
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H10
U 1 1 5E35E333
P 800 7900
F 0 "H10" V 1037 7903 50  0000 C CNN
F 1 "mnt" V 946 7903 50  0000 C CNN
F 2 "Connect:1pin" H 800 7900 50  0001 C CNN
F 3 "~" H 800 7900 50  0001 C CNN
	1    800  7900
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0137
U 1 1 5E35E339
P 900 7900
F 0 "#PWR0137" H 900 7650 50  0001 C CNN
F 1 "GND" H 905 7727 50  0000 C CNN
F 2 "" H 900 7900 50  0001 C CNN
F 3 "" H 900 7900 50  0001 C CNN
	1    900  7900
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H13
U 1 1 5E391307
P 800 8250
F 0 "H13" V 1037 8253 50  0000 C CNN
F 1 "mnt" V 946 8253 50  0000 C CNN
F 2 "Connect:1pin" H 800 8250 50  0001 C CNN
F 3 "~" H 800 8250 50  0001 C CNN
	1    800  8250
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0138
U 1 1 5E39130D
P 900 8250
F 0 "#PWR0138" H 900 8000 50  0001 C CNN
F 1 "GND" H 905 8077 50  0000 C CNN
F 2 "" H 900 8250 50  0001 C CNN
F 3 "" H 900 8250 50  0001 C CNN
	1    900  8250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R35
U 1 1 5E2344E1
P 8050 10000
F 0 "R35" H 8120 10046 50  0000 L CNN
F 1 "1K" H 8120 9955 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 7980 10000 50  0001 C CNN
F 3 "~" H 8050 10000 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 8050 10000 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 8050 10000 50  0001 C CNN "Digi-Key_PN"
	1    8050 10000
	0    1    1    0   
$EndComp
$Comp
L Device:LED D21
U 1 1 5E2348F5
P 7650 10000
F 0 "D21" H 7643 10216 50  0000 C CNN
F 1 "Output" H 7643 10125 50  0000 C CNN
F 2 "LEDs:LED_0603" H 7650 10000 50  0001 C CNN
F 3 "~" H 7650 10000 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/broadcom-limited/HSMA-C120/1235470" H 7650 10000 50  0001 C CNN "DK_Detail_Page"
F 5 "516-2486-1-ND" H 7650 10000 50  0001 C CNN "Digi-Key_PN"
	1    7650 10000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 10000 7800 10000
Text Label 8200 9900 0    50   ~ 0
Mctrl+
Wire Wire Line
	8200 9900 8200 10000
Connection ~ 10600 6700
Connection ~ 7500 10700
Wire Wire Line
	7500 10700 7500 10800
Connection ~ 7500 10350
Wire Wire Line
	7500 10350 7500 10700
Wire Wire Line
	7500 10000 7500 10350
Wire Wire Line
	8200 10600 8200 10700
Wire Wire Line
	8200 10350 8200 10250
Text Label 8200 10600 0    50   ~ 0
CHctrl
Text Label 8200 10250 0    50   ~ 0
Hctrl
Wire Wire Line
	7900 10350 7800 10350
$Comp
L Device:R R36
U 1 1 5E1AADBB
P 8050 10350
F 0 "R36" H 8120 10396 50  0000 L CNN
F 1 "1K" H 8120 10305 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 7980 10350 50  0001 C CNN
F 3 "~" H 8050 10350 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 8050 10350 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 8050 10350 50  0001 C CNN "Digi-Key_PN"
	1    8050 10350
	0    1    1    0   
$EndComp
$Comp
L Device:LED D22
U 1 1 5E1AABB8
P 7650 10350
F 0 "D22" H 7643 10566 50  0000 C CNN
F 1 "Heat" H 7643 10475 50  0000 C CNN
F 2 "LEDs:LED_0603" H 7650 10350 50  0001 C CNN
F 3 "~" H 7650 10350 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/broadcom-limited/HSMA-C120/1235470" H 7650 10350 50  0001 C CNN "DK_Detail_Page"
F 5 "516-2486-1-ND" H 7650 10350 50  0001 C CNN "Digi-Key_PN"
	1    7650 10350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 10700 7900 10700
$Comp
L Device:LED D23
U 1 1 5E1912F0
P 7650 10700
F 0 "D23" H 7643 10916 50  0000 C CNN
F 1 "Charge" H 7643 10825 50  0000 C CNN
F 2 "LEDs:LED_0603" H 7650 10700 50  0001 C CNN
F 3 "~" H 7650 10700 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/broadcom-limited/HSMA-C120/1235470" H 7650 10700 50  0001 C CNN "DK_Detail_Page"
F 5 "516-2486-1-ND" H 7650 10700 50  0001 C CNN "Digi-Key_PN"
	1    7650 10700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R37
U 1 1 5E1912EA
P 8050 10700
F 0 "R37" H 8120 10746 50  0000 L CNN
F 1 "1K" H 8120 10655 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 7980 10700 50  0001 C CNN
F 3 "~" H 8050 10700 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 8050 10700 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 8050 10700 50  0001 C CNN "Digi-Key_PN"
	1    8050 10700
	0    1    1    0   
$EndComp
$Comp
L dk_Rectangular-Connectors-Headers-Male-Pins:22-23-2021 J15
U 1 1 5E19537D
P 12350 1700
F 0 "J15" V 12400 1500 50  0000 C CNN
F 1 "12Vout" V 12550 1600 50  0000 C CNN
F 2 "digikey-footprints:PinHeader_1x2_P2.54mm_Drill1.02mm" H 12550 1900 60  0001 L CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 12550 2000 60  0001 L CNN
F 4 "" H 12550 2100 60  0001 L CNN "Digi-Key_PN"
F 5 "22-23-2021" H 12550 2200 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 12550 2300 60  0001 L CNN "Category"
F 7 "Rectangular Connectors - Headers, Male Pins" H 12550 2400 60  0001 L CNN "Family"
F 8 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 12550 2500 60  0001 L CNN "DK_Datasheet_Link"
F 9 "" H 12550 2600 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN HEADER VERT 2POS 2.54MM" H 12550 2700 60  0001 L CNN "Description"
F 11 "Molex" H 12550 2800 60  0001 L CNN "Manufacturer"
F 12 "Active" H 12550 2900 60  0001 L CNN "Status"
	1    12350 1700
	0    1    1    0   
$EndComp
$Comp
L power:+12V #PWR0140
U 1 1 5E195B37
P 12450 1700
F 0 "#PWR0140" H 12450 1550 50  0001 C CNN
F 1 "+12V" H 12465 1873 50  0000 C CNN
F 2 "" H 12450 1700 50  0001 C CNN
F 3 "" H 12450 1700 50  0001 C CNN
	1    12450 1700
	1    0    0    -1  
$EndComp
$Comp
L dk_Rectangular-Connectors-Headers-Male-Pins:22-23-2021 J16
U 1 1 5E19CBFB
P 11700 1700
F 0 "J16" V 11750 1500 50  0000 C CNN
F 1 "12Vin" V 11900 1550 50  0000 C CNN
F 2 "digikey-footprints:PinHeader_1x2_P2.54mm_Drill1.02mm" H 11900 1900 60  0001 L CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 11900 2000 60  0001 L CNN
F 4 "" H 11900 2100 60  0001 L CNN "Digi-Key_PN"
F 5 "22-23-2021" H 11900 2200 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 11900 2300 60  0001 L CNN "Category"
F 7 "Rectangular Connectors - Headers, Male Pins" H 11900 2400 60  0001 L CNN "Family"
F 8 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 11900 2500 60  0001 L CNN "DK_Datasheet_Link"
F 9 "" H 11900 2600 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN HEADER VERT 2POS 2.54MM" H 11900 2700 60  0001 L CNN "Description"
F 11 "Molex" H 11900 2800 60  0001 L CNN "Manufacturer"
F 12 "Active" H 11900 2900 60  0001 L CNN "Status"
	1    11700 1700
	0    1    1    0   
$EndComp
$Comp
L power:+12V #PWR0142
U 1 1 5E19E2BB
P 11800 1400
F 0 "#PWR0142" H 11800 1250 50  0001 C CNN
F 1 "+12V" H 11815 1573 50  0000 C CNN
F 2 "" H 11800 1400 50  0001 C CNN
F 3 "" H 11800 1400 50  0001 C CNN
	1    11800 1400
	1    0    0    -1  
$EndComp
Text Label 4500 3900 0    50   ~ 0
BCsense
Connection ~ 4250 3900
Wire Wire Line
	4500 3900 4250 3900
Wire Wire Line
	4050 3900 4250 3900
$Comp
L Device:R R11
U 1 1 5E13939D
P 3900 3900
F 0 "R11" H 3970 3946 50  0000 L CNN
F 1 "1K" H 3970 3855 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 3830 3900 50  0001 C CNN
F 3 "~" H 3900 3900 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 3900 3900 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 3900 3900 50  0001 C CNN "Digi-Key_PN"
	1    3900 3900
	0    1    1    0   
$EndComp
$Comp
L Device:C C12
U 1 1 5E137C0E
P 4250 4050
F 0 "C12" H 4365 4096 50  0000 L CNN
F 1 "1uf 25v" H 4365 4005 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 4288 3900 50  0001 C CNN
F 3 "~" H 4250 4050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10A105KA8NNNC/3886760" H 4250 4050 50  0001 C CNN "DK_Detail_Page"
F 5 "1276-1102-1-ND" H 4250 4050 50  0001 C CNN "Digi-Key_PN"
	1    4250 4050
	1    0    0    -1  
$EndComp
Connection ~ 8400 4400
$Comp
L power:GND #PWR030
U 1 1 5E81B91D
P 8400 4400
F 0 "#PWR030" H 8400 4150 50  0001 C CNN
F 1 "GND" H 8300 4300 50  0000 C CNN
F 2 "" H 8400 4400 50  0001 C CNN
F 3 "" H 8400 4400 50  0001 C CNN
	1    8400 4400
	1    0    0    -1  
$EndComp
Text Label 9700 4100 0    50   ~ 0
IntBus
$Comp
L Device:L L2
U 1 1 5E84078C
P 1700 2700
F 0 "L2" H 1657 2654 50  0000 R CNN
F 1 "4.7uH" H 1657 2745 50  0000 R CNN
F 2 "Inductors:Inductor_Wurth_HCI-1890" H 1700 2700 50  0001 C CNN
F 3 "~" H 1700 2700 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/bourns-inc/SRP1770TA-4R7M/5429645" H 1700 2700 50  0001 C CNN "DK_Detail_Page"
F 5 "SRP1770TA-4R7MCT-ND" H 1700 2700 50  0001 C CNN "Digi-Key_PN"
	1    1700 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	2800 600  2800 800 
Wire Wire Line
	3300 600  3300 800 
$Comp
L Device:D_Zener D26
U 1 1 5E8CF4C1
P 3050 800
F 0 "D26" V 3000 650 50  0000 L CNN
F 1 "15V" V 3150 600 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 3050 800 50  0001 C CNN
F 3 "~" H 3050 800 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 3050 800 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 3050 800 50  0001 C CNN "Digi-Key_PN"
	1    3050 800 
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 800  3300 800 
Connection ~ 3300 800 
Wire Wire Line
	2900 800  2800 800 
Connection ~ 2800 800 
$Comp
L Device:D_Schottky_AAK D10
U 1 1 5E916BFB
P 2050 2450
F 0 "D10" V 2121 2362 50  0000 R CNN
F 1 "D_Schottky_AAK" H 2100 2600 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:TO-277A" H 2050 2450 50  0001 C CNN
F 3 "~" H 2050 2450 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/on-semiconductor/FSV20100V/5306682" H 2050 2450 50  0001 C CNN "DK_Detail_Page"
F 5 "FSV20100VCT-ND" H 2050 2450 50  0001 C CNN "Digi-Key_PN"
	1    2050 2450
	-1   0    0    1   
$EndComp
Wire Wire Line
	2450 2350 2450 2450
Wire Wire Line
	2200 2450 2450 2450
Wire Wire Line
	1850 2450 1850 2550
Wire Wire Line
	1850 2450 1700 2450
Wire Wire Line
	1700 2450 1700 2550
Connection ~ 1850 2450
Wire Wire Line
	1700 2000 1700 2450
Connection ~ 1700 2450
Text Label 8000 5900 2    50   ~ 0
BC-
Connection ~ 8400 4900
Text Label 9700 4600 0    50   ~ 0
IntBus
Text Label 9700 6150 0    50   ~ 0
M+
Text Label 8000 6450 2    50   ~ 0
M-
$Comp
L Device:CP C14
U 1 1 5EAB2684
P 7250 4250
F 0 "C14" H 7365 4296 50  0000 L CNN
F 1 "10uf 100v" H 7150 4550 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 7288 4100 50  0001 C CNN
F 3 "~" H 7250 4250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 7250 4250 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 7250 4250 50  0001 C CNN "Digi-Key_PN"
	1    7250 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:L L1
U 1 1 5EAB8C7C
P 1650 5250
F 0 "L1" H 1607 5204 50  0000 R CNN
F 1 "4.7uH" H 1950 5200 50  0000 R CNN
F 2 "Inductors:Inductor_Wurth_HCI-1890" H 1650 5250 50  0001 C CNN
F 3 "~" H 1650 5250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/bourns-inc/SRP1770TA-4R7M/5429645" H 1650 5250 50  0001 C CNN "DK_Detail_Page"
F 5 "SRP1770TA-4R7MCT-ND" H 1650 5250 50  0001 C CNN "Digi-Key_PN"
	1    1650 5250
	-1   0    0    1   
$EndComp
$Comp
L Device:D_Schottky_AAK D9
U 1 1 5EAEAED8
P 1650 5900
F 0 "D9" V 1700 5750 50  0000 R CNN
F 1 "D_Schottky_AAK" V 1600 5800 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:TO-277A" H 1650 5900 50  0001 C CNN
F 3 "~" H 1650 5900 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/on-semiconductor/FSV20100V/5306682" H 1650 5900 50  0001 C CNN "DK_Detail_Page"
F 5 "FSV20100VCT-ND" H 1650 5900 50  0001 C CNN "Digi-Key_PN"
	1    1650 5900
	0    1    1    0   
$EndComp
Wire Wire Line
	1950 5300 1950 5400
Text Label 9700 6700 0    50   ~ 0
CH+
Text Label 8850 7000 2    50   ~ 0
CH-
Wire Wire Line
	7600 2850 7700 2850
Wire Wire Line
	7300 2850 7250 2850
$Comp
L Device:R R32
U 1 1 5E4946D0
P 7450 2850
F 0 "R32" H 7300 2900 50  0000 L CNN
F 1 "3" H 7350 2800 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 7380 2850 50  0001 C CNN
F 3 "~" H 7450 2850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/SDR03EZPJ3R0/9675019" H 7450 2850 50  0001 C CNN "DK_Detail_Page"
F 5 "511-1769-1-ND" H 7450 2850 50  0001 C CNN "Digi-Key_PN"
	1    7450 2850
	0    1    1    0   
$EndComp
Connection ~ 10450 3450
Connection ~ 10450 3150
Connection ~ 8250 3450
Wire Wire Line
	8000 3450 8250 3450
Connection ~ 8250 3150
$Comp
L Device:R R33
U 1 1 5E70C0C9
P 8250 3300
F 0 "R33" H 8320 3346 50  0000 L CNN
F 1 "10K" H 8320 3255 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 8180 3300 50  0001 C CNN
F 3 "~" H 8250 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/ESR03EZPJ103/1762722" H 8250 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "RHM10KDCT-ND" H 8250 3300 50  0001 C CNN "Digi-Key_PN"
	1    8250 3300
	1    0    0    -1  
$EndComp
Connection ~ 6550 3150
$Comp
L Device:R R20
U 1 1 5E66D72A
P 6550 3300
F 0 "R20" H 6620 3346 50  0000 L CNN
F 1 "10K" H 6620 3255 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 6480 3300 50  0001 C CNN
F 3 "~" H 6550 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/ESR03EZPJ103/1762722" H 6550 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "RHM10KDCT-ND" H 6550 3300 50  0001 C CNN "Digi-Key_PN"
	1    6550 3300
	1    0    0    -1  
$EndComp
Connection ~ 5950 3450
Connection ~ 5950 3150
Connection ~ 3950 3150
Wire Wire Line
	3950 3300 3950 3150
$Comp
L Device:R R9
U 1 1 5E4FA364
P 3800 3300
F 0 "R9" H 3650 3350 50  0000 L CNN
F 1 "3" H 3700 3250 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 3730 3300 50  0001 C CNN
F 3 "~" H 3800 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/SDR03EZPJ3R0/9675019" H 3800 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "511-1769-1-ND" H 3800 3300 50  0001 C CNN "Digi-Key_PN"
	1    3800 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	7250 2850 7250 3150
Wire Wire Line
	7700 2850 7700 3150
Connection ~ 7700 3150
$Comp
L Device:CP C66
U 1 1 5F428456
P 10750 3300
F 0 "C66" H 10750 3550 50  0000 L CNN
F 1 "10uf 25v" H 10600 2850 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 10788 3150 50  0001 C CNN
F 3 "~" H 10750 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 10750 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 10750 3300 50  0001 C CNN "Digi-Key_PN"
	1    10750 3300
	1    0    0    -1  
$EndComp
Connection ~ 7250 3150
Wire Wire Line
	7300 3150 7250 3150
Wire Wire Line
	7700 3150 7600 3150
Wire Wire Line
	10750 3450 10450 3450
Wire Wire Line
	10750 3150 10450 3150
$Comp
L Device:C C65
U 1 1 5E54CC2E
P 10450 3300
F 0 "C65" H 10450 3000 50  0000 L CNN
F 1 "0.1uf film" H 10350 3600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 10488 3150 50  0001 C CNN
F 3 "~" H 10450 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 10450 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 10450 3300 50  0001 C CNN "Digi-Key_PN"
	1    10450 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C41
U 1 1 5E510B5F
P 7700 3300
F 0 "C41" H 7700 3550 50  0000 L CNN
F 1 "10uf 25v" H 7650 3050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7738 3150 50  0001 C CNN
F 3 "~" H 7700 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 7700 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 7700 3300 50  0001 C CNN "Digi-Key_PN"
	1    7700 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:L L3
U 1 1 5E45FF37
P 3800 3150
F 0 "L3" V 3619 3150 50  0000 C CNN
F 1 "10uH" V 3710 3150 50  0000 C CNN
F 2 "Inductors:Inductor_Wurth_HCI-5040" H 3800 3150 50  0001 C CNN
F 3 "~" H 3800 3150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/w%C3%BCrth-elektronik/74404054100/4865412" H 3800 3150 50  0001 C CNN "DK_Detail_Page"
F 5 "732-5519-1-ND" H 3800 3150 50  0001 C CNN "Digi-Key_PN"
	1    3800 3150
	0    1    1    0   
$EndComp
$Comp
L Device:L L4
U 1 1 5E45F711
P 7450 3150
F 0 "L4" V 7269 3150 50  0000 C CNN
F 1 "10uH" V 7360 3150 50  0000 C CNN
F 2 "Inductors:Inductor_Wurth_HCI-5040" H 7450 3150 50  0001 C CNN
F 3 "~" H 7450 3150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/w%C3%BCrth-elektronik/74404054100/4865412" H 7450 3150 50  0001 C CNN "DK_Detail_Page"
F 5 "732-5519-1-ND" H 7450 3150 50  0001 C CNN "Digi-Key_PN"
	1    7450 3150
	0    1    1    0   
$EndComp
Connection ~ 7250 3450
Wire Wire Line
	7250 3450 7700 3450
Wire Wire Line
	7250 3450 6900 3450
Wire Wire Line
	6900 3150 7250 3150
$Comp
L Device:CP C34
U 1 1 5E3CE0E3
P 7250 3300
F 0 "C34" H 7200 3550 50  0000 L CNN
F 1 "10uf 25v" H 7150 3050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7288 3150 50  0001 C CNN
F 3 "~" H 7250 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 7250 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 7250 3300 50  0001 C CNN "Digi-Key_PN"
	1    7250 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 3150 5750 3150
$Comp
L Device:C C10
U 1 1 5E1D637A
P 5950 3300
F 0 "C10" H 6065 3346 50  0000 L CNN
F 1 "1uf 25v" H 5850 3600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5988 3150 50  0001 C CNN
F 3 "~" H 5950 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10A105KA8NNNC/3886760" H 5950 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "1276-1102-1-ND" H 5950 3300 50  0001 C CNN "Digi-Key_PN"
	1    5950 3300
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR017
U 1 1 5E1367BC
P 6900 3150
F 0 "#PWR017" H 6900 3000 50  0001 C CNN
F 1 "+12V" H 6915 3323 50  0000 C CNN
F 2 "" H 6900 3150 50  0001 C CNN
F 3 "" H 6900 3150 50  0001 C CNN
	1    6900 3150
	1    0    0    -1  
$EndComp
Connection ~ 9800 3150
$Comp
L power:+5V #PWR022
U 1 1 5E1360D8
P 9800 3150
F 0 "#PWR022" H 9800 3000 50  0001 C CNN
F 1 "+5V" H 9815 3323 50  0000 C CNN
F 2 "" H 9800 3150 50  0001 C CNN
F 3 "" H 9800 3150 50  0001 C CNN
	1    9800 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 5E135921
P 2700 3450
F 0 "#PWR023" H 2700 3200 50  0001 C CNN
F 1 "GND" H 2705 3277 50  0000 C CNN
F 2 "" H 2700 3450 50  0001 C CNN
F 3 "" H 2700 3450 50  0001 C CNN
	1    2700 3450
	1    0    0    -1  
$EndComp
Connection ~ 9250 3450
Wire Wire Line
	9800 3150 9550 3150
Connection ~ 5450 3450
Wire Wire Line
	5450 3450 5950 3450
$Comp
L dk_PMIC-Voltage-Regulators-Linear:L7805CV U6
U 1 1 5E126388
P 9250 3150
F 0 "U6" H 9250 3437 60  0000 C CNN
F 1 "L7805CV" H 9250 3331 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:TO-263-2" H 9450 3350 60  0001 L CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 9450 3450 60  0001 L CNN
F 4 "MC7805CD2TR4GOSCT-ND" H 9450 3550 60  0001 L CNN "Digi-Key_PN"
F 5 "L7805CV" H 9450 3650 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 9450 3750 60  0001 L CNN "Category"
F 7 "PMIC - Voltage Regulators - Linear" H 9450 3850 60  0001 L CNN "Family"
F 8 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 9450 3950 60  0001 L CNN "DK_Datasheet_Link"
F 9 "https://www.digikey.com/en/products/detail/on-semiconductor/MC7805CD2TR4G/919332" H 9450 4050 60  0001 L CNN "DK_Detail_Page"
F 10 "IC REG LINEAR 5V 1.5A TO220AB" H 9450 4150 60  0001 L CNN "Description"
F 11 "STMicroelectronics" H 9450 4250 60  0001 L CNN "Manufacturer"
F 12 "Active" H 9450 4350 60  0001 L CNN "Status"
	1    9250 3150
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM7812_TO220 U1
U 1 1 5E12387F
P 5450 3150
F 0 "U1" H 5450 3300 50  0000 C CNN
F 1 "R-78HB12-0.5" H 5350 3400 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220-3_Horizontal" H 5500 2900 50  0001 L CIN
F 3 "https://www.recom-power.com/pdf/Innoline/R-78HBxx-0.5_L.pdf" H 5450 3150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/recom-power/R-78HB12-0.5-W/5765380" H 5450 3150 50  0001 C CNN "DK_Detail_Page"
F 5 "945-2445-ND" H 5450 3150 50  0001 C CNN "Digi-Key_PN"
	1    5450 3150
	1    0    0    -1  
$EndComp
Connection ~ 1400 3450
Wire Wire Line
	3650 3300 3650 3150
Text Label 8000 7550 2    50   ~ 0
BP-
Text Label 9700 7250 0    50   ~ 0
B+
Connection ~ 2700 3450
Wire Wire Line
	12350 6200 12600 6200
Wire Wire Line
	7800 2000 8250 2000
Wire Wire Line
	10350 1050 10100 1050
Wire Wire Line
	10250 1100 10250 950 
$Comp
L Device:Q_NMOS_GDS Q8
U 1 1 5E9DA212
P 2050 5100
F 0 "Q8" H 2254 5146 50  0000 L CNN
F 1 "PSMN5R6-100BS" H 2000 5400 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:TO-263-2" H 2250 5200 50  0001 C CNN
F 3 "~" H 2050 5100 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/nexperia-usa-inc/PSMN5R6-100BS-118/3131570" H 2050 5100 50  0001 C CNN "DK_Detail_Page"
F 5 "1727-7125-1-ND" H 2050 5100 50  0001 C CNN "Digi-Key_PN"
	1    2050 5100
	-1   0    0    -1  
$EndComp
$Comp
L Device:D_Zener D24
U 1 1 5EA52374
P 2250 5250
F 0 "D24" V 2204 5329 50  0000 L CNN
F 1 "15V" V 2295 5329 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 2250 5250 50  0001 C CNN
F 3 "~" H 2250 5250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 2250 5250 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 2250 5250 50  0001 C CNN "Digi-Key_PN"
	1    2250 5250
	0    -1   1    0   
$EndComp
Connection ~ 1950 5400
Wire Wire Line
	1650 5100 1650 4350
Wire Wire Line
	1650 4350 1400 4350
Connection ~ 1400 4350
Connection ~ 1650 5400
Wire Wire Line
	1650 6100 1650 6200
Wire Wire Line
	1650 6200 1750 6200
Wire Wire Line
	1750 6100 1750 6200
Connection ~ 1750 6200
Wire Wire Line
	1750 6200 1950 6200
$Comp
L power:GND #PWR03
U 1 1 5EC382C3
P 1400 4700
F 0 "#PWR03" H 1400 4450 50  0001 C CNN
F 1 "GND" H 1405 4527 50  0000 C CNN
F 2 "" H 1400 4700 50  0001 C CNN
F 3 "" H 1400 4700 50  0001 C CNN
	1    1400 4700
	1    0    0    -1  
$EndComp
Connection ~ 1400 4700
$Comp
L Device:C C1
U 1 1 5EE1AACE
P 3600 5600
F 0 "C1" H 3450 5700 50  0000 L CNN
F 1 "1uf 25v" H 3600 5350 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3638 5450 50  0001 C CNN
F 3 "~" H 3600 5600 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10A105KA8NNNC/3886760" H 3600 5600 50  0001 C CNN "DK_Detail_Page"
F 5 "1276-1102-1-ND" H 3600 5600 50  0001 C CNN "Digi-Key_PN"
	1    3600 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 6200 1950 6200
Connection ~ 1950 6200
Wire Wire Line
	1950 6100 1950 6200
Wire Wire Line
	2250 5400 1950 5400
$Comp
L Device:R R5
U 1 1 5EB07628
P 2400 5650
F 0 "R5" V 2300 5650 50  0000 L CNN
F 1 "6" V 2400 5600 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 2330 5650 50  0001 C CNN
F 3 "~" H 2400 5650 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/yageo/RC0603FR-076R04L/727316" H 2400 5650 50  0001 C CNN "DK_Detail_Page"
F 5 "311-6.04HRCT-ND" H 2400 5650 50  0001 C CNN "Digi-Key_PN"
	1    2400 5650
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 5EB07B58
P 2400 4850
F 0 "R3" V 2300 4850 50  0000 L CNN
F 1 "12" V 2400 4800 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 2330 4850 50  0001 C CNN
F 3 "~" H 2400 4850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ERJ-UP3J120V/12139275" H 2400 4850 50  0001 C CNN "DK_Detail_Page"
F 5 "10-ERJ-UP3J120VCT-ND" H 2400 4850 50  0001 C CNN "Digi-Key_PN"
	1    2400 4850
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 3450 2700 3450
Wire Wire Line
	1300 3150 1400 3150
Wire Wire Line
	850  3100 1400 3100
Wire Wire Line
	1700 2850 1700 3100
Wire Wire Line
	1700 3100 1400 3100
Connection ~ 1400 3100
Wire Wire Line
	3600 5400 3600 5450
Wire Wire Line
	3600 5750 3600 5900
Wire Wire Line
	3600 5900 3450 5900
$Comp
L power:GND #PWR015
U 1 1 5ECF520D
P 3750 5650
F 0 "#PWR015" H 3750 5400 50  0001 C CNN
F 1 "GND" H 3850 5700 50  0000 C CNN
F 2 "" H 3750 5650 50  0001 C CNN
F 3 "" H 3750 5650 50  0001 C CNN
	1    3750 5650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 5ECF5915
P 3650 7450
F 0 "#PWR014" H 3650 7200 50  0001 C CNN
F 1 "GND" H 3655 7277 50  0000 C CNN
F 2 "" H 3650 7450 50  0001 C CNN
F 3 "" H 3650 7450 50  0001 C CNN
	1    3650 7450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5ECF5DD1
P 3200 8650
F 0 "#PWR08" H 3200 8400 50  0001 C CNN
F 1 "GND" H 3205 8477 50  0000 C CNN
F 2 "" H 3200 8650 50  0001 C CNN
F 3 "" H 3200 8650 50  0001 C CNN
	1    3200 8650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5ECF6363
P 3200 9800
F 0 "#PWR010" H 3200 9550 50  0001 C CNN
F 1 "GND" H 3205 9627 50  0000 C CNN
F 2 "" H 3200 9800 50  0001 C CNN
F 3 "" H 3200 9800 50  0001 C CNN
	1    3200 9800
	1    0    0    -1  
$EndComp
Connection ~ 3200 9800
$Comp
L power:GND #PWR011
U 1 1 5ECF65DF
P 6200 10450
F 0 "#PWR011" H 6200 10200 50  0001 C CNN
F 1 "GND" H 6205 10277 50  0000 C CNN
F 2 "" H 6200 10450 50  0001 C CNN
F 3 "" H 6200 10450 50  0001 C CNN
	1    6200 10450
	1    0    0    -1  
$EndComp
Connection ~ 6200 10450
$Comp
L power:GND #PWR032
U 1 1 5ECF6E15
P 7500 10800
F 0 "#PWR032" H 7500 10550 50  0001 C CNN
F 1 "GND" H 7505 10627 50  0000 C CNN
F 2 "" H 7500 10800 50  0001 C CNN
F 3 "" H 7500 10800 50  0001 C CNN
	1    7500 10800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR036
U 1 1 5ECF7348
P 11050 8450
F 0 "#PWR036" H 11050 8200 50  0001 C CNN
F 1 "GND" H 11055 8277 50  0000 C CNN
F 2 "" H 11050 8450 50  0001 C CNN
F 3 "" H 11050 8450 50  0001 C CNN
	1    11050 8450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR044
U 1 1 5ECF7AE1
P 13400 8950
F 0 "#PWR044" H 13400 8700 50  0001 C CNN
F 1 "GND" H 13405 8777 50  0000 C CNN
F 2 "" H 13400 8950 50  0001 C CNN
F 3 "" H 13400 8950 50  0001 C CNN
	1    13400 8950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR041
U 1 1 5ECF7E3D
P 12100 6200
F 0 "#PWR041" H 12100 5950 50  0001 C CNN
F 1 "GND" H 12105 6027 50  0000 C CNN
F 2 "" H 12100 6200 50  0001 C CNN
F 3 "" H 12100 6200 50  0001 C CNN
	1    12100 6200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR048
U 1 1 5ECF7FE5
P 14550 9250
F 0 "#PWR048" H 14550 9000 50  0001 C CNN
F 1 "GND" H 14555 9077 50  0000 C CNN
F 2 "" H 14550 9250 50  0001 C CNN
F 3 "" H 14550 9250 50  0001 C CNN
	1    14550 9250
	1    0    0    -1  
$EndComp
Wire Wire Line
	13600 8800 13700 8800
Connection ~ 13600 8800
Wire Wire Line
	13500 8800 13600 8800
Wire Wire Line
	13400 8800 13500 8800
Connection ~ 13500 8800
Wire Wire Line
	13400 6200 13500 6200
Connection ~ 13500 6200
Wire Wire Line
	13700 6200 13600 6200
Wire Wire Line
	13500 6200 13600 6200
Connection ~ 13600 6200
Connection ~ 13400 6200
Connection ~ 13400 8800
$Comp
L BTMS-rescue:dsPIC30F3011-PT-dspic U8
U 1 1 5E12A7C4
P 13550 7500
F 0 "U8" H 12650 8600 50  0000 C CNN
F 1 "dsPIC30F3011-PT" H 14150 8600 50  0000 C CNN
F 2 "digikey-footprints:TQFP-44_10x10mm" H 15000 8550 60  0001 C CNN
F 3 "" H 13550 7500 50  0001 C CNN
F 4 "Microchip" H 14950 6450 50  0001 C CNN "Manufacturer"
F 5 "https://www.digikey.com/en/products/detail/microchip-technology/DSPIC30F3011-30I-PT/718173" H 13550 7500 50  0001 C CNN "DK_Detail_Page"
F 6 "DSPIC30F301130IPT-ND" H 13550 7500 50  0001 C CNN "Digi-Key_PN"
	1    13550 7500
	1    0    0    -1  
$EndComp
Connection ~ 12100 6200
$Comp
L power:GND #PWR040
U 1 1 5ECFBAFE
P 10750 3450
F 0 "#PWR040" H 10750 3200 50  0001 C CNN
F 1 "GND" H 10755 3277 50  0000 C CNN
F 2 "" H 10750 3450 50  0001 C CNN
F 3 "" H 10750 3450 50  0001 C CNN
	1    10750 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 2550 10400 2550
$Comp
L power:GND #PWR039
U 1 1 5ECFC97E
P 10400 2550
F 0 "#PWR039" H 10400 2300 50  0001 C CNN
F 1 "GND" H 10405 2377 50  0000 C CNN
F 2 "" H 10400 2550 50  0001 C CNN
F 3 "" H 10400 2550 50  0001 C CNN
	1    10400 2550
	1    0    0    -1  
$EndComp
Connection ~ 10400 2550
Wire Wire Line
	10400 2550 10550 2550
$Comp
L power:GND #PWR034
U 1 1 5ECFCB57
P 13600 1050
F 0 "#PWR034" H 13600 800 50  0001 C CNN
F 1 "GND" H 13605 877 50  0000 C CNN
F 2 "" H 13600 1050 50  0001 C CNN
F 3 "" H 13600 1050 50  0001 C CNN
	1    13600 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR031
U 1 1 5ECFCEEB
P 7800 2000
F 0 "#PWR031" H 7800 1750 50  0001 C CNN
F 1 "GND" H 7805 1827 50  0000 C CNN
F 2 "" H 7800 2000 50  0001 C CNN
F 3 "" H 7800 2000 50  0001 C CNN
	1    7800 2000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR028
U 1 1 5ECFD4A6
P 5350 1650
F 0 "#PWR028" H 5350 1400 50  0001 C CNN
F 1 "GND" H 5355 1477 50  0000 C CNN
F 2 "" H 5350 1650 50  0001 C CNN
F 3 "" H 5350 1650 50  0001 C CNN
	1    5350 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR027
U 1 1 5ECFD657
P 5050 2700
F 0 "#PWR027" H 5050 2450 50  0001 C CNN
F 1 "GND" H 5055 2527 50  0000 C CNN
F 2 "" H 5050 2700 50  0001 C CNN
F 3 "" H 5050 2700 50  0001 C CNN
	1    5050 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR033
U 1 1 5ECFE129
P 8750 1250
F 0 "#PWR033" H 8750 1000 50  0001 C CNN
F 1 "GND" H 8755 1077 50  0000 C CNN
F 2 "" H 8750 1250 50  0001 C CNN
F 3 "" H 8750 1250 50  0001 C CNN
	1    8750 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 1850 10400 1850
$Comp
L power:GND #PWR038
U 1 1 5ECFE398
P 10400 1850
F 0 "#PWR038" H 10400 1600 50  0001 C CNN
F 1 "GND" H 10405 1677 50  0000 C CNN
F 2 "" H 10400 1850 50  0001 C CNN
F 3 "" H 10400 1850 50  0001 C CNN
	1    10400 1850
	1    0    0    -1  
$EndComp
Connection ~ 10400 1850
Wire Wire Line
	10400 1850 10550 1850
$Comp
L power:GND #PWR037
U 1 1 5ECFE63B
P 10250 1100
F 0 "#PWR037" H 10250 850 50  0001 C CNN
F 1 "GND" H 10255 927 50  0000 C CNN
F 2 "" H 10250 1100 50  0001 C CNN
F 3 "" H 10250 1100 50  0001 C CNN
	1    10250 1100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR042
U 1 1 5ECFE926
P 12200 1050
F 0 "#PWR042" H 12200 800 50  0001 C CNN
F 1 "GND" H 12205 877 50  0000 C CNN
F 2 "" H 12200 1050 50  0001 C CNN
F 3 "" H 12200 1050 50  0001 C CNN
	1    12200 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR043
U 1 1 5ECFEC63
P 11800 1800
F 0 "#PWR043" H 11800 1550 50  0001 C CNN
F 1 "GND" H 11805 1627 50  0000 C CNN
F 2 "" H 11800 1800 50  0001 C CNN
F 3 "" H 11800 1800 50  0001 C CNN
	1    11800 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR045
U 1 1 5ECFEF31
P 12450 1800
F 0 "#PWR045" H 12450 1550 50  0001 C CNN
F 1 "GND" H 12455 1627 50  0000 C CNN
F 2 "" H 12450 1800 50  0001 C CNN
F 3 "" H 12450 1800 50  0001 C CNN
	1    12450 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR047
U 1 1 5ECFF927
P 13350 2100
F 0 "#PWR047" H 13350 1850 50  0001 C CNN
F 1 "GND" H 13355 1927 50  0000 C CNN
F 2 "" H 13350 2100 50  0001 C CNN
F 3 "" H 13350 2100 50  0001 C CNN
	1    13350 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 5ED0155B
P 4550 5100
F 0 "#PWR019" H 4550 4850 50  0001 C CNN
F 1 "GND" H 4650 5150 50  0000 C CNN
F 2 "" H 4550 5100 50  0001 C CNN
F 3 "" H 4550 5100 50  0001 C CNN
	1    4550 5100
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR018
U 1 1 5ED01879
P 4550 4800
F 0 "#PWR018" H 4550 4650 50  0001 C CNN
F 1 "+12V" H 4565 4973 50  0000 C CNN
F 2 "" H 4550 4800 50  0001 C CNN
F 3 "" H 4550 4800 50  0001 C CNN
	1    4550 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 4800 4450 4800
Connection ~ 4550 4800
$Comp
L power:GND #PWR06
U 1 1 5ED3FCE2
P 5000 4100
F 0 "#PWR06" H 5000 3850 50  0001 C CNN
F 1 "GND" H 5005 3927 50  0000 C CNN
F 2 "" H 5000 4100 50  0001 C CNN
F 3 "" H 5000 4100 50  0001 C CNN
	1    5000 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5ED40047
P 3150 4200
F 0 "#PWR012" H 3150 3950 50  0001 C CNN
F 1 "GND" H 3155 4027 50  0000 C CNN
F 2 "" H 3150 4200 50  0001 C CNN
F 3 "" H 3150 4200 50  0001 C CNN
	1    3150 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5ED4248D
P 2750 6800
F 0 "#PWR04" H 2750 6550 50  0001 C CNN
F 1 "GND" H 2755 6627 50  0000 C CNN
F 2 "" H 2750 6800 50  0001 C CNN
F 3 "" H 2750 6800 50  0001 C CNN
	1    2750 6800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 5ED42FF0
P 4300 2100
F 0 "#PWR026" H 4300 1850 50  0001 C CNN
F 1 "GND" H 4305 1927 50  0000 C CNN
F 2 "" H 4300 2100 50  0001 C CNN
F 3 "" H 4300 2100 50  0001 C CNN
	1    4300 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 5ED43BA6
P 4250 4200
F 0 "#PWR024" H 4250 3950 50  0001 C CNN
F 1 "GND" H 4255 4027 50  0000 C CNN
F 2 "" H 4250 4200 50  0001 C CNN
F 3 "" H 4250 4200 50  0001 C CNN
	1    4250 4200
	1    0    0    -1  
$EndComp
Text Label 4500 7200 0    50   ~ 0
Hctrl
Text Label 5650 5400 0    50   ~ 0
Mctrl+
$Comp
L power:GND #PWR035
U 1 1 5EE3BA6F
P 10450 6700
F 0 "#PWR035" H 10450 6450 50  0001 C CNN
F 1 "GND" H 10455 6527 50  0000 C CNN
F 2 "" H 10450 6700 50  0001 C CNN
F 3 "" H 10450 6700 50  0001 C CNN
	1    10450 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10800 7050 11300 7050
Wire Wire Line
	11300 7050 11300 7450
Wire Wire Line
	11250 7100 11250 7850
Wire Wire Line
	10600 7100 11250 7100
Wire Wire Line
	15550 6950 15450 6950
Wire Wire Line
	15550 7150 15450 7150
$Comp
L Device:D_Zener D25
U 1 1 5ED94BA5
P 3450 5750
F 0 "D25" V 3404 5829 50  0000 L CNN
F 1 "15V" V 3495 5829 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 3450 5750 50  0001 C CNN
F 3 "~" H 3450 5750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 3450 5750 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 3450 5750 50  0001 C CNN "Digi-Key_PN"
	1    3450 5750
	0    -1   1    0   
$EndComp
Wire Wire Line
	7250 4100 7600 4100
Wire Wire Line
	7250 4400 7600 4400
Wire Wire Line
	7250 5600 7600 5600
Wire Wire Line
	7250 5900 7600 5900
Wire Wire Line
	7250 4600 7600 4600
Wire Wire Line
	7250 4900 7600 4900
Wire Wire Line
	7250 6150 7600 6150
Wire Wire Line
	7250 6450 7600 6450
Wire Wire Line
	7250 7250 7600 7250
Wire Wire Line
	7250 7550 7600 7550
$Comp
L Device:CP C28
U 1 1 5EDDD200
P 7600 4250
F 0 "C28" H 7715 4296 50  0000 L CNN
F 1 "10uf 100v" H 7500 4550 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 7638 4100 50  0001 C CNN
F 3 "~" H 7600 4250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 7600 4250 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 7600 4250 50  0001 C CNN "Digi-Key_PN"
	1    7600 4250
	1    0    0    -1  
$EndComp
Connection ~ 7600 4100
Connection ~ 7600 4400
$Comp
L Device:CP C29
U 1 1 5EDDD4A9
P 7600 5750
F 0 "C29" H 7715 5796 50  0000 L CNN
F 1 "10uf 100v" H 7500 6050 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 7638 5600 50  0001 C CNN
F 3 "~" H 7600 5750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 7600 5750 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 7600 5750 50  0001 C CNN "Digi-Key_PN"
	1    7600 5750
	1    0    0    -1  
$EndComp
Connection ~ 7600 5600
Connection ~ 7600 5900
$Comp
L Device:CP C30
U 1 1 5EDDD8C5
P 7600 4750
F 0 "C30" H 7715 4796 50  0000 L CNN
F 1 "10uf 100v" H 7500 5050 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 7638 4600 50  0001 C CNN
F 3 "~" H 7600 4750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 7600 4750 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 7600 4750 50  0001 C CNN "Digi-Key_PN"
	1    7600 4750
	1    0    0    -1  
$EndComp
Connection ~ 7600 4600
Connection ~ 7600 4900
$Comp
L Device:CP C31
U 1 1 5EDDDD06
P 7600 6300
F 0 "C31" H 7715 6346 50  0000 L CNN
F 1 "10uf 100v" H 7500 6600 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 7638 6150 50  0001 C CNN
F 3 "~" H 7600 6300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 7600 6300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 7600 6300 50  0001 C CNN "Digi-Key_PN"
	1    7600 6300
	1    0    0    -1  
$EndComp
Connection ~ 7600 6150
Connection ~ 7600 6450
$Comp
L Device:CP C33
U 1 1 5EDDE1AA
P 8500 6850
F 0 "C33" H 8615 6896 50  0000 L CNN
F 1 "10uf 100v" H 8400 7150 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 8538 6700 50  0001 C CNN
F 3 "~" H 8500 6850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 8500 6850 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 8500 6850 50  0001 C CNN "Digi-Key_PN"
	1    8500 6850
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C32
U 1 1 5EDDE837
P 7600 7400
F 0 "C32" H 7715 7446 50  0000 L CNN
F 1 "10uf 100v" H 7500 7700 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 7638 7250 50  0001 C CNN
F 3 "~" H 7600 7400 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 7600 7400 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 7600 7400 50  0001 C CNN "Digi-Key_PN"
	1    7600 7400
	1    0    0    -1  
$EndComp
Connection ~ 7600 7250
Connection ~ 7600 7550
$Comp
L Device:CP C27
U 1 1 5EDDED3F
P 7250 7400
F 0 "C27" H 7365 7446 50  0000 L CNN
F 1 "10uf 100v" H 7150 7700 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 7288 7250 50  0001 C CNN
F 3 "~" H 7250 7400 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 7250 7400 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 7250 7400 50  0001 C CNN "Digi-Key_PN"
	1    7250 7400
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C26
U 1 1 5EDDEFF5
P 7250 6300
F 0 "C26" H 7365 6346 50  0000 L CNN
F 1 "10uf 100v" H 7150 6600 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 7288 6150 50  0001 C CNN
F 3 "~" H 7250 6300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 7250 6300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 7250 6300 50  0001 C CNN "Digi-Key_PN"
	1    7250 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C25
U 1 1 5EDDF3B9
P 7250 4750
F 0 "C25" H 7365 4796 50  0000 L CNN
F 1 "10uf 100v" H 7150 5050 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 7288 4600 50  0001 C CNN
F 3 "~" H 7250 4750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 7250 4750 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 7250 4750 50  0001 C CNN "Digi-Key_PN"
	1    7250 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C24
U 1 1 5EDDF694
P 7250 5750
F 0 "C24" H 7365 5796 50  0000 L CNN
F 1 "10uf 100v" H 7150 6050 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 7288 5600 50  0001 C CNN
F 3 "~" H 7250 5750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 7250 5750 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 7250 5750 50  0001 C CNN "Digi-Key_PN"
	1    7250 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C5
U 1 1 5EDE0173
P 5100 3300
F 0 "C5" H 5215 3346 50  0000 L CNN
F 1 "10uf 100v" H 4800 3550 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 5138 3150 50  0001 C CNN
F 3 "~" H 5100 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 5100 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 5100 3300 50  0001 C CNN "Digi-Key_PN"
	1    5100 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C4
U 1 1 5EDE0736
P 4800 3300
F 0 "C4" H 4915 3346 50  0000 L CNN
F 1 "10uf 100v" H 4650 3050 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 4838 3150 50  0001 C CNN
F 3 "~" H 4800 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 4800 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 4800 3300 50  0001 C CNN "Digi-Key_PN"
	1    4800 3300
	1    0    0    -1  
$EndComp
Connection ~ 4800 3150
Wire Wire Line
	4800 3150 5100 3150
Connection ~ 4800 3450
Wire Wire Line
	4800 3450 5100 3450
Connection ~ 5100 3150
Wire Wire Line
	5100 3150 5150 3150
Connection ~ 5100 3450
Wire Wire Line
	5100 3450 5450 3450
Wire Wire Line
	8250 3150 8550 3150
Wire Wire Line
	8250 3450 8550 3450
$Comp
L dk_Rectangular-Connectors-Headers-Male-Pins:22-23-2021 J17
U 1 1 5EDAEE61
P 12350 2500
F 0 "J17" V 12125 2508 50  0000 C CNN
F 1 "5Vout" V 12216 2508 50  0000 C CNN
F 2 "digikey-footprints:PinHeader_1x2_P2.54mm_Drill1.02mm" H 12550 2700 60  0001 L CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 12550 2800 60  0001 L CNN
F 4 "" H 12550 2900 60  0001 L CNN "Digi-Key_PN"
F 5 "22-23-2021" H 12550 3000 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 12550 3100 60  0001 L CNN "Category"
F 7 "Rectangular Connectors - Headers, Male Pins" H 12550 3200 60  0001 L CNN "Family"
F 8 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 12550 3300 60  0001 L CNN "DK_Datasheet_Link"
F 9 "" H 12550 3400 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN HEADER VERT 2POS 2.54MM" H 12550 3500 60  0001 L CNN "Description"
F 11 "Molex" H 12550 3600 60  0001 L CNN "Manufacturer"
F 12 "Active" H 12550 3700 60  0001 L CNN "Status"
	1    12350 2500
	0    1    1    0   
$EndComp
$Comp
L dk_Rectangular-Connectors-Headers-Male-Pins:22-23-2021 J7
U 1 1 5EDAEE76
P 11950 2500
F 0 "J7" V 11725 2508 50  0000 C CNN
F 1 "5Vout" V 11816 2508 50  0000 C CNN
F 2 "digikey-footprints:PinHeader_1x2_P2.54mm_Drill1.02mm" H 12150 2700 60  0001 L CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 12150 2800 60  0001 L CNN
F 4 "" H 12150 2900 60  0001 L CNN "Digi-Key_PN"
F 5 "22-23-2021" H 12150 3000 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 12150 3100 60  0001 L CNN "Category"
F 7 "Rectangular Connectors - Headers, Male Pins" H 12150 3200 60  0001 L CNN "Family"
F 8 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 12150 3300 60  0001 L CNN "DK_Datasheet_Link"
F 9 "" H 12150 3400 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN HEADER VERT 2POS 2.54MM" H 12150 3500 60  0001 L CNN "Description"
F 11 "Molex" H 12150 3600 60  0001 L CNN "Manufacturer"
F 12 "Active" H 12150 3700 60  0001 L CNN "Status"
	1    11950 2500
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5EDAEE82
P 12050 2600
F 0 "#PWR0101" H 12050 2350 50  0001 C CNN
F 1 "GND" H 12055 2427 50  0000 C CNN
F 2 "" H 12050 2600 50  0001 C CNN
F 3 "" H 12050 2600 50  0001 C CNN
	1    12050 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5EDAEE88
P 12450 2600
F 0 "#PWR0106" H 12450 2350 50  0001 C CNN
F 1 "GND" H 12455 2427 50  0000 C CNN
F 2 "" H 12450 2600 50  0001 C CNN
F 3 "" H 12450 2600 50  0001 C CNN
	1    12450 2600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0108
U 1 1 5EE201F3
P 12050 2500
F 0 "#PWR0108" H 12050 2350 50  0001 C CNN
F 1 "+5V" H 12065 2673 50  0000 C CNN
F 2 "" H 12050 2500 50  0001 C CNN
F 3 "" H 12050 2500 50  0001 C CNN
	1    12050 2500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0110
U 1 1 5EE206CE
P 12450 2500
F 0 "#PWR0110" H 12450 2350 50  0001 C CNN
F 1 "+5V" H 12465 2673 50  0000 C CNN
F 2 "" H 12450 2500 50  0001 C CNN
F 3 "" H 12450 2500 50  0001 C CNN
	1    12450 2500
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H12
U 1 1 5EDBBD03
P 800 8550
F 0 "H12" V 1037 8553 50  0000 C CNN
F 1 "mnt" V 946 8553 50  0000 C CNN
F 2 "Connect:1pin" H 800 8550 50  0001 C CNN
F 3 "~" H 800 8550 50  0001 C CNN
	1    800  8550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5EDBBD09
P 900 8550
F 0 "#PWR0112" H 900 8300 50  0001 C CNN
F 1 "GND" H 905 8377 50  0000 C CNN
F 2 "" H 900 8550 50  0001 C CNN
F 3 "" H 900 8550 50  0001 C CNN
	1    900  8550
	1    0    0    -1  
$EndComp
Text Label 14050 2000 0    50   ~ 0
__PwrKey
Text Label 14300 2750 2    50   ~ 0
CHdetect
Connection ~ 10750 3450
$Comp
L Device:R R21
U 1 1 5EE93C8F
P 12400 750
F 0 "R21" H 12470 796 50  0000 L CNN
F 1 "500" H 12470 705 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 12330 750 50  0001 C CNN
F 3 "~" H 12400 750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 12400 750 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 12400 750 50  0001 C CNN "Digi-Key_PN"
	1    12400 750 
	0    1    1    0   
$EndComp
$Comp
L Device:R R26
U 1 1 5EE950EC
P 12400 950
F 0 "R26" H 12470 996 50  0000 L CNN
F 1 "500" H 12470 905 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 12330 950 50  0001 C CNN
F 3 "~" H 12400 950 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 12400 950 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 12400 950 50  0001 C CNN "Digi-Key_PN"
	1    12400 950 
	0    1    1    0   
$EndComp
Wire Wire Line
	12100 5900 12350 5900
$Comp
L Device:R R39
U 1 1 5EECC73B
P 13800 750
F 0 "R39" H 13870 796 50  0000 L CNN
F 1 "500" H 13870 705 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 13730 750 50  0001 C CNN
F 3 "~" H 13800 750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 13800 750 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 13800 750 50  0001 C CNN "Digi-Key_PN"
	1    13800 750 
	0    1    1    0   
$EndComp
$Comp
L Device:R R40
U 1 1 5EECCD4E
P 13800 950
F 0 "R40" H 13870 996 50  0000 L CNN
F 1 "500" H 13870 905 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 13730 950 50  0001 C CNN
F 3 "~" H 13800 950 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 13800 950 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 13800 950 50  0001 C CNN "Digi-Key_PN"
	1    13800 950 
	0    1    1    0   
$EndComp
Text Label 15550 6950 0    50   ~ 0
KeepAlive
Text Label 14300 2550 2    50   ~ 0
KeepAlive
$Comp
L Device:Q_PMOS_GSD Q9
U 1 1 5EF089E7
P 14900 2150
F 0 "Q9" V 15242 2150 50  0000 C CNN
F 1 "FDN340P" V 15400 2150 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 15100 2250 50  0001 C CNN
F 3 "~" H 14900 2150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/on-semiconductor/FDN340P/965604" H 14900 2150 50  0001 C CNN "DK_Detail_Page"
F 5 "FDN340PCT-ND" H 14900 2150 50  0001 C CNN "Digi-Key_PN"
	1    14900 2150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R43
U 1 1 5EF0BC39
P 15650 2350
F 0 "R43" H 15720 2396 50  0000 L CNN
F 1 "10K" H 15720 2305 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 15580 2350 50  0001 C CNN
F 3 "~" H 15650 2350 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/ESR03EZPJ103/1762722" H 15650 2350 50  0001 C CNN "DK_Detail_Page"
F 5 "RHM10KDCT-ND" H 15650 2350 50  0001 C CNN "Digi-Key_PN"
	1    15650 2350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	15800 2050 15800 2350
Connection ~ 14900 2350
$Comp
L power:+5C #PWR0113
U 1 1 5F0918BA
P 10100 2150
F 0 "#PWR0113" H 10100 2000 50  0001 C CNN
F 1 "+5C" H 10115 2323 50  0000 C CNN
F 2 "" H 10100 2150 50  0001 C CNN
F 3 "" H 10100 2150 50  0001 C CNN
	1    10100 2150
	1    0    0    -1  
$EndComp
$Comp
L power:+5C #PWR0115
U 1 1 5F092044
P 10100 1450
F 0 "#PWR0115" H 10100 1300 50  0001 C CNN
F 1 "+5C" H 10115 1623 50  0000 C CNN
F 2 "" H 10100 1450 50  0001 C CNN
F 3 "" H 10100 1450 50  0001 C CNN
	1    10100 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+5C #PWR0117
U 1 1 5F09249E
P 7500 1450
F 0 "#PWR0117" H 7500 1300 50  0001 C CNN
F 1 "+5C" H 7515 1623 50  0000 C CNN
F 2 "" H 7500 1450 50  0001 C CNN
F 3 "" H 7500 1450 50  0001 C CNN
	1    7500 1450
	1    0    0    -1  
$EndComp
Connection ~ 7500 1450
$Comp
L Device:Q_NMOS_GSD Q7
U 1 1 5F095595
P 14800 2550
F 0 "Q7" H 15005 2596 50  0000 L CNN
F 1 "DMN65D8L" H 15005 2505 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 15000 2650 50  0001 C CNN
F 3 "~" H 14800 2550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DMN65D8L-7/3678136" H 14800 2550 50  0001 C CNN "DK_Detail_Page"
F 5 "DMN65D8L-7DICT-ND" H 14800 2550 50  0001 C CNN "Digi-Key_PN"
	1    14800 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R41
U 1 1 5F0D1EFB
P 14750 2750
F 0 "R41" H 14820 2796 50  0000 L CNN
F 1 "10K" H 14820 2705 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 14680 2750 50  0001 C CNN
F 3 "~" H 14750 2750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/ESR03EZPJ103/1762722" H 14750 2750 50  0001 C CNN "DK_Detail_Page"
F 5 "RHM10KDCT-ND" H 14750 2750 50  0001 C CNN "Digi-Key_PN"
	1    14750 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	14600 2750 14600 2550
$Comp
L power:GND #PWR0118
U 1 1 5F14039E
P 14900 2750
F 0 "#PWR0118" H 14900 2500 50  0001 C CNN
F 1 "GND" H 14905 2577 50  0000 C CNN
F 2 "" H 14900 2750 50  0001 C CNN
F 3 "" H 14900 2750 50  0001 C CNN
	1    14900 2750
	1    0    0    -1  
$EndComp
Connection ~ 14900 2750
$Comp
L Device:C C67
U 1 1 5F193AA4
P 13100 6050
F 0 "C67" H 13100 5650 50  0000 L CNN
F 1 "0.1uf film" H 13000 5850 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 13138 5900 50  0001 C CNN
F 3 "~" H 13100 6050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 13100 6050 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 13100 6050 50  0001 C CNN "Digi-Key_PN"
	1    13100 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	13100 5900 12850 5900
Wire Wire Line
	13100 6200 12850 6200
Connection ~ 12850 6200
$Comp
L power:+5C #PWR0119
U 1 1 5EE13304
P 3150 3600
F 0 "#PWR0119" H 3150 3450 50  0001 C CNN
F 1 "+5C" H 3165 3773 50  0000 C CNN
F 2 "" H 3150 3600 50  0001 C CNN
F 3 "" H 3150 3600 50  0001 C CNN
	1    3150 3600
	1    0    0    -1  
$EndComp
$Comp
L power:+5C #PWR0121
U 1 1 5EE13909
P 5000 3800
F 0 "#PWR0121" H 5000 3650 50  0001 C CNN
F 1 "+5C" H 5015 3973 50  0000 C CNN
F 2 "" H 5000 3800 50  0001 C CNN
F 3 "" H 5000 3800 50  0001 C CNN
	1    5000 3800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R44
U 1 1 5EE9B6FC
P 15200 900
F 0 "R44" H 15270 946 50  0000 L CNN
F 1 "1K" H 15270 855 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 15130 900 50  0001 C CNN
F 3 "~" H 15200 900 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 15200 900 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 15200 900 50  0001 C CNN "Digi-Key_PN"
	1    15200 900 
	0    1    1    0   
$EndComp
$Comp
L Device:LED D30
U 1 1 5EE9B702
P 14800 900
F 0 "D30" H 14793 1116 50  0000 C CNN
F 1 "Power" H 14793 1025 50  0000 C CNN
F 2 "LEDs:LED_0603" H 14800 900 50  0001 C CNN
F 3 "~" H 14800 900 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/qt-brightek-qtb/QBLP601-IG/4814653" H 14800 900 50  0001 C CNN "DK_Detail_Page"
F 5 "1516-1055-1-ND" H 14800 900 50  0001 C CNN "Digi-Key_PN"
	1    14800 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	15050 900  14950 900 
Wire Wire Line
	15350 800  15350 900 
Wire Wire Line
	14650 900  14650 1250
$Comp
L power:GND #PWR0123
U 1 1 5EED1DAE
P 14650 1250
F 0 "#PWR0123" H 14650 1000 50  0001 C CNN
F 1 "GND" H 14655 1077 50  0000 C CNN
F 2 "" H 14650 1250 50  0001 C CNN
F 3 "" H 14650 1250 50  0001 C CNN
	1    14650 1250
	1    0    0    -1  
$EndComp
$Comp
L power:+5C #PWR0125
U 1 1 5EED216F
P 15350 800
F 0 "#PWR0125" H 15350 650 50  0001 C CNN
F 1 "+5C" H 15365 973 50  0000 C CNN
F 2 "" H 15350 800 50  0001 C CNN
F 3 "" H 15350 800 50  0001 C CNN
	1    15350 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	13750 2000 13750 2350
Wire Wire Line
	14050 2350 14900 2350
$Comp
L Device:Q_NMOS_GDS Q10
U 1 1 5FB4D2D3
P 2050 4400
F 0 "Q10" H 2254 4446 50  0000 L CNN
F 1 "PSMN5R6-100BS" H 2000 4700 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:TO-263-2" H 2250 4500 50  0001 C CNN
F 3 "~" H 2050 4400 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/nexperia-usa-inc/PSMN5R6-100BS-118/3131570" H 2050 4400 50  0001 C CNN "DK_Detail_Page"
F 5 "1727-7125-1-ND" H 2050 4400 50  0001 C CNN "Digi-Key_PN"
	1    2050 4400
	-1   0    0    -1  
$EndComp
$Comp
L Device:D_Zener D32
U 1 1 5FB4DBA6
P 2250 4550
F 0 "D32" V 2204 4629 50  0000 L CNN
F 1 "15V" V 2295 4629 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 2250 4550 50  0001 C CNN
F 3 "~" H 2250 4550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 2250 4550 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 2250 4550 50  0001 C CNN "Digi-Key_PN"
	1    2250 4550
	0    -1   1    0   
$EndComp
$Comp
L Device:R R25
U 1 1 5FB4E0BB
P 2400 4150
F 0 "R25" V 2300 4100 50  0000 L CNN
F 1 "12" V 2400 4100 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 2330 4150 50  0001 C CNN
F 3 "~" H 2400 4150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ERJ-UP3J120V/12139275" H 2400 4150 50  0001 C CNN "DK_Detail_Page"
F 5 "10-ERJ-UP3J120VCT-ND" H 2400 4150 50  0001 C CNN "Digi-Key_PN"
	1    2400 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	1950 4900 1850 4900
Wire Wire Line
	1850 4200 1950 4200
Wire Wire Line
	1950 4600 1950 4700
Wire Wire Line
	1950 4700 2250 4700
Wire Wire Line
	1950 4700 1800 4700
Connection ~ 1950 4700
Wire Wire Line
	2950 3150 3650 3150
Connection ~ 3650 3150
$Comp
L Device:D_Schottky_AAK D28
U 1 1 5FBC6E8C
P 2250 2200
F 0 "D28" V 2321 2112 50  0000 R CNN
F 1 "D_Schottky_AAK" V 2230 2112 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:TO-277A" H 2250 2200 50  0001 C CNN
F 3 "~" H 2250 2200 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/on-semiconductor/FSV20100V/5306682" H 2250 2200 50  0001 C CNN "DK_Detail_Page"
F 5 "FSV20100VCT-ND" H 2250 2200 50  0001 C CNN "Digi-Key_PN"
	1    2250 2200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2250 2350 2450 2350
Connection ~ 2450 2350
Wire Wire Line
	2350 2000 2250 2000
Connection ~ 2350 2000
Wire Wire Line
	2250 2000 2150 2000
Connection ~ 2250 2000
$Comp
L Mechanical:MountingHole_Pad H16
U 1 1 5FDDFF06
P 800 9300
F 0 "H16" V 1037 9303 50  0000 C CNN
F 1 "mnt" V 946 9303 50  0000 C CNN
F 2 "Connect:1pin" H 800 9300 50  0001 C CNN
F 3 "~" H 800 9300 50  0001 C CNN
	1    800  9300
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 5FDDFF10
P 900 9300
F 0 "#PWR0120" H 900 9050 50  0001 C CNN
F 1 "GND" H 905 9127 50  0000 C CNN
F 2 "" H 900 9300 50  0001 C CNN
F 3 "" H 900 9300 50  0001 C CNN
	1    900  9300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 9950 5700 9950
Text Label 2450 2450 3    50   ~ 0
ChargeIn
Text Label 1600 9500 2    50   ~ 0
ChargeIn
Text Label 15550 7750 0    50   ~ 0
HeatRLY
Text Label 3800 9300 0    50   ~ 0
chargeRLY
$Comp
L Device:D_Zener D34
U 1 1 600F4306
P 3650 10850
F 0 "D34" V 3604 10929 50  0000 L CNN
F 1 "15V" V 3695 10929 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 3650 10850 50  0001 C CNN
F 3 "~" H 3650 10850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 3650 10850 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 3650 10850 50  0001 C CNN "Digi-Key_PN"
	1    3650 10850
	0    -1   1    0   
$EndComp
Wire Wire Line
	3650 11000 3200 11000
Wire Wire Line
	3200 11000 3200 10900
Wire Wire Line
	3650 10700 3500 10700
$Comp
L power:+12V #PWR0124
U 1 1 600F4326
P 2250 10250
F 0 "#PWR0124" H 2250 10100 50  0001 C CNN
F 1 "+12V" H 2265 10423 50  0000 C CNN
F 2 "" H 2250 10250 50  0001 C CNN
F 3 "" H 2250 10250 50  0001 C CNN
	1    2250 10250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 10200 2450 10200
Wire Wire Line
	2450 10200 2450 10250
Wire Wire Line
	2450 10250 2250 10250
$Comp
L Device:R R42
U 1 1 600F433E
P 3650 10600
F 0 "R42" H 3720 10646 50  0000 L CNN
F 1 "500" H 3720 10555 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 3580 10600 50  0001 C CNN
F 3 "~" H 3650 10600 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 3650 10600 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 3650 10600 50  0001 C CNN "Digi-Key_PN"
	1    3650 10600
	0    1    1    0   
$EndComp
Wire Wire Line
	3500 10600 3500 10700
Wire Wire Line
	3800 10600 3800 10500
$Comp
L power:GND #PWR0126
U 1 1 600F434B
P 3200 11000
F 0 "#PWR0126" H 3200 10750 50  0001 C CNN
F 1 "GND" H 3205 10827 50  0000 C CNN
F 2 "" H 3200 11000 50  0001 C CNN
F 3 "" H 3200 11000 50  0001 C CNN
	1    3200 11000
	1    0    0    -1  
$EndComp
Connection ~ 3200 11000
Text Label 3800 10500 0    50   ~ 0
AUXpower
$Comp
L Mechanical:MountingHole_Pad H14
U 1 1 6021B8D3
P 750 10150
F 0 "H14" V 987 10153 50  0000 C CNN
F 1 "AUX+" V 896 10153 50  0000 C CNN
F 2 "Connect:1pin" H 750 10150 50  0001 C CNN
F 3 "~" H 750 10150 50  0001 C CNN
	1    750  10150
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H15
U 1 1 6021B8DD
P 750 10450
F 0 "H15" V 987 10453 50  0000 C CNN
F 1 "AUX-" V 896 10453 50  0000 C CNN
F 2 "Connect:1pin" H 750 10450 50  0001 C CNN
F 3 "~" H 750 10450 50  0001 C CNN
	1    750  10450
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0127
U 1 1 602AA9E7
P 850 10450
F 0 "#PWR0127" H 850 10200 50  0001 C CNN
F 1 "GND" H 855 10277 50  0000 C CNN
F 2 "" H 850 10450 50  0001 C CNN
F 3 "" H 850 10450 50  0001 C CNN
	1    850  10450
	1    0    0    -1  
$EndComp
Text Label 15550 7950 0    50   ~ 0
AUXpower
$Comp
L Device:D_Zener D36
U 1 1 602ACDFC
P 6650 8750
F 0 "D36" V 6604 8829 50  0000 L CNN
F 1 "15V" V 6695 8829 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 6650 8750 50  0001 C CNN
F 3 "~" H 6650 8750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 6650 8750 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 6650 8750 50  0001 C CNN "Digi-Key_PN"
	1    6650 8750
	0    -1   1    0   
$EndComp
Wire Wire Line
	6650 8900 6200 8900
Wire Wire Line
	6200 8900 6200 8800
Wire Wire Line
	6650 8600 6500 8600
$Comp
L dk_Rectangular-Connectors-Headers-Male-Pins:22-23-2021 J2
U 1 1 602ACE12
P 4850 7950
F 0 "J2" V 4625 7958 50  0000 C CNN
F 1 "mContactor" V 4716 7958 50  0000 C CNN
F 2 "digikey-footprints:PinHeader_1x2_P2.54mm_Drill1.02mm" H 5050 8150 60  0001 L CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 5050 8250 60  0001 L CNN
F 4 "" H 5050 8350 60  0001 L CNN "Digi-Key_PN"
F 5 "22-23-2021" H 5050 8450 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 5050 8550 60  0001 L CNN "Category"
F 7 "Rectangular Connectors - Headers, Male Pins" H 5050 8650 60  0001 L CNN "Family"
F 8 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 5050 8750 60  0001 L CNN "DK_Datasheet_Link"
F 9 "" H 5050 8850 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN HEADER VERT 2POS 2.54MM" H 5050 8950 60  0001 L CNN "Description"
F 11 "Molex" H 5050 9050 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5050 9150 60  0001 L CNN "Status"
	1    4850 7950
	-1   0    0    1   
$EndComp
$Comp
L power:+12V #PWR0128
U 1 1 602ACE1C
P 5200 8150
F 0 "#PWR0128" H 5200 8000 50  0001 C CNN
F 1 "+12V" H 5215 8323 50  0000 C CNN
F 2 "" H 5200 8150 50  0001 C CNN
F 3 "" H 5200 8150 50  0001 C CNN
	1    5200 8150
	1    0    0    -1  
$EndComp
Text Label 6800 8400 2    50   ~ 0
mainContactor
Wire Wire Line
	5700 8100 5400 8100
Wire Wire Line
	5400 8100 5400 8150
Wire Wire Line
	5400 8150 5200 8150
$Comp
L Device:R R45
U 1 1 602ACE34
P 6650 8500
F 0 "R45" H 6720 8546 50  0000 L CNN
F 1 "500" H 6720 8455 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 6580 8500 50  0001 C CNN
F 3 "~" H 6650 8500 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 6650 8500 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 6650 8500 50  0001 C CNN "Digi-Key_PN"
	1    6650 8500
	0    1    1    0   
$EndComp
Wire Wire Line
	6500 8500 6500 8600
Wire Wire Line
	6800 8500 6800 8400
$Comp
L power:GND #PWR0130
U 1 1 602ACE41
P 6200 8900
F 0 "#PWR0130" H 6200 8650 50  0001 C CNN
F 1 "GND" H 6205 8727 50  0000 C CNN
F 2 "" H 6200 8900 50  0001 C CNN
F 3 "" H 6200 8900 50  0001 C CNN
	1    6200 8900
	1    0    0    -1  
$EndComp
Connection ~ 6200 8900
Wire Wire Line
	5350 8400 5700 8400
$Comp
L Device:R R49
U 1 1 60481A16
P 8050 9300
F 0 "R49" H 8120 9346 50  0000 L CNN
F 1 "1K" H 8120 9255 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 7980 9300 50  0001 C CNN
F 3 "~" H 8050 9300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 8050 9300 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 8050 9300 50  0001 C CNN "Digi-Key_PN"
	1    8050 9300
	0    1    1    0   
$EndComp
$Comp
L Device:LED D40
U 1 1 60481A20
P 7650 9300
F 0 "D40" H 7643 9516 50  0000 C CNN
F 1 "Contactor" H 7643 9425 50  0000 C CNN
F 2 "LEDs:LED_0603" H 7650 9300 50  0001 C CNN
F 3 "~" H 7650 9300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/broadcom-limited/HSMA-C120/1235470" H 7650 9300 50  0001 C CNN "DK_Detail_Page"
F 5 "516-2486-1-ND" H 7650 9300 50  0001 C CNN "Digi-Key_PN"
	1    7650 9300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 9300 7800 9300
Wire Wire Line
	8200 9200 8200 9300
$Comp
L Device:R R48
U 1 1 605644DC
P 8050 8950
F 0 "R48" H 8120 8996 50  0000 L CNN
F 1 "1K" H 8120 8905 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 7980 8950 50  0001 C CNN
F 3 "~" H 8050 8950 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 8050 8950 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 8050 8950 50  0001 C CNN "Digi-Key_PN"
	1    8050 8950
	0    1    1    0   
$EndComp
$Comp
L Device:LED D39
U 1 1 605644E6
P 7650 8950
F 0 "D39" H 7643 9166 50  0000 C CNN
F 1 "AUXpwr" H 7643 9075 50  0000 C CNN
F 2 "LEDs:LED_0603" H 7650 8950 50  0001 C CNN
F 3 "~" H 7650 8950 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/broadcom-limited/HSMA-C120/1235470" H 7650 8950 50  0001 C CNN "DK_Detail_Page"
F 5 "516-2486-1-ND" H 7650 8950 50  0001 C CNN "Digi-Key_PN"
	1    7650 8950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 8950 7800 8950
Wire Wire Line
	8200 8850 8200 8950
$Comp
L Device:R R47
U 1 1 605B0057
P 8050 8600
F 0 "R47" H 8120 8646 50  0000 L CNN
F 1 "1K" H 8120 8555 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 7980 8600 50  0001 C CNN
F 3 "~" H 8050 8600 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 8050 8600 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 8050 8600 50  0001 C CNN "Digi-Key_PN"
	1    8050 8600
	0    1    1    0   
$EndComp
$Comp
L Device:LED D38
U 1 1 605B0061
P 7650 8600
F 0 "D38" H 7643 8816 50  0000 C CNN
F 1 "ChrgEnable" H 7643 8725 50  0000 C CNN
F 2 "LEDs:LED_0603" H 7650 8600 50  0001 C CNN
F 3 "~" H 7650 8600 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/broadcom-limited/HSMA-C120/1235470" H 7650 8600 50  0001 C CNN "DK_Detail_Page"
F 5 "516-2486-1-ND" H 7650 8600 50  0001 C CNN "Digi-Key_PN"
	1    7650 8600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 8600 7800 8600
Wire Wire Line
	8200 8500 8200 8600
$Comp
L Device:R R46
U 1 1 605B006D
P 8050 8250
F 0 "R46" H 8120 8296 50  0000 L CNN
F 1 "1K" H 8120 8205 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 7980 8250 50  0001 C CNN
F 3 "~" H 8050 8250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 8050 8250 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 8050 8250 50  0001 C CNN "Digi-Key_PN"
	1    8050 8250
	0    1    1    0   
$EndComp
$Comp
L Device:LED D37
U 1 1 605B0077
P 7650 8250
F 0 "D37" H 7643 8466 50  0000 C CNN
F 1 "HeatEnable" H 7643 8375 50  0000 C CNN
F 2 "LEDs:LED_0603" H 7650 8250 50  0001 C CNN
F 3 "~" H 7650 8250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/broadcom-limited/HSMA-C120/1235470" H 7650 8250 50  0001 C CNN "DK_Detail_Page"
F 5 "516-2486-1-ND" H 7650 8250 50  0001 C CNN "Digi-Key_PN"
	1    7650 8250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 8250 7800 8250
Wire Wire Line
	8200 8150 8200 8250
$Comp
L Device:R R50
U 1 1 605FD0C6
P 8050 9650
F 0 "R50" H 8120 9696 50  0000 L CNN
F 1 "1K" H 8120 9605 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 7980 9650 50  0001 C CNN
F 3 "~" H 8050 9650 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 8050 9650 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 8050 9650 50  0001 C CNN "Digi-Key_PN"
	1    8050 9650
	0    1    1    0   
$EndComp
$Comp
L Device:LED D41
U 1 1 605FD0D0
P 7650 9650
F 0 "D41" H 7643 9866 50  0000 C CNN
F 1 "Cool" H 7643 9775 50  0000 C CNN
F 2 "LEDs:LED_0603" H 7650 9650 50  0001 C CNN
F 3 "~" H 7650 9650 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/broadcom-limited/HSMA-C120/1235470" H 7650 9650 50  0001 C CNN "DK_Detail_Page"
F 5 "516-2486-1-ND" H 7650 9650 50  0001 C CNN "Digi-Key_PN"
	1    7650 9650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 9650 7800 9650
Wire Wire Line
	8200 9550 8200 9650
Text Label 8200 8150 0    50   ~ 0
HeatRLY
Text Label 8200 8500 0    50   ~ 0
chargeRLY
Text Label 8200 8850 0    50   ~ 0
AUXpower
Text Label 8200 9200 0    50   ~ 0
mainContactor
Text Label 8200 9550 0    50   ~ 0
CoolCTRL
Wire Wire Line
	7500 8250 7500 8600
Wire Wire Line
	7500 8600 7500 8950
Connection ~ 7500 8600
Wire Wire Line
	7500 8950 7500 9300
Connection ~ 7500 8950
Wire Wire Line
	7500 9300 7500 9650
Connection ~ 7500 9300
Wire Wire Line
	7500 9650 7500 10000
Connection ~ 7500 9650
Connection ~ 7500 10000
$Comp
L dk_Rectangular-Connectors-Headers-Male-Pins:22-23-2021 J3
U 1 1 60870492
P 10000 950
F 0 "J3" V 9775 958 50  0000 C CNN
F 1 "Tac" V 9866 958 50  0000 C CNN
F 2 "digikey-footprints:PinHeader_1x2_P2.54mm_Drill1.02mm" H 10200 1150 60  0001 L CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 10200 1250 60  0001 L CNN
F 4 "" H 10200 1350 60  0001 L CNN "Digi-Key_PN"
F 5 "22-23-2021" H 10200 1450 60  0001 L CNN "MPN"
F 6 "Connectors, Interconnects" H 10200 1550 60  0001 L CNN "Category"
F 7 "Rectangular Connectors - Headers, Male Pins" H 10200 1650 60  0001 L CNN "Family"
F 8 "https://media.digikey.com/pdf/Data%20Sheets/Molex%20PDFs/A-6373-N_Series_Dwg_2010-12-03.pdf" H 10200 1750 60  0001 L CNN "DK_Datasheet_Link"
F 9 "" H 10200 1850 60  0001 L CNN "DK_Detail_Page"
F 10 "CONN HEADER VERT 2POS 2.54MM" H 10200 1950 60  0001 L CNN "Description"
F 11 "Molex" H 10200 2050 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10200 2150 60  0001 L CNN "Status"
	1    10000 950 
	0    1    1    0   
$EndComp
$Comp
L Device:C C68
U 1 1 60872421
P 8550 3300
F 0 "C68" H 8550 3000 50  0000 L CNN
F 1 "0.1uf 100v" H 8350 3600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 8588 3150 50  0001 C CNN
F 3 "~" H 8550 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/yageo/CC0603KRX7R0BB104/3476112" H 8550 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "311-1523-1-ND" H 8550 3300 50  0001 C CNN "Digi-Key_PN"
	1    8550 3300
	1    0    0    -1  
$EndComp
Connection ~ 8550 3150
Connection ~ 8550 3450
$Comp
L Device:Q_NMOS_GSD Q5
U 1 1 6087C165
P 3300 8350
F 0 "Q5" H 3505 8396 50  0000 L CNN
F 1 "DMN65D8L" H 2450 8300 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3500 8450 50  0001 C CNN
F 3 "~" H 3300 8350 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DMN65D8L-7/3678136" H 3300 8350 50  0001 C CNN "DK_Detail_Page"
F 5 "DMN65D8L-7DICT-ND" H 3300 8350 50  0001 C CNN "Digi-Key_PN"
	1    3300 8350
	-1   0    0    -1  
$EndComp
Connection ~ 3500 8350
$Comp
L Device:Q_NMOS_GSD Q6
U 1 1 608CFE08
P 3300 9500
F 0 "Q6" H 3505 9546 50  0000 L CNN
F 1 "DMN65D8L" H 3505 9455 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3500 9600 50  0001 C CNN
F 3 "~" H 3300 9500 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DMN65D8L-7/3678136" H 3300 9500 50  0001 C CNN "DK_Detail_Page"
F 5 "DMN65D8L-7DICT-ND" H 3300 9500 50  0001 C CNN "Digi-Key_PN"
	1    3300 9500
	-1   0    0    -1  
$EndComp
Connection ~ 3500 9500
$Comp
L Device:Q_NMOS_GSD Q4
U 1 1 608D0A33
P 3300 10700
F 0 "Q4" H 3505 10746 50  0000 L CNN
F 1 "DMN65D8L" H 3505 10655 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 3500 10800 50  0001 C CNN
F 3 "~" H 3300 10700 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DMN65D8L-7/3678136" H 3300 10700 50  0001 C CNN "DK_Detail_Page"
F 5 "DMN65D8L-7DICT-ND" H 3300 10700 50  0001 C CNN "Digi-Key_PN"
	1    3300 10700
	-1   0    0    -1  
$EndComp
Connection ~ 3500 10700
$Comp
L Device:Q_NMOS_GSD Q12
U 1 1 608D11B2
P 6300 10150
F 0 "Q12" H 6505 10196 50  0000 L CNN
F 1 "DMN65D8L" H 6505 10105 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 6500 10250 50  0001 C CNN
F 3 "~" H 6300 10150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DMN65D8L-7/3678136" H 6300 10150 50  0001 C CNN "DK_Detail_Page"
F 5 "DMN65D8L-7DICT-ND" H 6300 10150 50  0001 C CNN "Digi-Key_PN"
	1    6300 10150
	-1   0    0    -1  
$EndComp
Connection ~ 6500 10150
$Comp
L Device:Q_NMOS_GSD Q11
U 1 1 608D1AA0
P 6300 8600
F 0 "Q11" H 6505 8646 50  0000 L CNN
F 1 "DMN65D8L" H 6505 8555 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 6500 8700 50  0001 C CNN
F 3 "~" H 6300 8600 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DMN65D8L-7/3678136" H 6300 8600 50  0001 C CNN "DK_Detail_Page"
F 5 "DMN65D8L-7DICT-ND" H 6300 8600 50  0001 C CNN "Digi-Key_PN"
	1    6300 8600
	-1   0    0    -1  
$EndComp
Connection ~ 6500 8600
$Comp
L Sensor_Current:ACS780xLRTR-050B U2
U 1 1 5E132C0D
P 3150 3900
F 0 "U2" H 3594 3946 50  0000 L CNN
F 1 "ACS780xLRTR-050B" H 3500 4050 50  0000 L CNN
F 2 "Sensor_Current:Allegro_PSOF-7_4.8x6.4mm_P1.60mm" H 3150 3900 50  0001 C CNN
F 3 "http://www.allegromicro.com/~/media/Files/Datasheets/ACS780-Datasheet.ashx?la=en" H 3150 3900 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/allegro-microsystems/ACS780LLRTR-050B-T/6189090" H 3150 3900 50  0001 C CNN "DK_Detail_Page"
F 5 "620-1817-1-ND" H 3150 3900 50  0001 C CNN "Digi-Key_PN"
	1    3150 3900
	1    0    0    -1  
$EndComp
Text Label 1950 4200 0    50   ~ 0
IntBus
Connection ~ 2250 5400
Wire Wire Line
	2250 5400 2550 5400
$Comp
L Device:D_Schottky D43
U 1 1 60B2B401
P 2700 4850
F 0 "D43" H 2650 4950 50  0000 L CNN
F 1 "D_Schottky100V" H 2800 4750 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 2700 4850 50  0001 C CNN
F 3 "~" H 2700 4850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/micro-commercial-co/MBR0580-TP/2423323" H 2700 4850 50  0001 C CNN "DK_Detail_Page"
F 5 "MBR0580-TPMSCT-ND" H 2700 4850 50  0001 C CNN "Digi-Key_PN"
	1    2700 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky D42
U 1 1 60B2BA4E
P 2700 4150
F 0 "D42" H 2600 4250 50  0000 L CNN
F 1 "D_Schottky100V" H 2750 4050 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 2700 4150 50  0001 C CNN
F 3 "~" H 2700 4150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/micro-commercial-co/MBR0580-TP/2423323" H 2700 4150 50  0001 C CNN "DK_Detail_Page"
F 5 "MBR0580-TPMSCT-ND" H 2700 4150 50  0001 C CNN "Digi-Key_PN"
	1    2700 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky D44
U 1 1 60B7B985
P 2700 5650
F 0 "D44" H 2650 5750 50  0000 L CNN
F 1 "D_Schottky100V" H 2800 5700 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 2700 5650 50  0001 C CNN
F 3 "~" H 2700 5650 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/micro-commercial-co/MBR0580-TP/2423323" H 2700 5650 50  0001 C CNN "DK_Detail_Page"
F 5 "MBR0580-TPMSCT-ND" H 2700 5650 50  0001 C CNN "Digi-Key_PN"
	1    2700 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 5700 1950 5400
Wire Wire Line
	1650 5400 1650 5750
$Comp
L BTMS-rescue:A4series-a4series U10
U 1 1 5FB8A273
P 2100 8350
F 0 "U10" V 2146 8072 50  0000 R CNN
F 1 "A41AS12VDC" V 2055 8072 50  0000 R CNN
F 2 "relays:A4series" H 1750 7850 50  0001 C CNN
F 3 "" H 1800 7900 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/cit-relay-and-switch/A41AS12VDC/12503216" H 2100 8350 50  0001 C CNN "DK_Detail_Page"
F 5 "2449-A41AS12VDC-ND" H 2100 8350 50  0001 C CNN "Digi-Key_PN"
	1    2100 8350
	0    -1   -1   0   
$EndComp
$Comp
L BTMS-rescue:A4series-a4series U11
U 1 1 5FB8C6D2
P 2100 9500
F 0 "U11" V 2146 9222 50  0000 R CNN
F 1 "A41AS12VDC" V 2055 9222 50  0000 R CNN
F 2 "relays:A4series" H 1750 9000 50  0001 C CNN
F 3 "" H 1800 9050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/cit-relay-and-switch/A41AS12VDC/12503216" H 2100 9500 50  0001 C CNN "DK_Detail_Page"
F 5 "2449-A41AS12VDC-ND" H 2100 9500 50  0001 C CNN "Digi-Key_PN"
	1    2100 9500
	0    -1   -1   0   
$EndComp
$Comp
L BTMS-rescue:A4series-a4series U12
U 1 1 5FB8DA7B
P 2100 10700
F 0 "U12" V 2146 10422 50  0000 R CNN
F 1 "A41AS12VDC" V 2055 10422 50  0000 R CNN
F 2 "relays:A4series" H 1750 10200 50  0001 C CNN
F 3 "" H 1800 10250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/cit-relay-and-switch/A41AS12VDC/12503216" H 2100 10700 50  0001 C CNN "DK_Detail_Page"
F 5 "2449-A41AS12VDC-ND" H 2100 10700 50  0001 C CNN "Digi-Key_PN"
	1    2100 10700
	0    -1   -1   0   
$EndComp
$Comp
L BTMS-rescue:A4series-a4series U14
U 1 1 5FB8F1EB
P 5050 10150
F 0 "U14" V 5096 9872 50  0000 R CNN
F 1 "A41AS12VDC" V 5005 9872 50  0000 R CNN
F 2 "relays:A4series" H 4700 9650 50  0001 C CNN
F 3 "" H 4750 9700 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/cit-relay-and-switch/A41AS12VDC/12503216" H 5050 10150 50  0001 C CNN "DK_Detail_Page"
F 5 "2449-A41AS12VDC-ND" H 5050 10150 50  0001 C CNN "Digi-Key_PN"
	1    5050 10150
	0    -1   -1   0   
$EndComp
Connection ~ 5200 9700
$Comp
L BTMS-rescue:A4series-a4series U13
U 1 1 5FB905AA
P 5050 8600
F 0 "U13" V 5096 8322 50  0000 R CNN
F 1 "A41AS12VDC" V 5005 8322 50  0000 R CNN
F 2 "relays:A4series" H 4700 8100 50  0001 C CNN
F 3 "" H 4750 8150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/cit-relay-and-switch/A41AS12VDC/12503216" H 5050 8600 50  0001 C CNN "DK_Detail_Page"
F 5 "2449-A41AS12VDC-ND" H 5050 8600 50  0001 C CNN "Digi-Key_PN"
	1    5050 8600
	0    -1   -1   0   
$EndComp
Connection ~ 5200 8150
Wire Wire Line
	4950 8150 4850 8150
Wire Wire Line
	4850 8150 4850 8050
Wire Wire Line
	4950 9700 4850 9700
Wire Wire Line
	4850 9700 4850 9600
Wire Wire Line
	5350 8400 5350 9050
Wire Wire Line
	5350 9050 5200 9050
Wire Wire Line
	5350 9950 5350 10600
Wire Wire Line
	5350 10600 5200 10600
Connection ~ 2250 9050
Connection ~ 2250 10250
Connection ~ 2250 7900
Wire Wire Line
	1300 8900 2000 8900
Wire Wire Line
	2000 8900 2000 9050
Wire Wire Line
	1300 8900 1300 7850
Wire Wire Line
	1300 7850 2000 7850
Wire Wire Line
	2000 7850 2000 7900
Wire Wire Line
	2000 10250 2000 10100
Wire Wire Line
	2250 8800 2500 8800
Wire Wire Line
	2500 8800 2500 8150
Wire Wire Line
	2500 8150 2750 8150
Wire Wire Line
	2250 9950 2500 9950
Wire Wire Line
	2500 9950 2500 9300
Wire Wire Line
	2500 9300 2750 9300
Wire Wire Line
	2250 11150 2500 11150
Wire Wire Line
	2500 11150 2500 10500
Wire Wire Line
	2500 10500 2750 10500
Wire Wire Line
	1100 10150 850  10150
Wire Wire Line
	4550 8600 4450 8600
Wire Wire Line
	4450 8600 4450 8050
Wire Wire Line
	4450 8050 4750 8050
Wire Wire Line
	4550 10150 4450 10150
Wire Wire Line
	4450 10150 4450 9600
Wire Wire Line
	4450 9600 4750 9600
Wire Wire Line
	2650 2000 2450 2000
Wire Wire Line
	2650 2400 2650 2000
$Comp
L Device:CP C69
U 1 1 5FB5C4BB
P 11000 3300
F 0 "C69" H 11000 3550 50  0000 L CNN
F 1 "10uf 25v" H 10950 2950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 11038 3150 50  0001 C CNN
F 3 "~" H 11000 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 11000 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 11000 3300 50  0001 C CNN "Digi-Key_PN"
	1    11000 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C70
U 1 1 5FBAA5D2
P 11250 3300
F 0 "C70" H 11250 3550 50  0000 L CNN
F 1 "10uf 25v" H 11100 3050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 11288 3150 50  0001 C CNN
F 3 "~" H 11250 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 11250 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 11250 3300 50  0001 C CNN "Digi-Key_PN"
	1    11250 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C71
U 1 1 5FBF85F3
P 11500 3300
F 0 "C71" H 11500 3550 50  0000 L CNN
F 1 "10uf 25v" H 11350 2950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 11538 3150 50  0001 C CNN
F 3 "~" H 11500 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 11500 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 11500 3300 50  0001 C CNN "Digi-Key_PN"
	1    11500 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C72
U 1 1 5FC465A8
P 11750 3300
F 0 "C72" H 11750 3550 50  0000 L CNN
F 1 "10uf 25v" H 11600 3100 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 11788 3150 50  0001 C CNN
F 3 "~" H 11750 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 11750 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 11750 3300 50  0001 C CNN "Digi-Key_PN"
	1    11750 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	11750 3150 11500 3150
Connection ~ 11500 3150
Wire Wire Line
	11000 3150 11250 3150
Connection ~ 11250 3150
Wire Wire Line
	11250 3150 11500 3150
Wire Wire Line
	10750 3150 11000 3150
Connection ~ 10750 3150
Connection ~ 11000 3150
Wire Wire Line
	10750 3450 11000 3450
Wire Wire Line
	11250 3450 11000 3450
Connection ~ 11000 3450
Wire Wire Line
	11500 3450 11250 3450
Connection ~ 11250 3450
Wire Wire Line
	11750 3450 11500 3450
Connection ~ 11500 3450
$Comp
L Device:CP C73
U 1 1 5FF85A6F
P 6900 3300
F 0 "C73" H 6900 3550 50  0000 L CNN
F 1 "10uf 25v" H 6700 3050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 6938 3150 50  0001 C CNN
F 3 "~" H 6900 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 6900 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 6900 3300 50  0001 C CNN "Digi-Key_PN"
	1    6900 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C74
U 1 1 60028B4F
P 8000 3300
F 0 "C74" H 8000 3550 50  0000 L CNN
F 1 "10uf 25v" H 7950 3050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8038 3150 50  0001 C CNN
F 3 "~" H 8000 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 8000 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 8000 3300 50  0001 C CNN "Digi-Key_PN"
	1    8000 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 3150 8000 3150
Connection ~ 8000 3150
Wire Wire Line
	8000 3150 8250 3150
Wire Wire Line
	7700 3450 8000 3450
Connection ~ 7700 3450
Connection ~ 8000 3450
Wire Wire Line
	6550 3150 6900 3150
Connection ~ 6900 3150
Wire Wire Line
	6550 3450 6900 3450
Connection ~ 6550 3450
Connection ~ 6900 3450
$Comp
L Device:C C75
U 1 1 5FBC19E5
P 10650 1200
F 0 "C75" H 10765 1246 50  0000 L CNN
F 1 "0.1uf film" H 10765 1155 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 10688 1050 50  0001 C CNN
F 3 "~" H 10650 1200 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 10650 1200 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 10650 1200 50  0001 C CNN "Digi-Key_PN"
	1    10650 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	10650 1350 10350 1350
Wire Wire Line
	10350 1350 10350 1100
Wire Wire Line
	10350 1100 10250 1100
Connection ~ 10250 1100
$Comp
L power:+12V #PWR0132
U 1 1 5FD3E6AD
P 6600 750
F 0 "#PWR0132" H 6600 600 50  0001 C CNN
F 1 "+12V" H 6615 923 50  0000 C CNN
F 2 "" H 6600 750 50  0001 C CNN
F 3 "" H 6600 750 50  0001 C CNN
	1    6600 750 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0133
U 1 1 5FD3E97F
P 6600 1350
F 0 "#PWR0133" H 6600 1100 50  0001 C CNN
F 1 "GND" H 6605 1177 50  0000 C CNN
F 2 "" H 6600 1350 50  0001 C CNN
F 3 "" H 6600 1350 50  0001 C CNN
	1    6600 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Zener D45
U 1 1 5FD3F709
P 6600 900
F 0 "D45" V 6550 750 50  0000 L CNN
F 1 "15V" V 6700 700 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 6600 900 50  0001 C CNN
F 3 "~" H 6600 900 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 6600 900 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 6600 900 50  0001 C CNN "Digi-Key_PN"
	1    6600 900 
	0    1    1    0   
$EndComp
$Comp
L Device:R R52
U 1 1 5FD40ACE
P 6600 1200
F 0 "R52" H 6670 1246 50  0000 L CNN
F 1 "1K" H 6670 1155 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 6530 1200 50  0001 C CNN
F 3 "~" H 6600 1200 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 6600 1200 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 6600 1200 50  0001 C CNN "Digi-Key_PN"
	1    6600 1200
	-1   0    0    1   
$EndComp
$Comp
L Device:C C76
U 1 1 5FD43655
P 6800 1200
F 0 "C76" H 6800 900 50  0000 L CNN
F 1 "0.1uf film" H 6700 1500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 6838 1050 50  0001 C CNN
F 3 "~" H 6800 1200 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 6800 1200 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 6800 1200 50  0001 C CNN "Digi-Key_PN"
	1    6800 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 1050 6600 1050
Connection ~ 6600 1050
Wire Wire Line
	6600 1350 6800 1350
Connection ~ 6600 1350
$Comp
L Device:Q_SCR_KAG D46
U 1 1 5FDEE2C1
P 6950 950
F 0 "D46" H 7038 996 50  0000 L CNN
F 1 "Q_SCR_KAG" H 7038 905 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:TO-252-2" V 6950 950 50  0001 C CNN
F 3 "~" V 6950 950 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/ween-semiconductors/BT151S-650R118/1155195" H 6950 950 50  0001 C CNN "DK_Detail_Page"
F 5 "1740-1071-1-ND" H 6950 950 50  0001 C CNN "Digi-Key_PN"
	1    6950 950 
	1    0    0    -1  
$EndComp
Connection ~ 6800 1050
Wire Wire Line
	6950 800  6950 750 
Wire Wire Line
	6950 750  6600 750 
Connection ~ 6600 750 
Wire Wire Line
	6950 1100 6950 1350
Wire Wire Line
	6950 1350 6800 1350
Connection ~ 6800 1350
$Comp
L Device:CP C81
U 1 1 5FB760BB
P 11850 6050
F 0 "C81" H 11850 6300 50  0000 L CNN
F 1 "10uf 25v" H 11800 5800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 11888 5900 50  0001 C CNN
F 3 "~" H 11850 6050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 11850 6050 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 11850 6050 50  0001 C CNN "Digi-Key_PN"
	1    11850 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C80
U 1 1 5FB769E3
P 11600 6050
F 0 "C80" H 11600 6300 50  0000 L CNN
F 1 "10uf 25v" H 11550 5800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 11638 5900 50  0001 C CNN
F 3 "~" H 11600 6050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 11600 6050 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 11600 6050 50  0001 C CNN "Digi-Key_PN"
	1    11600 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C79
U 1 1 5FB76C9B
P 11350 6050
F 0 "C79" H 11350 6300 50  0000 L CNN
F 1 "10uf 25v" H 11300 5800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 11388 5900 50  0001 C CNN
F 3 "~" H 11350 6050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 11350 6050 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 11350 6050 50  0001 C CNN "Digi-Key_PN"
	1    11350 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C78
U 1 1 5FB76EBB
P 11100 6050
F 0 "C78" H 11100 6300 50  0000 L CNN
F 1 "10uf 25v" H 11050 5800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 11138 5900 50  0001 C CNN
F 3 "~" H 11100 6050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 11100 6050 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 11100 6050 50  0001 C CNN "Digi-Key_PN"
	1    11100 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C77
U 1 1 5FB7718E
P 10850 6050
F 0 "C77" H 10850 6300 50  0000 L CNN
F 1 "10uf 25v" H 10800 5800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 10888 5900 50  0001 C CNN
F 3 "~" H 10850 6050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 10850 6050 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 10850 6050 50  0001 C CNN "Digi-Key_PN"
	1    10850 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	12100 5900 11850 5900
Connection ~ 12100 5900
Wire Wire Line
	11850 5900 11600 5900
Connection ~ 11850 5900
Wire Wire Line
	11600 5900 11350 5900
Connection ~ 11600 5900
Wire Wire Line
	10850 5900 11100 5900
Wire Wire Line
	11350 5900 11100 5900
Connection ~ 11350 5900
Connection ~ 11100 5900
Wire Wire Line
	11850 6200 12100 6200
Wire Wire Line
	11850 6200 11600 6200
Connection ~ 11850 6200
Wire Wire Line
	11600 6200 11350 6200
Connection ~ 11600 6200
Wire Wire Line
	11350 6200 11100 6200
Connection ~ 11350 6200
Wire Wire Line
	11100 6200 10850 6200
Connection ~ 11100 6200
$Comp
L Device:CP C83
U 1 1 5FEFFC37
P 10600 6050
F 0 "C83" H 10600 6300 50  0000 L CNN
F 1 "10uf 25v" H 10550 5800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 10638 5900 50  0001 C CNN
F 3 "~" H 10600 6050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 10600 6050 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 10600 6050 50  0001 C CNN "Digi-Key_PN"
	1    10600 6050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C82
U 1 1 5FEFFF0B
P 10350 6050
F 0 "C82" H 10350 6300 50  0000 L CNN
F 1 "10uf 25v" H 10300 5800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 10388 5900 50  0001 C CNN
F 3 "~" H 10350 6050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 10350 6050 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 10350 6050 50  0001 C CNN "Digi-Key_PN"
	1    10350 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	10850 5900 10600 5900
Connection ~ 10850 5900
Wire Wire Line
	10600 5900 10350 5900
Connection ~ 10600 5900
Wire Wire Line
	10600 6200 10850 6200
Connection ~ 10850 6200
Wire Wire Line
	10350 6200 10600 6200
Connection ~ 10600 6200
$Comp
L power:+5C #PWR0122
U 1 1 6017DCBC
P 10650 750
F 0 "#PWR0122" H 10650 600 50  0001 C CNN
F 1 "+5C" H 10665 923 50  0000 C CNN
F 2 "" H 10650 750 50  0001 C CNN
F 3 "" H 10650 750 50  0001 C CNN
	1    10650 750 
	1    0    0    -1  
$EndComp
$Comp
L power:+5C #PWR0103
U 1 1 60184476
P 14050 1700
F 0 "#PWR0103" H 14050 1550 50  0001 C CNN
F 1 "+5C" H 14065 1873 50  0000 C CNN
F 2 "" H 14050 1700 50  0001 C CNN
F 3 "" H 14050 1700 50  0001 C CNN
	1    14050 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	13450 2000 13350 2000
$Comp
L power:+5C #PWR0111
U 1 1 602416A0
P 14700 2050
F 0 "#PWR0111" H 14700 1900 50  0001 C CNN
F 1 "+5C" H 14715 2223 50  0000 C CNN
F 2 "" H 14700 2050 50  0001 C CNN
F 3 "" H 14700 2050 50  0001 C CNN
	1    14700 2050
	1    0    0    -1  
$EndComp
$Comp
L power:+5C #PWR0114
U 1 1 60241AD7
P 8600 1000
F 0 "#PWR0114" H 8600 850 50  0001 C CNN
F 1 "+5C" H 8615 1173 50  0000 C CNN
F 2 "" H 8600 1000 50  0001 C CNN
F 3 "" H 8600 1000 50  0001 C CNN
	1    8600 1000
	1    0    0    -1  
$EndComp
Connection ~ 5350 1300
$Comp
L power:+5C #PWR0116
U 1 1 6036F5E3
P 5900 1000
F 0 "#PWR0116" H 5900 850 50  0001 C CNN
F 1 "+5C" H 5915 1173 50  0000 C CNN
F 2 "" H 5900 1000 50  0001 C CNN
F 3 "" H 5900 1000 50  0001 C CNN
	1    5900 1000
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C84
U 1 1 6043AEFC
P 6350 2550
F 0 "C84" H 6350 2800 50  0000 L CNN
F 1 "10uf 25v" H 6300 2300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 6388 2400 50  0001 C CNN
F 3 "~" H 6350 2550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 6350 2550 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 6350 2550 50  0001 C CNN "Digi-Key_PN"
	1    6350 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C85
U 1 1 6043B29C
P 6600 2550
F 0 "C85" H 6600 2800 50  0000 L CNN
F 1 "10uf 25v" H 6550 2300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 6638 2400 50  0001 C CNN
F 3 "~" H 6600 2550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 6600 2550 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 6600 2550 50  0001 C CNN "Digi-Key_PN"
	1    6600 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C86
U 1 1 6043B623
P 6850 2550
F 0 "C86" H 6850 2800 50  0000 L CNN
F 1 "10uf 25v" H 6800 2300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 6888 2400 50  0001 C CNN
F 3 "~" H 6850 2550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 6850 2550 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 6850 2550 50  0001 C CNN "Digi-Key_PN"
	1    6850 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C87
U 1 1 6043B959
P 7100 2550
F 0 "C87" H 7100 2800 50  0000 L CNN
F 1 "10uf 25v" H 7050 2300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7138 2400 50  0001 C CNN
F 3 "~" H 7100 2550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 7100 2550 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 7100 2550 50  0001 C CNN "Digi-Key_PN"
	1    7100 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 2700 6850 2700
Wire Wire Line
	6600 2700 6850 2700
Connection ~ 6850 2700
Connection ~ 6600 2700
Wire Wire Line
	6350 2400 6600 2400
Wire Wire Line
	7100 2400 6850 2400
Wire Wire Line
	6600 2400 6850 2400
Connection ~ 6600 2400
Connection ~ 6850 2400
$Comp
L power:GND #PWR0134
U 1 1 60661CD0
P 6850 2700
F 0 "#PWR0134" H 6850 2450 50  0001 C CNN
F 1 "GND" H 6855 2527 50  0000 C CNN
F 2 "" H 6850 2700 50  0001 C CNN
F 3 "" H 6850 2700 50  0001 C CNN
	1    6850 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C88
U 1 1 60663062
P 7950 2550
F 0 "C88" H 7950 2800 50  0000 L CNN
F 1 "10uf 25v" H 7900 2300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7988 2400 50  0001 C CNN
F 3 "~" H 7950 2550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 7950 2550 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 7950 2550 50  0001 C CNN "Digi-Key_PN"
	1    7950 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C89
U 1 1 606634FD
P 8200 2550
F 0 "C89" H 8200 2800 50  0000 L CNN
F 1 "10uf 25v" H 8150 2300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8238 2400 50  0001 C CNN
F 3 "~" H 8200 2550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 8200 2550 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 8200 2550 50  0001 C CNN "Digi-Key_PN"
	1    8200 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C90
U 1 1 606638DF
P 8450 2550
F 0 "C90" H 8450 2800 50  0000 L CNN
F 1 "10uf 25v" H 8400 2300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8488 2400 50  0001 C CNN
F 3 "~" H 8450 2550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 8450 2550 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 8450 2550 50  0001 C CNN "Digi-Key_PN"
	1    8450 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C91
U 1 1 60663B7F
P 8700 2550
F 0 "C91" H 8700 2800 50  0000 L CNN
F 1 "10uf 25v" H 8650 2300 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8738 2400 50  0001 C CNN
F 3 "~" H 8700 2550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 8700 2550 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 8700 2550 50  0001 C CNN "Digi-Key_PN"
	1    8700 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 2700 8450 2700
Wire Wire Line
	7950 2700 8200 2700
Wire Wire Line
	8200 2400 7950 2400
Wire Wire Line
	8450 2400 8700 2400
Wire Wire Line
	8450 2400 8200 2400
Connection ~ 8450 2400
Connection ~ 8200 2400
Wire Wire Line
	8200 2700 8450 2700
Connection ~ 8200 2700
Connection ~ 8450 2700
$Comp
L power:GND #PWR0135
U 1 1 608991BA
P 8450 2700
F 0 "#PWR0135" H 8450 2450 50  0001 C CNN
F 1 "GND" H 8455 2527 50  0000 C CNN
F 2 "" H 8450 2700 50  0001 C CNN
F 3 "" H 8450 2700 50  0001 C CNN
	1    8450 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 2400 7700 2400
Wire Wire Line
	7700 2400 7700 2850
Connection ~ 7950 2400
Connection ~ 7700 2850
Wire Wire Line
	7100 2400 7250 2400
Wire Wire Line
	7250 2400 7250 2850
Connection ~ 7100 2400
Connection ~ 7250 2850
$Comp
L Device:Q_PMOS_GSD Q13
U 1 1 5FB95497
P 15500 2150
F 0 "Q13" V 15842 2150 50  0000 C CNN
F 1 "FDN340P" V 16000 2150 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 15700 2250 50  0001 C CNN
F 3 "~" H 15500 2150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/on-semiconductor/FDN340P/965604" H 15500 2150 50  0001 C CNN "DK_Detail_Page"
F 5 "FDN340PCT-ND" H 15500 2150 50  0001 C CNN "Digi-Key_PN"
	1    15500 2150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	15800 2050 15700 2050
Connection ~ 15700 2050
Wire Wire Line
	15500 2350 14900 2350
Connection ~ 15500 2350
Wire Wire Line
	15100 2050 15100 1900
Wire Wire Line
	15100 1900 15800 1900
Wire Wire Line
	15800 1900 15800 2050
Connection ~ 15800 2050
Wire Wire Line
	15300 2050 15300 1850
Wire Wire Line
	15300 1850 14600 1850
Wire Wire Line
	14600 1850 14600 2050
Wire Wire Line
	14600 2050 14700 2050
Connection ~ 14700 2050
$Comp
L Mechanical:MountingHole_Pad H17
U 1 1 5FBA0D4B
P 800 7500
F 0 "H17" V 1037 7503 50  0000 C CNN
F 1 "mnt" V 946 7503 50  0000 C CNN
F 2 "Connect:1pin" H 800 7500 50  0001 C CNN
F 3 "~" H 800 7500 50  0001 C CNN
	1    800  7500
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0136
U 1 1 5FBA0D55
P 900 7500
F 0 "#PWR0136" H 900 7250 50  0001 C CNN
F 1 "GND" H 905 7327 50  0000 C CNN
F 2 "" H 900 7500 50  0001 C CNN
F 3 "" H 900 7500 50  0001 C CNN
	1    900  7500
	1    0    0    -1  
$EndComp
Connection ~ 8400 5400
Text Label 9700 5100 0    50   ~ 0
IntBus
Wire Wire Line
	7250 5100 7600 5100
Wire Wire Line
	7250 5400 7600 5400
$Comp
L Device:CP C93
U 1 1 5FC0D677
P 7600 5250
F 0 "C93" H 7750 5300 50  0000 L CNN
F 1 "10uf 100v" H 7500 5550 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 7638 5100 50  0001 C CNN
F 3 "~" H 7600 5250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 7600 5250 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 7600 5250 50  0001 C CNN "Digi-Key_PN"
	1    7600 5250
	1    0    0    -1  
$EndComp
Connection ~ 7600 5100
Connection ~ 7600 5400
$Comp
L Device:CP C92
U 1 1 5FC0D685
P 7250 5250
F 0 "C92" H 7365 5296 50  0000 L CNN
F 1 "10uf 100v" H 7150 5550 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 7288 5100 50  0001 C CNN
F 3 "~" H 7250 5250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 7250 5250 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 7250 5250 50  0001 C CNN "Digi-Key_PN"
	1    7250 5250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0139
U 1 1 5FE94E27
P 8400 4900
F 0 "#PWR0139" H 8400 4650 50  0001 C CNN
F 1 "GND" H 8300 4800 50  0000 C CNN
F 2 "" H 8400 4900 50  0001 C CNN
F 3 "" H 8400 4900 50  0001 C CNN
	1    8400 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0141
U 1 1 5FE950AC
P 8400 5400
F 0 "#PWR0141" H 8400 5150 50  0001 C CNN
F 1 "GND" H 8300 5300 50  0000 C CNN
F 2 "" H 8400 5400 50  0001 C CNN
F 3 "" H 8400 5400 50  0001 C CNN
	1    8400 5400
	1    0    0    -1  
$EndComp
Text Label 9700 5600 0    50   ~ 0
ChargeIn
$Comp
L Device:C C99
U 1 1 5FBC858B
P 4850 4950
F 0 "C99" H 4965 4996 50  0000 L CNN
F 1 "1uf 25v" H 4965 4905 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 4888 4800 50  0001 C CNN
F 3 "~" H 4850 4950 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10A105KA8NNNC/3886760" H 4850 4950 50  0001 C CNN "DK_Detail_Page"
F 5 "1276-1102-1-ND" H 4850 4950 50  0001 C CNN "Digi-Key_PN"
	1    4850 4950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C100
U 1 1 5FBC8A76
P 5150 4950
F 0 "C100" H 5265 4996 50  0000 L CNN
F 1 "1uf 25v" H 5265 4905 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5188 4800 50  0001 C CNN
F 3 "~" H 5150 4950 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10A105KA8NNNC/3886760" H 5150 4950 50  0001 C CNN "DK_Detail_Page"
F 5 "1276-1102-1-ND" H 5150 4950 50  0001 C CNN "Digi-Key_PN"
	1    5150 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 5100 4850 5100
Wire Wire Line
	4850 5100 4550 5100
Connection ~ 4850 5100
Wire Wire Line
	4850 4800 4550 4800
Wire Wire Line
	5150 4800 4850 4800
Connection ~ 4850 4800
Connection ~ 5150 4800
Connection ~ 5150 5100
Wire Wire Line
	5950 3150 6250 3150
Wire Wire Line
	5950 3450 6250 3450
$Comp
L Device:C C102
U 1 1 5FF3FB62
P 6250 3300
F 0 "C102" H 6200 2950 50  0000 L CNN
F 1 "0.1uf 100v" H 5950 3050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 6288 3150 50  0001 C CNN
F 3 "~" H 6250 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/yageo/CC0603KRX7R0BB104/3476112" H 6250 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "311-1523-1-ND" H 6250 3300 50  0001 C CNN "Digi-Key_PN"
	1    6250 3300
	1    0    0    -1  
$EndComp
Connection ~ 6250 3450
Wire Wire Line
	6250 3450 6550 3450
$Comp
L Device:R R53
U 1 1 5FF5FFF3
P 2250 800
F 0 "R53" H 2320 846 50  0000 L CNN
F 1 "10K" H 2320 755 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 2180 800 50  0001 C CNN
F 3 "~" H 2250 800 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/ESR03EZPJ103/1762722" H 2250 800 50  0001 C CNN "DK_Detail_Page"
F 5 "RHM10KDCT-ND" H 2250 800 50  0001 C CNN "Digi-Key_PN"
	1    2250 800 
	-1   0    0    1   
$EndComp
$Comp
L Device:D_Zener D49
U 1 1 600382D7
P 3050 1000
F 0 "D49" V 3000 850 50  0000 L CNN
F 1 "15V" V 3150 800 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 3050 1000 50  0001 C CNN
F 3 "~" H 3050 1000 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 3050 1000 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 3050 1000 50  0001 C CNN "Digi-Key_PN"
	1    3050 1000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R7
U 1 1 60143459
P 3200 2300
F 0 "R7" H 3270 2346 50  0000 L CNN
F 1 "16K" H 3270 2255 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 3130 2300 50  0001 C CNN
F 3 "~" H 3200 2300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/vishay-dale/CRCW060316K0FKEAHP/2226306" H 3200 2300 50  0001 C CNN "DK_Detail_Page"
F 5 "541-CRCW060316K0FKEAHPCT-ND" H 3200 2300 50  0001 C CNN "Digi-Key_PN"
	1    3200 2300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R54
U 1 1 602F2B0D
P 3200 2500
F 0 "R54" H 3270 2546 50  0000 L CNN
F 1 "16K" H 3270 2455 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 3130 2500 50  0001 C CNN
F 3 "~" H 3200 2500 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/vishay-dale/CRCW060316K0FKEAHP/2226306" H 3200 2500 50  0001 C CNN "DK_Detail_Page"
F 5 "541-CRCW060316K0FKEAHPCT-ND" H 3200 2500 50  0001 C CNN "Digi-Key_PN"
	1    3200 2500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3350 2300 3350 2400
Wire Wire Line
	3350 2500 3350 2400
Connection ~ 3350 2400
Wire Wire Line
	3050 2400 3050 2300
Wire Wire Line
	3050 2400 3050 2500
Connection ~ 3050 2400
$Comp
L Device:D_Zener D50
U 1 1 5FBE01B9
P 6000 4950
F 0 "D50" V 5954 5029 50  0000 L CNN
F 1 "15V" V 6100 4800 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 6000 4950 50  0001 C CNN
F 3 "~" H 6000 4950 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 6000 4950 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 6000 4950 50  0001 C CNN "Digi-Key_PN"
	1    6000 4950
	0    -1   1    0   
$EndComp
$Comp
L Device:D_Zener D51
U 1 1 5FCBF48A
P 6100 2550
F 0 "D51" V 6054 2629 50  0000 L CNN
F 1 "15V" V 6145 2629 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 6100 2550 50  0001 C CNN
F 3 "~" H 6100 2550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 6100 2550 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 6100 2550 50  0001 C CNN "Digi-Key_PN"
	1    6100 2550
	0    -1   1    0   
$EndComp
$Comp
L Device:D_Zener D52
U 1 1 5FCC06E8
P 8950 2550
F 0 "D52" V 8904 2629 50  0000 L CNN
F 1 "15V" V 8995 2629 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 8950 2550 50  0001 C CNN
F 3 "~" H 8950 2550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DDZ15-7/3877405" H 8950 2550 50  0001 C CNN "DK_Detail_Page"
F 5 "DDZ15-7DICT-ND" H 8950 2550 50  0001 C CNN "Digi-Key_PN"
	1    8950 2550
	0    -1   1    0   
$EndComp
Wire Wire Line
	8950 2400 8700 2400
Connection ~ 8700 2400
Wire Wire Line
	8700 2700 8950 2700
Connection ~ 8700 2700
Wire Wire Line
	6350 2400 6100 2400
Connection ~ 6350 2400
Wire Wire Line
	6100 2700 6350 2700
Connection ~ 6350 2700
Wire Wire Line
	6350 2700 6600 2700
Text Label 11550 7250 2    50   ~ 0
Mctrl-
Wire Wire Line
	11650 7250 11550 7250
Text Label 5650 5500 0    50   ~ 0
Mctrl-
Wire Wire Line
	3300 800  3300 1000
Connection ~ 3300 1500
Wire Wire Line
	3300 1500 3350 1500
Wire Wire Line
	2800 800  2800 1000
Wire Wire Line
	2900 1250 2800 1250
Connection ~ 2800 1250
Wire Wire Line
	2800 1250 2800 1500
Wire Wire Line
	3200 1250 3300 1250
Connection ~ 3300 1250
Wire Wire Line
	3300 1250 3300 1500
Wire Wire Line
	3200 1000 3300 1000
Connection ~ 3300 1000
Wire Wire Line
	3300 1000 3300 1250
Wire Wire Line
	2900 1000 2800 1000
Connection ~ 2800 1000
Wire Wire Line
	2800 1000 2800 1250
Wire Wire Line
	2250 950  2450 950 
Wire Wire Line
	2450 950  2450 1200
Connection ~ 2450 950 
Connection ~ 2450 1200
Wire Wire Line
	2250 650  2450 650 
Wire Wire Line
	2450 650  2450 500 
Wire Wire Line
	2450 500  3300 500 
Wire Wire Line
	3300 500  3300 600 
Connection ~ 2450 650 
Connection ~ 3300 600 
$Comp
L Device:R R51
U 1 1 600D45F1
P 2400 5000
F 0 "R51" V 2300 4950 50  0000 L CNN
F 1 "3" V 2400 4950 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 2330 5000 50  0001 C CNN
F 3 "~" H 2400 5000 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/SDR03EZPJ3R0/9675019" H 2400 5000 50  0001 C CNN "DK_Detail_Page"
F 5 "511-1769-1-ND" H 2400 5000 50  0001 C CNN "Digi-Key_PN"
	1    2400 5000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1650 5400 1800 5400
Wire Wire Line
	1850 4200 1850 4900
Wire Wire Line
	1800 4700 1800 5400
Connection ~ 1800 5400
Wire Wire Line
	1800 5400 1950 5400
$Comp
L Device:R R38
U 1 1 602976E4
P 2400 4300
F 0 "R38" V 2300 4250 50  0000 L CNN
F 1 "3" V 2400 4250 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 2330 4300 50  0001 C CNN
F 3 "~" H 2400 4300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/SDR03EZPJ3R0/9675019" H 2400 4300 50  0001 C CNN "DK_Detail_Page"
F 5 "511-1769-1-ND" H 2400 4300 50  0001 C CNN "Digi-Key_PN"
	1    2400 4300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R55
U 1 1 603F0F7D
P 2400 5800
F 0 "R55" V 2300 5750 50  0000 L CNN
F 1 "3" V 2400 5800 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 2330 5800 50  0001 C CNN
F 3 "~" H 2400 5800 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/rohm-semiconductor/SDR03EZPJ3R0/9675019" H 2400 5800 50  0001 C CNN "DK_Detail_Page"
F 5 "511-1769-1-ND" H 2400 5800 50  0001 C CNN "Digi-Key_PN"
	1    2400 5800
	0    -1   -1   0   
$EndComp
Connection ~ 3600 5400
Wire Wire Line
	3450 5600 3450 5400
Wire Wire Line
	3450 5400 3600 5400
$Comp
L Device:Q_PNP_BEC Q14
U 1 1 5FD93D39
P 2650 5200
F 0 "Q14" H 2450 5350 50  0000 L CNN
F 1 "ZXTP2025FTA" H 2050 5250 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 2850 5300 50  0001 C CNN
F 3 "~" H 2650 5200 50  0001 C CNN
F 4 "ZXTP2025FCT-ND" H 2650 5200 50  0001 C CNN "Digi-Key_PN"
F 5 "https://www.digikey.com/en/products/detail/diodes-incorporated/ZXTP2025FTA/1089895" H 2650 5200 50  0001 C CNN "DK_Detail_Page"
	1    2650 5200
	-1   0    0    1   
$EndComp
Connection ~ 2550 5400
$Comp
L Device:Q_PNP_BEC Q15
U 1 1 5FF1A741
P 2650 4500
F 0 "Q15" H 2550 4650 50  0000 L CNN
F 1 "ZXTP2025FTA" H 2050 4550 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 2850 4600 50  0001 C CNN
F 3 "~" H 2650 4500 50  0001 C CNN
F 4 "ZXTP2025FCT-ND" H 2650 4500 50  0001 C CNN "Digi-Key_PN"
F 5 "https://www.digikey.com/en/products/detail/diodes-incorporated/ZXTP2025FTA/1089895" H 2650 4500 50  0001 C CNN "DK_Detail_Page"
	1    2650 4500
	-1   0    0    1   
$EndComp
Wire Wire Line
	2550 4700 2250 4700
Connection ~ 2250 4700
Wire Wire Line
	2250 4300 2250 4400
Connection ~ 2250 4400
Wire Wire Line
	2250 5000 2250 5100
Connection ~ 2250 5100
Wire Wire Line
	2850 4150 2850 4500
Wire Wire Line
	2850 4500 2850 4850
Connection ~ 2850 4500
Connection ~ 2850 4850
Wire Wire Line
	2850 4850 2850 5200
Connection ~ 2850 5200
Wire Wire Line
	2250 4850 2250 5000
Connection ~ 2250 5000
Wire Wire Line
	2250 4150 2250 4300
Connection ~ 2250 4300
$Comp
L Device:Q_PNP_BEC Q16
U 1 1 603A2D50
P 2650 6000
F 0 "Q16" H 2450 6150 50  0000 L CNN
F 1 "ZXTP2025FTA" H 2050 6050 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 2850 6100 50  0001 C CNN
F 3 "~" H 2650 6000 50  0001 C CNN
F 4 "ZXTP2025FCT-ND" H 2650 6000 50  0001 C CNN "Digi-Key_PN"
F 5 "https://www.digikey.com/en/products/detail/diodes-incorporated/ZXTP2025FTA/1089895" H 2650 6000 50  0001 C CNN "DK_Detail_Page"
	1    2650 6000
	-1   0    0    1   
$EndComp
Wire Wire Line
	2250 5900 2250 5800
Connection ~ 2250 5900
Wire Wire Line
	2250 5650 2250 5800
Connection ~ 2250 5800
Wire Wire Line
	2250 6200 2550 6200
Connection ~ 2250 6200
Wire Wire Line
	2850 5650 2850 6000
Wire Wire Line
	3450 5900 3250 5900
Wire Wire Line
	3050 5900 3050 5400
Wire Wire Line
	2550 5400 3050 5400
Connection ~ 3450 5900
$Comp
L Mechanical:MountingHole_Pad H18
U 1 1 5FEA0693
P 800 5550
F 0 "H18" V 1037 5553 50  0000 C CNN
F 1 "mnt" V 946 5553 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_2.7mm" H 800 5550 50  0001 C CNN
F 3 "~" H 800 5550 50  0001 C CNN
	1    800  5550
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H19
U 1 1 5FF1522F
P 800 5800
F 0 "H19" V 1037 5803 50  0000 C CNN
F 1 "mnt" V 946 5803 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_2.7mm" H 800 5800 50  0001 C CNN
F 3 "~" H 800 5800 50  0001 C CNN
	1    800  5800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7600 4400 8100 4400
Wire Wire Line
	7600 4100 8100 4100
Wire Wire Line
	8400 4400 8500 4400
Wire Wire Line
	8400 4900 8500 4900
Wire Wire Line
	7600 4600 8100 4600
Wire Wire Line
	7600 4900 8100 4900
Wire Wire Line
	7600 5400 8100 5400
Wire Wire Line
	7600 5100 8100 5100
Wire Wire Line
	8400 5400 8500 5400
Wire Wire Line
	7600 5600 8100 5600
Wire Wire Line
	7600 5900 8100 5900
Wire Wire Line
	7600 6150 8100 6150
Wire Wire Line
	7600 6450 8100 6450
Wire Wire Line
	8500 6700 8950 6700
Wire Wire Line
	8500 7000 8950 7000
Wire Wire Line
	7600 7250 8100 7250
Wire Wire Line
	7600 7550 8100 7550
$Comp
L Device:C C95
U 1 1 5FE1B41A
P 9700 4250
F 0 "C95" H 9750 4350 50  0000 L CNN
F 1 "1uf 100v" H 9700 4000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 9738 4100 50  0001 C CNN
F 3 "~" H 9700 4250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 9700 4250 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 9700 4250 50  0001 C CNN "Digi-Key_PN"
	1    9700 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C59
U 1 1 5FE1BC99
P 9350 4250
F 0 "C59" H 9400 4350 50  0000 L CNN
F 1 "1uf 100v" H 9350 4000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 9388 4100 50  0001 C CNN
F 3 "~" H 9350 4250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 9350 4250 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 9350 4250 50  0001 C CNN "Digi-Key_PN"
	1    9350 4250
	1    0    0    -1  
$EndComp
Connection ~ 9350 4100
Wire Wire Line
	9350 4100 9700 4100
Connection ~ 9350 4400
Wire Wire Line
	9350 4400 9700 4400
$Comp
L Device:C C53
U 1 1 5FE1C136
P 8950 4250
F 0 "C53" H 9000 4350 50  0000 L CNN
F 1 "1uf 100v" H 8950 4000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8988 4100 50  0001 C CNN
F 3 "~" H 8950 4250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8950 4250 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8950 4250 50  0001 C CNN "Digi-Key_PN"
	1    8950 4250
	1    0    0    -1  
$EndComp
Connection ~ 8950 4100
Wire Wire Line
	8950 4100 9350 4100
Connection ~ 8950 4400
Wire Wire Line
	8950 4400 9350 4400
$Comp
L Device:C C45
U 1 1 5FE1C3FF
P 8500 4250
F 0 "C45" H 8550 4350 50  0000 L CNN
F 1 "1uf 100v" H 8500 4000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8538 4100 50  0001 C CNN
F 3 "~" H 8500 4250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8500 4250 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8500 4250 50  0001 C CNN "Digi-Key_PN"
	1    8500 4250
	1    0    0    -1  
$EndComp
Connection ~ 8500 4100
Wire Wire Line
	8500 4100 8950 4100
Connection ~ 8500 4400
Wire Wire Line
	8500 4400 8950 4400
$Comp
L Device:C C37
U 1 1 5FE1C766
P 8100 4250
F 0 "C37" H 8150 4350 50  0000 L CNN
F 1 "1uf 100v" H 8100 4000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8138 4100 50  0001 C CNN
F 3 "~" H 8100 4250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8100 4250 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8100 4250 50  0001 C CNN "Digi-Key_PN"
	1    8100 4250
	1    0    0    -1  
$EndComp
Connection ~ 8100 4100
Wire Wire Line
	8100 4100 8500 4100
Connection ~ 8100 4400
Wire Wire Line
	8100 4400 8400 4400
$Comp
L Device:C C96
U 1 1 5FE1FE8A
P 9700 4750
F 0 "C96" H 9750 4850 50  0000 L CNN
F 1 "1uf 100v" H 9700 4500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 9738 4600 50  0001 C CNN
F 3 "~" H 9700 4750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 9700 4750 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 9700 4750 50  0001 C CNN "Digi-Key_PN"
	1    9700 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C60
U 1 1 5FE1FE92
P 9350 4750
F 0 "C60" H 9400 4850 50  0000 L CNN
F 1 "1uf 100v" H 9350 4500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 9388 4600 50  0001 C CNN
F 3 "~" H 9350 4750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 9350 4750 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 9350 4750 50  0001 C CNN "Digi-Key_PN"
	1    9350 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C54
U 1 1 5FE1FE9A
P 8950 4750
F 0 "C54" H 9000 4850 50  0000 L CNN
F 1 "1uf 100v" H 8950 4500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8988 4600 50  0001 C CNN
F 3 "~" H 8950 4750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8950 4750 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8950 4750 50  0001 C CNN "Digi-Key_PN"
	1    8950 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C46
U 1 1 5FE1FEA2
P 8500 4750
F 0 "C46" H 8550 4850 50  0000 L CNN
F 1 "1uf 100v" H 8500 4500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8538 4600 50  0001 C CNN
F 3 "~" H 8500 4750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8500 4750 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8500 4750 50  0001 C CNN "Digi-Key_PN"
	1    8500 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C38
U 1 1 5FE1FEAA
P 8100 4750
F 0 "C38" H 8150 4850 50  0000 L CNN
F 1 "1uf 100v" H 8100 4500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8138 4600 50  0001 C CNN
F 3 "~" H 8100 4750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8100 4750 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8100 4750 50  0001 C CNN "Digi-Key_PN"
	1    8100 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C97
U 1 1 5FE81818
P 9700 5250
F 0 "C97" H 9750 5350 50  0000 L CNN
F 1 "1uf 100v" H 9700 5000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 9738 5100 50  0001 C CNN
F 3 "~" H 9700 5250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 9700 5250 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 9700 5250 50  0001 C CNN "Digi-Key_PN"
	1    9700 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C61
U 1 1 5FE81820
P 9350 5250
F 0 "C61" H 9400 5350 50  0000 L CNN
F 1 "1uf 100v" H 9350 5000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 9388 5100 50  0001 C CNN
F 3 "~" H 9350 5250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 9350 5250 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 9350 5250 50  0001 C CNN "Digi-Key_PN"
	1    9350 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C55
U 1 1 5FE81828
P 8950 5250
F 0 "C55" H 9000 5350 50  0000 L CNN
F 1 "1uf 100v" H 8950 5000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8988 5100 50  0001 C CNN
F 3 "~" H 8950 5250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8950 5250 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8950 5250 50  0001 C CNN "Digi-Key_PN"
	1    8950 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C47
U 1 1 5FE81830
P 8500 5250
F 0 "C47" H 8550 5350 50  0000 L CNN
F 1 "1uf 100v" H 8500 5000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8538 5100 50  0001 C CNN
F 3 "~" H 8500 5250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8500 5250 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8500 5250 50  0001 C CNN "Digi-Key_PN"
	1    8500 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C39
U 1 1 5FE81838
P 8100 5250
F 0 "C39" H 8150 5350 50  0000 L CNN
F 1 "1uf 100v" H 8100 5000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8138 5100 50  0001 C CNN
F 3 "~" H 8100 5250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8100 5250 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8100 5250 50  0001 C CNN "Digi-Key_PN"
	1    8100 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C98
U 1 1 5FEE234A
P 9700 5750
F 0 "C98" H 9750 5850 50  0000 L CNN
F 1 "1uf 100v" H 9700 5500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 9738 5600 50  0001 C CNN
F 3 "~" H 9700 5750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 9700 5750 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 9700 5750 50  0001 C CNN "Digi-Key_PN"
	1    9700 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C62
U 1 1 5FEE2352
P 9350 5750
F 0 "C62" H 9400 5850 50  0000 L CNN
F 1 "1uf 100v" H 9350 5500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 9388 5600 50  0001 C CNN
F 3 "~" H 9350 5750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 9350 5750 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 9350 5750 50  0001 C CNN "Digi-Key_PN"
	1    9350 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C56
U 1 1 5FEE235A
P 8950 5750
F 0 "C56" H 9050 5850 50  0000 L CNN
F 1 "1uf 100v" H 8950 5500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8988 5600 50  0001 C CNN
F 3 "~" H 8950 5750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8950 5750 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8950 5750 50  0001 C CNN "Digi-Key_PN"
	1    8950 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C48
U 1 1 5FEE2362
P 8500 5750
F 0 "C48" H 8550 5850 50  0000 L CNN
F 1 "1uf 100v" H 8500 5500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8538 5600 50  0001 C CNN
F 3 "~" H 8500 5750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8500 5750 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8500 5750 50  0001 C CNN "Digi-Key_PN"
	1    8500 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C40
U 1 1 5FEE236A
P 8100 5750
F 0 "C40" H 8150 5850 50  0000 L CNN
F 1 "1uf 100v" H 8100 5500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8138 5600 50  0001 C CNN
F 3 "~" H 8100 5750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8100 5750 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8100 5750 50  0001 C CNN "Digi-Key_PN"
	1    8100 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C101
U 1 1 5FF428A3
P 9700 6300
F 0 "C101" H 9750 6400 50  0000 L CNN
F 1 "1uf 100v" H 9700 6050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 9738 6150 50  0001 C CNN
F 3 "~" H 9700 6300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 9700 6300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 9700 6300 50  0001 C CNN "Digi-Key_PN"
	1    9700 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C63
U 1 1 5FF428AB
P 9350 6300
F 0 "C63" H 9400 6400 50  0000 L CNN
F 1 "1uf 100v" H 9350 6050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 9388 6150 50  0001 C CNN
F 3 "~" H 9350 6300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 9350 6300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 9350 6300 50  0001 C CNN "Digi-Key_PN"
	1    9350 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C57
U 1 1 5FF428B3
P 8950 6300
F 0 "C57" H 9000 6400 50  0000 L CNN
F 1 "1uf 100v" H 8950 6050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8988 6150 50  0001 C CNN
F 3 "~" H 8950 6300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8950 6300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8950 6300 50  0001 C CNN "Digi-Key_PN"
	1    8950 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C49
U 1 1 5FF428BB
P 8500 6300
F 0 "C49" H 8550 6400 50  0000 L CNN
F 1 "1uf 100v" H 8500 6050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8538 6150 50  0001 C CNN
F 3 "~" H 8500 6300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8500 6300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8500 6300 50  0001 C CNN "Digi-Key_PN"
	1    8500 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C42
U 1 1 5FF428C3
P 8100 6300
F 0 "C42" H 8150 6400 50  0000 L CNN
F 1 "1uf 100v" H 8100 6050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8138 6150 50  0001 C CNN
F 3 "~" H 8100 6300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8100 6300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8100 6300 50  0001 C CNN "Digi-Key_PN"
	1    8100 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C52
U 1 1 5FFA3644
P 9700 6850
F 0 "C52" H 9750 6950 50  0000 L CNN
F 1 "1uf 100v" H 9700 6600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 9738 6700 50  0001 C CNN
F 3 "~" H 9700 6850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 9700 6850 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 9700 6850 50  0001 C CNN "Digi-Key_PN"
	1    9700 6850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C50
U 1 1 5FFA364C
P 9350 6850
F 0 "C50" H 9400 6950 50  0000 L CNN
F 1 "1uf 100v" H 9350 6600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 9388 6700 50  0001 C CNN
F 3 "~" H 9350 6850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 9350 6850 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 9350 6850 50  0001 C CNN "Digi-Key_PN"
	1    9350 6850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C43
U 1 1 5FFA3654
P 8950 6850
F 0 "C43" H 9000 6950 50  0000 L CNN
F 1 "1uf 100v" H 8950 6600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8988 6700 50  0001 C CNN
F 3 "~" H 8950 6850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8950 6850 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8950 6850 50  0001 C CNN "Digi-Key_PN"
	1    8950 6850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C103
U 1 1 60003B75
P 9700 7400
F 0 "C103" H 9750 7500 50  0000 L CNN
F 1 "1uf 100v" H 9700 7150 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 9738 7250 50  0001 C CNN
F 3 "~" H 9700 7400 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 9700 7400 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 9700 7400 50  0001 C CNN "Digi-Key_PN"
	1    9700 7400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C94
U 1 1 60003B7D
P 9350 7400
F 0 "C94" H 9400 7500 50  0000 L CNN
F 1 "1uf 100v" H 9350 7150 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 9388 7250 50  0001 C CNN
F 3 "~" H 9350 7400 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 9350 7400 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 9350 7400 50  0001 C CNN "Digi-Key_PN"
	1    9350 7400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C58
U 1 1 60003B85
P 8950 7400
F 0 "C58" H 9000 7500 50  0000 L CNN
F 1 "1uf 100v" H 8950 7150 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8988 7250 50  0001 C CNN
F 3 "~" H 8950 7400 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8950 7400 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8950 7400 50  0001 C CNN "Digi-Key_PN"
	1    8950 7400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C51
U 1 1 60003B8D
P 8500 7400
F 0 "C51" H 8550 7500 50  0000 L CNN
F 1 "1uf 100v" H 8500 7150 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8538 7250 50  0001 C CNN
F 3 "~" H 8500 7400 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8500 7400 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8500 7400 50  0001 C CNN "Digi-Key_PN"
	1    8500 7400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C44
U 1 1 60003B95
P 8100 7400
F 0 "C44" H 8150 7500 50  0000 L CNN
F 1 "1uf 100v" H 8100 7150 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8138 7250 50  0001 C CNN
F 3 "~" H 8100 7400 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8100 7400 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8100 7400 50  0001 C CNN "Digi-Key_PN"
	1    8100 7400
	1    0    0    -1  
$EndComp
Connection ~ 9350 7250
Wire Wire Line
	9350 7250 9700 7250
Connection ~ 9350 7550
Wire Wire Line
	9350 7550 9700 7550
Connection ~ 8950 7250
Wire Wire Line
	8950 7250 9350 7250
Connection ~ 8950 7550
Wire Wire Line
	8950 7550 9350 7550
Connection ~ 8500 7250
Wire Wire Line
	8500 7250 8950 7250
Connection ~ 8500 7550
Wire Wire Line
	8500 7550 8950 7550
Connection ~ 8100 7250
Wire Wire Line
	8100 7250 8500 7250
Connection ~ 8100 7550
Wire Wire Line
	8100 7550 8500 7550
Connection ~ 8950 6700
Wire Wire Line
	8950 6700 9350 6700
Connection ~ 8950 7000
Wire Wire Line
	8950 7000 9350 7000
Connection ~ 9350 6700
Wire Wire Line
	9350 6700 9700 6700
Connection ~ 9350 7000
Wire Wire Line
	9350 7000 9700 7000
Connection ~ 8100 6150
Wire Wire Line
	8100 6150 8500 6150
Connection ~ 8100 6450
Wire Wire Line
	8100 6450 8500 6450
Connection ~ 8500 6150
Wire Wire Line
	8500 6150 8950 6150
Connection ~ 8500 6450
Wire Wire Line
	8500 6450 8950 6450
Connection ~ 8950 6150
Wire Wire Line
	8950 6150 9350 6150
Connection ~ 8950 6450
Wire Wire Line
	8950 6450 9350 6450
Connection ~ 9350 6150
Wire Wire Line
	9350 6150 9700 6150
Connection ~ 9350 6450
Wire Wire Line
	9350 6450 9700 6450
Connection ~ 9350 5600
Wire Wire Line
	9350 5600 9700 5600
Connection ~ 9350 5900
Wire Wire Line
	9350 5900 9700 5900
Connection ~ 8950 5600
Wire Wire Line
	8950 5600 9350 5600
Connection ~ 8950 5900
Wire Wire Line
	8950 5900 9350 5900
Connection ~ 8500 5600
Wire Wire Line
	8500 5600 8950 5600
Connection ~ 8500 5900
Wire Wire Line
	8500 5900 8950 5900
Connection ~ 8100 5600
Wire Wire Line
	8100 5600 8500 5600
Connection ~ 8100 5900
Wire Wire Line
	8100 5900 8500 5900
Connection ~ 8100 5100
Wire Wire Line
	8100 5100 8500 5100
Connection ~ 8100 5400
Wire Wire Line
	8100 5400 8400 5400
Connection ~ 8500 5100
Wire Wire Line
	8500 5100 8950 5100
Connection ~ 8500 5400
Wire Wire Line
	8500 5400 8950 5400
Connection ~ 8950 5100
Wire Wire Line
	8950 5100 9350 5100
Connection ~ 8950 5400
Wire Wire Line
	8950 5400 9350 5400
Connection ~ 9350 5100
Wire Wire Line
	9350 5100 9700 5100
Connection ~ 9350 5400
Wire Wire Line
	9350 5400 9700 5400
Connection ~ 9350 4600
Wire Wire Line
	9350 4600 9700 4600
Connection ~ 9350 4900
Wire Wire Line
	9350 4900 9700 4900
Connection ~ 8950 4600
Wire Wire Line
	8950 4600 9350 4600
Connection ~ 8950 4900
Wire Wire Line
	8950 4900 9350 4900
Connection ~ 8500 4600
Wire Wire Line
	8500 4600 8950 4600
Connection ~ 8500 4900
Wire Wire Line
	8500 4900 8950 4900
Connection ~ 8100 4600
Wire Wire Line
	8100 4600 8500 4600
Connection ~ 8100 4900
Wire Wire Line
	8100 4900 8400 4900
Wire Wire Line
	3950 3150 4150 3150
Wire Wire Line
	2700 3450 4150 3450
$Comp
L Device:C C9
U 1 1 6006693F
P 4450 3300
F 0 "C9" H 4450 2900 50  0000 L CNN
F 1 "1uf 100v" H 4450 3050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4488 3150 50  0001 C CNN
F 3 "~" H 4450 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 4450 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 4450 3300 50  0001 C CNN "Digi-Key_PN"
	1    4450 3300
	1    0    0    -1  
$EndComp
Connection ~ 4450 3150
Wire Wire Line
	4450 3150 4800 3150
Connection ~ 4450 3450
Wire Wire Line
	4450 3450 4800 3450
$Comp
L Device:C C7
U 1 1 60066FD9
P 4150 3300
F 0 "C7" H 4150 2900 50  0000 L CNN
F 1 "1uf 100v" H 4150 3050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4188 3150 50  0001 C CNN
F 3 "~" H 4150 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 4150 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 4150 3300 50  0001 C CNN "Digi-Key_PN"
	1    4150 3300
	1    0    0    -1  
$EndComp
Connection ~ 4150 3150
Wire Wire Line
	4150 3150 4450 3150
Connection ~ 4150 3450
Wire Wire Line
	4150 3450 4450 3450
Wire Wire Line
	5150 4800 5500 4800
Wire Wire Line
	5150 5100 5500 5100
$Comp
L Device:CP C35
U 1 1 600718E9
P 5500 4950
F 0 "C35" H 5500 5200 50  0000 L CNN
F 1 "10uf 25v" H 5450 4700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 5538 4800 50  0001 C CNN
F 3 "~" H 5500 4950 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM21BR61E106MA73L/5251352" H 5500 4950 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10748-1-ND" H 5500 4950 50  0001 C CNN "Digi-Key_PN"
	1    5500 4950
	1    0    0    -1  
$EndComp
Connection ~ 5500 4800
Wire Wire Line
	5500 4800 5750 4800
Connection ~ 5500 5100
Wire Wire Line
	5500 5100 5750 5100
$Comp
L Device:C C36
U 1 1 600727C2
P 5750 4950
F 0 "C36" H 5800 5050 50  0000 L CNN
F 1 "0.1uf film" H 5800 5200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5788 4800 50  0001 C CNN
F 3 "~" H 5750 4950 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 5750 4950 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 5750 4950 50  0001 C CNN "Digi-Key_PN"
	1    5750 4950
	1    0    0    -1  
$EndComp
Connection ~ 5750 4800
Wire Wire Line
	5750 4800 6000 4800
Connection ~ 5750 5100
Wire Wire Line
	5750 5100 6000 5100
$Comp
L Device:C C13
U 1 1 6007301D
P 4550 4950
F 0 "C13" H 4600 5050 50  0000 L CNN
F 1 "0.1uf film" H 4600 5200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 4588 4800 50  0001 C CNN
F 3 "~" H 4550 4950 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 4550 4950 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 4550 4950 50  0001 C CNN "Digi-Key_PN"
	1    4550 4950
	1    0    0    -1  
$EndComp
Connection ~ 4550 5100
$Comp
L Device:C C2
U 1 1 601582B7
P 2750 6650
F 0 "C2" H 2800 6750 50  0000 L CNN
F 1 "0.1uf film" H 2800 6900 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 2788 6500 50  0001 C CNN
F 3 "~" H 2750 6650 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 2750 6650 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 2750 6650 50  0001 C CNN "Digi-Key_PN"
	1    2750 6650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5FEA3732
P 3050 1500
F 0 "C6" H 3165 1546 50  0000 L CNN
F 1 "1uf 25v" H 2950 1800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3088 1350 50  0001 C CNN
F 3 "~" H 3050 1500 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10A105KA8NNNC/3886760" H 3050 1500 50  0001 C CNN "DK_Detail_Page"
F 5 "1276-1102-1-ND" H 3050 1500 50  0001 C CNN "Digi-Key_PN"
	1    3050 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	3200 1500 3300 1500
$Comp
L Device:C C3
U 1 1 5FEA40AA
P 3050 1250
F 0 "C3" H 3165 1296 50  0000 L CNN
F 1 "1uf 25v" H 2950 1550 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3088 1100 50  0001 C CNN
F 3 "~" H 3050 1250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10A105KA8NNNC/3886760" H 3050 1250 50  0001 C CNN "DK_Detail_Page"
F 5 "1276-1102-1-ND" H 3050 1250 50  0001 C CNN "Digi-Key_PN"
	1    3050 1250
	0    1    1    0   
$EndComp
$Comp
L Device:C C11
U 1 1 5FF2E7CE
P 8850 3300
F 0 "C11" H 8965 3346 50  0000 L CNN
F 1 "1uf 25v" H 8965 3255 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 8888 3150 50  0001 C CNN
F 3 "~" H 8850 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10A105KA8NNNC/3886760" H 8850 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "1276-1102-1-ND" H 8850 3300 50  0001 C CNN "Digi-Key_PN"
	1    8850 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 3150 8850 3150
Wire Wire Line
	8550 3450 8850 3450
Connection ~ 8850 3150
Wire Wire Line
	8850 3150 8950 3150
Connection ~ 8850 3450
Wire Wire Line
	8850 3450 9250 3450
$Comp
L Device:C C64
U 1 1 5FF333D5
P 10150 3300
F 0 "C64" H 10265 3346 50  0000 L CNN
F 1 "1uf 25v" H 10265 3255 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 10188 3150 50  0001 C CNN
F 3 "~" H 10150 3300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10A105KA8NNNC/3886760" H 10150 3300 50  0001 C CNN "DK_Detail_Page"
F 5 "1276-1102-1-ND" H 10150 3300 50  0001 C CNN "Digi-Key_PN"
	1    10150 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 3150 10150 3150
Wire Wire Line
	9250 3450 10150 3450
Connection ~ 10150 3150
Wire Wire Line
	10150 3150 10450 3150
Connection ~ 10150 3450
Wire Wire Line
	10150 3450 10450 3450
Text Label 7200 7000 2    50   ~ 0
CH-
$Comp
L Device:CP C104
U 1 1 5FF76A86
P 6850 6850
F 0 "C104" H 6965 6896 50  0000 L CNN
F 1 "10uf 100v" H 6750 7150 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210" H 6888 6700 50  0001 C CNN
F 3 "~" H 6850 6850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRM32EC72A106KE05L/7319356" H 6850 6850 50  0001 C CNN "DK_Detail_Page"
F 5 "490-16266-1-ND" H 6850 6850 50  0001 C CNN "Digi-Key_PN"
	1    6850 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 6700 7300 6700
Wire Wire Line
	6850 7000 7300 7000
$Comp
L Device:C C107
U 1 1 5FF76A90
P 8050 6850
F 0 "C107" H 8100 6950 50  0000 L CNN
F 1 "1uf 100v" H 8050 6600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 8088 6700 50  0001 C CNN
F 3 "~" H 8050 6850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 8050 6850 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 8050 6850 50  0001 C CNN "Digi-Key_PN"
	1    8050 6850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C106
U 1 1 5FF76A98
P 7700 6850
F 0 "C106" H 7750 6950 50  0000 L CNN
F 1 "1uf 100v" H 7700 6600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7738 6700 50  0001 C CNN
F 3 "~" H 7700 6850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 7700 6850 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 7700 6850 50  0001 C CNN "Digi-Key_PN"
	1    7700 6850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C105
U 1 1 5FF76AA0
P 7300 6850
F 0 "C105" H 7350 6950 50  0000 L CNN
F 1 "1uf 100v" H 7300 6600 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7338 6700 50  0001 C CNN
F 3 "~" H 7300 6850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 7300 6850 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 7300 6850 50  0001 C CNN "Digi-Key_PN"
	1    7300 6850
	1    0    0    -1  
$EndComp
Connection ~ 7300 6700
Wire Wire Line
	7300 6700 7700 6700
Connection ~ 7300 7000
Wire Wire Line
	7300 7000 7700 7000
Connection ~ 7700 6700
Wire Wire Line
	7700 6700 8050 6700
Connection ~ 7700 7000
Wire Wire Line
	7700 7000 8050 7000
Text Label 6850 6700 2    50   ~ 0
ChargeIn
$Comp
L Device:D D31
U 1 1 600A36E4
P 13600 2000
F 0 "D31" V 13554 2079 50  0000 L CNN
F 1 "Diode40V" V 13645 2079 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 13600 2000 50  0001 C CNN
F 3 "~" H 13600 2000 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 13600 2000 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 13600 2000 50  0001 C CNN "Digi-Key_PN"
	1    13600 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:D D47
U 1 1 60208A6E
P 13900 2000
F 0 "D47" V 13854 2079 50  0000 L CNN
F 1 "Diode40V" V 13945 2079 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 13900 2000 50  0001 C CNN
F 3 "~" H 13900 2000 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 13900 2000 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 13900 2000 50  0001 C CNN "Digi-Key_PN"
	1    13900 2000
	1    0    0    -1  
$EndComp
Connection ~ 13750 2000
$Comp
L Device:D D48
U 1 1 60208E82
P 13900 2350
F 0 "D48" V 13854 2429 50  0000 L CNN
F 1 "Diode40V" V 13945 2429 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 13900 2350 50  0001 C CNN
F 3 "~" H 13900 2350 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 13900 2350 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 13900 2350 50  0001 C CNN "Digi-Key_PN"
	1    13900 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:D D53
U 1 1 60209181
P 14450 2550
F 0 "D53" V 14404 2629 50  0000 L CNN
F 1 "Diode40V" V 14495 2629 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 14450 2550 50  0001 C CNN
F 3 "~" H 14450 2550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 14450 2550 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 14450 2550 50  0001 C CNN "Digi-Key_PN"
	1    14450 2550
	-1   0    0    1   
$EndComp
Connection ~ 14600 2550
$Comp
L Device:D D54
U 1 1 60209BD1
P 14450 2750
F 0 "D54" V 14404 2829 50  0000 L CNN
F 1 "Diode40V" V 14495 2829 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 14450 2750 50  0001 C CNN
F 3 "~" H 14450 2750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 14450 2750 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 14450 2750 50  0001 C CNN "Digi-Key_PN"
	1    14450 2750
	-1   0    0    1   
$EndComp
Connection ~ 14600 2750
$Comp
L Device:D D29
U 1 1 60082688
P 11800 1550
F 0 "D29" V 11754 1629 50  0000 L CNN
F 1 "Diode40V" V 11845 1629 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 11800 1550 50  0001 C CNN
F 3 "~" H 11800 1550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 11800 1550 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 11800 1550 50  0001 C CNN "Digi-Key_PN"
	1    11800 1550
	0    1    1    0   
$EndComp
$Comp
L Device:D D33
U 1 1 60089AB6
P 6400 3150
F 0 "D33" V 6354 3229 50  0000 L CNN
F 1 "Diode40V" V 6445 3229 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 6400 3150 50  0001 C CNN
F 3 "~" H 6400 3150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 6400 3150 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 6400 3150 50  0001 C CNN "Digi-Key_PN"
	1    6400 3150
	-1   0    0    1   
$EndComp
Connection ~ 6250 3150
$Comp
L Device:D D6
U 1 1 6008BC67
P 2750 8000
F 0 "D6" V 2704 8079 50  0000 L CNN
F 1 "Diode40V" V 2795 8079 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 2750 8000 50  0001 C CNN
F 3 "~" H 2750 8000 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 2750 8000 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 2750 8000 50  0001 C CNN "Digi-Key_PN"
	1    2750 8000
	0    1    1    0   
$EndComp
$Comp
L Device:D D8
U 1 1 6008D14D
P 2750 9150
F 0 "D8" V 2704 9229 50  0000 L CNN
F 1 "Diode40V" V 2795 9229 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 2750 9150 50  0001 C CNN
F 3 "~" H 2750 9150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 2750 9150 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 2750 9150 50  0001 C CNN "Digi-Key_PN"
	1    2750 9150
	0    1    1    0   
$EndComp
$Comp
L Device:D D12
U 1 1 6008DDF7
P 5700 8250
F 0 "D12" V 5654 8329 50  0000 L CNN
F 1 "Diode40V" V 5745 8329 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 5700 8250 50  0001 C CNN
F 3 "~" H 5700 8250 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 5700 8250 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 5700 8250 50  0001 C CNN "Digi-Key_PN"
	1    5700 8250
	0    1    1    0   
$EndComp
$Comp
L Device:D D16
U 1 1 6008E7EB
P 5700 9800
F 0 "D16" V 5654 9879 50  0000 L CNN
F 1 "Diode40V" V 5745 9879 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 5700 9800 50  0001 C CNN
F 3 "~" H 5700 9800 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 5700 9800 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 5700 9800 50  0001 C CNN "Digi-Key_PN"
	1    5700 9800
	0    1    1    0   
$EndComp
$Comp
L Device:D D11
U 1 1 6008EEAF
P 2750 10350
F 0 "D11" V 2704 10429 50  0000 L CNN
F 1 "Diode40V" V 2795 10429 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 2750 10350 50  0001 C CNN
F 3 "~" H 2750 10350 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 2750 10350 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 2750 10350 50  0001 C CNN "Digi-Key_PN"
	1    2750 10350
	0    1    1    0   
$EndComp
$Comp
L Device:D D35
U 1 1 600906CE
P 11000 7800
F 0 "D35" V 10954 7879 50  0000 L CNN
F 1 "Diode40V" V 11045 7879 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 11000 7800 50  0001 C CNN
F 3 "~" H 11000 7800 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 11000 7800 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 11000 7800 50  0001 C CNN "Digi-Key_PN"
	1    11000 7800
	0    -1   -1   0   
$EndComp
Connection ~ 11000 7950
$Comp
L Device:D D27
U 1 1 6009FB6C
P 10500 1050
F 0 "D27" V 10454 1129 50  0000 L CNN
F 1 "Diode40V" V 10545 1129 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 10500 1050 50  0001 C CNN
F 3 "~" H 10500 1050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 10500 1050 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 10500 1050 50  0001 C CNN "Digi-Key_PN"
	1    10500 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 5050 3600 5400
$Comp
L Device:D D55
U 1 1 601ACCFB
P 6400 3000
F 0 "D55" V 6354 3079 50  0000 L CNN
F 1 "Diode40V" V 6445 3079 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 6400 3000 50  0001 C CNN
F 3 "~" H 6400 3000 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 6400 3000 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 6400 3000 50  0001 C CNN "Digi-Key_PN"
	1    6400 3000
	-1   0    0    1   
$EndComp
Wire Wire Line
	6550 3000 6550 3150
Wire Wire Line
	6250 3000 6250 3150
$Comp
L Device:D D56
U 1 1 6029AE54
P 11950 1550
F 0 "D56" V 11904 1629 50  0000 L CNN
F 1 "Diode40V" V 11995 1629 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 11950 1550 50  0001 C CNN
F 3 "~" H 11950 1550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 11950 1550 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 11950 1550 50  0001 C CNN "Digi-Key_PN"
	1    11950 1550
	0    1    1    0   
$EndComp
Wire Wire Line
	11950 1400 11800 1400
Connection ~ 11800 1400
Wire Wire Line
	11800 1700 11950 1700
Connection ~ 11800 1700
$Comp
L Device:D_Schottky D57
U 1 1 603AE2E8
P 3950 5050
F 0 "D57" H 3900 5150 50  0000 L CNN
F 1 "D_Schottky100V" H 3600 4950 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 3950 5050 50  0001 C CNN
F 3 "~" H 3950 5050 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/micro-commercial-co/MBR0580-TP/2423323" H 3950 5050 50  0001 C CNN "DK_Detail_Page"
F 5 "MBR0580-TPMSCT-ND" H 3950 5050 50  0001 C CNN "Digi-Key_PN"
	1    3950 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 5050 3800 5050
Wire Wire Line
	4100 4800 4100 5050
$Comp
L Device:D_Schottky D20
U 1 1 60427764
P 3950 4800
F 0 "D20" H 3900 4900 50  0000 L CNN
F 1 "D_Schottky100V" H 3600 4700 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 3950 4800 50  0001 C CNN
F 3 "~" H 3950 4800 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/micro-commercial-co/MBR0580-TP/2423323" H 3950 4800 50  0001 C CNN "DK_Detail_Page"
F 5 "MBR0580-TPMSCT-ND" H 3950 4800 50  0001 C CNN "Digi-Key_PN"
	1    3950 4800
	1    0    0    -1  
$EndComp
Connection ~ 4100 4800
Wire Wire Line
	3800 4800 3800 5050
Connection ~ 3800 5050
Connection ~ 2350 7400
$Comp
L Device:C C108
U 1 1 602192A2
P 1800 6750
F 0 "C108" H 1850 6850 50  0000 L CNN
F 1 "1uf 100v" H 1800 6500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1838 6600 50  0001 C CNN
F 3 "~" H 1800 6750 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/murata-electronics/GRJ21BC72A105KE11L/5321119" H 1800 6750 50  0001 C CNN "DK_Detail_Page"
F 5 "490-10918-1-ND" H 1800 6750 50  0001 C CNN "Digi-Key_PN"
	1    1800 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 6900 1350 6900
Wire Wire Line
	1800 6600 1600 6600
Wire Wire Line
	1600 6600 1600 8350
Connection ~ 1800 6600
Wire Wire Line
	1800 6400 1800 6600
$Comp
L Device:D_Schottky_AAK D58
U 1 1 605256AE
P 2350 6700
F 0 "D58" V 2400 6550 50  0000 R CNN
F 1 "D_Schottky_AAK" V 2300 6600 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:TO-277A" H 2350 6700 50  0001 C CNN
F 3 "~" H 2350 6700 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/on-semiconductor/FSV20100V/5306682" H 2350 6700 50  0001 C CNN "DK_Detail_Page"
F 5 "FSV20100VCT-ND" H 2350 6700 50  0001 C CNN "Digi-Key_PN"
	1    2350 6700
	0    1    1    0   
$EndComp
Connection ~ 2350 6900
Wire Wire Line
	2450 6900 2350 6900
Wire Wire Line
	2350 6550 2350 6400
Wire Wire Line
	2350 6400 1800 6400
Connection ~ 1800 6400
Wire Wire Line
	1300 10100 1300 8900
Wire Wire Line
	1300 10100 2000 10100
Connection ~ 1300 8900
Wire Wire Line
	1100 10700 1100 10150
Wire Wire Line
	1100 10700 1600 10700
$Comp
L Device:R R60
U 1 1 6056882D
P 5500 5500
F 0 "R60" V 5600 5400 50  0000 L CNN
F 1 "500" V 5500 5400 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 5430 5500 50  0001 C CNN
F 3 "~" H 5500 5500 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 5500 5500 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 5500 5500 50  0001 C CNN "Digi-Key_PN"
	1    5500 5500
	0    1    1    0   
$EndComp
$Comp
L Device:R R56
U 1 1 6056FD1E
P 3400 6350
F 0 "R56" V 3500 6350 50  0000 L CNN
F 1 "200K" V 3400 6250 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 3330 6350 50  0001 C CNN
F 3 "~" H 3400 6350 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ERJ-PA3F2003V/5035886" H 3400 6350 50  0001 C CNN "DK_Detail_Page"
F 5 "P200KBYCT-ND" H 3400 6350 50  0001 C CNN "Digi-Key_PN"
	1    3400 6350
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R57
U 1 1 6056FD2D
P 3700 6200
F 0 "R57" V 3650 6300 50  0000 L CNN
F 1 "200K" V 3700 6100 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 3630 6200 50  0001 C CNN
F 3 "~" H 3700 6200 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ERJ-PA3F2003V/5035886" H 3700 6200 50  0001 C CNN "DK_Detail_Page"
F 5 "P200KBYCT-ND" H 3700 6200 50  0001 C CNN "Digi-Key_PN"
	1    3700 6200
	0    1    1    0   
$EndComp
$Comp
L power:+5C #PWR0144
U 1 1 6056FD33
P 3550 6200
F 0 "#PWR0144" H 3550 6050 50  0001 C CNN
F 1 "+5C" H 3550 6350 50  0000 C CNN
F 2 "" H 3550 6200 50  0001 C CNN
F 3 "" H 3550 6200 50  0001 C CNN
	1    3550 6200
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky D59
U 1 1 6056FD3C
P 3700 6350
F 0 "D59" H 3850 6400 50  0000 L CNN
F 1 "D_Schottky100V" H 3500 6300 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 3700 6350 50  0001 C CNN
F 3 "~" H 3700 6350 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/micro-commercial-co/MBR0580-TP/2423323" H 3700 6350 50  0001 C CNN "DK_Detail_Page"
F 5 "MBR0580-TPMSCT-ND" H 3700 6350 50  0001 C CNN "Digi-Key_PN"
	1    3700 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 6200 3850 6350
Wire Wire Line
	3250 6350 3250 5900
Connection ~ 3250 5900
Wire Wire Line
	3250 5900 3050 5900
$Comp
L power:GND #PWR0145
U 1 1 60A5B9A5
P 5150 7050
F 0 "#PWR0145" H 5150 6800 50  0001 C CNN
F 1 "GND" H 5250 7050 50  0000 C CNN
F 2 "" H 5150 7050 50  0001 C CNN
F 3 "" H 5150 7050 50  0001 C CNN
	1    5150 7050
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_GSD Q18
U 1 1 60C527E3
P 5050 6850
F 0 "Q18" H 4800 7100 50  0000 L CNN
F 1 "DMN65D8L" H 4700 7000 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 5250 6950 50  0001 C CNN
F 3 "~" H 5050 6850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DMN65D8L-7/3678136" H 5050 6850 50  0001 C CNN "DK_Detail_Page"
F 5 "DMN65D8L-7DICT-ND" H 5050 6850 50  0001 C CNN "Digi-Key_PN"
	1    5050 6850
	1    0    0    -1  
$EndComp
Text Label 4550 6850 2    50   ~ 0
Mctrl+
$Comp
L Device:R R61
U 1 1 60E55597
P 5350 6700
F 0 "R61" V 5250 6650 50  0000 L CNN
F 1 "500" V 5350 6650 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 5280 6700 50  0001 C CNN
F 3 "~" H 5350 6700 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 5350 6700 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 5350 6700 50  0001 C CNN "Digi-Key_PN"
	1    5350 6700
	-1   0    0    1   
$EndComp
$Comp
L power:+5C #PWR0146
U 1 1 60E55D49
P 5350 6550
F 0 "#PWR0146" H 5350 6400 50  0001 C CNN
F 1 "+5C" H 5350 6700 50  0000 C CNN
F 2 "" H 5350 6550 50  0001 C CNN
F 3 "" H 5350 6550 50  0001 C CNN
	1    5350 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 6650 5250 6650
Wire Wire Line
	5250 6650 5250 6850
Wire Wire Line
	5250 6850 5350 6850
$Comp
L BTMS-rescue:NL17SZ74USG-nl17sz74usg U15
U 1 1 6056CB7B
P 5500 5800
F 0 "U15" H 5500 5875 50  0000 C CNN
F 1 "NL17SZ74USG" H 5500 5784 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-8_Handsoldering" H 5500 5800 50  0001 C CNN
F 3 "https://www.onsemi.com/pdf/datasheet/nl17sz74-d.pdf" H 5500 5800 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/on-semiconductor/NL17SZ74USG/661531" H 5500 5800 50  0001 C CNN "DK_Detail_Page"
F 5 "NL17SZ74USGOSCT-ND" H 5500 5800 50  0001 C CNN "Digi-Key_PN"
	1    5500 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 6150 6100 6150
Wire Wire Line
	5250 6400 5250 6650
Connection ~ 5250 6650
Wire Wire Line
	6150 6050 6050 6050
$Comp
L power:GND #PWR0147
U 1 1 6076F93C
P 4950 6250
F 0 "#PWR0147" H 4950 6000 50  0001 C CNN
F 1 "GND" H 5050 6250 50  0000 C CNN
F 2 "" H 4950 6250 50  0001 C CNN
F 3 "" H 4950 6250 50  0001 C CNN
	1    4950 6250
	1    0    0    -1  
$EndComp
$Comp
L power:+5C #PWR0148
U 1 1 6076FC67
P 6050 5950
F 0 "#PWR0148" H 6050 5800 50  0001 C CNN
F 1 "+5C" H 6050 6100 50  0000 C CNN
F 2 "" H 6050 5950 50  0001 C CNN
F 3 "" H 6050 5950 50  0001 C CNN
	1    6050 5950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0149
U 1 1 6076FE94
P 4950 6050
F 0 "#PWR0149" H 4950 5800 50  0001 C CNN
F 1 "GND" H 5050 6050 50  0000 C CNN
F 2 "" H 4950 6050 50  0001 C CNN
F 3 "" H 4950 6050 50  0001 C CNN
	1    4950 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 5950 4950 6050
Connection ~ 4950 6050
$Comp
L Device:R R59
U 1 1 60873367
P 5500 5400
F 0 "R59" V 5400 5300 50  0000 L CNN
F 1 "500" V 5500 5300 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 5430 5400 50  0001 C CNN
F 3 "~" H 5500 5400 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 5500 5400 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 5500 5400 50  0001 C CNN "Digi-Key_PN"
	1    5500 5400
	0    1    1    0   
$EndComp
$Comp
L Device:R R63
U 1 1 60A10E81
P 4700 6850
F 0 "R63" V 4800 6750 50  0000 L CNN
F 1 "500" V 4700 6750 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 4630 6850 50  0001 C CNN
F 3 "~" H 4700 6850 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 4700 6850 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 4700 6850 50  0001 C CNN "Digi-Key_PN"
	1    4700 6850
	0    1    1    0   
$EndComp
Wire Wire Line
	5250 6400 6100 6400
Wire Wire Line
	6100 6400 6100 6150
Wire Wire Line
	3850 6350 6150 6350
Wire Wire Line
	6150 6350 6150 6050
Connection ~ 3850 6350
$Comp
L Device:C C110
U 1 1 60826FA1
P 6300 6150
F 0 "C110" H 6415 6196 50  0000 L CNN
F 1 "0.1uf film" H 6415 6105 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 6338 6000 50  0001 C CNN
F 3 "~" H 6300 6150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECP-U1C104MA5/285446?s=N4IgTCBcDaIIxzANgCIGkBKBaAcikAugL5A" H 6300 6150 50  0001 C CNN "DK_Detail_Page"
F 5 "PCF1126CT-ND" H 6300 6150 50  0001 C CNN "Digi-Key_PN"
	1    6300 6150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0150
U 1 1 60826FA7
P 6300 6300
F 0 "#PWR0150" H 6300 6050 50  0001 C CNN
F 1 "GND" H 6305 6127 50  0000 C CNN
F 2 "" H 6300 6300 50  0001 C CNN
F 3 "" H 6300 6300 50  0001 C CNN
	1    6300 6300
	1    0    0    -1  
$EndComp
$Comp
L power:+5C #PWR0151
U 1 1 60826FAD
P 6300 6000
F 0 "#PWR0151" H 6300 5850 50  0001 C CNN
F 1 "+5C" H 6315 6173 50  0000 C CNN
F 2 "" H 6300 6000 50  0001 C CNN
F 3 "" H 6300 6000 50  0001 C CNN
	1    6300 6000
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky D61
U 1 1 608AB1ED
P 6150 6500
F 0 "D61" H 6200 6600 50  0000 L CNN
F 1 "D_Schottky100V" H 6100 6400 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 6150 6500 50  0001 C CNN
F 3 "~" H 6150 6500 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/micro-commercial-co/MBR0580-TP/2423323" H 6150 6500 50  0001 C CNN "DK_Detail_Page"
F 5 "MBR0580-TPMSCT-ND" H 6150 6500 50  0001 C CNN "Digi-Key_PN"
	1    6150 6500
	0    1    1    0   
$EndComp
Connection ~ 6150 6350
$Comp
L power:GND #PWR0152
U 1 1 608AC193
P 6150 6650
F 0 "#PWR0152" H 6150 6400 50  0001 C CNN
F 1 "GND" H 6155 6477 50  0000 C CNN
F 2 "" H 6150 6650 50  0001 C CNN
F 3 "" H 6150 6650 50  0001 C CNN
	1    6150 6650
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky D60
U 1 1 608ADE8D
P 4800 6150
F 0 "D60" H 4850 6250 50  0000 L CNN
F 1 "D_Schottky100V" H 4700 6300 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 4800 6150 50  0001 C CNN
F 3 "~" H 4800 6150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/micro-commercial-co/MBR0580-TP/2423323" H 4800 6150 50  0001 C CNN "DK_Detail_Page"
F 5 "MBR0580-TPMSCT-ND" H 4800 6150 50  0001 C CNN "Digi-Key_PN"
	1    4800 6150
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 8550 3200 8650
Connection ~ 3200 8650
$Comp
L Device:R R62
U 1 1 60FBDB50
P 2900 8150
F 0 "R62" V 2850 7850 50  0000 L CNN
F 1 "500" V 2900 8050 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 2830 8150 50  0001 C CNN
F 3 "~" H 2900 8150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 2900 8150 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 2900 8150 50  0001 C CNN "Digi-Key_PN"
	1    2900 8150
	0    1    1    0   
$EndComp
$Comp
L Device:CP C111
U 1 1 60FBDB5C
P 2900 8300
F 0 "C111" V 2950 8400 50  0000 L CNN
F 1 "100uf 16v" V 2750 8100 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_6.3x5.7" H 2938 8150 50  0001 C CNN
F 3 "~" H 2900 8300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/illinois-capacitor/107AXZ016MQ5/5964380" H 2900 8300 50  0001 C CNN "DK_Detail_Page"
F 5 "1572-1239-1-ND" H 2900 8300 50  0001 C CNN "Digi-Key_PN"
	1    2900 8300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3050 8150 3050 8300
Wire Wire Line
	2750 8150 2750 8300
Connection ~ 2750 8150
Wire Wire Line
	3200 8150 3050 8150
Connection ~ 3050 8150
$Comp
L Device:R R64
U 1 1 611D064C
P 2900 9300
F 0 "R64" V 2850 9100 50  0000 L CNN
F 1 "500" V 2900 9200 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 2830 9300 50  0001 C CNN
F 3 "~" H 2900 9300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 2900 9300 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 2900 9300 50  0001 C CNN "Digi-Key_PN"
	1    2900 9300
	0    1    1    0   
$EndComp
Wire Wire Line
	3050 9300 3050 9450
Wire Wire Line
	2750 9300 2750 9450
Connection ~ 2750 9300
Wire Wire Line
	3200 9300 3050 9300
Connection ~ 3050 9300
$Comp
L Device:R R65
U 1 1 61467AF5
P 2900 10500
F 0 "R65" V 2850 10300 50  0000 L CNN
F 1 "500" V 2900 10400 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 2830 10500 50  0001 C CNN
F 3 "~" H 2900 10500 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 2900 10500 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 2900 10500 50  0001 C CNN "Digi-Key_PN"
	1    2900 10500
	0    1    1    0   
$EndComp
Wire Wire Line
	3050 10500 3050 10650
Wire Wire Line
	2750 10500 2750 10650
Wire Wire Line
	3200 10500 3050 10500
Connection ~ 3050 10500
$Comp
L Device:R R66
U 1 1 615F9245
P 5850 8400
F 0 "R66" V 5800 8200 50  0000 L CNN
F 1 "500" V 5850 8300 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 5780 8400 50  0001 C CNN
F 3 "~" H 5850 8400 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 5850 8400 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 5850 8400 50  0001 C CNN "Digi-Key_PN"
	1    5850 8400
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 8400 6000 8550
Wire Wire Line
	5700 8400 5700 8550
Wire Wire Line
	6200 8400 6000 8400
Connection ~ 6000 8400
$Comp
L Device:R R67
U 1 1 6178E7E8
P 5850 9950
F 0 "R67" V 5800 9750 50  0000 L CNN
F 1 "500" V 5850 9850 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 5780 9950 50  0001 C CNN
F 3 "~" H 5850 9950 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 5850 9950 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 5850 9950 50  0001 C CNN "Digi-Key_PN"
	1    5850 9950
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 9950 6000 10100
Wire Wire Line
	5700 9950 5700 10100
Wire Wire Line
	6200 9950 6000 9950
Connection ~ 6000 9950
$Comp
L ucc27201ddar:UCC27201DDAR U3
U 1 1 61187C6B
P 4350 5600
F 0 "U3" V 4000 5950 50  0000 L CNN
F 1 "UCC27201DDAR" V 4100 5750 50  0000 L CNN
F 2 "Housings_SOIC:TI_SO-PowerPAD-8_ThermalVias" H 4350 5600 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/ucc27200.pdf?HQS=dis-dk-null-digikeymode-dsf-pf-null-wwe&ts=1628373640405&ref_url=https%253A%252F%252Fwww.ti.com%252Fgeneral%252Fdocs%252Fsuppproductinfo.tsp%253FdistId%253D10%2526gotoUrl%253Dhttps%253A%252F%252Fwww.ti.com%252Flit%252Fgpn%252Fucc27200" H 4350 5600 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/texas-instruments/UCC27201DDAR/1911333" H 4350 5600 50  0001 C CNN "DK_Detail_Page"
F 5 "296-31998-1-ND" H 4350 5600 50  0001 C CNN "Digi-Key_PN"
	1    4350 5600
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 5250 4450 4800
Wire Wire Line
	4400 7200 4500 7200
Connection ~ 4450 4800
Wire Wire Line
	4450 4800 4100 4800
Wire Wire Line
	4300 5250 4300 5150
Wire Wire Line
	4300 5150 3800 5150
Wire Wire Line
	3800 5150 3800 5050
Wire Wire Line
	4150 5250 4150 5200
Wire Wire Line
	2850 5200 4150 5200
Wire Wire Line
	4000 5250 3050 5250
Wire Wire Line
	3050 5250 3050 5400
Connection ~ 3050 5400
Wire Wire Line
	2850 6000 3200 6000
Wire Wire Line
	3200 6000 3200 6650
Wire Wire Line
	3200 6650 4450 6650
Wire Wire Line
	4450 6650 4450 6000
Connection ~ 2850 6000
$Comp
L power:GND #PWR0153
U 1 1 6142815F
P 4300 6000
F 0 "#PWR0153" H 4300 5750 50  0001 C CNN
F 1 "GND" H 4400 6050 50  0000 C CNN
F 2 "" H 4300 6000 50  0001 C CNN
F 3 "" H 4300 6000 50  0001 C CNN
	1    4300 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 6000 4150 6100
Wire Wire Line
	4150 6100 4650 6100
Wire Wire Line
	4650 6100 4650 5500
Wire Wire Line
	4650 5500 4750 5500
Wire Wire Line
	4550 5400 4550 6150
Wire Wire Line
	4550 6150 4000 6150
Wire Wire Line
	4000 6150 4000 6000
Wire Wire Line
	4650 6150 4650 6100
Connection ~ 4650 6100
$Comp
L Device:Q_NMOS_GSD Q17
U 1 1 61CDE917
P 4850 5700
F 0 "Q17" H 4600 5950 50  0000 L CNN
F 1 "DMN65D8L" H 4500 5850 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 5050 5800 50  0001 C CNN
F 3 "~" H 4850 5700 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/diodes-incorporated/DMN65D8L-7/3678136" H 4850 5700 50  0001 C CNN "DK_Detail_Page"
F 5 "DMN65D8L-7DICT-ND" H 4850 5700 50  0001 C CNN "Digi-Key_PN"
	1    4850 5700
	-1   0    0    -1  
$EndComp
Connection ~ 4750 5500
Wire Wire Line
	4750 5500 5350 5500
$Comp
L power:GND #PWR0154
U 1 1 61DF4C68
P 4750 5900
F 0 "#PWR0154" H 4750 5650 50  0001 C CNN
F 1 "GND" H 4850 5900 50  0000 C CNN
F 2 "" H 4750 5900 50  0001 C CNN
F 3 "" H 4750 5900 50  0001 C CNN
	1    4750 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 5400 5350 5400
Text Label 5350 5700 0    50   ~ 0
Mctrl+
$Comp
L Device:R R68
U 1 1 61DFA87C
P 5200 5700
F 0 "R68" V 5300 5600 50  0000 L CNN
F 1 "500" V 5200 5600 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 5130 5700 50  0001 C CNN
F 3 "~" H 5200 5700 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RNCP0603FTD499R/2240098" H 5200 5700 50  0001 C CNN "DK_Detail_Page"
F 5 "RNCP0603FTD499RCT-ND" H 5200 5700 50  0001 C CNN "Digi-Key_PN"
	1    5200 5700
	0    1    1    0   
$EndComp
$Comp
L Device:CP C112
U 1 1 62113170
P 2900 9450
F 0 "C112" V 2950 9550 50  0000 L CNN
F 1 "100uf 16v" V 2750 9250 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_6.3x5.7" H 2938 9300 50  0001 C CNN
F 3 "~" H 2900 9450 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/illinois-capacitor/107AXZ016MQ5/5964380" H 2900 9450 50  0001 C CNN "DK_Detail_Page"
F 5 "1572-1239-1-ND" H 2900 9450 50  0001 C CNN "Digi-Key_PN"
	1    2900 9450
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP C113
U 1 1 62113BDC
P 2900 10650
F 0 "C113" V 2950 10750 50  0000 L CNN
F 1 "100uf 16v" V 2750 10450 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_6.3x5.7" H 2938 10500 50  0001 C CNN
F 3 "~" H 2900 10650 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/illinois-capacitor/107AXZ016MQ5/5964380" H 2900 10650 50  0001 C CNN "DK_Detail_Page"
F 5 "1572-1239-1-ND" H 2900 10650 50  0001 C CNN "Digi-Key_PN"
	1    2900 10650
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP C115
U 1 1 62114193
P 5850 10100
F 0 "C115" V 5900 10200 50  0000 L CNN
F 1 "100uf 16v" V 5700 9900 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_6.3x5.7" H 5888 9950 50  0001 C CNN
F 3 "~" H 5850 10100 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/illinois-capacitor/107AXZ016MQ5/5964380" H 5850 10100 50  0001 C CNN "DK_Detail_Page"
F 5 "1572-1239-1-ND" H 5850 10100 50  0001 C CNN "Digi-Key_PN"
	1    5850 10100
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP C114
U 1 1 62114F09
P 5850 8550
F 0 "C114" V 5900 8650 50  0000 L CNN
F 1 "100uf 16v" V 5700 8350 50  0000 L CNN
F 2 "Capacitors_SMD:CP_Elec_6.3x5.7" H 5888 8400 50  0001 C CNN
F 3 "~" H 5850 8550 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/illinois-capacitor/107AXZ016MQ5/5964380" H 5850 8550 50  0001 C CNN "DK_Detail_Page"
F 5 "1572-1239-1-ND" H 5850 8550 50  0001 C CNN "Digi-Key_PN"
	1    5850 8550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 621298A5
P 5900 1600
F 0 "#PWR07" H 5900 1350 50  0001 C CNN
F 1 "GND" H 5905 1427 50  0000 C CNN
F 2 "" H 5900 1600 50  0001 C CNN
F 3 "" H 5900 1600 50  0001 C CNN
	1    5900 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:D D15
U 1 1 6212D514
P 5900 1150
F 0 "D15" V 5854 1229 50  0000 L CNN
F 1 "Diode40V" V 5945 1229 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 5900 1150 50  0001 C CNN
F 3 "~" H 5900 1150 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 5900 1150 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 5900 1150 50  0001 C CNN "Digi-Key_PN"
	1    5900 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	5800 1300 5900 1300
Connection ~ 5900 1300
Wire Wire Line
	5900 1300 6000 1300
$Comp
L Device:D D62
U 1 1 6212F823
P 5900 1450
F 0 "D62" V 5854 1529 50  0000 L CNN
F 1 "Diode40V" V 5945 1529 50  0000 L CNN
F 2 "Diodes_SMD:D_0603" H 5900 1450 50  0001 C CNN
F 3 "~" H 5900 1450 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/CCS15S40L3F/5210646" H 5900 1450 50  0001 C CNN "DK_Detail_Page"
F 5 "CCS15S40L3FCT-ND" H 5900 1450 50  0001 C CNN "Digi-Key_PN"
	1    5900 1450
	0    1    1    0   
$EndComp
$Comp
L Device:R R27
U 1 1 62134C51
P 5650 1300
F 0 "R27" H 5720 1346 50  0000 L CNN
F 1 "1K" H 5720 1255 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 5580 1300 50  0001 C CNN
F 3 "~" H 5650 1300 50  0001 C CNN
F 4 "https://www.digikey.com/en/products/detail/te-connectivity-passive-product/CRGP0603F1K0/8577018" H 5650 1300 50  0001 C CNN "DK_Detail_Page"
F 5 "A130416CT-ND" H 5650 1300 50  0001 C CNN "Digi-Key_PN"
	1    5650 1300
	0    -1   -1   0   
$EndComp
$Comp
L power:+5C #PWR?
U 1 1 6212B3B2
P 3950 7000
F 0 "#PWR?" H 3950 6850 50  0001 C CNN
F 1 "+5C" H 3965 7173 50  0000 C CNN
F 2 "" H 3950 7000 50  0001 C CNN
F 3 "" H 3950 7000 50  0001 C CNN
	1    3950 7000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
