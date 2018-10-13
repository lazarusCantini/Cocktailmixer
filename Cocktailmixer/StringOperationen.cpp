/*
 * StringOperationen.cpp
 *
 * Created: 18.06.2018 15:42:37
 *  Author: Bastian Reul
 */ 

#include "StringOperationen.h"

char * double_to_char_array(double dValue)
{
	char buf[10];
	char *Zeiger_auf_CharArray = buf;
	sprintf(buf,"%u.%u",(int)dValue, (int)((dValue - (int)dValue) *100) );
	return Zeiger_auf_CharArray;
}

char * int_to_char_array(unsigned int iValue)
{
	char buf[10];
	char *Zeiger_auf_CharArray = buf;
	sprintf(buf,"%u",(int)iValue );
	return Zeiger_auf_CharArray;
}