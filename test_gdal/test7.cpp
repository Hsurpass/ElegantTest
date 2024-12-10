使用gdal在多点组成的线上按比例计算插值后获取起点到插值点之间的点 ChatGPT
    要在一条由多个点组成的线上按比例计算插值后，获取起点到插值点之间的所有点，可以执行以下步骤：

        计算线段总长度：先计算整条线字符串的总长度。 确定插值点的位置：通过给定的比例计算插值点在总长度上的位置。
            遍历线段：从线字符串的起点开始遍历，累计每个线段的长度，直到找到插值点所在的线段。
                记录插值点之前的所有点：在遍历过程中，记录插值点之前的所有点。
                    插入插值点：在插值点所在的线段，根据比例计算插值点的位置并插入。 以下是使用 GDAL 和 C++ 的示例代码：

#include <iostream>
#include <vector>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_geometry.h>

    void
    interpolateAndCollectPoints(const OGRLineString* line,
                                double ratio,
                                OGRPoint* interpolatedPoint,
                                std::vector<OGRPoint>& points)
{
    if (ratio < 0.0 || ratio > 1.0) {
        std::cerr << "Ratio must be between 0.0 and 1.0" << std::endl;
        return;
    }

    double totalLength = line->get_Length();
    double targetLength = totalLength * ratio;
    double accumulatedLength = 0.0;

    for (int i = 1; i < line->getNumPoints(); ++i) {
        OGRPoint point1, point2;
        line->getPoint(i - 1, &point1);
        line->getPoint(i, &point2);
        points.push_back(point1);

        double segmentLength = point1.Distance(&point2);
        if (accumulatedLength + segmentLength >= targetLength) {
            double segmentRatio = (targetLength - accumulatedLength) / segmentLength;
            interpolatedPoint->setX(point1.getX() + segmentRatio * (point2.getX() - point1.getX()));
            interpolatedPoint->setY(point1.getY() + segmentRatio * (point2.getY() - point1.getY()));
            interpolatedPoint->setZ(point1.getZ() + segmentRatio * (point2.getZ() - point1.getZ()));
            points.push_back(*interpolatedPoint);
            return;
        }

        accumulatedLength += segmentLength;
    }

    // 如果未找到，则插值点在最后一个点上
    line->getPoint(line->getNumPoints() - 1, interpolatedPoint);
    points.push_back(*interpolatedPoint);
}

int main()
{
    GDALAllRegister();

    OGRLineString line;
    line.addPoint(114.0, 40.0);
    line.addPoint(114.1, 40.1);
    line.addPoint(114.2, 40.2);

    double ratio = 0.5;
    OGRPoint interpolatedPoint;
    std::vector<OGRPoint> points;

    interpolateAndCollectPoints(&line, ratio, &interpolatedPoint, points);

    std::cout << "Interpolated Point: (" << interpolatedPoint.getX() << ", " << interpolatedPoint.getY() << ")"
              << std::endl;
    std::cout << "Points from start to interpolated point:" << std::endl;
    for (const auto& point : points) {
        std::cout << "(" << point.getX() << ", " << point.getY() << ")" << std::endl;
    }

    return 0;
}

说明
interpolateAndCollectPoints
    函数：这个函数遍历线字符串的各个线段，累计每个线段的长度，直到找到插值点所在的线段。在找到插值点之前，所有的点都被添加到
        points 容器中。 插值点计算：当累计长度超过目标长度时，计算插值点的位置，并将其添加到 points 容器中。
            输出结果：程序最终输出插值点的坐标，以及从起点到插值点的所有点。 这样，你就可以获得插值点之前的所有点，包括插值点本身。这个方法在处理地理数据和需要精确定位的应用中非常有用。
