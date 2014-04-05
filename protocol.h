#include<stdint.h>

#ifndef PROTOCOL_H
#define PROTOCOL_H
//从串口中读取数据
extern uint8_t protocol_readData(uint8_t **data);

//向串口写入数据
extern void protocol_writeData(uint8_t type, uint8_t* _data, int len);
#endif
