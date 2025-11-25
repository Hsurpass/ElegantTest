#include <iostream>
#include <cmath>
#include <limits>

int getMeshID(double longitude, double latitude, int level)
{
    // Validate longitude and latitude
    if (longitude > 180.0 || longitude < -180.0 || latitude > 90.0 || latitude < -90.0) {
        return -1;
    }

    int dwCode = 0; // return value
    int nLevel = level; // fixed level

    double dMinX = 0.0;
    double dMinY = -90.0;

        // Process level 0 code
    if (longitude >= 0.0) {
        dMinX = 0.0; // East Hemisphere
    }
    else {
        dMinX = -180.0; // West Hemisphere
        dwCode = 1 << (2 * nLevel);
    }

        // Process level 1 to nLevel
    for (int i = 1; i <= nLevel; i++) {
        int nTiles = 1 << i; // 2^i

        double longitudeInterval = 180.0 / nTiles;
        double latitudeInterval = 180.0 / nTiles;

        double longitudeMiddle = dMinX + longitudeInterval;
        double latitudeMiddle = dMinY + latitudeInterval;

        int dwLevelSubCode = 0;

        if (i == 1) { // Level 1
            if (longitude >= longitudeMiddle) {
                dMinX = longitudeMiddle;

                if (latitude >= latitudeMiddle) {
                    dMinY = latitudeMiddle;
                    dwLevelSubCode = 1; // 01
                }
                else {
                    dwLevelSubCode = 3; // 11
                }
            }
            else {
                if (latitude >= latitudeMiddle) {
                    dMinY = latitudeMiddle;
                    dwLevelSubCode = 0; // 00
                }
                else {
                    dwLevelSubCode = 2; // 10
                }
            }
        }
        else {
            if (longitude >= longitudeMiddle) {
                dMinX = longitudeMiddle;

                if (latitude >= latitudeMiddle) {
                    dMinY = latitudeMiddle;
                    dwLevelSubCode = 3; // 11
                }
                else {
                    dwLevelSubCode = 1; // 01
                }
            }
            else {
                if (latitude >= latitudeMiddle) {
                    dMinY = latitudeMiddle;
                    dwLevelSubCode = 2; // 10
                }
                else {
                    dwLevelSubCode = 0; // 00
                }
            }
        }

            // Update dwCode
        dwCode += dwLevelSubCode << ((nLevel - i) * 2);
    }

    return dwCode;
}

int main()
{
    double longitude = 90.0;
    double latitude = 39.0713854;
    int level = 13;

    int meshID = getMeshID(longitude, latitude, level);
    std::cout << "Mesh ID: " << meshID << std::endl;

    return 0;
}