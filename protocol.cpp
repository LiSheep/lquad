#include <Arduino.h>
#include <avr-libc/calloc.c>
#include<stdint.h>
#include <string.h>

#include "protocol.h"
#include "define.h"

extern volatile unsigned long timer0_millis;

static int sleep2available()
{
	  unsigned long st = timer0_millis;
	  while( (timer0_millis-st) >= TIME_UP || !Serial.available() );
		  return Serial.available();
}

extern uint8_t protocol_readData(uint8_t **_data){

	if(!Serial.available()){	//串口没有数据
		return 0;
	}
	byte a = Serial.read();
	if(a - 255 != 0){	//不是头
		return PROTOCOL_FAILD;
	}
	if(!sleep2available()){
          return PROTOCOL_FAILD;
        }
	byte len = Serial.read();	//长度
	*_data = (uint8_t*)calloc( len-2, sizeof(uint8_t));	//pure数据，不包括type\sum
	if(*_data ==NULL )
	   	return PROTOCOL_FAILD;	//动态分配内存失败 
	if(!sleep2available()){
          return PROTOCOL_FAILD;
        }

	uint8_t type = Serial.read();	//数据类型
	uint8_t i = 0, sumCalc = 0;	//校验和
	for(; i < len-2; ++i){
		if(!sleep2available()){
                  return PROTOCOL_FAILD;
                }
		*(*_data+i) = Serial.read();
		if(i == 0){	//第一个
			sumCalc = **_data;
		}else{
			sumCalc += *(*_data+i);
		}
	}
	if(!sleep2available()){
                  return PROTOCOL_FAILD;
                }
	uint8_t sum = Serial.read(); 	//校验和
//	if(sum != sumCalc){
//		free(*_data); 
//		*_data = NULL;		//校验失败
//		return PROTOCOL_FAILD;
//	}
	return type;
}

extern void protocol_writeData(uint8_t type, uint8_t* _data, int len){
	uint8_t *write_data = (uint8_t*)calloc(len+3, sizeof(uint8_t) ); //写入的数据
	if(write_data == NULL){	
		return;
	}
	write_data[0] = 255;
	write_data[1] = len+1;	//加上type
	write_data[2] = type;

	int i = 0;
	for(; i<len; ++i){
		write_data[i+3] = *_data++;
	}

	Serial.write(write_data, len+3);
	free(write_data);
}
