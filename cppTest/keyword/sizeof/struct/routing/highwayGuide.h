#pragma once

namespace ncStruct {

enum ServiceAreaGasBrand {
   ServiceAreaGasBrand_none = 0,
   ServiceAreaGasBrand_cnpc = 1,    ///< 中石油
   ServiceAreaGasBrand_sinopec = 2, ///< 中石化
   ServiceAreaGasBrand_shell = 4,   ///< 壳牌
   ServiceAreaGasBrand_mobil = 8,   ///< 美孚
   ServiceAreaGasBrand_bp = 16,     ///< 英国石油公司
   ServiceAreaGasBrand_other = 32,  ///< 其他
};

enum ServiceAreaEstablishment {
    ServiceAreaEstablishment_none = 0,
    ServiceAreaEstablishment_restaurant = 1,       ///< 餐馆
    ServiceAreaEstablishment_shop = 2,             ///< 商店
    ServiceAreaEstablishment_hotel = 4,            ///< 旅馆
    ServiceAreaEstablishment_publicToilet = 8,     ///< 公厕
    ServiceAreaEstablishment_gasStation = 16,      ///< 加油站
    ServiceAreaEstablishment_chargingStation = 32, ///< 电动汽车充电站
    ServiceAreaEstablishment_autoRepair = 64,      ///< 汽车修理
    ServiceAreaEstablishment_atm = 128,            ///< ATM(自动取款机)
};

enum RoadNumberType {
    RoadNumberType_none = 0,
    RoadNumberType_nationalHighway = 1,   ///< 国家级高速编号
    RoadNumberType_provincialHighway = 2, ///< 省级高速编号
    RoadNumberType_nationalRoad = 3,      ///< 国道编号
    RoadNumberType_provincialRoad = 4,    ///< 省道编号
    RoadNumberType_countyRoad = 5,        ///< 县道编号
    RoadNumberType_townRoad = 6,          ///< 乡道编号
    RoadNumberType_specialUseRoad = 7,    ///< 专用道编号
};

enum HighwayGuideType {
    HighwayGuideType_invalid = 0, ///< 无效类型
    HighwayGuideType_IC = 1,      ///< 出口
    HighwayGuideType_JC = 2,      ///< 高速连接线
    HighwayGuideType_SA = 3,      ///< 服务区
    HighwayGuideType_PA = 4,      ///< 停车区
    HighwayGuideType_TG = 5,      ///< 收费站
};

struct HighwayGuide {
    /** 高速行程路牌距离 */
    int dis;

    /** 高速行程路牌上的文字，多条文字用 ';' 分隔 */
    std::string nm;

    /** 高速行程路牌类型，注：无 ty 段默认为 IC */
    HighwayGuideType ty;
    
    /**
    * 高速行程路牌编号
    * 根据 nm 中的顺序，依次表明每个文字对应的路牌编号
    * 为节省流量，只记录到最后一个值不为 none 的元素
    * 如果所有元素的值均为 none，则本字段不下发
    */
    std::vector<RoadNumberType> roadNumberTypes;

    /**
    * 服务区设施信息
    * 同时包含多个信息时，由对应的几个枚举值进行位或运算的结果表示
    * 仅当 仅当 ty 为 SA 或 PA 时有意义
    * 缺省表示没有服务区设施信息
    */
    ServiceAreaEstablishment serviceAreaEstablishment;

    /**
    * 加油站品牌信息
    * 同时包含多个信息时，由对应的几个枚举值进行位或运算的结果表示
    * 缺省表示没有加油站品牌信息
    */
    ServiceAreaGasBrand serviceAreaGasBrand;

    /** 高速出口编号，缺省值为空字符串，表示不存在出口编号。 */
    std::string exitNumber;

    /** 出边是否在路线上，非0值表示是，0值表示否，缺省值为0。 */
    int onRoute;
};

struct HighwayGuideArray {
    // 成功失败标识，100: 成功
    int code;

    // 协议版本号
    std::string ver;

    // 高速行程数据对象信息
    std::vector<HighwayGuide> hgs;
};

}