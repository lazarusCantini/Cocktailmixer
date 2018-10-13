/*
 * BootBildschirm.h
 *
 * Created: 24.05.2018 10:43:24
 *  Author: Bastian Reul
 */ 


#ifndef BOOTBILDSCHIRM_H_
#define BOOTBILDSCHIRM_H_

void BootBildschirm();
void Debug_Start_gedrueckt();
void Debug_Stop_gedrueckt();
void Display_Init();
void IdleBildschirm();
void Max_Fuellmaenge_beachten(unsigned int maxFuellmenge);
void Bildschirmausgabe_Rezeptur_einlesen_1();
void Bildschirmausgabe_Rezeptur_einlesen_2(unsigned int Menge);


void Debug_Pin_Nummer_nicht_initialisiert();
void Debug_Port_Buchstabe_nicht_initialisiert();
void Debug_PWM_aktiviert();
void Debug_PWM_deaktiviert();
void Debug_MotorTest_PMW_Status(double PWM_Prozent);
void Debug_ADC_Wert_ausgeben(unsigned int ADC_Value);
void Debug_Abweichung_ausgeben(unsigned int abweichung);
void Debug_Halt_wurde_erreicht();
void Debug_Rezept_wird_ausgegeben();
void Debug_Pumpe_NrX_wird_angesprochen(unsigned int x);
void Debug_UART_String_erkannt();
#endif /* BOOTBILDSCHIRM_H_ */