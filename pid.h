#ifndef PID_H
#define PID_H

#include "pidlib.h"
#include "define.h"

extern void PID_init(double rollP, double rollI, double rollD, double pitchP, double pitchI, double pitchD);

extern void PID_compute();

extern void PID_toControl(Control *ctrl);

extern void Angle_to_PID(Angle *angleIn, Angle *angleExp);

#endif
