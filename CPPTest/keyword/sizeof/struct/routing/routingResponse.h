#pragma once

#include "basicTypes.h"
#include "route.h"
#include "cameraList.h"
#include "highwayGuide.h"

namespace ncStruct {

struct RestrictionShape {
    // encoded points string with PolylineCodec::allocEncodedData()
    // һ�� RestrictionShape �����п��ܺ��ж��������״��(INT_MAX, INT_MAX)Ϊ�ָ�����
    std::string pts;     

    //shape type: polyline or polygon
    RestrictionShapeType shapeType;
};

struct RegulationGroupShape {
    // shape id of the regulation
    // int64 id = 1;
	int64_t id;
    // ����������״��
    std::vector<RestrictionShape> shapes;
};

enum RoutingRule {
    RoutingRule_recommended = 0,
    RoutingRule_shortest = 1,
    RoutingRule_preferHighway = 2,
    RoutingRule_economic = 3,
    RoutingRule_pedestrian = 4,
    RoutingRule_userDefined = 5,
    RoutingRule_max = 6,
};

struct RouteSortProfile {
    int eta;                  // unit: second
    int length;               // unit: meter
    int maneuverCount;
    int trafficLightCount;    // ·�ڣ�������Ҫ����ʱ��ĺ��̵�����
    int trafficLightWithoutDetailCount; // ����ʱ����ٵ����˺��̵�����

    int tollboothCount;
    int tollCharge;           // offline toll charge
    int tollSegmentLength;

    int searchCost;
    int roadChunkCount;

    int segmentCount;
    std::vector<unsigned int> segmentCountForPriority;
    int delayToAvoidRegulationRestriction;
};

struct RouteCollectionSortProfile {
    std::vector<RouteSortProfile> profiles;
    RoutingRule rule;
    bool avoidCongestion;

    // similarFactorMatrix is a square matrix,
    // whose dimension is equal to route count in result.
    // similarFactorMatrix[i][j] means the similar factor
    // of the jth route relative to the ith one.
    std::vector<std::vector<int> > similarFactorMatrix;
};

struct RouteTimeDistribution {
    int totalDuration;               // ���������յ���·�����·���·���֮��ĺ�ʱ
    int basicRoutingCalculation;     // ���������� RouteEngine �ӿڼ���·�߹��̵ĺ�ʱ
    int etaCalculation;
    int segmentPropertyExtraction;
    int maneuverCalculation; 
    int highwayGuideCalculation;  // ����汾�Ų�С�� 2.1.0
    int tollChargeCalculation;    // �����д� tca ���أ�
                                        //���� RoutePlan::transportationType() != TransportationType_walk
    int enrouteRestrictionCalculation;    // ���� flag �д� regulations, ���� RoutePlan �п����������кͷ�ʱ����
    int removePoorRouteCalculation;       // �޳���·��ʱ
    int sortProfileCalculation;          // RoutePlan::resultReorderEnabled() ���ú�·�߾��������ʱ
    int routeStoring;                    //����·�����ú�ʱ
    int hadMapMatching; // if Request.needHadData == 1 // ���� HAD map-matching �ĺ�ʱ
};

struct TcaDebug {
    std::string url;     // ������շѽӿڷ�������� url��
    std::string data;    // �� Base64 ���ܵĸ����շѽӿڽ��ܵ� post data��
};

struct RouteResult {
    Route route;
    CameraList camera;
    HighwayGuideArray hg;
};

struct RoutingResponse{
    std::vector<RouteResult> result;

    // The original data version. // NavInfo Ҳ����д�� NaviInfo
    std::string dataVersion;
    
    // ������Ϣ�е����������Ϣ�����õĵ�Э��汾��
    int cameraVersion;
    
    // ������Ϣ�����������Ϣ�����õ�Э��汾��
    int guidanceVersion;
    
    // The guid of routing file. like "097b1b1b559db449b227bcea36c3bdd3"
    std::string guid;
    
    // debug info of highway toll interface. if Request.tca == 1 and Request.tcaDebug == 1
    TcaDebug tcaDebug;
    
    // If the image id of junction views are stable.
    // If true, offline images should be queried first to save network bandwidth.
    // If false, must use online images only.
    bool jvImageIdStable;

    // ������·������, if errorCode != RouteError_none
    int errorCode;
    
    // ������·���������,if errorCode != RouteError_none;
    std::string errorMessage;
    
    // ������·ץ·ʧ��ʱ�����ص�ǰλ�õĿհ����뾶 (���Χ�뾶1000)����λ����
    // if errorCode == RouteErrorCode_offCourseGrabFailed
    int blankZoneRadius;
    
    // ���� ty=explore ʱ���ڡ�
    // ��¼�ִ�·������Ҫ���Ƴ���·�ߵ��±�
    // ������� 0�����ʾ��ǰ·����Ҫ�滻Ϊ result �еĵ�һ��·�ߡ�
    // result �б��������Ҫ���ӵ���·��
    std::vector<int> existingRoutesToRemove;
    
    // һ����·�����У������ֵĺ�ʱͳ��
	RouteTimeDistribution timeDistribution;
    
    // ·�ߵ�·�����������ƶ���Ϣ
    RouteCollectionSortProfile sortProfile;
    
    // ����·�ߵ�����������״���ϣ�ÿ������ͨ��shapeId�ҵ���Ӧ����״
    std::vector<RegulationGroupShape> regulationGroupShape;

    // ��ǰ·���Ƿ�֧��ָ������ʱ����·
    bool supportRouteForecast;

    // ���niid��64λ�ķ��ظ��ֶΣ�����û�и��ֶ�
	std::string niidtype;
};

}