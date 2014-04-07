#include <Wire.h>
#include<EEPROM.h>

#include "define.h"
#include "mpu.h"
#include "pid.h"
#include "protocol.h"
#include "setup.h"
#include "control.h"
#include "rom.h"

//#include "utils.h"

Control ctrl;
AutoPID autoPIDRoll;
AutoPID autoPIDPitch;

void setup(){
	setup_init();
	mpu_init();
	ctrl.isFly = 0;
	double pidRoll[3], pidPitch[3];
	rom_readPID(pidRoll, pidPitch);
//        int i = 0;
//        Serial.print("roll: ");
//        for(;i<3;i++){
//          Serial.print(pidRoll[i]);
//          Serial.print(" ");
//        }
//        Serial.println("");
//        Serial.print("pitch: ");
//        i=0;
//        for(;i<3;i++){
//          Serial.print(pidPitch[i]);
//          Serial.print(" ");
//        }
	PID_init(pidRoll[0], pidRoll[1], pidRoll[2], pidPitch[0], pidPitch[1], pidPitch[2]);
}

void loop(){
	uint8_t *data = NULL;
	int type = protocol_readData(&data);
	switch(type){
		case PROTOCOL_SERVO:
	      	control_data2Servo(data[0], &ctrl);
			ctrl.isFly = 1;
		break;
		case PROTOCOL_ROM_R:
			uint8_t piddata[24];
			rom_read(piddata, 24, 0);
			protocol_writeData(PROTOCOL_ROM_R, piddata, 24);
		break;
		case PROTOCOL_ROM_W:
			protocol_writeData(PROTOCOL_ROM_W, data, 24);
			rom_writePID(data);	
		break;
		case PROTOCOL_POWER:
    		ctrl.isFly = data[0];
		break;

	}
	if(ctrl.isFly){
  		unsigned long time = millis();
		Angle nowAngle;
		mpu_getData(&nowAngle);	//获取当前角度
		Angle targetAngle;
		targetAngle.x_roll = 0;
		targetAngle.y_pitch = 0;


		Angle_to_PID(&nowAngle, &targetAngle);

		PID_compute();

		PID_toControl(&ctrl);

        control_writeServo(&ctrl);
	}

}
