
#ifndef CONFIG_H
#define CONFIG_H
#define MEGA
	#define SERVO_ALL 4
        #define SPEED_MIN 1000
        #define SPEED_MAX 2000
        
        #define CTRL_MIN 125
        #define CTRL_MAX 250

	#ifdef MEGA
		#define SERVO_MIN 8000
		#define SERVO_MAX 16000

		#define OCR_PRE_LEFT	 OCR3C	//D3
		#define OCR_PRE_RIGHT	 OCR3A	//D5
		#define OCR_BACK_LEFT	 OCR4A	//D6
		#define OCR_BACK_RIGHT	 OCR3B	//D2
	#endif

	#ifdef PROMICRO
		#define SERVO_MIN 125
		#define SERVO_MAX 250

		#define OCR_PRE_LEFT	 OCR1A	//D9
		#define OCR_PRE_RIGHT	 OCR1B	//D10
		#define OCR_BACK_LEFT	 OCR2A	//D11
		#define OCR_BACK_RIGHT	 OCR2B	//D3
	#endif

	#define PROTOCOL_ROM_R 1
	#define PROTOCOL_ROM_W 2
	#define PROTOCOL_SERVO 3
	#define PROTOCOL_POWER 4
	#define PROTOCOL_FAILD 0 

								//UNO		//MEGA
	#define SERVO_PRE_LEFT	 0	//D9		D3
	#define SERVO_PRE_RIGHT	 1	//D10		D5
	#define SERVO_BACK_LEFT	 2	//D11		D6
	#define SERVO_BACK_RIGHT 3	//D3 		D2

	#define TIME_UP 50

	typedef struct 
	{
		int baseServo;				//基本油门
		int throttle[SERVO_ALL];	//四个值分别存储PID计算值
		int isFly;					//是否起飞,false为关机
	}Control;

	typedef struct
	{
		double in, out, setpoint, p, i, d;
	}AutoPID;

	typedef struct
	{
			double x_roll, y_pitch, z_yaw;
	}Angle;

#endif
