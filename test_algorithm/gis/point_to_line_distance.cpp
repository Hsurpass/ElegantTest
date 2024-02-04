/*
要计算点(经纬度)到直线的距离，您可以使用以下方法：

首先，计算点 P1 到直线上的最近点 P 的坐标。
然后，计算点 P1 到点 P 的距离，这个距离就是点 P1 到直线的距离。
下面是一个简单的 C++ 实现，假设经度和纬度使用弧度表示，高度使用米作为单位：

在这个示例中，我们使用了 Haversine 公式来计算两点之间的距离，并使用向量的投影计算点到直线的最近点。这段代码假设经度和纬度使用弧度表示，高度使用米作为单位。您可以根据实际情况进行调整。
*/

#include <math.h>
#include <iostream>

// 计算两点之间的距离
double distance(double lat1, double lon1, double alt1, double lat2, double lon2, double alt2)
{
    double earthRadius = 6371000; // 地球半径，单位米
    double phi1 = lat1;
    double phi2 = lat2;
    double deltaPhi = lat2 - lat1;
    double deltaLambda = lon2 - lon1;

    double a =
        sin(deltaPhi / 2) * sin(deltaPhi / 2) + cos(phi1) * cos(phi2) * sin(deltaLambda / 2) * sin(deltaLambda / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    double distance = earthRadius * c;
    double height = alt1 - alt2;
    distance = sqrt(distance * distance + height * height);
    return distance;
}

// 计算点P1到直线上的最近点P的坐标
void closestPoint(double lat1,
                  double lon1,
                  double alt1,
                  double lat2,
                  double lon2,
                  double alt2,
                  double latP1,
                  double lonP1,
                  double altP1,
                  double& latP,
                  double& lonP,
                  double& altP)
{
    // 计算直线上的单位向量
    double dx = lon2 - lon1;
    double dy = lat2 - lat1;
    double dz = alt2 - alt1;
    double mag = sqrt(dx * dx + dy * dy + dz * dz);
    dx /= mag;
    dy /= mag;
    dz /= mag;

    // 计算P1到P2的向量
    double vx = lonP1 - lon1;
    double vy = latP1 - lat1;
    double vz = altP1 - alt1;

    // 计算P1到P点的投影长度
    double dotProduct = vx * dx + vy * dy + vz * dz;

    // 计算P点的坐标
    latP = lat1 + dotProduct * dx;
    lonP = lon1 + dotProduct * dy;
    altP = alt1 + dotProduct * dz;
}

int main()
{
    // 点的经度、纬度、高度
    double lat1 = 40.7128 * M_PI / 180; // 纬度转换为弧度
    double lon1 = -74.0060 * M_PI / 180; // 经度转换为弧度
    double alt1 = 0; // 高度，单位米

    double lat2 = 34.0522 * M_PI / 180;
    double lon2 = -118.2437 * M_PI / 180;
    double alt2 = 0;

    double latP1 = 41.8781 * M_PI / 180;
    double lonP1 = -87.6298 * M_PI / 180;
    double altP1 = 0;

    // 计算点P1到直线上的最近点P的坐标
    double latP, lonP, altP;
    closestPoint(lat1, lon1, alt1, lat2, lon2, alt2, latP1, lonP1, altP1, latP, lonP, altP);

    // 计算点P1到直线的距离
    double dist = distance(latP1, lonP1, altP1, latP, lonP, altP);
    std::cout << "点P1到直线的距离: " << dist << " 米" << std::endl;

    return 0;
}