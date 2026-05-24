
#include "DS18B20.h"

void delay1(unsigned short cnt)
{
	while(cnt--)
	{
		__asm__ volatile ("");		__asm__ volatile ("");
		__asm__ volatile ("");		__asm__ volatile ("");
		__asm__ volatile ("");		__asm__ volatile ("");
		__asm__ volatile ("");		__asm__ volatile ("");
		__asm__ volatile ("");		__asm__ volatile ("");
		__asm__ volatile ("");		__asm__ volatile ("");
		__asm__ volatile ("");		__asm__ volatile ("");
		__asm__ volatile ("");		__asm__ volatile ("");
	}
}

//Initialization function
unsigned char Reset_DS18B20(void)
{
	unsigned char i=0;
	
	DQ_DIR_OUT;
	DQ_LOW;    		//SCM will be pulled down DQ
	
	delay1(480); //Accurate than 480us delay
	
	DQ_DIR_IN;
	
	delay1(70);
	
	if(DQ_SENSE) i=1;
	else		 i=0;

	delay1(410);
	return i;
}


//Reading a byte
unsigned char ReadOneChar(void)
{
	unsigned char i=8;
	unsigned char dat = 0;
	
	for (i=0;i<8;i++)
	{
		dat>>=1;

		DQ_DIR_OUT;
		DQ_LOW;
		
		delay1(3);

		DQ_DIR_IN;
		delay1(10);
		
		if(DQ_SENSE) dat |= 0x80;
		
		delay1(53);
	}
	
	return dat;
}


//Write a byte
void WriteOneChar(unsigned char dat)
{
	unsigned char i=8;

	for(i=0; i<8; i++)
	{
		DQ_DIR_OUT;
		DQ_LOW;
		
		delay1(1);
		
		if(dat & 0x01) DQ_DIR_IN;

		delay1(60);
		
		DQ_DIR_IN;
		
		dat>>=1;
	}
}

unsigned char CS18B20_CRC_Check(unsigned char *p, unsigned char num)
{
	unsigned char crc=0;

	while(num--)
	{
		crc = onewire_crc_table[crc ^ *p++];
	}
	return crc;
}
