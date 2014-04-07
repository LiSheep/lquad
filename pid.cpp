#include "pid.h"

#include <Arduino.h>

#include "pidlib.h"
#include "define.h"

static PID *pidRoll;
static PID *pidPitch;

static AutoPID autoPIDRoll;
static AutoPID autoPIDPitch;

extern void PID_init(double rollP, double rollI, double rollD, double pitchP, double pitchI, double pitchD){
	autoPIDRoll.p = rollP;
        autoPIDRoll.i = rollI;
        autoPIDRoll.d = rollD;
        
        autoPIDPitch.p = pitchP;
        autoPIDPitch.i = pitchI;
        autoPIDPitch.d = pitchD;

        static PID _pidRoll( &autoPIDRoll.in, &autoPIDRoll.out, &autoPIDRoll.setpoint, autoPIDRoll.p, autoPIDRoll.i, autoPIDRoll.d, DIRECT);
	static PID _pidPitch( &autoPIDPitch.in, &autoPIDPitch.out, &autoPIDPitch.setpoint, autoPIDPitch.p, autoPIDPitch.i, autoPIDPitch.d, DIRECT);
	
        pidRoll = &_pidRoll;
        pidPitch = &_pidPitch;
        pidRoll->SetOutputLimits(-SPEED_MAX, SPEED_MAX);
	pidPitch->SetOutputLimits(-SPEED_MAX, SPEED_MAX);

	pidRoll->SetMode(AUTOMATIC);
	pidPitch->SetMode(AUTOMATIC);
}

extern void PID_compute(){
	bool a = pidRoll->Compute();
	bool b = pidPitch->Compute();
}

extern void PID_toControl(Control *ctrl){
	int roll = (int)autoPIDRoll.out;
	int pitch = (int)autoPIDPitch.out;

	/*
 	 * 0   1
	 *   x
	 * 2   3
	 *
	 */
	ctrl->throttle[SERVO_PRE_LEFT] = roll - pitch;
	ctrl->throttle[SERVO_PRE_RIGHT] = -roll - pitch;
	ctrl->throttle[SERVO_BACK_LEFT] = roll + pitch;
	ctrl->throttle[SERVO_BACK_RIGHT] = -roll + pitch;

//Serial.print("0; ");
//Serial.print(ctrl->throttle[SERVO_PRE_LEFT]);
//Serial.print("  1; ");
//Serial.print(ctrl->throttle[SERVO_PRE_RIGHT]);
//Serial.print("  2; ");
//Serial.print(ctrl->throttle[SERVO_BACK_LEFT]);
//Serial.print("  3; ");
//Serial.println(ctrl->throttle[SERVO_BACK_RIGHT]);


}

extern void Angle_to_PID(Angle *angleIn, Angle *angleExp){
	autoPIDRoll.in = angleIn->x_roll;
	autoPIDRoll.setpoint = angleExp-> x_roll;

	autoPIDPitch.in = angleIn->y_pitch;
	autoPIDPitch.setpoint = angleExp->y_pitch;

}
