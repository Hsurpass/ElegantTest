#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

struct Point
{
    double x;
    double y;
};

// 计算一条线段与正北方向（Y轴正方向）之间的夹角，并且角度范围是 0～360 度 (顺时针方向为正)
double cal_angel_north(double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;

    if (dx == 0 && dy == 0) {
        return 0; // 两点重合，返回 0 度
    }

    // atan2(y, x) 给出与 X 轴正方向夹角，范围 (-π, π]
    // 注意参数顺序是 dx, dy，确保是与 Y轴的夹角
    double angle_rad = atan2(dx, dy); // atan2 返回的是弧度
    double angle_deg = angle_rad * 180 / M_PI; // 转换为度

    if (angle_deg < 0) {
        angle_deg += 360; // 确保角度在 0 到 360 度之间
    }
    return angle_deg;
}

double cal_angel_north(const Point& p1, const Point& p2)
{
    return cal_angel_north(p1.x, p1.y, p2.x, p2.y);
}

/*
为什么是 atan2(dx, dy) 而不是 atan2(dy, dx)？
因为我们要计算与北（Y轴正方向）的夹角，而 atan2(y, x) 默认是与 X 轴正方向的夹角。

我们想得到 “顺时针角度从正北方向开始”，所以要把 dx 放前面，dy 放后面，这样就是：

与 Y轴正方向的夹角，顺时针方向为正。
*/

void test_cal_angel_north()
{
    cout << cal_angel_north(Point{0, 0}, Point{1, 1}) << endl; // 45
    cout << cal_angel_north(Point{0, 0}, Point{1, 0}) << endl; // 90

    cout << atan2(0, 1) * 180 / M_PI << endl; // 0 (x: 1, y: 0)
    cout << atan2(1, 0) * 180 / M_PI << endl; // 90 (x: 0, y: 1)
    cout << atan2(0, -1) * 180 / M_PI << endl; // 180
    cout << atan2(0, -1) << endl; // +PI

    cout << atan2(-1, 0) * 180 / M_PI << endl; // -90
    cout << atan2(-0.0, -1) * 180 / M_PI << endl; // -180
    cout << atan2(-0.0, -1) << endl; //-PI
}

// 选准一条任意方向的基准线，计算一条线与这条线的夹角，以这条基准线的正方向/负方向为0度，逆时针为基准（默认）要求计算角度范围为0～360。
double angleFromBaseLine(const Point& p1,
                         const Point& p2,
                         const Point& p3,
                         const Point& p4,
                         bool use_base_line_positive = true,
                         bool use_base_anticlockwise = true)
{
    double base_angle_rad_positive = atan2(p2.y - p1.y, p2.x - p1.x); // 基准线的角度
    cout << "base_angle_deg_positive: " << base_angle_rad_positive << ", " << base_angle_rad_positive * 180 / M_PI
         << endl;
    double base_angle_rad_negative = base_angle_rad_positive + M_PI; // 基准线的角度
    cout << "base_angle_deg_negative: " << base_angle_rad_negative << ", " << base_angle_rad_negative * 180 / M_PI
         << endl;
    double line2_angle_rad_to_line1 = atan2(p4.y - p3.y, p4.x - p3.x);
    cout << "line2_angle_rad_to_line1: " << line2_angle_rad_to_line1 << ", " << line2_angle_rad_to_line1 * 180 / M_PI
         << endl;
    double delta_rad = 0;
    if (use_base_line_positive) {
        delta_rad = line2_angle_rad_to_line1 - base_angle_rad_positive;
    }
    else {
        delta_rad = line2_angle_rad_to_line1 - base_angle_rad_negative;
    }

    cout << "delta_rad: " << delta_rad << endl;

    delta_rad = std::fmod(delta_rad, 2 * M_PI); // 确保 delta_rad 在 0 到 2π 之间

    if (!use_base_anticlockwise) {
        delta_rad = -delta_rad; // 如果是顺时针方向为正，则取反
    }

    cout << "delta_rad: " << delta_rad << endl;
    double delta_deg = delta_rad * 180 / M_PI; // 转换为度
    cout << "delta_deg: " << delta_deg << endl;
    if (delta_deg < 0) {
        delta_deg += 360; // 确保角度在 0 到 360 度之间
    }

    return delta_deg;
}

void test_angleFromBaseLine()
{
    Point p1{0, 0};
    Point p2{1, 1};
    Point p3{1, 0}; // 1 - 0, 0 - 1
    Point p4{0, 1};

    cout << angleFromBaseLine(p1, p2, p3, p4) << endl; // 基准线为p1p2，p3p4与基准线的夹角 90
    cout << angleFromBaseLine(p1, p2, p3, p4, false) << endl; // 基准线为p1p2，p3p4与基准线的夹角，基准线反向 270

    cout << "-----positive anticlockwise: " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{1, 0}, Point{0, 0}, Point{0, 1}) << endl; // 90
    cout << "-----positive clockwise: " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{1, 0}, Point{0, 0}, Point{0, 1}, true, false) << endl; // 270

    cout << "-----negative anticlockwise: " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{1, 0}, Point{0, 0}, Point{0, 1}, false) << endl; // 270
    cout << "-----negative clockwise: " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{1, 0}, Point{0, 0}, Point{0, 1}, false, false) << endl; // 90

    cout << "-----positive anticlockwise (0,0) (0,-1): " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{1, 0}, Point{0, 0}, Point{0, -1}) << endl; // 270
    cout << "-----positive clockwise (0,0) (0,-1): " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{1, 0}, Point{0, 0}, Point{0, -1}, true, false) << endl; // 90

    cout << "-----negative anticlockwise (0,0) (0,-1): " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{1, 0}, Point{0, 0}, Point{0, -1}, false) << endl; // 90
    cout << "-----negative clockwise (0,0) (0,-1): " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{1, 0}, Point{0, 0}, Point{0, -1}, false, false) << endl; // 270

    cout << "-----positive anticlockwise (-1,0) (-100,-400): " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{1, 0}, Point{-1, 0}, Point{-100, -400}) << endl; // 256.099
    cout << "-----positive clockwise (-1,0) (-100,-400): " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{1, 0}, Point{-1, 0}, Point{-100, -400}, true, false)
         << endl; // 103.901

    cout << "-----negative anticlockwise (-1,0) (-100,-400): " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{1, 0}, Point{-1, 0}, Point{-100, -400}, false) << endl; // 76.0986
    cout << "-----negative clockwise (-1,0) (-100,-400): " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{1, 0}, Point{-1, 0}, Point{-100, -400}, false, false)
         << endl; // 283.901

    cout << "-----positive anticlockwise (0,0) (-1,-1): " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{-1, 0}, Point{0, 0}, Point{-1, -1}, true, true) << endl; // 45
    cout << "-----positive clockwise (0,0) (-1,-1): " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{-1, 0}, Point{0, 0}, Point{-1, -1}, true, false) << endl; // 315

    cout << "-----negative anticlockwise (0,0) (-1,-1): " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{-1, 0}, Point{0, 0}, Point{-1, -1}, false, true) << endl; // 225
    cout << "-----negative clockwise (0,0) (-1,-1): " << endl;
    cout << angleFromBaseLine(Point{0, 0}, Point{-1, 0}, Point{0, 0}, Point{-1, -1}, false, false) << endl; // 135
}

void test_atan_atan2()
{
    cout << atan(0) << endl;
    cout << atan2(0, 0) << endl;
}

int main()
{
    // test_cal_angel_north();
    test_angleFromBaseLine();
    // test_atan_atan2();

    return 0;
}