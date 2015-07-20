#ifndef __EEPROM_H
#define __EEPROM_H
#include"i2c.h"
void  Eeprom_ByteWrite(int addr,int dat);
int Eeprom_ReadOneByte(int addr);
void eeprom_PageWrite(int addr,char* table,int len );
void eeprom_write(int addr,char* table,int len );
void  Eeprom_SquRead(int addr,int len);

#endif

