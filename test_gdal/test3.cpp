// 在代码中怎么根据UTM Zone 找到对应的ESPG CODE

#include <iostream>
#include <vector>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_spatialref.h>

// 函数：根据UTM Zone和北/南半球找到EPSG Code
int findUTMZoneEPSGCode(int utmZone, bool isNorthernHemisphere) {
    if (isNorthernHemisphere) {
        return 32600 + utmZone;  // EPSG:32600 series for northern hemisphere
    } else {
        return 32700 + utmZone;  // EPSG:32700 series for southern hemisphere
    }
}

// 函数：插值计算
void interpolatePoint(const std::vector<OGRPoint>& points, double t, OGRPoint& result) {
    if (points.empty()) {
        std::cerr << "No points in the LineString." << std::endl;
        return;
    }

    // 创建一个LineString
    OGRLineString line;
    for (const auto& point : points) {
        line.addPoint(&point);
    }

    // 计算给定比例t的插值点
    double distance = t * line.get_Length();
    line.Value(distance, &result);
}

int main() {
    // 初始化GDAL
    GDALAllRegister();

    // 定义UTM Zone和北/南半球
    int utmZone = 54;
    bool isNorthernHemisphere = true;

    // 根据UTM Zone和北/南半球找到对应的EPSG Code
    int epsgCode = findUTMZoneEPSGCode(utmZone, isNorthernHemisphere);

    // 设置EPSG的空间参考
    OGRSpatialReference spatialRef;
    spatialRef.importFromEPSG(epsgCode);

    // 定义UTM坐标（示例坐标在UTM Zone 54N）
    std::vector<OGRPoint> utmPoints = {
        OGRPoint(500000, 6200000),
        OGRPoint(500100, 6200100),
        OGRPoint(500200, 6200200)
    };

    // 将空间参考分配给每个点
    for (auto& point : utmPoints) {
        point.assignSpatialReference(&spatialRef);
    }

    // 计算插值点
    OGRPoint interpolatedPoint1, interpolatedPoint2;
    interpolatePoint(utmPoints, 0.2, interpolatedPoint1);
    interpolatePoint(utmPoints, 0.8, interpolatedPoint2);

    // 输出结果
    std::cout << "Interpolated Point at 0.2: (" 
              << interpolatedPoint1.getX() << ", " 
              << interpolatedPoint1.getY() << ")" << std::endl;
    std::cout << "Interpolated Point at 0.8: (" 
              << interpolatedPoint2.getX() << ", " 
              << interpolatedPoint2.getY() << ")" << std::endl;

    return 0;
}


// gdal计算插值是不用设置EPSG code 吗/

#include <iostream>
#include <vector>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_spatialref.h>

// 函数：插值计算
void interpolatePoint(const std::vector<OGRPoint>& points, double t, OGRPoint& result) {
    if (points.empty()) {
        std::cerr << "No points in the LineString." << std::endl;
        return;
    }

    // 创建一个LineString
    OGRLineString line;
    for (const auto& point : points) {
        line.addPoint(&point);
    }

    // 计算给定比例t的插值点
    double distance = t * line.get_Length();
    line.Value(distance, &result);
}

int main() {
    // 初始化GDAL
    GDALAllRegister();

    // 定义UTM坐标（示例坐标在UTM Zone 54N）
    std::vector<OGRPoint> utmPoints = {
        OGRPoint(500000, 6200000),
        OGRPoint(500100, 6200100),
        OGRPoint(500200, 6200200)
    };

    // 设置EPSG:32654（UTM Zone 54N）的空间参考
    OGRSpatialReference spatialRef;
    spatialRef.importFromEPSG(32654);

    // 将空间参考分配给每个点
    for (auto& point : utmPoints) {
        point.assignSpatialReference(&spatialRef);
    }

    // 计算插值点
    OGRPoint interpolatedPoint1, interpolatedPoint2;
    interpolatePoint(utmPoints, 0.2, interpolatedPoint1);
    interpolatePoint(utmPoints, 0.8, interpolatedPoint2);

    // 输出结果
    std::cout << "Interpolated Point at 0.2: (" 
              << interpolatedPoint1.getX() << ", " 
              << interpolatedPoint1.getY() << ")" << std::endl;
    std::cout << "Interpolated Point at 0.8: (" 
              << interpolatedPoint2.getX() << ", " 
              << interpolatedPoint2.getY() << ")" << std::endl;

    return 0;
}

