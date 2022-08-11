#pragma once

namespace ncStruct {

enum ServiceAreaGasBrand {
   ServiceAreaGasBrand_none = 0,
   ServiceAreaGasBrand_cnpc = 1,    ///< ��ʯ��
   ServiceAreaGasBrand_sinopec = 2, ///< ��ʯ��
   ServiceAreaGasBrand_shell = 4,   ///< ����
   ServiceAreaGasBrand_mobil = 8,   ///< ����
   ServiceAreaGasBrand_bp = 16,     ///< Ӣ��ʯ�͹�˾
   ServiceAreaGasBrand_other = 32,  ///< ����
};

enum ServiceAreaEstablishment {
    ServiceAreaEstablishment_none = 0,
    ServiceAreaEstablishment_restaurant = 1,       ///< �͹�
    ServiceAreaEstablishment_shop = 2,             ///< �̵�
    ServiceAreaEstablishment_hotel = 4,            ///< �ù�
    ServiceAreaEstablishment_publicToilet = 8,     ///< ����
    ServiceAreaEstablishment_gasStation = 16,      ///< ����վ
    ServiceAreaEstablishment_chargingStation = 32, ///< �綯�������վ
    ServiceAreaEstablishment_autoRepair = 64,      ///< ��������
    ServiceAreaEstablishment_atm = 128,            ///< ATM(�Զ�ȡ���)
};

enum RoadNumberType {
    RoadNumberType_none = 0,
    RoadNumberType_nationalHighway = 1,   ///< ���Ҽ����ٱ��
    RoadNumberType_provincialHighway = 2, ///< ʡ�����ٱ��
    RoadNumberType_nationalRoad = 3,      ///< �������
    RoadNumberType_provincialRoad = 4,    ///< ʡ�����
    RoadNumberType_countyRoad = 5,        ///< �ص����
    RoadNumberType_townRoad = 6,          ///< ������
    RoadNumberType_specialUseRoad = 7,    ///< ר�õ����
};

enum HighwayGuideType {
    HighwayGuideType_invalid = 0, ///< ��Ч����
    HighwayGuideType_IC = 1,      ///< ����
    HighwayGuideType_JC = 2,      ///< ����������
    HighwayGuideType_SA = 3,      ///< ������
    HighwayGuideType_PA = 4,      ///< ͣ����
    HighwayGuideType_TG = 5,      ///< �շ�վ
};

struct HighwayGuide {
    /** �����г�·�ƾ��� */
    int dis;

    /** �����г�·���ϵ����֣����������� ';' �ָ� */
    std::string nm;

    /** �����г�·�����ͣ�ע���� ty ��Ĭ��Ϊ IC */
    HighwayGuideType ty;
    
    /**
    * �����г�·�Ʊ��
    * ���� nm �е�˳�����α���ÿ�����ֶ�Ӧ��·�Ʊ��
    * Ϊ��ʡ������ֻ��¼�����һ��ֵ��Ϊ none ��Ԫ��
    * �������Ԫ�ص�ֵ��Ϊ none�����ֶβ��·�
    */
    std::vector<RoadNumberType> roadNumberTypes;

    /**
    * ��������ʩ��Ϣ
    * ͬʱ���������Ϣʱ���ɶ�Ӧ�ļ���ö��ֵ����λ������Ľ����ʾ
    * ���� ���� ty Ϊ SA �� PA ʱ������
    * ȱʡ��ʾû�з�������ʩ��Ϣ
    */
    ServiceAreaEstablishment serviceAreaEstablishment;

    /**
    * ����վƷ����Ϣ
    * ͬʱ���������Ϣʱ���ɶ�Ӧ�ļ���ö��ֵ����λ������Ľ����ʾ
    * ȱʡ��ʾû�м���վƷ����Ϣ
    */
    ServiceAreaGasBrand serviceAreaGasBrand;

    /** ���ٳ��ڱ�ţ�ȱʡֵΪ���ַ�������ʾ�����ڳ��ڱ�š� */
    std::string exitNumber;

    /** �����Ƿ���·���ϣ���0ֵ��ʾ�ǣ�0ֵ��ʾ��ȱʡֵΪ0�� */
    int onRoute;
};

struct HighwayGuideArray {
    // �ɹ�ʧ�ܱ�ʶ��100: �ɹ�
    int code;

    // Э��汾��
    std::string ver;

    // �����г����ݶ�����Ϣ
    std::vector<HighwayGuide> hgs;
};

}