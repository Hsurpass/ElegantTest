#pragma once

namespace ncStruct {

struct AdasData {
    int linkCount;

    /**
    * encode format `IntegerArrayEncodeType_onlyZipped`, decoded length `linkCount`.
    * encode with `IntegerArrayEncoder.encodeInt16Array()`
    */
    std::string adasPointCountArray;

    /**
    * distances, slopes contain data of `linkCount` segments,
    * each segment with data length `adasPointCountArray[i]`.
    * distance data means distance from link start point to current point, unit: meters.
    * slope data is with units of 0.001 degrees, in [-32768, 32767].
    * encode format `IntegerArrayEncodeType_zippedDiff`.
    */
    /** encode with `IntegerArrayEncoder.encodeInt16Array()` */
    std::string slopes;
    /** encode with `IntegerArrayEncoder.encodeInt32Array()` */
    std::string distances;

    /**
    * headings, curvatures contain data of `linkCount` segments at most,
    * if `adasPointCountArray[i]` is less than 3, then segment data doesn't exist.
    * each segment's data has a length of `max(0, adasPointCountArray[i]-2)`, without segment's end points.
    * For curvature, Positive: left turn, negative: right turn. unit: 10^(-6) meter^(-1).
    * For heading, North: 0, positive direction: clockwise. Unit: 360/65536 degree.
    * encode format `IntegerArrayEncodeType_zippedDiff`.
    * if requireCurvatureAndHeadingAngle,
    * encode with `IntegerArrayEncoder.encodeInt32Array()`
    */
    std::string curvatures;
    /**
    * if requireCurvatureAndHeadingAngle,
    * encode with `IntegerArrayEncoder.encodeInt32Array()`
    */
    std::string headings;

    /**
    * encode format `IntegerArrayEncodeType_onlyZipped`, decoded length `linkCount-1`.
    * if requireCurvatureAndHeadingAngle
    * encode with `IntegerArrayEncoder.encodeInt32Array()
    */
    std::string transitionCurvatures;
    /**
    * encode format `IntegerArrayEncodeType_onlyZipped`, decoded length `linkCount-1`.
    * if requireCurvatureAndHeadingAngle
    * encode with `IntegerArrayEncoder.encodeInt32Array()`
    */
    std::string transitionHeadings;
};

}