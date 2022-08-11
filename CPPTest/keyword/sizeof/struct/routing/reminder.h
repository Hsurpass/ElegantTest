#pragma once

#include "basicTypes.h"
#include "laneModel.h"

namespace ncStruct {

enum ReminderType {
    ReminderType_none = 0,
    // guidanceVersion <= 11000时，表示一般直行。包括红绿灯路口直行、二岔路靠左/右直行。
    // guidanceVersion >= 13000时废除，细分为 ReminderType_passJunction 和 ReminderType_passFork.
    ReminderType_goStraight = 1,
    
    // 沿辅路继续行驶
    ReminderType_keepSideRoad = 2,
    
    // 7.0 or above "请保持左侧主路行驶"，仅适用于高速路和快速路
    ReminderType_keepMainRoad = 3,
    
    // guidanceVersion >= 13000, 表示“直行通过路口”
    ReminderType_passJunction = 4,
    
    // guidanceVersion >= 13000, 表示二叉顺行，T字口或者Y字口，旁边有个分叉
    ReminderType_passFork = 5,
    
    // guidanceVersion >= 14000, 表示通过第一个路口，前方有转向构成歧义的maneuver 
    ReminderType_passFirstJunction = 6,
    
    // guidanceVersion >= 21000, 隧道
    ReminderType_enterTunnel = 7,
};

struct Reminder {
    // 机动点位置
    std::string pos;

    // 提示点位置（距离路线起点）
    int dis;

    // Remidner的类型. guidanceVersion >= 6000
    // 无 ty 字段，表示ReminderType_goStraight
    ReminderType ty;    // [default = ReminderType_goStraight];

    // 播报提示类型，注：无 tnTy 段默认为 TurnType_straight
    TurnType tnTy; // [default = TurnType_straight];

    // 坡度提示. 无此字段，表示 SlopeHint_none.
    SlopeHint sH;

    // reminder事件前的路段在路线中的下标
    int sI;

    // reminder事件后的路段在路线中的下标
    int eI;

    // 不同guidance版本时格式不同, (dv >= 2.1.4)
    LaneModel laneModel;

    //  一些标记，以";"分割。T表示有红绿灯。 guidanceVersion >= 10000
    // optional string flags = 9;
    std::string flags;

    // 扩展属性参数，预留给定制化服务器设置任意扩展属性用，里面可以是任意 JSON 类型
    // optional google.protobuf.Any exts = 20;
    // void* exts = NULL;
};

}