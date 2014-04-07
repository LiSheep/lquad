#ifndef ROM_H
#define ROM_H

#include<stdint.h>

typedef union{
	double v;
	uint8_t dchar[4];
}dvalue;

extern void rom_read(uint8_t *res, uint8_t len, uint8_t start);
extern void rom_readPID(double *pidRoll, double *pidPitch);
extern void rom_writePID(uint8_t *pid);

#endif
