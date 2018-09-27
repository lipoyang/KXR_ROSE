#include <Arduino.h>
#include "MotionController.h"

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(x)		Serial.print(x)
#define DEBUG_PRINTLN(x)	Serial.println(x)
#else
#define DEBUG_PRINT(x)		
#define DEBUG_PRINTLN(x)	
#endif

// サーボを設定する
// servos: ICSサーボの配列
void MotionController::setServo(IcsServo *servos)
{
	m_servos = servos;
}

// トリム位置を設定する
// servos: トリム位置の配列
void MotionController::setTrim(const int16_t *trims)
{
	for(int i=0;i<SERVO_NUM;i++){
		m_trims[i] = trims[i];
	}
}

// 開始する
// main_motion: メインのモーションデータ
void MotionController::begin(const MotionData* main_motion)
{
	// 変数の初期化
	m_motion = main_motion;
	m_sp = 0;
	m_pc = 0;
	m_waiting = false;
	
	// トリムポジションに移動
	for(int i=0;i<SERVO_NUM;i++){
		m_servos[i].setPosition(NEUT_POS + m_trims[i]);
	}
}

// メインループから呼ぶ
void MotionController::loop()
{
	bool next = false; // 次の命令に進むか？
	
	// 各命令の処理
	switch (m_motion[m_pc].cmd){
		case CMD_POS:
			next = cmd_pos();
			break;
		case CMD_SET:
			next = cmd_set();
			break;
		case CMD_JUMP:
			next = cmd_jump();
			break;
		case CMD_CALL:
			next = cmd_call();
			break;
		case CMD_RET:
			next = cmd_ret();
			break;
		case CMD_HALT:
			next = cmd_halt();
			break;
		case CMD_CNT:
			next = cmd_cnt();
			break;
	}
	
	// 次の命令に進むか？
	if (next)
	{
		m_pc++;
		m_waiting = false;
		//DEBUG_PRINT("PC=");
		//DEBUG_PRINTLN(m_pc);
	}
}

// ボタンフラグをセットする
// buttonNo: ボタン番号
void MotionController::setButton(uint32_t buttonFlag)
{
	//DEBUG_PRINT("BUTTON ON: ");
	//DEBUG_PRINTLN(buttonFlag);
	m_button |= buttonFlag;
}

// ボタンフラグをクリアする
// buttonNo: ボタン番号
void MotionController::clrButton(uint32_t buttonFlag)
{
	//DEBUG_PRINT("BUTTON OFF: ");
	//DEBUG_PRINTLN(buttonFlag);
	m_button &= ~buttonFlag;
}

// ポジション設定命令
bool MotionController::cmd_pos()
{
	// ICSコマンド送信
	if (m_waiting == false){
		m_waiting = true;
		DEBUG_PRINT("POS ");

		CmdPos *param = (CmdPos*)m_motion[m_pc].param;
		uint16_t frame = param->frame;
		int16_t *pos = param->pos;

		// 各サーボ
		for (int i = 0; i < SERVO_NUM; i++){
			if (pos[i] != POS_NO_CHANGE){
				m_servos[i].requestPosition(NEUT_POS + m_trims[i] + pos[i]);
				DEBUG_PRINT(pos[i]);
				//DEBUG_PRINT(NEUT_POS + m_trims[i] + pos[i]);
				DEBUG_PRINT(" ");
			}
			else{
				DEBUG_PRINT("POS_NO_CHANGE ");
			}
		}
		DEBUG_PRINT("\n");
		
		// 待ち時間セット
		setTimer(frame * FRAME_TIME);
		
		return false;
	}
	// 指定フレーム数待ち
	else{
		if (isTimeUp()){
			return true;
		}
		return false;
	}
}

// パラメータ設定命令
bool MotionController::cmd_set()
{
	// ICSコマンド送信
#if 0
	if (m_waiting == false){
		m_waiting = true;
#endif
		CmdSet *param = (CmdSet*)m_motion[m_pc].param;
		uint8_t type = param->type;
		int16_t *val = param->val;
		
		// ストレッチの設定
		if(type == SET_STRETCH){
			DEBUG_PRINT("SET STRETCH ");
			// 各サーボ
			for (int i = 0; i < SERVO_NUM; i++)
			{
				if (val[i] != -1){
					m_servos[i].setStretch((uint8_t)val[i]);
					DEBUG_PRINT((uint8_t)val[i]);
				}else{
					DEBUG_PRINT("NO");
				}
				DEBUG_PRINT(" ");
			}
		}
		// スピードの設定
		else{
			DEBUG_PRINT("SET SPEED ");
			// 各サーボ
			for (int i = 0; i < SERVO_NUM; i++)
			{
				if (val[i] != -1){
					m_servos[i].setSpeed(val[i]);
					DEBUG_PRINT(val[i]);
				}else{
					DEBUG_PRINT("NO");
				}
				DEBUG_PRINT(" ");
			}
		}
		DEBUG_PRINT("\n");
		return true; // 現状ではパラメータ設定メソッドは同期待ちのみ
#if 0
		return false;
	}
	// 通信完了待ち
	else{
		if (s_timer_flag){
			return true;
		}
		return false;
	}
#endif
}

// カウンタ設定命令
bool MotionController::cmd_cnt()
{
	CmdCnt *param = (CmdCnt*)m_motion[m_pc].param;
	int cnt = param->cnt;
	int val = param->value;

	if (cnt < CNT_NUM)
	{
		m_cnt[cnt] = val;
	}

	return true;
}

// ジャンプ命令
bool MotionController::cmd_jump()
{
	CmdJump *param = (CmdJump*)m_motion[m_pc].param;
	uint8_t condType = param->condType;
	uint32_t condParam = param->condParam;
	int8_t dest = param->dest;
	
	bool flag = false; // ジャンプするか？
	
	// 条件種別
	switch (condType)
	{
		// 無条件
		case COND_NONE:
			//DEBUG_PRINT("JUMP ");
			flag = true;
			break;
		// ループ
		case COND_LOOP:
			if (condParam < CNT_NUM){
				m_cnt[condParam]--;
				if (m_cnt[condParam] == 0){
					DEBUG_PRINT("JUMP LOOP ");
					DEBUG_PRINTLN(m_pc + dest);
					flag = true;
				}
			}
			break;
		// ボタンON
		case COND_BTN_ON:
			if ((m_button & condParam) == condParam){
				DEBUG_PRINT("JUMP BTN_ON ");
				DEBUG_PRINTLN(m_pc + dest);
				flag = true;
			}
			break;
		// ボタンOFF
		case COND_BTN_OFF:
			if ((m_button & condParam) == 0){
				//DEBUG_PRINT("JUMP BTN_OFF ");
				flag = true;
			}
			break;
	}
	
	// ジャンプするか？
	if (flag){
		m_pc += dest; // 行先(相対ジャンプ)
		m_waiting = false;
		return false; // ジャンプするので次の命令には進まない
	}else{
		return true; // ジャンプせず次の命令に進む
	}
}

// コール命令
bool MotionController::cmd_call()
{
	CmdCall *param = (CmdCall*)m_motion[m_pc].param;
	uint8_t condType = param->condType;
	uint32_t condParam = param->condParam;
	const MotionData *dest = param->dest;

	bool flag = false; // コールするか？
	
	// 条件種別
	switch (condType)
	{
		// 無条件
		case COND_NONE:
			DEBUG_PRINT("CALL ");
			flag = true;
			break;
		// ボタンON
		case COND_BTN_ON:
			if ((m_button & condParam) != 0){
				DEBUG_PRINT("CALL BTN_ON ");
				flag = true;
			}
			break;
		// ボタンOFF
		case COND_BTN_OFF:
			if ((m_button & condParam) == 0){
				DEBUG_PRINT("CALL BTN_OFF ");
				flag = true;
			}
			break;
	}
	
	// コールするか？
	if (flag){
		if (m_sp < MOTION_STACK_SIZE){
			DEBUG_PRINTLN("");
			m_stack[m_sp] = m_motion;
			m_sp++;
			m_motion = param->dest; // 行先のモーションデータ
			m_pc = 0;
			m_waiting = false;
			return false; // コールするので次の命令には進まない
		}
		return true; // コールせず次の命令に進む
	}else{
		return true; // コールせず次の命令に進む
	}
}

// 復帰命令
bool MotionController::cmd_ret()
{
	if (m_sp > 0){
		DEBUG_PRINTLN("RET");
		m_sp--;
		m_motion = m_stack[m_sp]; // 戻り先のモーションデータ
		m_pc = 0;
		m_waiting = false;
	}
	return false;
}

// 停止命令
bool MotionController::cmd_halt()
{
	static bool flag = false;
	if (!flag){
		flag = true;
		DEBUG_PRINTLN("HALT");
	}

	// 何もしない
	return false;
}

// 時間待ちセット
// ms: 待ち時間[ms]
void MotionController::setTimer(int ms)
{
	// 開始時刻
	m_time_s = (uint32_t)micros();
	// 終了時刻
	m_time_e = m_time_s + (uint32_t)ms * 1000;

//	DEBUG_PRINT(m_time_s);
//	DEBUG_PRINT(" ");
//	DEBUG_PRINT(m_time_e);
//	DEBUG_PRINT(" ");
}

// 時間待ちチェック
bool MotionController::isTimeUp()
{
	// 現在時刻
	uint32_t t = (uint32_t)micros();
	
	if(m_time_e > m_time_s){
		if((t >= m_time_e) || (t < m_time_s)){
			//DEBUG_PRINTLN(t);
			return true;
		}
	}else{
		if((t >= m_time_e) && (t < m_time_s)){
			//DEBUG_PRINTLN(t);
			return true;
		}
	}
	return false;
}

