#ifndef _MOTION_CONTROLLER_H_
#define _MOTION_CONTROLLER_H_

#include <stdint.h>
#include "ICS.h"

// サーボの数
#define SERVO_NUM 16

// モーションのスタックサイズ
#define MOTION_STACK_SIZE 1

// カウンタの数
#define CNT_NUM 8

// ボタンの数
#define BUTTON_NUM 16

// 1フレームの時間[ms]
#define FRAME_TIME 15

// ニュートラル位置
#define NEUT_POS 7500

// コマンド
#define CMD_POS		0x00 // ポジション設定
#define CMD_SET		0x01 // パラメータ設定 (ストレッチ/スピード)
#define CMD_CNT		0x10 // カウンタ設定
#define CMD_JUMP	0x20 // ジャンプ
#define CMD_CALL	0x21 // コール
#define CMD_RET		0x22 // 復帰
#define CMD_HALT	0x23 // 停止

// パラメータ種別
#define SET_STRETCH	0x01 // ストレッチ
#define SET_SPEED	0x02 // スピード

// 分岐条件
#define COND_NONE	0x00 // 無条件
#define COND_LOOP	0x01 // ループ
#define COND_BTN	0x02 // ボタン

// ポジション定数
#define POS_NO_CHANGE	-32768 // ポジション変更なし

// モーションデータ
struct MotionData
{
	uint8_t cmd;	// コマンド
	void* param;	// パラメータ
};

// ポジション設定命令のパラメータ
struct CmdPos
{
	uint16_t frame;			// フレーム数
	int16_t pos[SERVO_NUM];	// 各サーボのポジション
};

// パラメータ設定命令のパラメータ
struct CmdSet
{
	uint8_t type;			// パラメータ種別 (ストレッチ/スピード)
	int16_t val[SERVO_NUM];	// 各サーボのパラメータ値
};

// カウンタ設定命令のパラメータ
struct CmdCnt
{
	uint8_t  cnt;	// カウンタ番号
	uint16_t value;	// カウント値
};

// ジャンプ命令のパラメータ
struct CmdJump
{
	uint8_t condType;	// 条件種別
	uint8_t condParam;	// 条件パラメータ 
	int8_t  dest;		// 行先
};

// コール命令のパラメータ
struct CmdCall
{
	uint8_t condType;	// 条件種別
	uint8_t condParam;	// 条件パラメータ 
	MotionData* dest;	// 行先
};

// モーションコントローラ
class MotionController{
public:
	// サーボをセットする
	void setServo(IcsServo *servos);
	// トリム位置をセットする
	void setTrim(const int16_t *trims);
	// 開始する
	void begin(const MotionData* main_motion);
	// メインループから呼ぶ
	void loop();
	// ボタンフラグをセットする
	void setButton(unsigned int buttonNo);
	// ボタンフラグをクリアする
	void clrButton(unsigned int buttonNo);

private:
	// 各コマンド処理
	bool cmd_pos();		// ポジション設定命令
	bool cmd_set();		// パラメータ設定命令
	bool cmd_cnt();		// カウンタ設定命令
	bool cmd_jump();	// ジャンプ命令
	bool cmd_call();	// コール命令
	bool cmd_ret();		// 復帰命令
	bool cmd_halt();	// 停止命令
	// タイマ処理
	void setTimer(int ms);	// 時間待ちセット
	bool isTimeUp();		// 時間待ちチェック

private:
	const MotionData *m_motion;	// 実行中のモーションデータへのポインタ
	const MotionData *m_stack[MOTION_STACK_SIZE]; // モーションデータのスタック
	int m_sp;					// モーションデータのスタック・ポインタ
	int m_pc;					// モーションデータのプログラム・カウンタ
	bool m_waiting;				// 待ち状態フラグ
	int m_cnt[CNT_NUM];			// カウンタ
	bool m_button[BUTTON_NUM];	// ボタンフラグ
	
	IcsServo *m_servos;			// ICSサーボの配列へのポインタ
	int16_t m_trims[SERVO_NUM];	// ICSサーボのトリム位置の配列
	
	uint32_t m_time_s;	// タイマ開始時刻
	uint32_t m_time_e;	// タイマ終了時刻
};

#endif
