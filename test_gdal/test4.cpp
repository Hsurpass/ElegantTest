// 在一根由多个utm坐标组成的线上进行按比例插值, c++代码实现

#include <iostream>
#include <vector>
#include <gdal/ogrsf_frmts.h>

void interpolatePoint(const std::vector<OGRPoint>& points, double t, OGRPoint& result) {
    if (points.empty()) {
        std::cerr << "No points in the LineString." << std::endl;
        return;
    }

    // Create a LineString from the given points
    OGRLineString line;
    for (const auto& point : points) {
        line.addPoint(&point);
    }

    // Compute the interpolated point at the given ratio t
    double distance = t * line.get_Length();
    line.Value(distance, &result);
}

int main() {
    // Initialize GDAL
    GDALAllRegister();

    // Define UTM coordinates (example coordinates in UTM Zone 54N)
    std::vector<OGRPoint> utmPoints = {
        OGRPoint(500000, 6200000),
        OGRPoint(500100, 6200100),
        OGRPoint(500200, 6200200)
    };

    // Perform interpolation at 0.2 and 0.8 positions
    OGRPoint interpolatedPoint1, interpolatedPoint2;
    interpolatePoint(utmPoints, 0.2, interpolatedPoint1);
    interpolatePoint(utmPoints, 0.8, interpolatedPoint2);

    // Output the results
    std::cout << "Interpolated Point at 0.2: (" << interpolatedPoint1.getX() << ", " << interpolatedPoint1.getY() << ")" << std::endl;
    std::cout << "Interpolated Point at 0.8: (" << interpolatedPoint2.getX() << ", " << interpolatedPoint2.getY() << ")" << std::endl;

    return 0;
}


WITH original_line AS (
    -- 创建一个LineString并设置SRID为4326
    SELECT ST_SetSRID(ST_GeomFromText('LINESTRING(-122.42 37.78, -122.45 37.91)'), 4326) AS line
),
interpolated_point_1 AS (
    -- 在0.2位置插值点
    SELECT ST_LineInterpolatePoint(line, 0.2) AS point
    FROM original_line
),
interpolated_point_2 AS (
    -- 在0.8位置插值点
    SELECT ST_LineInterpolatePoint(line, 0.8) AS point
    FROM original_line
),
substring_line AS (
    -- 获取两个插值点之间的子线段
    SELECT ST_LineSubstring(line, 0.2, 0.8) AS line
    FROM original_line
)
-- 选择插值点和子线段
SELECT 
    ST_AsText((SELECT point FROM interpolated_point_1)) AS point_1,
    ST_AsText((SELECT point FROM interpolated_point_2)) AS point_2,
    ST_AsText(line) AS substring_line
FROM substring_line;

