#pragma once

#include <stdint.h>
#include <string>
#include <vector>

namespace ncStruct
{
	struct HadGridInRoute {
		int32_t gridId;     // ��ƬID ��NdsGridId��
		int32_t distance;   // ��·���״���Ҫʹ�õ�����Ƭʱ��·�߾��룬��λ����
	};

	struct HadPoint3D
	{
		int64_t x;   // ���ȣ���λ��1e-8��
		int64_t y;   // γ�ȣ���λ��1e-8��
		int32_t z;   // �߶ȣ���λ��cm
	};

	struct HadLink
	{
		int64_t id;           // HadDirectedLink��ID
		int64_t originalId;   // HadDirectedLink��ԭʼID
		int32_t length;       // HadDirectedLink�ĳ��ȣ���λ��cm
	};

	struct AdTrip
	{
		int32_t location;     // ���������·���ϵ�λ�ã���λ����
		int32_t length;       // ���򳤶ȣ���λ����
	};

	struct HadTrip {
		int32_t startPosInRoute;      // hadTrip��Ӧ��ԭʼ·�ߵ���ʼλ�ã���λ����
		int32_t tripLength;           // hadTrip��Ӧ��ԭʼ·�ߵĳ��ȣ���λ����
		HadPoint3D startPos;          // hadTrip����ʼ����
		HadPoint3D endPos;            // hadTrip���յ�����
		int32_t startHeading;         // hadTrip���ķ��򣨺���ʻ����һ�£���λ��1e-4�ȣ�����Ϊ0����ʱ��Ϊ����
		int32_t endHeading;           // hadTrip�յ�ķ��򣨺���ʻ����һ�£���λ��1e-4�ȣ�����Ϊ0����ʱ��Ϊ����
		std::vector<HadLink> links;   // hadTrip������link����
		std::vector<AdTrip> adTrips;  // hadTrip�����Ŀ��Լ�������Ϣ
	};

	struct EnrouteHadData {
		// ʹ�õ���Ƭ���ݰ汾��ָncVersion
		std::string version;

		// ·�ߵ�����������Ҫ����Ƭ�����б�������ʻ˳������
		std::vector<HadGridInRoute> gridList;

		// ·��ƥ�䵽�� HadTrip��������ʻ˳������
		std::vector<HadTrip> trips;
	};
}
