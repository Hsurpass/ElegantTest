#pragma once

namespace ncStruct {

/**
* ������Ĵ�˳��
* ��ʱ���ܻ��������͡��ͻ�����Ҫ�ܺ���δʶ�������
*/
enum CameraType {
    CameraType_none = 0,
    /* ����ͷ�࿪ʼ */
    CameraType_cameraBegin = 1,
    /* ��������ͷ */
    CameraType_speed = 1,
    /* ���̵����� */
    CameraType_light = 2,
    /* ·���������ͷ(deprecate) */
    CameraType_roadCondition = 3,
    /* �״��������ͷ(deprecate) */
    CameraType_radar = 4,
    /* ����������ͷ */
    CameraType_onewayStreet = 5,
    /* �ǻ�����������ͷ */
    CameraType_bicycle = 6,
    /* ���������ͷ */
    CameraType_exitrance = 7,
    /* ������������ͷ */
    CameraType_bus = 8,
    /* ��ֹ����ת����ͷ */
    CameraType_turnForbidden = 9,
    /* �ƶ�ʽ��������ͷ(deprecate) */
    CameraType_mobile = 10,
    /* ���̵�����(deprecate) */
    CameraType_redLight = 11,
    /* ���Ӽ�� */
    CameraType_monitor = 12,
    /* ���������� */
    CameraType_areaSpeedingBegin = 13,
    /* ��������յ� */
    CameraType_areaSpeedingEnd = 14,
    /* Ӧ����������ͷ */
    CameraType_emergencyVehicle = 15,
    /* Υ��ͣ������ͷ */
    CameraType_illegalParking = 16,
    /* �����޺�����ͷ */
    CameraType_plateRestriction = 17,
    /* ��ͨ��������ͷ */
    CameraType_trafficMarking = 18,
    /* �ɱ����� */
    CameraType_variableSpeed = 19,
    /* ��ֹ���� */
    CameraType_tootingForbidden = 20,
    /* ����ͷ����� */
    CameraType_cameraEnd = 21,

    /** ������(deprecate) */
    CameraType_serviceAreaDeprecated = 51,
    /* �շ�վ(deprecate) */
    CameraType_tollDeprecated = 52,
    /* ����(deprecate) */
    CameraType_tunnelDeprecated = 53,

    /** ��ͨ��־�࿪ʼ */
    CameraType_signsBegin = 100,
    /* ��ͨ�źű�ʶ */
    CameraType_trafficSign = 100,
    /* ������· */
    CameraType_sharpLeftCurve = 101,
    /* ���Ҽ���· */
    CameraType_sharpRightCurve = 102,
    /* ������·(��) */
    CameraType_reverseCurve = 103,
    /* ������· */
    CameraType_windingRoad = 104,
    /* �϶��� */
    CameraType_steepAscent = 105,
    /* �¶��� */
    CameraType_steepDecent = 106,
    /* �����խ */
    CameraType_roadNarrowsFromBothSides = 107,
    /* �Ҳ��խ */
    CameraType_roadNarrowsFromTheRight = 108,
    /* ����խ */
    CameraType_roadNarrowsFromTheLeft = 109,
    /* խ�� */
    CameraType_narrowBridge = 110,
    /* ˫��ͨ */
    CameraType_twowayTraffic = 111,
    /* ע���ͯ */
    CameraType_childrenCrossing = 112,
    /* ע������ */
    CameraType_cattleCrossing = 113,
    /* ע������ʯ */
    CameraType_fallingRocksOnTheLeft = 114,
    /* ע������ʯ */
    CameraType_fallingRocksOnTheRight = 115,
    /* ע���� */
    CameraType_crosswinds = 116,
    /* �׻� */
    CameraType_slipperyRoad = 117,
    /* ����ɽ��· */
    CameraType_hillsOnTheLeft = 118,
    /* �Ҳ��ɽ��· */
    CameraType_hillsOnTheRight = 119,
    /* �Ҳ�̰�· */
    CameraType_embankmentOnTheRight = 120,
    /* ���̰�· */
    CameraType_embankmentOnTheLeft = 121,
    /* ��ׯ */
    CameraType_village = 122,
    /* �շ��� */
    CameraType_humpbackBridge = 123,
    /* ·�治ƽ */
    CameraType_unevenRoadSurface = 124,
    /* ��ˮ·�� */
    CameraType_roadFloods = 125,
    /* ���˿�����·���� */
    CameraType_guardedRailroadCrossing = 126,
    /* ���˿�����·���� */
    CameraType_unguardedRailroadCrossing = 127,
    /* �¹��׷�·�� */
    CameraType_highAccidentArea = 128,
    /* �������� */
    CameraType_passLeftOrRightOfObstacle = 129,
    /* ������� */
    CameraType_passLeftOfObstacle = 130,
    /* �Ҳ����� */
    CameraType_passRightOfObstacle = 131,
    /* ע��Σ�� */
    CameraType_dangerAhead = 132,
    /* ��ֹ���� */
    CameraType_noOvertaking = 133,
    /* �����ֹ���� */
    CameraType_overtakingAllowed = 134,
    /* ������ */
    CameraType_audibleWarning = 135,
    /* �������� */
    CameraType_continuousDecent = 136,
    /* �����Ծ�ʾ���� */
    CameraType_textWarning = 137,
    /* ע�������� */
    CameraType_confluenceFromLeft = 138,
    /* ע���Ҳ���� */
    CameraType_confluenceFromRight = 139,
    /* ͣ������ */
    CameraType_stopToGiveWay = 140,
    /* �ᳵ���� */
    CameraType_joinToGiveWay = 141,
    /* �������� */
    CameraType_decelerationToGiveWay = 142,
    /* �������� */
    CameraType_tunnelToLight = 143,
    /* ��ϫ���� */
    CameraType_tideRoad = 144,
    /* ·���͹ */
    CameraType_convexRoad = 145,
    /* ·����� */
    CameraType_hollowRoad = 146,
    /* ������·(��) */
    CameraType_reverseCurveRight = 147,
    /* ��ͨ����ڵ� */
    CameraType_accidentBlackSpot = 148,
    /* ��ͨ��־����� */
    CameraType_signsEnd = 149,
    CameraType_max = 149,
};

struct CameraData {
    // ��������������
    std::string pos;

    // �����۾���
    int dis;

    // ���������ͣ�ȱʡΪ CameraType_speed
    CameraType ty;

    // ����������ֵ��ȱʡΪ 0
    int sdLt;

    // ��������������ֵ��ȱʡΪ 0
    int vanSdLt;

    // �Ƿ�Υ�¸߷������ۣ�ȱʡΪ 0����ʾ��
    int isHighRisk;

    int groupId;

    uint64_t endLinkId;

    //���л���TimeSpan����; like "17509995355293462543-125239302-0;17509995355293462543-125239302-0"
    std::string timeSpans;
};

struct CameraList {
    // �ɹ�ʧ�ܱ�ʶ��100: �ɹ�
    int code;

    // ��ʽ���汾�����û������е� dv �ֶ�һ��
    // ��ʷ�ϵ�����汾���ȡ����ֶν��м����Լ��
    // ��Ȼ��ʵûʵ������
    // �����·�����ֶξ�����ͻ����ʧ��
    // ���Ա����·�
    std::string ver;

    // �����۶�����Ϣ
    std::vector<CameraData> cmrs;
};


}
