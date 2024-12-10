// 用gdal计算两个84坐标之间的距离

#include <iostream>
#include <cmath>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_geometry.h>
#include <gdal/ogr_spatialref.h>

// 初始化GDAL
void InitializeGDAL() {
    GDALAllRegister();
    OGRRegisterAll();
}

// 计算两个WGS84坐标点之间的测地线距离
double CalculateGeodesicDistance(double lon1, double lat1, double lon2, double lat2) {
    OGRSpatialReference sourceSRS, targetSRS;
    sourceSRS.SetWellKnownGeogCS("WGS84");
    targetSRS.SetWellKnownGeogCS("WGS84");

    OGRCoordinateTransformation* transform = OGRCreateCoordinateTransformation(&sourceSRS, &targetSRS);
    if (!transform) {
        std::cerr << "Failed to create coordinate transformation." << std::endl;
        return -1;
    }

    OGRPoint point1(lon1, lat1);
    OGRPoint point2(lon2, lat2);

    // 投影到同一坐标系
    point1.assignSpatialReference(&sourceSRS);
    point2.assignSpatialReference(&sourceSRS);

    // 使用测地线计算距离
    double distance = point1.Distance(&point2);

    // 清理
    OCTDestroyCoordinateTransformation(transform);

    return distance;
}

int main() {
    // 初始化GDAL
    InitializeGDAL();

    // 定义两个WGS84坐标点
    double lon1 = -122.42, lat1 = 37.78;
    double lon2 = -122.45, lat2 = 37.91;

    // 计算距离
    double distance = CalculateGeodesicDistance(lon1, lat1, lon2, lat2);

    if (distance >= 0) {
        std::cout << "Geodesic Distance: " << distance << " meters" << std::endl;
    } else {
        std::cerr << "Failed to calculate distance." << std::endl;
    }

    return 0;
}



///////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cmath>
#include <gdal/ogr_geometry.h>
#include <gdal/ogr_spatialref.h>

// 计算Haversine公式的弧长
double haversineDistance(double lon1, double lat1, double lon2, double lat2) {
    const double R = 6371.0; // 地球半径（单位：千米）
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double a = pow(sin(dLat / 2), 2) + cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) * pow(sin(dLon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c * 1000; // 返回距离，单位：米
}

// 将WGS84坐标转换为UTM坐标
void convertToUTM(double lon, double lat, double& utmX, double& utmY, int& zone) {
    OGRSpatialReference wgs84;
    wgs84.SetWellKnownGeogCS("WGS84");

    OGRSpatialReference utm;
    zone = static_cast<int>((lon + 180) / 6) + 1;
    bool isNorthernHemisphere = (lat >= 0);
    utm.SetUTM(zone, isNorthernHemisphere);

    OGRCoordinateTransformation* transform = OGRCreateCoordinateTransformation(&wgs84, &utm);

    if (transform != nullptr) {
        transform->Transform(1, &lon, &lat);
        utmX = lon;
        utmY = lat;
        OGRCoordinateTransformation::DestroyCT(transform);
    } else {
        std::cerr << "Failed to create coordinate transformation." << std::endl;
    }
}

// 计算欧式距离
double euclideanDistance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main() {
    double lon1 = -122.42, lat1 = 37.78;
    double lon2 = -122.45, lat2 = 37.91;

    // 计算弧长
    double arcLength = haversineDistance(lon1, lat1, lon2, lat2);
    std::cout << "Great Circle Distance: " << arcLength << " meters" << std::endl;

    // 将WGS84坐标转换为UTM坐标
    double utmX1, utmY1, utmX2, utmY2;
    int zone1, zone2;
    convertToUTM(lon1, lat1, utmX1, utmY1, zone1);
    convertToUTM(lon2, lat2, utmX2, utmY2, zone2);

    if (zone1 != zone2) {
        std::cerr << "Points are in different UTM zones." << std::endl;
        return 1;
    }

    // 计算欧式距离
    double euclideanDist = euclideanDistance(utmX1, utmY1, utmX2, utmY2);
    std::cout << "Euclidean Distance in UTM: " << euclideanDist << " meters" << std::endl;

    return 0;
}

