#pragma once

#include "basicTypes.h"
#include "laneModel.h"

namespace ncStruct {

struct LinkBusLane {
    int lc;
    unsigned int blb;
    std::string blc;
    std::string tsr;
    std::string ts;
};

/** @brief �ɰ��շ�վ�������쿨��ʽ��һ��ֻ�ܱ�ʾһ���쿨��ʽ */
enum TollLaneCardMode {
	TollLaneCardMode_none = 0,
	TollLaneCardMode_etc = 1,        ///< ETC
	TollLaneCardMode_manual = 2,     ///< �˹�
	TollLaneCardMode_selfService = 3, ///< ����
};

/** @brief �շ�վ������֧����ʽ */
enum TollLanePayMode {
    TollLanePayMode_none = 0,
	TollLanePayMode_etc = 1,          ///< ETC
	TollLanePayMode_cash = 2,         ///< �ֽ�
	TollLanePayMode_debitCard = 4,    ///< ���п�(��ǿ�)
	TollLanePayMode_creditCard = 8,   ///< ���ÿ�
	TollLanePayMode_icCard = 16,      ///< IC��
	TollLanePayMode_prepaidCard = 32, ///< Ԥ����(��Ʊ����Ʊ)

	// ����3��ȡֵҪ����ʹ�����ݵı������汾������ 0.8.88��@sa NAVICORE-4027
	TollLanePayMode_wechat = 64,      ///< ΢��
	TollLanePayMode_alipay = 128,     ///< ֧����
	TollLanePayMode_otherApp = 256,    ///< ���� APP
};

struct TollLane {
    TollLanePayMode payMode;    // ���ѷ�ʽ��Ϊ��ѡ���
    TollLaneCardMode cardMode;  // �쿨��ʽ
    bool isWeighingLane;        // �Ƿ��ǳ��س�����������Ĭ��Ϊ false
};

/** @brief �շ�վ���� */
enum TollStationType {
    TollStationType_none = 0,
	TollStationType_collectTicket = 1,                         ///< �쿨
	TollStationType_returnTicketAndPay = 2,                    ///< ��������
	TollStationType_payFixedFee = 3,                           ///< �̶��շ�(�η�)
	TollStationType_returnTicketPayAndCollectNewTicket = 4,    ///< �������Ѻ����쿨
	TollStationType_returnTicketPayWithAdditionalFixedFee = 5, ///< �������Ѳ����չ̶�����
	TollStationType_checkTicket = 6,                           ///< ��Ʊ
	TollStationType_collectTicketAndPayFixedFee = 7,           ///< �쿨�����չ̶�����
	TollStationType_markTicket = 8,                            ///< �ֿ����ʶ���շ�
	TollStationType_checkAndCollectTicket = 9,                 ///< ��Ʊ�쿨
	TollStationType_returnTicketWithoutPay = 10,                ///< �������շ�
};

struct Tollbooth {
    std::string name;    // �շ�վ����
    std::string pos;     // ��������
    uint64_t id;      // �շ�վ ID
    TollStationType type;
    std::vector<TollLane> lanes;
};

enum ExpandViewType {
    ExpandViewType_unknown = 0,
    ExpandViewType_signboard = 1,
    ExpandViewType_pattern = 2,
    ExpandViewType_normalRoadReal = 3,
    ExpandViewType_real = 4,
};

struct EvRecord {
    ExpandViewType type;        // Record���ͣ���Ӧ����� ExpandViewType
    std::string hintPos;        // SpatialDb ��ѯ�� hint position
    std::string bk;             // backgound image id, like "472377116882"
    std::string dir;            // arrow image id, like "864197937362"
};

enum ManeuverType {
    ManeuverType_none = 0,
    ManeuverType_turn = 1,
    ManeuverType_fork = 2,
    ManeuverType_enterMainRoad = 3,
    ManeuverType_exitMainRoad = 4,        // obsolete
    ManeuverType_enterSideRoad = 5,
    ManeuverType_enterRotary = 6,
    ManeuverType_exitRotary = 7,
    ManeuverType_enterTunnel = 8,
    ManeuverType_takeJunction = 9,
    ManeuverType_takeFerry = 10,
    ManeuverType_arriveDest = 11,
    ManeuverType_nameChange = 12,
    ManeuverType_enterRightTurnLane = 13,   ///< ahead-of-time enter right turn lane.
    ManeuverType_passLeftTurnLane = 14,     ///< ����ת����
    ManeuverType_passWaypointDeprecated = 15, ///< ����
    ManeuverType_acrossPark = 25,           ///< ������԰
    ManeuverType_acrossSquare = 26,         ///< ��Խ�㳡
    ManeuverType_crossWalk = 28,            ///< ���е�
    ManeuverType_underPass = 29,            ///< ����ͨ��
    ManeuverType_footbridge = 30,           ///< ��������
    ManeuverType_walkAlongRotary = 31,      ///< �ػ�����
    ManeuverType_bridge = 32,               ///< ����
    ManeuverType_crossStreet = 33,          ///< ����·�������е�
    ManeuverType_stair = 34,                ///< �߽���
    ManeuverType_enterMiniRotary = 35,      ///< ����С����
    ManeuverType_exitHighway = 36,          ///< guidanceVersion >= 3000
    ManeuverType_exitExpressway = 27,       ///< guidanceVersion >= 3000
    ManeuverType_enterHighway = 37,         ///< guidanceVersion >= 4000
    ManeuverType_passTollbooth = 38,        ///< guidanceVersion >= 5000
    ManeuverType_keepSideRoad = 39,         ///< guidanceVersion >= 6000
    ManeuverType_keepMainRoad = 40,         ///< guidanceVersion >= 7000  ������·��ʻ
    ManeuverType_enterInternalRoad = 41,    ///< guidanceVersion >= 8000  �����ڲ���·
    ManeuverType_turnOnRamp = 42,           ///< guidanceVersion >= 11000 ���ѵ���ת��
    ManeuverType_enterElevatedRoad = 43,    ///< guidanceVersion >= 11000 �ϸ߼�
    ManeuverType_exitElevatedRoad = 44,     ///< guidanceVersion >= 11000 �¸߼�
    ManeuverType_passWaypoint = 45,         ///< guidanceVersion >= 17000 ͨ��;����
    ManeuverType_enterLane = 46,            ///< guidanceVersion >= 18000 �������
};

struct Maneuver {
    // maneuver��ת��Ƕ�
    int turnAngle;

    // ������λ��
    std::string pos;

    // ����
    int dis = 3;                  

    //[default = turn];       // ���������ͣ�ע���� mnTy ��Ĭ��Ϊ ManeuverType_turn
    ManeuverType mnTy;

    // ת�����ͣ�ע���� tnTy ��Ĭ��Ϊ TurnType_straight
    TurnType tnTy;

    // �¶���ʾ��ע���� sH ��Ĭ��Ϊ SlopeHint_none
    SlopeHint sH;
    
    // ��ͨ����ע���� tD �� Ĭ��Ϊ TrafficDirection_rightHand
    TrafficDirection tD;

    // ��ʼ·���±�
    int sSI;

    // ��ֹ·���±�
    int eSI;

    // ����������� if mnTy == ManeuverType_enterRotary or mnTy == ManeuverType_exitRotary
    int ordInd;
    
    // �������� if mnTy == ManeuverType_enterRotary or mnTy == ManeuverType_exitRotary
    // dv >= 2.1.4
    int totalOrdinalCount;
    
    // ���ƣ��п�����·����DR��IC������Ҫ�� mnType ��֪����
    // ��roadName��signNameȡ�� (guidanceVersion <= 3000)
    std::string nm;     

    // ת���·�� (guidanceVersion >= 4000)
    std::string roadName;

    // ת��� DR/IC �� (guidanceVersion >= 4000)
    std::string signName;

    // ǰ��·��������toLinkΪ����ڻ����ѵ�ʱ����ȡǰ����·�� (guidanceVersion >= 4000)
    std::string roadNameAhead;

    // ���ڱ�� like "3A" (guidanceVersion >= 4000)
    std::string exitNumber;

    // ��ǰ150m�ڸ���·�ڵ���Ŀ
    int fcc;

    // ���150m�ڸ���·�ڵľ�������
    std::vector<int> bcd;

    // ��·�����Ƿ�ı�,ȡֵΪ 0 �� 1, Ĭ��Ϊ 0
    int nc;

    // �Ƿ�Ϊͬ·��ͷ,ȡֵΪ 0 �� 1, Ĭ��Ϊ 0
    int ut;

    // ·����Ϣ����(dv >= 2.1.4)
    SignInfoType signInfoType;

    // �Ƿ�λ�ڵ�·ĩ��(dv >= 2.1.4)��ȡֵΪ 0 �� 1, Ĭ��Ϊ 0
    int endOfRoad;

    // �Ŵ�ͼ��Ϣ
    EvRecord evRecord;

    // ��ͬguidance�汾ʱ��ʽ��ͬ, if dv >= 2.1.4
    LaneModel laneModel;

    // ����ת���
    std::string turnIconModel;

    // �շ�վ����, if mnTy == ManeuverType_passTollbooth
    Tollbooth tollbooth;

    // if not empty and if mnTy == ManeuverType_passTollbooth,  // �շ�վ����
    std::string tollboothName;

    // if mnTy == ManeuverType_passTollbooth, // �շ�վ�����/�����Ƿ�����·��,Ĭ��Ϊ false
    bool isMainLineTollbooth;

    // optional. �к��̵� guidanceVersion >= 10000. Ĭ��Ϊ false
    bool hasTrafficLight;

    // if Maneuver.type == ManeuverType_passWaypoint, // ��ʾ;�������Ҫ��0��ʾ��һ��;����
    // (guidanceVersion >= 17000)
    int waypointIndex; 

    // �Զ��岥������
    int decorations;

    // �Ƿ�׷�ӱ������(guidanceVersion >= 18000)
    bool shouldAddLaneHint;

    // ��ʾ���·��ǰ���������Ƶ���ת/��ת������ת��
    bool hasAmbiguousTurn;

    LinkBusLane linkBusLaneAfterTurn;

    // google.protobuf.Any exts = 50;      // ��չ���Բ�����Ԥ�������ƻ�����������������չ�����ã�������������� JSON ����
    // void* exts = NULL;      // ��չ���Բ�����Ԥ�������ƻ�����������������չ�����ã�������������� JSON ����

};

}