#include "MotionController.h"

// ↑: 歩行前
namespace M001{
    const CmdSet ServoParam1={SET_STRETCH,{ -1, -1, -1, -1, -1, -1, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60}};
    const CmdPos Pos1={  5,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  250,  300,  500,  150,  250, -200, -150}};
    const CmdPos Pos2={ 12,{    0,    0,    0,    0,-1200,-1200,    0,    0,  600,   50, 1200,    0,  800,  150,    0, -300}};
    const CmdPos Pos4={  4,{  400,  400,    0,    0,-1200,-1200,  -50,    0,  500, -200, 1000,  -30,  500,  200,    0, -200}};
    const CmdPos Pos5={  3,{  400,  400,    0,    0,-1200,-1200,  -50,    0,  500, -400,  600,  -50,  100,  350,    0, -200}};
    const CmdSet ServoParam2={SET_STRETCH,{ -1, -1, -1, -1, -1, -1, 90, 40,100, 40,100, 40,100, 40, 90, 40}};
    const CmdPos Pos6={  8,{  400,  400,    0,    0,-1200,-1200,    0,    0,  800, -400, 1100,    0,  400,  400,  200,  200}};
    const CmdJump CmpButton1={COND_BTN_OFF, BTN_UP, +9};
    const CmdPos Pos7={ 10,{    0,    0,    0,    0,-1200,-1200,    0,   50,   50,  600,    0, 1200,  120,  550,  250,    0}};
    const CmdPos Pos8={  4,{ -400, -400,    0,    0,-1200,-1200,    0,   50, -200,  500,  -30, 1000,  200,  500,  200,    0}};
    const CmdPos Pos9={  3,{ -400, -400,    0,    0,-1200,-1200,    0,   50, -400,  500,  -50,  600,  350,  100,  200,    0}};
    const CmdSet ServoParam3={SET_STRETCH,{ -1, -1, -1, -1, -1, -1, 60, 90, 40,100, 40,100, 40,100, 60, 90}};
    const CmdPos Pos10={  8,{ -400, -400,    0,    0,-1200,-1200,    0,    0, -400,  800,    0, 1100,  400,  400, -200, -200}};
    const CmdJump CmpButton2={COND_BTN_OFF, BTN_UP, +3};
    const CmdPos Pos3={ 10,{    0,    0,    0,    0,-1200,-1200,  -50,    0,  600,   50, 1200,    0,  550,  120,    0, -250}};
    const CmdJump Jump1={COND_NONE, 0, -12};
    const CmdSet HomeStretch={SET_STRETCH,{ 20, 20, 20, 20, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65}};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    
    const MotionData motion[] = {
        { CMD_SET, (void*)&ServoParam1 },
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_SET, (void*)&ServoParam2 },
        { CMD_POS, (void*)&Pos6 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&Pos7 },
        { CMD_POS, (void*)&Pos8 },
        { CMD_POS, (void*)&Pos9 },
        { CMD_SET, (void*)&ServoParam3 },
        { CMD_POS, (void*)&Pos10 },
        { CMD_JUMP,(void*)&CmpButton2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_JUMP,(void*)&Jump1 },
        { CMD_SET, (void*)&HomeStretch },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// ↓: 歩行後
namespace M002{
    const CmdSet ServoParam1={SET_STRETCH,{ -1, -1, -1, -1, -1, -1, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60}};
    const CmdPos Pos1={  5,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  250,  300,  500,  150,  250, -200, -150}};
    const CmdPos Pos2={ 12,{    0,    0,    0,    0,-1200,-1200,    0,    0,  600,   50, 1200,    0,  800,    0,    0, -300}};
    const CmdJump CmpButton1={COND_BTN_OFF, BTN_DOWN, +11};
    const CmdPos Pos7={ 10,{ -400, -400,    0,    0,-1200,-1200,    0,    0, -400,  600,    0,  750,  400,  150,    0, -300}};
    const CmdPos Pos8={  6,{ -400, -400,    0,    0,-1200,-1200,    0,    0, -400,  200,    0,  200,  200,  100,  200,  200}};
    const CmdPos Pos9={  6,{ -400, -400,    0,    0,-1200,-1200,    0,    0, -200,  500,    0, 1000,  100,  300,  300,    0}};
    const CmdPos Pos10={  8,{    0,    0,    0,    0,-1200,-1200,    0,    0,   50,  600,    0, 1200,  -50,  400,  300,    0}};
    const CmdJump CmpButton2={COND_BTN_OFF, BTN_DOWN, +6};
    const CmdPos Pos3={ 10,{  400,  400,    0,    0,-1200,-1200,    0,    0,  600, -400,  750,    0,  150,  400,    0,  300}};
    const CmdPos Pos4={  6,{  400,  400,    0,    0,-1200,-1200,    0,    0,  200, -400,  200,    0,  100,  200, -200, -200}};
    const CmdPos Pos5={  6,{  400,  400,    0,    0,-1200,-1200,    0,    0,  500, -200, 1000,    0,  300,  100,    0, -300}};
    const CmdPos Pos6={  8,{    0,    0,    0,    0,-1200,-1200,    0,    0,  600,   50, 1200,    0,  400,  -50,    0, -300}};
    const CmdJump Jump1={COND_NONE, 0, -10};
    const CmdSet HomeStretch={SET_STRETCH,{ 20, 20, 20, 20, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65}};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_SET, (void*)&ServoParam1 },
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&Pos7 },
        { CMD_POS, (void*)&Pos8 },
        { CMD_POS, (void*)&Pos9 },
        { CMD_POS, (void*)&Pos10 },
        { CMD_JUMP,(void*)&CmpButton2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_POS, (void*)&Pos6 },
        { CMD_JUMP,(void*)&Jump1 },
        { CMD_SET, (void*)&HomeStretch },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// ←: 歩行左
namespace M003{
    const CmdPos Pos1={  4,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,    0,  300,    0,  150,    0,  200,  400}};
    const CmdPos Pos2={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,    0,  500,  -50, 1000,    0,  500,  400,    0}};
    const CmdPos Pos3={  3,{  400, -400,    0,    0,-1200,-1200, -300,  500,    0,  500,  -50, 1000,    0,  500,    0,  300}};
    const CmdPos Pos4={  6,{  400, -400,    0,    0,-1200,-1200, -500,  500,    0,  500,  -50, 1000,    0,  500, -200,  300}};
    const CmdPos Pos5={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0, -200}};
    const CmdJump CmpButton1={COND_BTN_ON, BTN_LEFT, -5};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// →: 歩行右
namespace M004{
    const CmdPos Pos1={  4,{  400, -400,    0,    0,-1200,-1200,    0,    0,    0,  150,    0,  300,    0,  150, -400, -200}};
    const CmdPos Pos2={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  500,    0, 1000,  -50,  500,    0,    0, -400}};
    const CmdPos Pos3={  3,{  400, -400,    0,    0,-1200,-1200, -500,  300,  500,    0, 1000,  -50,  500,    0, -300,    0}};
    const CmdPos Pos4={  6,{  400, -400,    0,    0,-1200,-1200, -500,  500,  500,    0, 1000,  -50,  500,    0, -300,  200}};
    const CmdPos Pos5={ 10,{  400, -390,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,  200,    0}};
    const CmdJump CmpButton1={COND_BTN_ON, BTN_RIGHT, -5};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// L2: 歩行左旋回
namespace M021{
    const CmdPos Pos1={  3,{  400, -400,    0,    0,-1200,-1200, -120,  120,  650, -500,  300,  200, -400,  650, -300,  300}};
    const CmdPos Pos2={  5,{  400, -400,    0,    0,-1200,-1200, -200,  200,  650, -500,  300,  200, -400,  650, -300,  300}};
    const CmdPos Pos3={ 20,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const CmdJump CmpButton1={COND_BTN_ON, BTN_L2, -3};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// R2: 歩行右旋回
namespace M022{
    const CmdPos Pos1={  3,{  400, -400,    0,    0,-1200,-1200, -120,  120, -500,  650,  200,  300,  650, -400, -300,  300}};
    const CmdPos Pos2={  5,{  400, -400,    0,    0,-1200,-1200, -200,  200, -500,  650,  200,  300,  650, -400, -300,  300}};
    const CmdPos Pos3={ 20,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const CmdJump CmpButton1={COND_BTN_ON, BTN_R2, -3};
    const CmdPos HomePos={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
        { CMD_POS, (void*)&Pos3 },
        { CMD_JUMP,(void*)&CmpButton1 },
        { CMD_POS, (void*)&HomePos },
        { CMD_RET, NULL }
    };
}

// メインモーション
namespace M000{
    const CmdSet ServoParam1={SET_STRETCH,{ 20, 20, 20, 20, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65}};
    const CmdPos Pos1={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
	const CmdJump Wait = { COND_BTN_OFF, BTN_ALL, 0 };
    const CmdCall CallM001 ={COND_BTN_ON, BTN_UP,           M001::motion}; // ↑: 歩行前
    const CmdCall CallM002 ={COND_BTN_ON, BTN_DOWN,         M002::motion}; // ↓: 歩行後
    const CmdCall CallM003 ={COND_BTN_ON, BTN_LEFT,         M003::motion}; // ←: 歩行左
    const CmdCall CallM004 ={COND_BTN_ON, BTN_RIGHT,        M004::motion}; // →: 歩行右
//    const CmdCall CallM011 ={COND_BTN_ON, BTN_L1|BTN_UP,    M011::motion}; // L1+↑: 歩行少し前
//    const CmdCall CallM012 ={COND_BTN_ON, BTN_L1|BTN_DOWN,  M012::motion}; // L1+↓: 歩行少し後
//    const CmdCall CallM013 ={COND_BTN_ON, BTN_L1|BTN_LEFT,  M013::motion}; // L1+←: 歩行少し左
//    const CmdCall CallM014 ={COND_BTN_ON, BTN_L1|BTN_RIGHT, M014::motion}; // L1+→: 歩行少し右
    const CmdCall CallM021 ={COND_BTN_ON, BTN_L2,           M021::motion}; // L2: 歩行左旋回
    const CmdCall CallM022 ={COND_BTN_ON, BTN_R2,           M022::motion}; // R2: 歩行右旋回
//    const CmdCall CallM101 ={COND_BTN_ON, BTN_R1|BTN_UP,    M101::motion}; // R1+↑: 起き上がり(仰向け)
//    const CmdCall CallM102 ={COND_BTN_ON, BTN_R1|BTN_DOWN,  M102::motion}; // R1+↓: 起き上がり(うつ伏せ)
//    const CmdCall CallM201 ={COND_BTN_ON, BTN_L1|BTN_TRNGL, M201::motion}; // L1+△: パンチ左ストレート
//    const CmdCall CallM202 ={COND_BTN_ON, BTN_R1|BTN_TRNGL, M202::motion}; // R1+△: パンチ右ストレート
//    const CmdCall CallM211 ={COND_BTN_ON, BTN_L1|BTN_CROSS, M211::motion}; // L1+×: パンチ左裏拳
//    const CmdCall CallM212 ={COND_BTN_ON, BTN_R1|BTN_CROSS, M212::motion}; // R1+×: パンチ右裏拳
//    const CmdCall CallM220 ={COND_BTN_ON, BTN_L1|BTN_R1,    M220::motion}; // L1+R1: 防御
//    const CmdCall CallM301 ={COND_BTN_ON, BTN_L1|BTN_SQUARE,M301::motion}; // L1+□: あいさつ
//    const CmdCall CallM302 ={COND_BTN_ON, BTN_L1|BTN_CIRCLE,M302::motion}; // L1+○: 手を振る
//    const CmdCall CallM401 ={COND_BTN_ON, BTN_L2|BTN_SQUARE,M401::motion}; // R1+□: 腕立て
//    const CmdCall CallM402 ={COND_BTN_ON, BTN_L2|BTN_CIRCLE,M402::motion}; // R1+○: 前転
    const CmdJump Jump1 ={COND_NONE, 0, -7};
    
    const MotionData motion[] = {
        { CMD_SET, (void*)&ServoParam1 },
        { CMD_POS, (void*)&Pos1 },
		{ CMD_JUMP, (void*)&Wait },
		{ CMD_CALL, (void*)&CallM001 },
        { CMD_CALL, (void*)&CallM002 },
        { CMD_CALL, (void*)&CallM003 },
        { CMD_CALL, (void*)&CallM004 },
//        { CMD_CALL, (void*)&CallM011 },
//        { CMD_CALL, (void*)&CallM012 },
//        { CMD_CALL, (void*)&CallM013 },
//        { CMD_CALL, (void*)&CallM014 },
        { CMD_CALL, (void*)&CallM021 },
        { CMD_CALL, (void*)&CallM022 },
//        { CMD_CALL, (void*)&CallM101 },
//        { CMD_CALL, (void*)&CallM102 },
//        { CMD_CALL, (void*)&CallM201 },
//        { CMD_CALL, (void*)&CallM202 },
//        { CMD_CALL, (void*)&CallM211 },
//        { CMD_CALL, (void*)&CallM212 },
//        { CMD_CALL, (void*)&CallM220 },
//        { CMD_CALL, (void*)&CallM301 },
//        { CMD_CALL, (void*)&CallM302 },
//        { CMD_CALL, (void*)&CallM401 },
//        { CMD_CALL, (void*)&CallM402 },
        { CMD_JUMP, (void*)&Jump1 }
    };
}
