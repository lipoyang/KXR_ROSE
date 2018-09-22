#include "MotionController.h"

// XL2_000_ゆっくり歩行前（1回）
namespace M000{
    const CmdSet ServoParam1={SET_STRETCH,{ -1, -1, -1, -1, -1, -1, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80}};
    const CmdSet ServoParam2={SET_SPEED,  { 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80}};
    const CmdPos Pos1={  5,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  250,  300,  500,  150,  250, -200, -150}};
    const CmdPos Pos2={ 12,{    0,    0,    0,    0,-1200,-1200,    0,    0,  600,   50, 1200,    0,  800,  150,    0, -300}};
//    const CmdPos Pos3={ 30,{    0,    0,    0,    0,-1200,-1200,    0,    0,  600,   50, 1200,    0,  800,    0,    0, -400}};
    const CmdPos Pos4={ 15,{  400,  400,    0,    0,-1200,-1200,    0,    0,  500, -200, 1000,    0,  800,  250,    0, -400}};
    const CmdPos Pos5={ 20,{  400,  400,    0,    0,-1200,-1200,    0,    0,  500, -400,  600,    0,  100,  350,    0, -200}};
    const CmdPos Pos6={ 25,{  400,  400,    0,    0,-1200,-1200,    0,    0,  600, -400,  750,    0,  150,  400,  200,  200}};
    const CmdPos Pos7={ 30,{    0,    0,    0,    0,-1200,-1200,    0,    0,   50,  600,    0, 1200,    0,  800,  400,    0}};
    const CmdPos Pos8={ 15,{ -400, -400,    0,    0,-1200,-1200,    0,    0, -200,  500,    0, 1000,  250,  800,  400,    0}};
    const CmdPos Pos9={ 20,{ -400, -400,    0,    0,-1200,-1200,    0,    0, -400,  500,    0,  600,  350,  100,  200,    0}};
    const CmdPos Pos10={ 25,{ -400, -400,    0,    0,-1200,-1200,    0,    0, -400,  600,    0,  750,  400,  150, -200, -200}};
    const CmdSet ServoParam16={SET_STRETCH,{ 20, 20, 20, 20, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65}};
    const CmdPos Pos15={ 10,{  400, -400,    0,    0,-1200,-1200,    0,    0,  150,  150,  300,  300,  150,  150,    0,    0}};
    const MotionData motion[] = {
        { CMD_SET, (void*)&ServoParam1 },
        { CMD_SET, (void*)&ServoParam2 },
        { CMD_POS, (void*)&Pos1 },
        { CMD_POS, (void*)&Pos2 },
//        { CMD_POS, (void*)&Pos3 },
        { CMD_POS, (void*)&Pos4 },
        { CMD_POS, (void*)&Pos5 },
        { CMD_POS, (void*)&Pos6 },
        { CMD_POS, (void*)&Pos7 },
        { CMD_POS, (void*)&Pos8 },
        { CMD_POS, (void*)&Pos9 },
        { CMD_POS, (void*)&Pos10 },
        { CMD_SET, (void*)&ServoParam16 },
        { CMD_POS, (void*)&Pos15 },
        { CMD_HALT, NULL }
    };
}
