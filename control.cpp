#include<Arduino.h>
#include<stdint.h>

#include "control.h"
#include "define.h"


static void control_setServo(int baseServo, Control* ctrl){
	if(baseServo > SPEED_MAX){
		baseServo = SPEED_MAX;
	}else if(baseServo < SPEED_MIN){
		baseServo = SPEED_MIN;
	}

	ctrl->baseServo = baseServo;
}


extern void control_writeServo(Control *ctrl){
	int pl_servo = 0;
	int pr_servo = 0;
	int bl_servo = 0;
	int br_servo = 0;

	if(ctrl->isFly){
		pl_servo = ctrl->baseServo + ctrl->throttle[SERVO_PRE_LEFT];
		pr_servo = ctrl->baseServo + ctrl->throttle[SERVO_PRE_RIGHT];
		bl_servo = ctrl->baseServo + ctrl->throttle[SERVO_BACK_LEFT];
		br_servo = ctrl->baseServo + ctrl->throttle[SERVO_BACK_RIGHT];
	}else{
		pl_servo = pr_servo = bl_servo = br_servo = SPEED_MIN;
	}

	OCR_PRE_LEFT = map(pl_servo, SPEED_MIN, SPEED_MAX, SERVO_MIN, SERVO_MAX);	//将1000~2000转换成PWM的125~250(8000~16000);
	OCR_PRE_RIGHT = map(pr_servo, SPEED_MIN, SPEED_MAX, SERVO_MIN, SERVO_MAX);	//将1000~2000转换成PWM的125~250;
	OCR_BACK_RIGHT = map(bl_servo, SPEED_MIN, SPEED_MAX, SERVO_MIN, SERVO_MAX);
	OCR_BACK_LEFT = map(br_servo, SPEED_MIN, SPEED_MAX, SERVO_MIN, SERVO_MAX);
}

extern void control_data2Servo(uint8_t speed, Control *ctrl){

	control_setServo(map(speed, CTRL_MIN, CTRL_MAX, SPEED_MIN, SPEED_MAX), ctrl);	//125~250转1000~2000
}
