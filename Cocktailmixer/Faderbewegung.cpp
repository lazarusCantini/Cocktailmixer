/*
 * Faderbewegung.cpp
 *
 * Created: 04.07.2018 10:49:17
 *  Author: Bastian Reul
 */ 

#include "Faderbewegung.h"
//debugging
//#include "Pin.h"
//Pin DebuggingPin('B', 3, false);
#include <stdlib.h>
#define ObereBeschraenkung 240
#define UntereBeschraenkung 15
#define K 0.6
#define Abweichung_Max 4 
#define offset 18 //Dieser Offset ist dafür da, um den Spannungseinruch beim bewegen der Motoren zu kompensieren


uint8_t Regler(uint8_t abweichung, uint8_t Iteration)
{
	uint8_t Reglerwert = 0;
	if ((abweichung > 80) && (Iteration > 3)) // Falls die Abweichung in der vierten Runde immer noch über 80 liegen sollte, beschneide die Verstärkung um ein Schwingen zu verhindern
	{
		abweichung = 80;
	}
	Reglerwert = abweichung + Iteration;
	return Reglerwert;
}

__attribute__((optimize(0)))
void verfahre_Fader_auf_Wert(int *zeiger_auf_soll_array, PwmPin *Motor_Fader_Enable, AnalogDigitalConverter *FaderADC, Fader_Motor *Motor_Fader)
{
		volatile uint8_t ist_array[6];
		volatile uint8_t abweichung_array[6] = {0,0,0,0,0,0};
		volatile bool Fader_Halt_erreicht[6] = {false, false, false, false, false, false};
		volatile int i = 0;
		int Richtungsinitialisierung = 0;
		double iterativer_PWM_Wert = 0.0;
		volatile char *Debug_Buchstabe;
		while (!(Fader_Halt_erreicht[0] && Fader_Halt_erreicht[1] && Fader_Halt_erreicht[2] && Fader_Halt_erreicht[3] && Fader_Halt_erreicht[4] && Fader_Halt_erreicht[5]) )
		{

			for (; i<6; i++)
			{
				iterativer_PWM_Wert = 0.0;
				while(!Fader_Halt_erreicht[i])
				{
					Motor_Fader_Array[i].Disable_Motor();
					if (zeiger_auf_soll_array[i] <= 50) //Die Nuller (die eigentlich wegen der Normalisierung auf mll nicht 0 sind müssen beim Offset ausgeschlossen werden
					{
						ist_array[i] = FaderADC_Array[i].getValue();
					} 
					else
					{
						ist_array[i] = FaderADC_Array[i].getValue() + offset;
					}
					
					Motor_Fader_Array[i].Enable_Motor();
					if (ist_array[i] <= zeiger_auf_soll_array[i] )
					{
						//Motor_Fader_Array[i].Enable_Motor();
						abweichung_array[i] = zeiger_auf_soll_array[i] - ist_array[i];
						Motor_Fader_Array[i].setze_Drehrichtung(true);
					}
					if (ist_array[i] > zeiger_auf_soll_array[i] )
					{
						//Motor_Fader_Array[i].Enable_Motor();
						abweichung_array[i] = ist_array[i] - zeiger_auf_soll_array[i];
						Motor_Fader_Array[i].setze_Drehrichtung(false);
					}
					//Debug_Abweichung_ausgeben(abweichung);
					if (Drehrichtung[i] == Motor_Fader_Array[i].get_Drehsinn())
					{
						if (Richtungsinitialisierung < 1)
						{
							aktualisiere_alle_Gliederwerte();
							Schubverband.Setze_Ist_auf_Soll();
							Schubverband.Aktualisiere_Alle_Register();
							Schubverband.Aktualisiere_ist_gleich_Soll(true);
							Drehrichtung[i] = Motor_Fader_Array[i].get_Drehsinn();
						}
						
					}
					else
					{
						aktualisiere_alle_Gliederwerte();
						Schubverband.Setze_Ist_auf_Soll();
						Schubverband.Aktualisiere_Alle_Register();
						Schubverband.Aktualisiere_ist_gleich_Soll(true);
						Drehrichtung[i] = Motor_Fader_Array[i].get_Drehsinn();
					}
					Richtungsinitialisierung++;
					Motor_Fader_Array[i].Enable_Motor();

			
				if (abweichung_array[i] <= 1)
				{
						Motor_Fader_Array[i].Disable_Motor();
						Fader_Halt_erreicht[i] = true;
						//Send_UART("Motor #:  ausgeschaltet\n");
				}
				else
				{
					if (abweichung_array[i] <= 30)
					{
						if (Motor_Fader_Enable_Array[i].get_Dutycycle() != 15.0)
						{
							Motor_Fader_Enable_Array[i].set_Dutycycle(15.0);
						}
						
					} 
					else
					{
						Motor_Fader_Enable_Array[i].set_Dutycycle(double(abweichung_array[i])/1.5);  //Original_ 2.35 // eigen 2.15
					}
					
				}
				//Nochmal schauen ob sich ein ehemals korrekt positionierter Fader wieder verfahren hat
				//Muss noch an die Offset geschichte angepasst werden
			/*	if (i==5 && Fader_Halt_erreicht[5])
				{
					for (volatile int j=0; j<6; j++)
					{
						Send_UART("Kontrollrunde\n");
						//if (soll == FaderADC_Array[j].getValue())
						ist_array[j] = FaderADC_Array[j].getValue();
						//Der Betrag der Abweichung wird gebildet (könnte man auch über abs machen, soll aber zeigen wie man es auch machen kann
						if (ist_array[j] <= zeiger_auf_soll_array[j] )
						{
							abweichung_array[j] = zeiger_auf_soll_array[j] - ist_array[j];
						}
						else
						{
							abweichung_array[j] = ist_array[j] - zeiger_auf_soll_array[j];
						}
						//Betrag wurde berechnet und in aweichungs_array gespeichert
						if ( abweichung_array[j] <= Abweichung_Max)
						{
							Fader_Halt_erreicht[j] = true;
						}
						else
						{	//Dann werden alle nochmal korrigiert
							Fader_Halt_erreicht[j] = false;
							i=-1;
						}
					}
				}
				*/
			}
			
		}
	}
}
				
__attribute__((optimize(0)))
void verfahre_alle_Fader_auf_gleichen_wert(uint8_t soll)
{
	double PWM = 0.0;
	volatile uint8_t ist_array[6];
	volatile uint8_t abweichung_array[6] = {0,0,0,0,0,0};
	volatile bool Fader_Halt_erreicht[6] = {false, false, false, false, false, false};
	volatile int i = 0;
	int Richtungsinitialisierung = 0;
	while (!(Fader_Halt_erreicht[0] && Fader_Halt_erreicht[1] && Fader_Halt_erreicht[2] && Fader_Halt_erreicht[3] && Fader_Halt_erreicht[4] && Fader_Halt_erreicht[5]) )
	{
		for (; i<6; i++)
		{
			while(!Fader_Halt_erreicht[i])
			{

				ist_array[i] = FaderADC_Array[i].getValue();
				if (ist_array[i] < soll )
				{
					abweichung_array[i] = soll - ist_array[i];
					Motor_Fader_Array[i].setze_Drehrichtung(true);
				}
				
				if (ist_array[i] > soll )
				{
					abweichung_array[i] = ist_array[i] - soll;
					Motor_Fader_Array[i].setze_Drehrichtung(false);
				}
				
				if (Drehrichtung[i] == Motor_Fader_Array[i].get_Drehsinn())
				{
					if (Richtungsinitialisierung < 1)
					{
						aktualisiere_alle_Gliederwerte();
						Schubverband.Setze_Ist_auf_Soll();
						Schubverband.Aktualisiere_Alle_Register();
						Schubverband.Aktualisiere_ist_gleich_Soll(true);
						Drehrichtung[i] = Motor_Fader_Array[i].get_Drehsinn();
					}
			
				}
				else
				{
					Motor_Fader_Enable_Array[i].set_Dutycycle(0.0);
					aktualisiere_alle_Gliederwerte();
					Schubverband.Setze_Ist_auf_Soll();
					Schubverband.Aktualisiere_Alle_Register();
					Schubverband.Aktualisiere_ist_gleich_Soll(true);
					Drehrichtung[i] = Motor_Fader_Array[i].get_Drehsinn();
					//Motor_Fader_Enable_Array[i].set_Dutycycle(PWM);
				}
				Richtungsinitialisierung++;

				if (abweichung_array[i] <= 1 | (i==3))
				{
						Motor_Fader_Array[i].Disable_Motor();
						Fader_Halt_erreicht[i] = true;
						if (i == 3)
						{
							double duty3 = Motor_Fader_Enable_Array[i].get_Dutycycle();
						}
						
				}
				else
				{
					if (abweichung_array[i] <= 20)
					{
						if (Motor_Fader_Enable_Array[i].get_Dutycycle() != 30.0)
						{
							PWM = 30.0;
							Motor_Fader_Enable_Array[i].set_Dutycycle(PWM);
						}
					}
					else
					if (abweichung_array[i] <= 30)
					{
					if (Motor_Fader_Enable_Array[i].get_Dutycycle() != 40.0)
							{
								PWM = 40.0;
								Motor_Fader_Enable_Array[i].set_Dutycycle(PWM);
							}
						}
					
					else
					{
						//Motor_Fader_Enable_Array[i].set_Dutycycle(double(abweichung_array[i])/2.35);
						PWM = 80.0;
						Motor_Fader_Enable_Array[i].set_Dutycycle(PWM);
					}
					Motor_Fader_Array[i].Enable_Motor();
					Motor_Fader_Array[3].Disable_Motor();
				}
			} // Ende while(!Fader_Halt_erreicht[i])
			
			//Nochmal schauen ob sich ein ehemals korrekt positionierter Fader wieder verfahren hat
			if (i==5)
			{
				for (volatile int j=0; j<6; j++)
				{
					ist_array[j] = FaderADC_Array[j].getValue();
					if ( ( ist_array[j]- soll) < 2)
					{
						Fader_Halt_erreicht[j] = true;
					} 
					else
					{	//Dann werden alle nochmal korrigiert
						Fader_Halt_erreicht[j] = false;
						i=-1;
					}
				}
			}
		}
	}
	
}

//Der Funktion wird eine Zahl im Bereich 0-255 übergeben und gibt eine Zahl von 0.0 - 100.0 zurück
__attribute__((optimize(0)))
double normiere_Fader_Wert_auf_Prozent(uint8_t FaderWert_uint8t)
{
	double Prozentwert;
	if (FaderWert_uint8t > ObereBeschraenkung)
	{
		FaderWert_uint8t = ObereBeschraenkung;
	}
	if (FaderWert_uint8t < UntereBeschraenkung)
	{
		FaderWert_uint8t = UntereBeschraenkung;
	}
	Prozentwert = double(FaderWert_uint8t) / double(ObereBeschraenkung) * 100.0;
	return Prozentwert;
}
__attribute__((optimize(0)))
uint8_t normiere_ProzentWert_auf_Fader_Wert(double Prozentwert)
{
	double Faderwert;
	if (Prozentwert >=100.0 || Prozentwert <= 0.0)
	{
			if (Prozentwert > 100.0)
			{
				Faderwert = 240.0;
			}
			if (Prozentwert <= 0.0)
			{
				Faderwert = 15.0;
			}
	} 
	else
	{
		Faderwert = (ObereBeschraenkung - UntereBeschraenkung) / (100 / Prozentwert)+15;
	}
	return round(Faderwert);
}
/*
__attribute__((optimize(0)))
int * normiere_Array_auf_Fader_Wert(int *ProzentWerteArray)
{
	int FaderWertArray[] = {0,0,0,0,0,0};
	int *ZeigerAufFaderWertArray = FaderWertArray;
	for (int i=0; i<6; i++)
	{
		FaderWertArray[i] = normiere_ProzentWert_auf_Fader_Wert(double(ProzentWerteArray[i]));
	}
	return ZeigerAufFaderWertArray;
}*/

__attribute__((optimize(0)))
void normiere_Array_auf_Fader_Wert(int *ProzentWerteArray)
{

	for (int i=0; i<6; i++)
	{
		ProzentWerteArray[i] = normiere_ProzentWert_auf_Fader_Wert(double(ProzentWerteArray[i]));
	}

}