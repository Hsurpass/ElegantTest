
#pragma once

#include "basicTypes.h"
#include "adasData.h"
#include "maneuver.h"
#include "reminder.h"
#include "enroute_had_data.h"

namespace ncStruct {

struct RestrictionTimePeriod {
    unsigned int dateTypeBitmap;
	uint32_t excludedDateTypeBitmap;
    std::string times;
    std::string specialDays;
    unsigned int extendDateTypeBitmap;
};

// ���е�������Ϣ
struct CityDetail {
   // ��״������
   int adminCode;
   // ��������
   std::string name;
};

struct RegulationShape {
    /*
     * encoded points string with PolylineCodec::allocEncodedData()
     * һ�� RestrictionShape �����п��ܺ��ж��������״��(INT_MAX, INT_MAX)Ϊ�ָ�����
     */
    std::string pts;

    /* shape type: polyline or polygon */
    RestrictionShapeType shapeType;
};

/** ������ʾ��Ԥ��·�ߵ�ͬʱ��AppӦ���úܼ��ĵ�����ʾչʾĳ��·�ߵĻ���Υ����� */
struct EnrouteRegulationNotice {
    /* ������ʾ����, like "4/6 �廷β������".*/
    std::string title;
    /** like "��㴦���޷��ܿ������У���������ų���"; ������ʾ������ */
    std::string subtitle;
    /** ��������޷��ܿ��ģ����Ի���Ϊ��ɫ��Ϊ��ʾ */
    bool hasUnavoidableTerms;
    /**
     * ����������״��
     * ����ж����״���ߣ����ǻ�Ԥ�Ƚ��ж���κϲ���Ŀ���Ǽ���������������ֹ�ظ����ơ�
     * ÿ��shape��ʾһ������Σ����߱�ʾͬ����һ�����ߵ�һ��polyline��
     */
    std::vector<RegulationShape> shapes;
};

enum RestrictionIconType {
	RestrictionIconType_none = 0,
	RestrictionIconType_forbiddenCarPass = 1,		///< ��ֹ�ͳ�ͨ�У������������ͣ�ʱ��ε���Ϣ�����-������ʽ
	RestrictionIconType_forbiddenTruckPass = 2,		///< ��ֹ����ͨ�У����-������ʽ
	RestrictionIconType_heightLimit = 3,			///< ���޸�
	RestrictionIconType_widthLimit = 4,				///< ���޿�
	RestrictionIconType_weightLimit = 5,			///< ������
	RestrictionIconType_axleWeightLimit = 6,		///< ��������
	RestrictionIconType_underConstruction = 7,		///< ��·�ڽ�
	RestrictionIconType_underRepair = 8,			///< ��·ʩ����
	RestrictionIconType_oneWay = 9,					///< ��������ͨ��
	RestrictionIconType_forbidThrough = 10,			///< ��·�ν�ֹ����
	RestrictionIconType_forbidEnter = 11,			///< ��·�ν�ֹ����
	RestrictionIconType_regulationForCar = 12,		///< �������У�β������
	RestrictionIconType_regulationForTruck = 13,		///< �������У�β������
};

enum RestrictionItemType {
	RestrictionItemType_none = 0,
	RestrictionItemType_forbiddenCarPass = 1,		///< ��ֹ�ͳ�ͨ�У������������ͣ�ʱ��ε���Ϣ�����-������ʽ
	RestrictionItemType_forbiddenTruckPass = 2,		///< ��ֹ����ͨ�У����-������ʽ
	RestrictionItemType_physicalRestriction = 3,	///< ���������У������޸����ص�
	RestrictionItemType_underConstruction = 4,		///< ��·�ڽ�
	RestrictionItemType_underRepair = 5,			///< ��·ʩ����
	RestrictionItemType_oneWay = 6,					///< ��������ͨ��
	RestrictionItemType_forbidThrough = 7,			///< ��·�ν�ֹ����
	RestrictionItemType_forbidEnter = 8,			///< ��·�ν�ֹ����
	RestrictionItemType_regulationBasedRestriction = 9,		///< �������У�β������
};

enum RegulationAvoidanceState {
    RegulationAvoidanceState_none = 0,
	RegulationAvoidanceState_unavoidable = 1,		// �޷��ܿ�������
	RegulationAvoidanceState_avoided = 2,			// �ѱܿ�������
	RegulationAvoidanceState_latent = 3,			// δ��Ч������Ǳ�ڷ��յ�����
};


struct RestrictionDescribe
{
	std::string dateSpan;
	std::string displayText;
};

/* ��ʾ����������߽��е�link range��startIndices��·����link���±ꡣlengths��·��������*/
struct Range {
	std::vector<int> startIndices;  // is empty array if state == RegulationAvoidanceState_avoided
	std::vector<int> lengths;   // is empty array if state == RegulationAvoidanceState_avoided
};

struct VehicleRestrictionItem {
    RegulationAvoidanceState state;
	uint32_t adminCode = (uint32_t)-1;

	int startIndex = -1;
	int linkCount = -1;
	Range ranges;

    std::string position;
    RestrictionItemType itemType;
    RestrictionIconType iconType;
    
    /** encrypted limit data corresponding to iconType.
    *
    * if PostData.requirePhysicalRestrictionData == 1
    *    && (iconType == heightLimit || iconType == widthLimit
    *        || iconType == weightLimit || iconType == axWeightLimit);
    */
    int v;

    // Default as true.
    bool isTruckRestriction;

    // Whether or not this restriction work when the current vehicle pass it. Default as true.
    bool workForCurrentVehicle;

    /**
    * If not present, it means this restriction is not regulation based.
    */
    int64_t regulationId;

    /** ��Щ���ߵ���״��һ���ģ�Ϊ�˽�Լ�ռ䣬����ֻ����������״��ID */
    int64_t regulationShapeGroupId;

    /** description of the regulation */
	RestrictionDescribe description;

    // ��״��
    std::string shape;

    /*
	����ʱ�����Ϣ��������ʾһ�����е���Чʱ�����Ϣ��
	���Ա�������֧�ֵ�����ʱ�����Ϣ�����磺
		
	* 2006��1��1������2020��12��31��ֹ��ÿ�����8�㵽��8��
	* ��2009��7��1���𣬹����յ�7�㵽19:30
	* �ڼ��գ���ĩ

		�ȵȡ�
	*/
	std::vector<RestrictionTimePeriod> timePeriods;
};

// ��·������Ϣ
struct RegulationResult {
   std::vector<VehicleRestrictionItem> vehicleRestrictionItems;
   std::vector<EnrouteRegulationNotice> notices;
   std::vector<CityDetail> cityDetails; // ��������
};

struct TollStation {
   std::string nm;   // �շ�վ����
   std::string pos;  // ��������
   uint64_t id;   // �շ�վ ID
};

/// ת����ͼ�� ID
enum TNaviTurnIconID {
    ENTI_None = 0,
	ENTI_Arrival = 1,                       // ����Ŀ�ĵء�GUIDANCE_ENGINE_VERSION_17�����ENTI_routePointOnLeft/ENTI_routePointOnRight/ENTI_routePointOnMiddle
	ENTI_TurnAround = 2,                    // ��ͷ
	ENTI_EnterMainRoute = 3,                // ���������·
	ENTI_EnterRotary = 4,                   // ���뻷����(ת�����ֻ�е��յ��ڻ����ϻ�ʹ��)
	ENTI_GoStraight = 5,                    // ֱ��
	ENTI_LeaveMainRoute = 6,                // ���ҽ��븨·
	ENTI_LeaveRotary = 7,                   // �뿪������ת�������ö�̬���Ƶĸ���ת���
	ENTI_TurnLeft = 8,                      // ��ת��ת�������ö�̬���Ƶĸ���ת���
	ENTI_TurnRight = 9,                     // ��ת��ת�������ö�̬���Ƶĸ���ת���
	ENTI_TurnSlightlyLeft = 10,         	// ��ǰ��ת�䡣ת�������ö�̬���Ƶĸ���ת���
	ENTI_TurnSlightlyRight = 11,            // ��ǰ��ת�䡣ת�������ö�̬���Ƶĸ���ת���
	ENTI_Rotary1 = 12,                      // �ѷ���������ENTI_LeaveRotary
	ENTI_Rotary2 = 13,                      // �ѷ���������ENTI_LeaveRotary
	ENTI_Rotary3 = 14,                      // �ѷ���������ENTI_LeaveRotary
	ENTI_Rotary4 = 15,                      // �ѷ���������ENTI_LeaveRotary
	ENTI_Rotary5 = 16,                      // �ѷ���������ENTI_LeaveRotary
	ENTI_Rotary6 = 17,                      // �ѷ���������ENTI_LeaveRotary
	ENTI_Rotary7 = 18,                      // �ѷ���������ENTI_LeaveRotary
	ENTI_Rotary8 = 19,                      // �ѷ���������ENTI_LeaveRotary
	ENTI_Rotary9 = 20,	                    // �ѷ���������ENTI_LeaveRotary
	ENTI_2wayForkLeft = 21,                 // �ѷ����������ڴ�ֵ
	ENTI_2wayForkRight = 22,                // �ѷ����������ڴ�ֵ
	ENTI_TurnHardLeft = 23,                 // ���ת�䡣ת�������ö�̬���Ƶĸ���ת���
	ENTI_TurnHardRight = 24,                // �Һ�ת�䡣ת�������ö�̬���Ƶĸ���ת���
	ENTI_TurnLeftKeepLeft = 25,             // ��ת����ת�������ö�̬���Ƶĸ���ת���
	ENTI_TurnLeftKeepRight = 26,            // ��ת���ҡ�ת�������ö�̬���Ƶĸ���ת���
	ENTI_TurnRightKeepLeft = 27,            // ��ת����ת�������ö�̬���Ƶĸ���ת���
	ENTI_TurnRightKeepRight = 28,           // ��ת���ҡ�ת�������ö�̬���Ƶĸ���ת���
	ENTI_EnterTunnel = 29,                  // ����������
	ENTI_TakeFerry = 30,                    // �����ֶ�
	ENTI_Start = 31,                        // ��������
	ENTI_WayPoints1 = 32,                   // �����һ��;����
	ENTI_WayPoints2 = 33,                   // ����ڶ���;����
	ENTI_WayPoints3 = 34,                   // ���������;����
	ENTI_IC = 35,	                        // �ѷ����������ڴ�ֵ
	ENTI_DR = 36,	                        // �ѷ����������ڴ�ֵ
	ENTI_Overpass = 37,                 	// �ѷ����������ڴ�ֵ
	ENTI_WindOverpass = 38,	                // �ѷ����������ڴ�ֵ
	ENTI_StraightKeepLeft = 39,             // ���ֱ�С�ת�������ö�̬���Ƶĸ���ת���
	ENTI_StraightKeepRight = 40,            // �Ҳ�ֱ�С�ת�������ö�̬���Ƶĸ���ת���

	ENTI_DetourOnTheLeft = 41,              // ����ʻ����١�ת�������ö�̬���Ƶĸ���ת���
	ENTI_DetourOnTheRight = 42,             // ����ʻ����١�ת�������ö�̬���Ƶĸ���ת���

	ENTI_Stair = 43,                        // �߽��ݣ�����ר��
	ENTI_Underpass = 44,                    // �ߵ���ͨ��������ר��
	ENTI_Footbridge = 45,                   // �߹������ţ�����ר��
	ENTI_Square = 46,                       // ��Խ�㳡������ר��
	ENTI_Bridge = 47,                       // ���ţ�����ר��
	ENTI_Park = 48,                         // ������԰������ר��

	ENTI_3WayForkLeft = 49,                 // ����·����ֱ�С�ת�������ö�̬���Ƶĸ���ת���
	ENTI_3WayForkMiddle = 50,               // ����·�м�ֱ�С�ת�������ö�̬���Ƶĸ���ת���
	ENTI_3WayForkRight = 51,                // ����·����ֱ�С�ת�������ö�̬���Ƶĸ���ת���

	ENTI_WayPoints4 = 52,                   // ������ĸ�;����
	ENTI_KeepDrivingOnCurrentRoad = 53,     // ��·ֱ��

	ENTI_passTollbooth = 54,	            // �����շ�վ��since GUIDANCE_ENGINE_VERSION_16
	ENTI_uTurnOnRotary = 55,	            // ��������ͷ��since GUIDANCE_ENGINE_VERSION_16

	ENTI_routePointOnLeft = 56,				// ·���ڵ�·����ࡣsince GUIDANCE_ENGINE_VERSION_17
	ENTI_routePointOnRight = 57,			// ·���ڵ�·���Ҳࡣsince GUIDANCE_ENGINE_VERSION_17
	ENTI_routePointOnMiddle = 58,           // ·���ڵ�·���м䡣since GUIDANCE_ENGINE_VERSION_17

	//drive on left
	ENTI_DriveOnLeft_TurnAround = 1002,     // �Ҷ棬�ο���Ӧ�����
	ENTI_DriveOnLeft_EnterMainRoute = 6,    // �Ҷ棬�ο���Ӧ�����
	ENTI_DriveOnLeft_EnterRotary = 1004,    // �Ҷ棬�ο���Ӧ�����
	ENTI_DriveOnLeft_LeaveMainRoute = 3,    // �Ҷ棬�ο���Ӧ�����
	ENTI_DriveOnLeft_LeaveRotary = 1007,    // �Ҷ棬�ο���Ӧ�����
	ENTI_DriveOnLeft_Rotary1 = 1012,        // �ѷ���������ENTI_DriveOnLeft_LeaveRotary
	ENTI_DriveOnLeft_Rotary2 = 1013,        // �ѷ���������ENTI_DriveOnLeft_LeaveRotary
	ENTI_DriveOnLeft_Rotary3 = 1014,        // �ѷ���������ENTI_DriveOnLeft_LeaveRotary
	ENTI_DriveOnLeft_Rotary4 = 1015,        // �ѷ���������ENTI_DriveOnLeft_LeaveRotary
	ENTI_DriveOnLeft_Rotary5 = 1016,        // �ѷ���������ENTI_DriveOnLeft_LeaveRotary
	ENTI_DriveOnLeft_Rotary6 = 1017,        // �ѷ���������ENTI_DriveOnLeft_LeaveRotary
	ENTI_DriveOnLeft_Rotary7 = 1018,        // �ѷ���������ENTI_DriveOnLeft_LeaveRotary
	ENTI_DriveOnLeft_Rotary8 = 1019,        // �ѷ���������ENTI_DriveOnLeft_LeaveRotary
	ENTI_DriveOnLeft_Rotary9 = 1020,        // �ѷ���������ENTI_DriveOnLeft_LeaveRotary
	ENTI_DriveOnLeft_uTurnOnRotary = 1021,	// �Ҷ棬�ο���Ӧ����档since GUIDANCE_ENGINE_VERSION_16
};

struct DetailDescription {
    /** ����һ��·��������Ŀ�ľ��� */
    int dis;
    /** ·�������ı��� */
    std::string tit;
    /** ·���������ӱ��� */
    std::string st;
    /** ת����ͼ�� ID */
    TNaviTurnIconID ty;
    /** ·��������Ӧ·���Ӽ��еĵ�һ��·����·���ϵ��±� */
    int sSI;
    /** ����������� pet ָ����ʽ����ľ�γ�� */
    std::string pos;
    /** �Ƿ�Ϊ������ */
    bool chd;
};

enum SidewalkType {
	SidewalkType_none = 0,
	SidewalkType_crosswalk = 1,
	SidewalkType_underpass = 2,
	SidewalkType_footbridge = 3,
	SidewalkType_square = 4,
	SidewalkType_park = 5,
	SidewalkType_stair = 6,
	SidewalkType_junction = 7,
	SidewalkType_rotary = 8,
	SidewalkType_bridge = 9,
};

// ·��˵�����ͣ�ע�ⲻҪ�޸��京�������
enum DirectionType {
	DirectionType_none = 0,			///<	none
	DirectionType_start = 1,		///<	���
	DirectionType_nameChange = 2,	///<	·���仯 obsolete
	DirectionType_turn = 3,			///<	ת��
	DirectionType_overpass = 4,		///<	����  obsolete
	DirectionType_IC = 5,			///<	IC
	DirectionType_DR = 6,			///<	DR
	DirectionType_passWaypoint = 7,	///<	;����
	DirectionType_arriveDest = 8,	///<	�յ�

	// for pedestrian route.
	DirectionType_sidewalk = 9,		///<	�����б��;�µ�routeDetail����ö�ٴ�������ר�ã������������б��������������ͨ������������ר������
};

struct RouteDirection {
    std::string pos;             // ��������������
    int dis;              // ��·�����ľ���
    DirectionType ty;       // ���ͣ�ע�� �� ty ��Ĭ��Ϊ DirectionType_turn
    TurnType tnTy;          // ת�����ͣ�ע���� tnTy ��Ĭ��Ϊ TurnType_straight
    int wpId;             // if ty == 7;    // ;������
    int wd;               // �Ƿ����Ź�����
    std::string nm;              // ·��
    SignInfoType sITy;      // ·������
    std::string sNm;             // ·������
    int lv;              // �ȼ�
    int sSI;             // ��ʼ·���±�
    int eSI;             // ����·���±�
    int nc;              // ��·�����Ƿ�ı�
    SidewalkType st;       // ���б������
};

struct TrafficLightDetail {
    /** the index of which segment the traffic light lies at */
    int segIndex;
    /** unit: second */
    int travelTime;

    /** the follow fields are debug only; would not appear in formal product */
    int cost;
    int capacity;
};

/** ƽ��·��ʶ */
enum ParallelRoadMark
{
	ParallelRoadMark_none = 0,
	ParallelRoadMark_hasSideRoad = 1,              // �и�·
	ParallelRoadMark_hasMainRoad = 2,              // ����·

	// ע������ö�ٵ�֧��Ҫ�����ݱ����� rdbc.exe �汾������ 0.8.45���Ҹ������� prm.exe �汾������ 1.1.0
	ParallelRoadMark_hasElevatedRoad = 4,            // �и߼�·
	ParallelRoadMark_hasRoadUnderElevatedRoad = 8,   // �и߼��µ�·

	// 16; 32; 64; ...
};

enum TrafficState {
    TrafficState_unknown = 0,      // δ֪
    TrafficState_light = 1,        // ͨ��
    TrafficState_medium = 2,       // ����
    TrafficState_heavy = 3,        // ӵ��
    TrafficState_severe = 4,       // ����ӵ�£�dv >= 2.2.0 ��ʼ֧��
    TrafficState_max = 5,
};

/// ��·��;��
enum SegmentUsage {
	SegmentUsage_rotary = 0,                        // ����
	SegmentUsage_unknown = 1,                       // ��ͨ��·
	SegmentUsage_divided = 2,                       // �����з����·
	SegmentUsage_ramp = 3,                          // �ѵ�
	SegmentUsage_highBridge = 3,                    // ͬramp��֮ǰ�� highBridge������
	SegmentUsage_junction = 4,                       // ·���ڵ�·��ͨ��������4��·�Ρ�
	SegmentUsage_exitrance = 5,                      // ����ڡ�
	SegmentUsage_parkingLot = 6,                     // ͣ������
	SegmentUsage_serviceArea = 7,                    // ��������
	SegmentUsage_bridge = 8,                         // ��(ͨ��ָ�����)�����ϣ�abolished���Ժ�NKVD���ݲ����ٳ���������ԡ�
	SegmentUsage_pedestrianStreetDeprecated = 9,     // ���ϡ���ʹ��pedestrianEnable���ԡ�
	SegmentUsage_sideRoadDeprecated = 10,            // ���ϡ���ʹ��sideRoad���ԡ�
	SegmentUsage_immediateRightTurn = 11,
	SegmentUsage_uTurn = 12,                      // ��ͷ����
	SegmentUsage_leftTurn = 13,                   // ��ת����
	SegmentUsage_rightTurn = 14,                  // ��ǰ��ת����
	SegmentUsage_tunnelDeprecated = 15,           // ���ϡ���ʹ��tunnel���ԡ�
	SegmentUsage_MAXNUM = 16,
};

/// ��·�ȼ�����ֵԽС�ȼ�Խ�ߡ�
enum SegmentPriority {
	SegmentPriority_highway = 0,      // ���ٹ�·
	SegmentPriority_expWay = 1,       // ���п���·
	SegmentPriority_arterial = 2,     // ����
	SegmentPriority_localMajor = 3,   // ʡ��
	SegmentPriority_local = 4,
	SegmentPriority_localPath = 5,
	SegmentPriority_localMinor = 6,
	SegmentPriority_poiConnector = 7, // POI�����ߣ�������С��·�������Դ���
	SegmentPriority_other = 8,        // С��·�����ܴ���
	SegmentPriority_bicycleLane = 9,  // ��ά�����еġ��ż���·���ǻ�������ͨ�еĸ�·���Ƕ���Ϊ�ż���·����
	SegmentPriority_sailingRoute = 10,
	SegmentPriority_pedestrian = 11,
	SegmentPriority_MAXNUM = 16,
};

struct Segment {
    /*
    * flag ���� linkId ʱ�����ֶδ��ڣ��京��Ϊ���Ի�Ŵ�ͼʹ�õ�link id��
    * ���ֶ����� RouteServerResult.guid ���ʹ�á�
    * ���ֶν�������� flag ���� linkId ʱ�·���
    * ������ʷԭ�򣬸��ֶ�����ϴ����©�����庬����ʷ�ϳ��ֹ��䶯���Ѳ��ٽ���ʹ�á�
    */
    int id;
    
    // ·�γ���
    int dis;         
    
    // ·�εȼ�
    SegmentPriority pr;

    // ·����; (dv >= 2.1.3)
    SegmentUsage usage;

    // ·�γ�����; �������һ�� segment ȡֵ��ͬ��ʡ�Ը��ֶ�.
    int laneCount;

    // ·��ĩ���Ƿ��к��̵�. (dv >= 2.1.3)
    int trafficLight;

    // ·�����ƣ�ȱʡ��ʾ��ǰһ�� Segment ��·������ͬ
    std::string nm;

    // ��״��
    std::string shPos;
    
    // ��άID�������� flag �а��� linkDir �����ڸ�·���б� link Ϊ����
    // link ��From node2 to node1��ʱ�� * ��β
    std::string niId;       
    
    // ��ͨ״��
    TrafficState tmcLv;

    // �Ƿ�Ϊ����
    int tunnel;

    // ·�ε���ͨ����ֵ����λ��km/h��ȱʡֵ��ǰһ��·�ε���ͨ����ֵ��ͬ
    int spl;                 
    
    // ·�εĻ�������ֵ����ͨ����ֵ�Ĳ�ֵ����λ��km/h��������һ��·����ͬ������ֶ�ʡ�ԡ�
    // ��һ��·�θ��ֶε�ȱʡֵ�� 0
    int tspld;

    // �������ƣ�ȱʡ��ʾ��ǰһ�� Segment ����������ͬ
    std::string tunnelName;

    // ������ȱʡ��ʾ��ǰһ�� Segment ��������ͬ
    std::string bridgeName;

    // ͨ�з��򣨿���/���ң���������һ��·�εķ�����ͬ������ֶ�ʡ�ԡ�
    // ��һ��·�θ��ֶ�ȱʡΪ TrafficDirection_rightHand��
    TrafficDirection trafficDirection; 
    
    // ƽ��·��ǣ�������һ��·�ε�ƽ��·�����ͬ������ֶ�ʡ�ԡ�
    // ��һ��·�θ��ֶ�ȱʡΪ ParallelRoadMark_none��
    ParallelRoadMark prm;  

    // ·�ε� 3D ��״��(Three-D Shape Points)���� routing_ext::Enroute3DLinkEncoder 
    // ����õ����ַ�����
    // ȱʡֵΪ�գ���ʾ��·��û�� 3D ��״�㡣
    // ���ֶν�������� flag ���� tdsp ʱ�·���
    std::string tdsp;
};

enum VehicleRestrictionState {
    VehicleRestrictionState_none = 0,
    VehicleRestrictionState_notRestricted = 1,
    VehicleRestrictionState_restricted = 2,
};

struct VehicleRestriction {
    // e.g. "_": [0; "11432456;4672113"; 0; 2; 0; 2; 0]
    // if dv >= 2.1.5
    int segmentIndex;
    std::string position;

	VehicleRestrictionState widthState;
	VehicleRestrictionState heightState;
	VehicleRestrictionState weightState;
    VehicleRestrictionState axleWeightState;
    
    float width = 7;			///< �����Ŀ��ȣ���λ�ף�0 ��ʾ��������һ��
	float height = 8;			///< �����ĸ߶ȣ���λ�ף�0 ��ʾ��������һ��
	int weight = 9;			///< ��������������λǧ�ˣ�0 ��ʾ��������һ��
	int payload = 10;			///< �����ĺ˶����أ���λǧ�ˣ�0 ��ʾ��������һ��
	int axleWeight = 11;		///< ���������أ���λǧ�ˣ�0 ��ʾ��������һ��
    int axleCount = 12;		///< ������������0 ��ʾ��������һ��
};

struct WayPoint {
    std::string position;      // ��������������
    int distance;       // ��㵽;�������
    // ;������·�ߵ����/�Ҳ�/·���ϣ�ȱʡֵΪ Sideness_unknown��
    // �ο�: https://jira.mapbar.com/browse/NAVICORE-4008
    Sideness sd;
};

struct NaviHead {
    // OnlineRouteErrorCode ������
    int code;
    // ��ʽ�淶�汾
    std::string ver;
    // TMC ����ʱ�� (format : "2012/12/04 05:26:18"; using UTC+8).
    std::string tmcTm;
    // �Ƿ�ʹ����Ԥ��·��;  if Request.PostData.routePlan.departInFuture.
    bool usePredictedTi;
    // ����ʱ���Ƿ�Ϊ�ڼ���ǰһ�졢�ڼ��ա��ڼ��պ��һ���Լ����� // if Request.PostData.routePlan.departInFuture
    bool departOnHolidays;
     
    int rruc;
};

struct Route {
    NaviHead naviHead;

    // ·�߳���; ��ӦjsonЭ��dis�ֶ�
    int dis;

    // ·����ʱ��; ��ӦjsonЭ��dur�ֶ�
    int dur;

    // ·�ߴ���
    int cost;

    // ;����
    std::vector<WayPoint> wp;

    // �յ���·�ߵ���ࡢ�Ҳ໹��·���ϣ�ȱʡֵΪ Sideness_unknown
    // �ο�: https://jira.mapbar.com/browse/NAVICORE-4008
    Sideness eSd;  
    
    // RouteTrait[] ·�߱��ö��ֵ�ı���ö���»��ߺ�����ݣ�.
    // ���ö����';'�ָ�
    std::string traits;
    
    // ·���ϵ�ȫ������������Ϣ��
    std::vector<VehicleRestriction> restrictions;

    // �滮��·���Ƿ������ĳ�����С�
    bool hasBrokenRestrictions;

    // ��������Ƿ�ɹ���ȱʡΪ�ɹ���
    bool areaAvoidanceSucceeded;

    // ·���Ƿ�����������������Ƶĵ�·��ȱʡΪ false��
    bool containsRegulationRestrictedRoad;
    
    // �� Base64 ���ܵĴ�ץ·�㿪ʼָ����������· ADAS
    // ���ݸ�ʽ��� Enroute Adas Data Format >> Output format >> AdasData
    AdasData adasData;   
    
    // ��ѡ�ķ��������Զ������ݣ����������� JSON ���ݡ�
    // �ͻ����� RouteBase::serverCustomData() ��ȡ��
    // �ο�: https://jira.mapbar.com/browse/NAVICORE-3973
    // google.protobuf.Any serverCustomData = 13;
    // void* serverCustomData = NULL;

    std::vector<Segment> segm;

    /**
    * ÿ��·�εĵ�ǰ·���ٶȡ�flag = ts���á�
    * x8 ��ʾ���� 8��60
    * ? ��ʾ�ٶ�δ֪
    * For example: "30;60x8;30;80;?x3";
    */
    std::string trafficSpeeds;

    // dv >= 2.1.7 ��ʼ
    std::vector<TrafficLightDetail> trafficLightDetails;

    // ��������Ϣ
    std::vector<Maneuver> mnv;

    // ������ʾ��Ϣ
    std::vector<Reminder> rmd;

    // ·������; flag=noDir1���Խ�����
    std::vector<RouteDirection> dir;

    // ·�߼�Ҫ����
    std::string desc;

    // ·����ϸ����; flag ���� 8 �Ż��·�
    std::vector<DetailDescription> rDD;

    // �Ƿ����շ�·��
    int toll;

    // �Ƿ����ֶ�
    int sr;

    // �շѽ���λ��Ԫ
    int fee;
    
    // ���ĵ�ͼ�շѽӿڷ��ص��շѽ��� tca=1 �ҷǲ�����·ʱ�·�����λ��Ԫ
    // -1 ��ʾ���ýӿڵ����ش��� -2 ��ʾ��·���������ô���
    int tcaFee;

    // if Request.tca == 1 and Route.tcaFee < 0.
    std::string tcaMsg;

    // �շ�վ��Ϣ
    std::vector<TollStation> ts;

    // Ƭ���ڴ�·���е� startIndex-endIndex-ETT; like "0-3-70;3-8-73;8-15-120";
    // ETT ��ʾԤ��ͨ����·�ε�ʱ�䣬������endIndex����·��
    std::string fragments;

    // if Request.flag contains "regulations";
    RegulationResult regulations;

    // Default as false. Ŀǰ���ֶ�ֻ���ô�����Ŀ�ĸ�����·ģʽ
    bool isObviouslyWorseThanCommonDays;

    // �Ƿ�֧����ʷ ETA ��ѯ��ȱʡΪ true����֧��
    bool supportPastEta;

    // ·��ĩ�˵Ĳ���·����Ŀ��ȱʡΪ 0
    int endPedestrianSegmentCount;

    // ·�� ID��2.4.57 �汾��ʼ֧�֣����ҽ��������� storeRoute ֵΪ 1 ��·�߱���ɹ�ʱ�·���
    std::string routeId;
    
    // ·��ͨ���Ӻ�(����0)����ǰ(С��0)�����ܿ����е�ʱ�䣬��λΪ�롣
    // ȱʡ��ʾ��·�߲������л����޷�ͨ���Ӻ����ǰ�ܿ�����
    int delayToAvoidRegulationRestriction;

    // ·�߶�Ӧ�� HAD ������Ϣ��2.4.58 �汾��ʼ֧�֣�ע�⣺����û�л��߽��в���·���ж�Ӧ��Ϣ��
    // ������·ʱ�������Ƿ�����·HAD�������󣬶������·���·HAD���ݡ�
    EnrouteHadData hadData; // if Request.needHadData == 1
};

}