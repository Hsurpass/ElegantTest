// 在一根由多个84坐标组成的线上进行按比例插值, c++代码实现

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

    // 定义WGS84坐标（示例坐标）
    std::vector<OGRPoint> wgs84Points = {
        OGRPoint(-122.42, 37.78),
        OGRPoint(-122.45, 37.91),
        OGRPoint(-122.48, 38.01)
    };

    // 设置EPSG:4326的空间参考
    OGRSpatialReference spatialRef;
    spatialRef.importFromEPSG(4326);

    // 将空间参考分配给每个点
    for (auto& point : wgs84Points) {
        point.assignSpatialReference(&spatialRef);
    }

    // 计算插值点
    OGRPoint interpolatedPoint1, interpolatedPoint2;
    interpolatePoint(wgs84Points, 0.2, interpolatedPoint1);
    interpolatePoint(wgs84Points, 0.8, interpolatedPoint2);

    // 输出结果
    std::cout << "Interpolated Point at 0.2: (" 
              << interpolatedPoint1.getX() << ", " 
              << interpolatedPoint1.getY() << ")" << std::endl;
    std::cout << "Interpolated Point at 0.8: (" 
              << interpolatedPoint2.getX() << ", " 
              << interpolatedPoint2.getY() << ")" << std::endl;

    return 0;
}
