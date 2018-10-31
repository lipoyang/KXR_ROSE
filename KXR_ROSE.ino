#include <stdint.h>
#include <Arduino.h>
#include "./ICS.h"
#include "./MotionController.h"
#include "./Motion.h"
#include "./common.h"
#include "./UdpComm.h"
#include "./ESP8266Writer.h"

// ICSサーボ
IcsController ics1(Serial1); // 右半身系統
IcsController ics2(Serial2); // 左半身系統
IcsServo servos[SERVO_NUM];

// モーションコントローラ
MotionController motionCtrl;

// トリム位置
const int16_t TRIM_POS[SERVO_NUM]={
//  肩P(右,左) 肩R         肘          腿R         腿P         膝           足首P       足首R
    1350,-1350,-2700,-2700,    0,    0,    0,    0, -250, -250,-2000,-2000,  520,  520,    0,    0
};

// ホームポジション
const int16_t HOME_POS[SERVO_NUM]={
//  肩P(右,左) 肩R         肘          腿R         腿P         膝           足首P       足首R
     400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0
};

// ホームストレッチ
const uint8_t HOME_STRETCH[SERVO_NUM]={
//  肩P(右,左) 肩R         肘          腿R         腿P         膝           足首P       足首R
      20,   20,   20,   20,   65,   65,   65,   65,   65,   65,   65,   65,   65,   65,   65,   65
};

// ESP8266 Flash
ESP8266Writer esp_writer;
// UDP通信クラス
UdpComm udpComm;
// UDP受信コールバック
void udpComm_callback(char* buff);

// 送信バッファ
static char txbuff[256];

/**
 * バッテリー電圧チェック （仮）
 */
void battery_check()
{
	// 現状は固定値(3.7V)送信
	
	static uint32_t s_prev = 0;			// 前回の電圧値送信時刻
	uint32_t now = (uint32_t)millis();	// 現在時刻[msec]
	uint32_t elapsed = now - s_prev;	// 経過時間[msec]
	
	// 約1秒に1回送信
	if(elapsed >= 1000){
		s_prev = now;
		
		// 仮の固定値
		unsigned short Vbat_ave = 573; // 573 = 3.7V
		
		// 送信
		txbuff[0]='#';
		txbuff[1]='B';
		Uint16ToHex(&txbuff[2], Vbat_ave, 3);
		txbuff[5]='$';
		txbuff[6]='\0';
		udpComm.send(txbuff);
		//Serial.println(txbuff);
	}
}

// 初期化
void setup()
{
	// 起動時にピン21がLOWならESP8266書き込みモードへ(復帰しない)
	esp_writer.begin(21);
	
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
	motionCtrl.setHome(HOME_POS, HOME_STRETCH);
	motionCtrl.begin(M000::motion);
/*	
	while(1){
		for(int i=0;i<SERVO_NUM;i++){
			uint16_t pos = servos[i].getPosition();
			Serial.print(pos);Serial.print(" ");
		}
		Serial.println(" ");
		delay(1000);
	}
*/	
	// UDP通信の設定
	udpComm.begin();
	udpComm.onReceive = udpComm_callback;
	
	// シリアル通信で's'を受信するか
	// ピン20がHIGHであれば動作開始
	pinMode(20, INPUT_PULLUP);
	while(1)
	{
		if(Serial.available() > 0){
			char c = Serial.read();
			if(c == 's') break;
		}
		if(digitalRead(20) == HIGH){
			break;
		}
	}
	// ホームポジションに移動
	motionCtrl.standHome();
}

// メインループ
void loop()
{
	motionCtrl.loop();
	ics1.loop();
	ics2.loop();
	
	// TODO
	delayMicroseconds(SERVO_WAIT);
	//delay(1);
	
	if(Serial.available() > 0){
		char c = Serial.read();
		if(c == '1') motionCtrl.setButton(BTN_L1);
		if(c == '2') motionCtrl.setButton(BTN_L2);
		if(c == '3') motionCtrl.setButton(BTN_R1);
		if(c == '4') motionCtrl.setButton(BTN_R2);
		if(c == 'a') motionCtrl.setButton(BTN_LEFT);
		if(c == 's') motionCtrl.setButton(BTN_DOWN);
		if(c == 'd') motionCtrl.setButton(BTN_UP);
		if(c == 'f') motionCtrl.setButton(BTN_RIGHT);
		if(c == 'h') motionCtrl.setButton(BTN_X);
		if(c == 'j') motionCtrl.setButton(BTN_A);
		if(c == 'k') motionCtrl.setButton(BTN_Y);
		if(c == 'l') motionCtrl.setButton(BTN_B);
		if(c == ' ') motionCtrl.clrButton(BTN_ALL);
	}
	
	// UDP通信
	udpComm.loop();
	
	// バッテリーチェック(仮)
	battery_check();
}

/**
 * 受信したコマンドの実行
 *
 * @param buff 受信したコマンドへのポインタ
 */
void udpComm_callback(char* buff)
{
	uint16_t val;
	int sval;
	
	Serial.print("udpComm_callback:");Serial.println(buff);
	
	switch(buff[0])
	{
	/* Dコマンド(デジタルボタン)
	   書式: #Dxx$
	   xx: 0のとき停止、正のとき前進、負のとき後退。
	 */
	case 'D':
		// 値の解釈
		if( HexToUint16(&buff[1], &val, 4) != 0 ) break;
		Serial.print("D:");
		Serial.println(val);
		motionCtrl.movButton(val);
		break;
	}
}

