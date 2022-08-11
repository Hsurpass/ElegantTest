#pragma once

#include "basicTypes.h"

namespace ncStruct {

enum LaneArrow {
    unknown = 0,

    bus = 1,
    /** ^ */
    up = 2,
    /** V */
    down = 3,
    /** < */
    left = 4,
    /** > */
    right = 5,
    /** <^ */
    leftUp = 6,
    /** ^> */
    rightUp = 7,
    /** <V */
    leftDown = 8,
    /** V> */
    rightDown = 9,
    /** V^ */
    upDown = 10,
    /** <> */
    leftRight = 11,
    /** <^> */
    leftUpRight = 12,
    /** V R */
    downReversed = 13,
    /** <V R */
    leftDownReversed = 14,
    /** V> R */
    rightDownReversed = 15,
    /** ^V R */
    upDownReversed = 16,
    /** aka "tidal lane" */
    tidal = 17,
    /** variable turn lane */
    variable = 18,

    etc = 19,
    ellipsis = 20,
    lowerMax = 21,

    busUpper = 50,
    tidalUpper = 51,
    upperMax = 52,
};

struct Lane {
    LaneArrow arrow;
    bool shouldUse;
};

struct LaneModelV1 {
    int laneNumber;
    LaneArrow driveArrow;
    std::vector<Lane> lanes;
};

struct LaneModelV2 {
    // common 以 ';' 为分隔符，分为三部分
    // 第一部分对应 LaneModelV1.laneNumber
    // 第二部分对应 LaneModelV1.driveArrow
    // 第三部分对应 LaneModelV1.lanes

    // LaneArrow 与字母之间的对应关系为：
    // 'a' 对应 LaneArrow_unknown, 'b' 对应 LaneArrow_bus, ..., 's' 对应 LaneArrow_variableTurn
    // 其中第三部分中，大写字母对应 LaneModelV1.Lane.shouldUse 为 true

    // 如该示例对应 LaneModelV1：
    // {
    //    laneNumber: 3,
    //    driveArrow: 5,
    //    lanes: [
    //      {arrow: 0,shouldUse: false},
    //      {arrow: 2,shouldUse: false},
    //      {arrow: 7,shouldUse: true}
    //    ]
    // }
    std::string common;
};

struct LaneModelV3 {
    Direction dir;
    // 符号化表达的车道信息, like "(↰) (↰) ↑ ↑ ↑ ↑"
    std::string lanesV3;
};

struct LaneModel{
	LaneModelV1 laneModelV1; 
	LaneModelV2 laneModelV2; 
	LaneModelV3 laneModelV3; 

	// V1, V2, V3;
    std::string version;
};

}