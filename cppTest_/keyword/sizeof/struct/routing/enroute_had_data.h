#pragma once

#include <stdint.h>
#include <string>
#include <vector>

namespace ncStruct
{
	struct HadGridInRoute {
		int32_t gridId;     // 瓦片ID （NdsGridId）
		int32_t distance;   // 沿路线首次需要使用到该瓦片时的路线距离，单位：米
	};

	struct HadPoint3D
	{
		int64_t x;   // 经度，单位：1e-8度
		int64_t y;   // 纬度，单位：1e-8度
		int32_t z;   // 高度，单位：cm
	};

	struct HadLink
	{
		int64_t id;           // HadDirectedLink的ID
		int64_t originalId;   // HadDirectedLink的原始ID
		int32_t length;       // HadDirectedLink的长度，单位：cm
	};

	struct AdTrip
	{
		int32_t location;     // 区域起点在路线上的位置，单位：米
		int32_t length;       // 区域长度，单位：米
	};

	struct HadTrip {
		int32_t startPosInRoute;      // hadTrip对应的原始路线的起始位置，单位：米
		int32_t tripLength;           // hadTrip对应的原始路线的长度，单位：米
		HadPoint3D startPos;          // hadTrip的起始坐标
		HadPoint3D endPos;            // hadTrip的终点坐标
		int32_t startHeading;         // hadTrip起点的方向（和行驶方向一致，单位：1e-4度，正东为0，逆时针为正）
		int32_t endHeading;           // hadTrip终点的方向（和行驶方向一致，单位：1e-4度，正东为0，逆时针为正）
		std::vector<HadLink> links;   // hadTrip包含的link序列
		std::vector<AdTrip> adTrips;  // hadTrip包含的可自驾区域信息
	};

	struct EnrouteHadData {
		// 使用的瓦片数据版本，指ncVersion
		std::string version;

		// 路线导航过程中需要的瓦片数据列表，按照行驶顺序排列
		std::vector<HadGridInRoute> gridList;

		// 路线匹配到的 HadTrip，按照行驶顺序排列
		std::vector<HadTrip> trips;
	};
}
