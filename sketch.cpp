#include <stdint.h>
#include <Arduino.h>
#include "ICS.h"
#include "MotionController.h"
#include "M000.h"

// ICSサーボ
IcsController ics1(Serial1); // 右半身系統
IcsController ics2(Serial2); // 左半身系統
IcsServo servos[SERVO_NUM];

// モーションコントローラ
MotionController motionCtrl;

// トリム位置
const int16_t TRIM_POS[SERVO_NUM]={
//  肩P(右,左) 肩R         肘          腿R         腿P         膝           足首P       足首R
    1350,-1350,-2700,-2700,    0,    0,    0,    0, -250, -250,-2000, -2000,  520,  520,    0,    0
};

// 初期化
void setup()
{
	Serial.begin(115200);

	// ICSサーボの初期化
	ics1.begin();
	ics2.begin();
	for(int i=0; i<(SERVO_NUM/2); i++){
		servos[i*2  ].attach(ics1, 1+i); // 右半身のサーボ
		servos[i*2+1].attach(ics2, 1+i); // 左半身のサーボ
	}
	
	// モーションコントローラの初期化
	motionCtrl.setServo(servos);
	motionCtrl.setTrim(TRIM_POS);
	motionCtrl.begin(M000::motion);
	
	while(1)
	{
		if(Serial.available() > 0){
			char c = Serial.read();
			if(c = 's') break;
		}
	}
}

// メインループ
void loop()
{
	motionCtrl.loop();
	ics1.loop();
	ics2.loop();
	
	delay(1);
	
	if(Serial.available() > 0){
		char c = Serial.read();
		if(c = 'r'){
			SYSTEM.PRCR.WORD = 0xa502;
			SYSTEM.SWRR = 0xa501;
		}
	}
}
