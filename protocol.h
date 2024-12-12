#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#pragma pack(1)

struct ClientToServerMessage
{
    int stateDemand;
    int shutdown;
    int allHome;
    int axisHome;
    char musicPath[256]; // Fixed size array for simplicity
};

struct LimbStatus
{
    float posDes = 0.0;
    float pos = 1.0;
    float vel = 2.0;
    float cur = 3.0;
    int status = 1;
    int homeDone = 0;
};

struct ServerToClientMessage
{
    int mainState = 1;

    int can1Status = 1;
    int can2Status = 0;
    int can3Status = 1;

    LimbStatus L1;
    LimbStatus L2;
    LimbStatus L3;
    LimbStatus LW;
    LimbStatus R1;
    LimbStatus R2;
    LimbStatus R3;
    LimbStatus RW;
    LimbStatus Waist;
};

#endif // PROTOCOL_H
