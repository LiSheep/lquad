#include "rom.h"

#include<EEPROM.h>
#include<Arduino.h>
#include<stdint.h>

static void rom_write(uint8_t *data, uint8_t len, uint8_t start){
	uint8_t end = len + start;
	for(; start<end; start++){
		EEPROM.write(start, *data++);
	}
}

extern void rom_read(uint8_t *res, uint8_t len, uint8_t start){
	uint8_t end = len + start;
	for(; start<end; start++){
		*res++ = EEPROM.read(start);
	}
}

extern void rom_readPID(double* pidRoll, double *pidPitch){
	uint8_t roll[12], pitch[12];

	rom_read(roll, 12, 0);
	rom_read(pitch, 12, 12);

	dvalue *dataRoll = (dvalue*)roll;
	dvalue *dataPitch = (dvalue*)pitch;

	*pidRoll = dataRoll->v;
	*pidPitch = dataPitch->v;
}

extern void rom_writePID(uint8_t *pid){
	rom_write(pid, 24, 0);
}
