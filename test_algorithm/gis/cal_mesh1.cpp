#include <iostream>
#include <cmath>
#include <limits>

int GetMeshID(const double &longitude, const double &latitude,
                       int level /*= s_level*/) {
  // 判断是否在全球经纬度范围之内，如果不在合法范围内，则返回非法图幅号
  if (longitude > 180.0 || longitude < -180.0 || latitude > 90.0 ||
      latitude < -90.0) {
    return -1;
  }

  int dwCode = 0;      // 返回值，NDS Level13 编码double
  int nLevel = level;  // 固定的等级，就是13等级

  double dMinX = 0.0;
  // double dMaxX = 0.0;

  double dMinY = -90.0;
  // double dMaxY = 90.0;

  // 在NDS的编码计算中，Level 0, Level 1 稍微有些许差异，需要单独处理，Level
  // 2以后规律很明显，可以循环处理
  // 先处理0级编码
  // 先判断是在西半球，还是在东半球，Level 0级，西半球编码为1，东半球编码为0
  // 0 级编码
  if (longitude > 0.0 ||
      std::fabs(longitude) < std::numeric_limits<double>::epsilon()) {
    dMinX = 0.0;  // 东半球范围
    // dMaxX = 180.0;  // 东半球范围
  } else {
    dMinX = -180.0;  // 西半球
    // dMaxX = 0.0;                   // 西半球
    // 将Level0的编码 1 写入到图幅号中
    dwCode = static_cast<int>(1 << (2 * nLevel));
  }

  // 再处理一下1级编码
  // 循环迭代，一直到nLevel等级
  for (int i = 1; i <= nLevel; i++) {
    // 通过等级，计算当前等级下，判断半球被切分了多少次，2^n
    int nTiles = static_cast<int>(1 << i);

    // 当前等级的经纬度间隔数
    double longitudeInterval = 180.0 / static_cast<double>(nTiles);
    double latitudeInterval = 180.0 / static_cast<double>(nTiles);

    double longitudeMiddle = dMinX + longitudeInterval;
    double latitudeMiddle = dMinY + latitudeInterval;

    int dwLevelSubCode = 0;

    if (i == 1)  // level1不同
    {
      // 从上往下，从左往右
      if (longitude > longitudeMiddle ||
          std::fabs(longitude - longitudeMiddle) <
              std::numeric_limits<double>::epsilon()) {
        dMinX = longitudeMiddle;

        if (latitude > latitudeMiddle ||
            std::fabs(latitude - latitudeMiddle) <
                std::numeric_limits<double>::epsilon()) {
          // 01
          dMinY = latitudeMiddle;
          dwLevelSubCode = 1;
        } else {
          // 11
          // dMaxY = latitudeMiddle;
          dwLevelSubCode = 3;
        }
      } else {
        // dMaxX = longitudeMiddle;

        if (latitude > latitudeMiddle ||
            std::fabs(latitude - latitudeMiddle) <
                std::numeric_limits<double>::epsilon()) {
          // 00
          dMinY = latitudeMiddle;
          dwLevelSubCode = 0;
        } else {
          // 10
          // dMaxY = latitudeMiddle;
          dwLevelSubCode = 2;
        }
      }
    } else {
      // 从下往上，从左往右
      if (longitude > longitudeMiddle ||
          std::fabs(longitude - longitudeMiddle) <
              std::numeric_limits<double>::epsilon()) {
        dMinX = longitudeMiddle;

        if (latitude > latitudeMiddle ||
            std::fabs(latitude - latitudeMiddle) <
                std::numeric_limits<double>::epsilon()) {
          // 11
          dMinY = latitudeMiddle;
          dwLevelSubCode = 3;  // 11
        } else {
          // 01
          // dMaxY = latitudeMiddle;
          dwLevelSubCode = 1;  // 01
        }
      } else {
        // dMaxX = longitudeMiddle;

        if (latitude > latitudeMiddle ||
            std::fabs(latitude - latitudeMiddle) <
                std::numeric_limits<double>::epsilon()) {
          // 10
          dMinY = latitudeMiddle;
          dwLevelSubCode = 2;  // 10
        } else {
          // 00
          // dMaxY = latitudeMiddle;
          dwLevelSubCode = 0;
        }
      }
    }
    // 更新dwCode
    dwCode |= dwLevelSubCode << ((nLevel - i) * 2);
  }

  return dwCode;
}

int main() {
    double longitude = 90.0;
    // double longitude = 89.999999995990024;
    // double longitude = 89.9;
    double latitude = 39.0713854;
    int level = 13;

    int meshID = GetMeshID(longitude, latitude, level);
    std::cout << "Mesh ID: " << meshID << std::endl;

    return 0;
}