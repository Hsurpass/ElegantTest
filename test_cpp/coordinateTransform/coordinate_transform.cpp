#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

// https://github.com/proj4js/proj4js.git
// https://blog.csdn.net/Aries1Chan/article/details/118492601

#define INT_MAX 2147483647    /* maximum (signed) int value */

typedef struct Point
{
    int x, y;
#ifdef __cplusplus
    Point& set(int x_, int y_)
    {
        this->x = x_, this->y = y_;
        return *this;
    }
    void invalidate()
    {
        this->x = INT_MAX, this->y = INT_MAX;
    }
    bool isValid()
    {
        return this->x != INT_MAX || this->y != INT_MAX;
    }
    void setZero()
    {
        this->x = this->y = 0;
    }
    bool isZero()
    {
        return this->x == 0 && this->y == 0;
    }
    void offset(int x_, int y_)
    {
        this->x += x_;
        this->y += y_;
    }
    void offset(Point offset)
    {
        this->x += offset.x;
        this->y += offset.y;
    }
#endif
} Point;

/** @brief 以度为单位的经纬度坐标, x 是经度, y 是纬度。 */
typedef struct PointD
{
    double x, y;
} PointD;

static PointD PointD_make(double x, double y)
{
    PointD o;
    o.x = x;
    o.y = y;
    return o;
}

//////////////////////////////////////////////////////////////////////////
// Start of 84 -> 02

static const double pi = 3.14159265358979324;

//
// Krasovsky 1940
//
// a = 6378245.0, 1/f = 298.3
// b = a * (1 - f)
// ee = (a^2 - b^2) / a^2;
static const double a = 6378245.0;
static const double ee = 0.00669342162296594323;

static bool outOfChina(double lat, double lon)
{
    if (lon < 72.004 || lon > 137.8347)
        return true;
    if (lat < 0.8293 || lat > 55.8271)
        return true;
    return false;
}

static double transformLat(double x, double y)
{
    double ret = -100.0 + 2.0 * x + 3.0 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * sqrt(fabsf(x));
    ret += (20.0 * sin(6.0 * x * pi) + 20.0 * sin(2.0 * x * pi)) * 2.0 / 3.0;
    ret += (20.0 * sin(y * pi) + 40.0 * sin(y / 3.0 * pi)) * 2.0 / 3.0;
    ret += (160.0 * sin(y / 12.0 * pi) + 320 * sin(y * pi / 30.0)) * 2.0 / 3.0;
    return ret;
}

static double transformLon(double x, double y)
{
    double ret = 300.0 + x + 2.0 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * sqrt(fabsf(x));
    ret += (20.0 * sin(6.0 * x * pi) + 20.0 * sin(2.0 * x * pi)) * 2.0 / 3.0;
    ret += (20.0 * sin(x * pi) + 40.0 * sin(x / 3.0 * pi)) * 2.0 / 3.0;
    ret += (150.0 * sin(x / 12.0 * pi) + 300.0 * sin(x / 30.0 * pi)) * 2.0 / 3.0;
    return ret;
}

//
// World Geodetic System ==> Mars Geodetic System
PointD Math_wgsToMarsD(PointD wgsCoordinate)
{
    double dLat;
    double dLon;
    double radLat;
    double magic;
    double sqrtMagic;

    double wgLat = wgsCoordinate.y;
    double wgLon = wgsCoordinate.x;

    if (outOfChina(wgLat, wgLon)) {
        return wgsCoordinate;
    }

    dLat = transformLat(wgLon - 105.0, wgLat - 35.0);
    dLon = transformLon(wgLon - 105.0, wgLat - 35.0);
    radLat = wgLat / 180.0 * pi;
    magic = sin(radLat);
    magic = 1 - ee * magic * magic;
    sqrtMagic = sqrt(magic);
    dLat = (dLat * 180.0) / ((a * (1 - ee)) / (magic * sqrtMagic) * pi);
    dLon = (dLon * 180.0) / (a / sqrtMagic * cos(radLat) * pi);

    wgsCoordinate.x = wgLon + dLon;
    wgsCoordinate.y = wgLat + dLat;

    return wgsCoordinate;
}

PointD Math_marsToWgsD(PointD marsCoordinate)
{
    PointD p1, p2;
    p1 = marsCoordinate;
    p2 = Math_wgsToMarsD(p1);
    p1.x = marsCoordinate.x - p2.x + p1.x;
    p1.y = marsCoordinate.y - p2.y + p1.y;
    p2 = Math_wgsToMarsD(p1);
    p1.x = marsCoordinate.x - p2.x + p1.x;
    p1.y = marsCoordinate.y - p2.y + p1.y;
    p2 = Math_wgsToMarsD(p1);
    p1.x = marsCoordinate.x - p2.x + p1.x;
    p1.y = marsCoordinate.y - p2.y + p1.y;
    return p1;
}

void Math_wgsToMars(const Point* wgsCoordinate, Point* marsCoordinate)
{
    PointD input = PointD_make(wgsCoordinate->x / 100000.0, wgsCoordinate->y / 100000.0);
    PointD output = Math_wgsToMarsD(input);
    marsCoordinate->x = (int)(output.x * 100000.0 + 0.5);
    marsCoordinate->y = (int)(output.y * 100000.0 + 0.5);
}

void Math_marsToWgs(const Point* marsCoordinate, Point* wgsCoordinate)
{
    PointD input = PointD_make(marsCoordinate->x / 100000.0, marsCoordinate->y / 100000.0);
    PointD output = Math_marsToWgsD(input);
    wgsCoordinate->x = (int)(output.x * 100000.0 + 0.5);
    wgsCoordinate->y = (int)(output.y * 100000.0 + 0.5);
}

// END of 84 -> 02
//////////////////////////////////////////////////////////////////////////

void convert02PointsTo84Points()
{
    std::fstream inFile("02points1.txt", std::fstream::in);
    if (!inFile)
        std::cout << "open file failed!!" << std::endl;

    std::fstream outFile("84points1.txt", std::fstream::out | std::fstream::trunc);
    if (!outFile)
        std::cout << "open file failed!!" << std::endl;

    std::string str;
    while (std::getline(inFile, str)) {
        const char* tmp = str.c_str();
        char line[64] = {0};
        strcpy(line, tmp);

        Point point02;
        int count = 0;
        char* p = NULL;
        p = strtok(line, ",");
        while (p != NULL) {
            switch (count) {
            case 0:
                point02.x = atoi(p);
                break;
            case 1:
                point02.y = atoi(p);
            default:
                break;
            }
            ++count;
            p = strtok(NULL, ", ");
        }
        Point point84;
        Math_marsToWgs(&point02, &point84);
        std::string str84 = std::to_string(point84.x);
        str84 += ",";
        str84 += std::to_string(point84.y);
        outFile << str84;
        outFile << "\n";
    }

    inFile.close();
    outFile.close();
}

void convert02LogTo84Log()
{
    std::fstream inFile("simulate02.info", std::fstream::in);
    if (!inFile)
        std::cout << "open file failed!!" << std::endl;

    std::fstream outFile("simulate84.info", std::fstream::out | std::fstream::trunc);
    if (!outFile)
        std::cout << "open file failed!!" << std::endl;

    std::string str;
    std::getline(inFile, str);
    outFile << str;
    while (std::getline(inFile, str)) {
        const char* tmp = str.c_str();
        char line[1024] = {0};
        strcpy(line, tmp);

        Point point02;
        int count = 0;
        char* p = NULL;
        p = strtok(line, ",");
        while (p != NULL) {
            switch (count) {
            case 0: // valid
                break;
            case 1: // dateTime
                break;
            case 2: // pos.x
                point02.x = atoi(p);
                break;
            case 3: // pos.y
                point02.y = atoi(p);
            case 4: // altitude
                break;
            case 5: // ori
                break;
            default:
                break;
            }
            ++count;
            p = strtok(NULL, ",");
        }
        Point point84;
        Math_marsToWgs(&point02, &point84);
        std::string str84 = std::to_string(point84.x);
        str84 += ",";
        str84 += std::to_string(point84.y);
        str.replace(22, 16, str84);
        outFile << str;
    }

    inFile.close();
    outFile.close();
}

void getPosition(std::string& str, size_t& pos, char* p)
{
    size_t nextPos;
    int oldLen;
    nextPos = str.find(",", pos + 1);
    oldLen = nextPos - (pos + 1);
    // newLen = strlen(p);
    str.replace(pos + 1, oldLen, p);
    pos = str.find(",", pos + 1);
}

void replace02LogTo84Log()
{
    std::fstream inFile("807/simulate_original.info", std::fstream::in);
    if (!inFile)
        std::cout << "open file failed!!" << std::endl;

    std::fstream _inFile("807/simulationPointOriSpeed.txt", std::fstream::in);
    if (!_inFile)
        std::cout << "open file failed!!" << std::endl;

    std::fstream outFile("807/simulate84_807.info", std::fstream::out | std::fstream::trunc);
    if (!outFile)
        std::cout << "open file failed!!" << std::endl;

    std::string str, str1;
    std::getline(inFile, str);
    outFile << str;
    while (std::getline(inFile, str) && std::getline(_inFile, str1)) {
        const char* tmp = str1.c_str();
        char line[1024] = {0};
        strncpy(line, tmp, (strlen(tmp) - 1));

        int count = 0;
        size_t pos;
        // size_t nextPos;
        // int oldLen, newLen;
        char* p = NULL;
        p = strtok(line, ",");
        while (p != NULL) {
            switch (count) {
            case 0: // valid
                pos = str.find(",", 0);
                break;
            case 1: // dateTime
                pos = str.find(",", pos + 1);
                break;
            case 2: // pos.x
                getPosition(str, pos, p);
                break;
            case 3: // pos.y
                getPosition(str, pos, p);
                break;
            case 4: // altitude
                pos = str.find(",", pos + 1);
                break;
            case 5: // ori
                getPosition(str, pos, p);
                break;
            case 6: // speed
                getPosition(str, pos, p);
                break;
            default:
                break;
            }

            ++count;
            p = strtok(NULL, ",");
        }

        outFile << str;
    }

    inFile.close();
    _inFile.close();
    outFile.close();
}

int main()
{
    // convert02PointsTo84Points();
    // convert02LogTo84Log();
    replace02LogTo84Log();

    return 0;
}