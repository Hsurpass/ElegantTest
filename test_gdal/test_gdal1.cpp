#include <iostream>
#include <gdal/gdal.h>
#include <gdal/gdal_priv.h>

int main() {
    GDALAllRegister(); // 注册 GDAL 驱动

    int utmZone = 33; // 例：UTM Zone 33

    // 构造 UTM 投影字符串
    std::string utmProjString = "+proj=utm +zone=" + std::to_string(utmZone);

    // 创建 SpatialReference 对象
    OGRSpatialReference utmSRS;
    utmSRS.importFromProj4(utmProjString.c_str());

    // 获取 EPSG 空间参考代码
    char* epsgCode = NULL;
    utmSRS.AutoIdentifyEPSG();
    utmSRS.exportToWkt(&epsgCode);

    std::cout << "EPSG Code for UTM Zone " << utmZone << ": " << epsgCode << std::endl;

    // 释放资源
    CPLFree(epsgCode);

    GDALDestroyDriverManager(); // 释放 GDAL 驱动资源

    return 0;
}