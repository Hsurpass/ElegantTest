#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>

using namespace std;

enum PointType
{
    PointType_NONE,
    PointType_CORE,
    PointType_BORDE,
    PointType_Noise
};

class Point
{
public:
    Point() {}
    Point(int x, int y) : m_x(x), m_y(y) {}
    int m_x;
    int m_y;

    PointType m_type; // 点的类型：核心点、边界点、噪声点
    int m_clusterID;  // 簇的编号
};

// 欧氏距离
double calDistance(const Point &currPoint, const Point &otherPoint)
{
    return sqrt(pow(otherPoint.m_x - currPoint.m_x, 2) + pow(otherPoint.m_y - currPoint.m_y, 2));
}

// 得到当前点的r-邻域内的点。
void getNeighbors(int currPointIdx, Point *arr, int size, double eps, vector<int> &clusterIndex)
{
    for (int i = 0; i < size; i++)
    {
        if (calDistance(arr[currPointIdx], arr[i]) <= eps)
        {
            clusterIndex.push_back(i);
        }
    }
}

void expandCluster(vector<int> &clusterSeeds, Point *arr, int size, int eps, int minpts, int clusterId, int *cluster)
{
    int count = clusterSeeds.size();
    for (int i = 0; i < count; i++)
    {
        // 从候选集合中任选一点q, 检查点q的r-邻域
        int q = clusterSeeds[i];
        if (arr[q].m_clusterID >= 0)
            continue;

        vector<int> neighborindices;
        getNeighbors(q, arr, size, eps, neighborindices);
        if (neighborindices.size() < minpts) // 如果小于minpts,则标记为边界点，边界点应该也属于同一簇中。
        {
            // 如果之前被标记为噪声了，则修改为边界点
            arr[q].m_type = PointType_BORDE;
            arr[q].m_clusterID = clusterId;
            cluster[q] = clusterId;
        }
        else // 如果大于minpts，则为核心点，并把r-邻域内的点加入到候选集合中
        {
            arr[q].m_type = PointType_CORE;
            arr[q].m_clusterID = clusterId;
            cluster[q] = clusterId;

            for (int j = 0; j < neighborindices.size(); j++)
            {
                // if(arr[j].m_clusterID >= 0)
                //     continue;

                clusterSeeds.push_back(neighborindices[j]);
                count = clusterSeeds.size();
            }
        }
    }
}

// 要保证传入的点q是还没归簇的
void expandCluster_recursive(int q, Point *arr, int size, int eps, int minpts, int clusterId, int *cluster)
{
    if (arr[q].m_clusterID >= 0)
        return;

    vector<int> neighborindices;
    getNeighbors(q, arr, size, eps, neighborindices);
    if (neighborindices.size() < minpts) // 如果小于minpts,则标记为边界点，边界点应该也属于同一簇中。
    {
        // 如果之前被标记为噪声了，则修改为边界点
        arr[q].m_type = PointType_BORDE;
        arr[q].m_clusterID = clusterId;
        cluster[q] = clusterId;
    }
    else // 如果大于minpts，则为核心点，并把r-邻域内的点加入到候选集合中
    {
        arr[q].m_type = PointType_CORE;
        arr[q].m_clusterID = clusterId;
        cluster[q] = clusterId;

        for (int j = 0; j < neighborindices.size(); j++)
        {
            int neighborIdx = neighborindices[j];
            if (arr[neighborIdx].m_clusterID >= 0)
                continue;

            expandCluster_recursive(neighborIdx, arr, size, eps, minpts, clusterId, cluster);
        }
    }
}

void dbscan(Point *arr, int size, double eps, int minpts)
{
    // 1.初始化：设置所有点都是未标记的，并设置点不属于任何一个簇
    for (int i = 0; i < size; i++)
    {
        arr[i].m_type = PointType_NONE;
        arr[i].m_clusterID = -1;
    }
    // 记录每个点属于哪个簇
    int cluster[size] = {-1};

    // 2.新建簇：选择数据集中的任意点p，检查它的r-邻域中点的个数是否不少于minpts。
    //      如果小于minpts则暂时标记为噪声点；
    //      如果大于则把点p标记为核心点，并把r-邻域内的点加入到候选集合N中, 建立一个新簇，并把点P添加到新簇中。
    int clusterId = 0;
    for (int i = 0; i < size; i++)
    {
        // 已经被归类了，则continue
        if (arr[i].m_clusterID >= 0)
            continue;

        vector<int> clusterSeeds;
        getNeighbors(i, arr, size, eps, clusterSeeds);
        if (clusterSeeds.size() < minpts)
        {
            arr[i].m_type = PointType_Noise; // 暂时标记为噪声点
        }
        else
        {
#if 0
            arr[i].m_type = PointType_CORE;
            arr[i].m_clusterID = clusterId;
            cluster[i] = clusterId;

            // 3.扩展簇：遍历候选集合N中没有访问的点q, 检查其r-邻域内点的个数是否不少于minpts。
            //      如果小于minpts，则标记为边界点。
            //      如果大于minpts，则标记为核心点，并把点q添加到新簇中，把点q的r-邻域内的其他点加入到候选集合N中。
            // 4.重复步骤3，直到候选集合为空，说明当前簇扩展完成。
            expandCluster(clusterSeeds, arr, size, eps, minpts, clusterId, cluster);
#endif
#if 1
            expandCluster_recursive(i, arr, size, eps, minpts, clusterId, cluster);
#endif
            clusterId++;
        }
    } // 5.重复步骤2、3、4,直到所有点都被归入某个簇中或标记为噪声点。
}

void printClusters(Point *points, int num_points)
{
    int i = 0;
    printf("Number of points: %u\n"
           " x     y     z     cluster_id\n"
           "-----------------------------\n",
           num_points);

    while (i < num_points)
    {
        printf("(%d, %d): %d\n", points[i].m_x, points[i].m_y, points[i].m_clusterID);
        ++i;
    }
}

void test_dbscan()
{
    Point p1(1, 2);
    Point p2(2, 1);
    Point p3(2, 4);
    Point p4(4, 3);
    Point p5(5, 8);
    Point p6(6, 7);
    Point p7(6, 9);
    Point p8(7, 9);
    Point p9(9, 5);
    Point p10(1, 12);
    Point p11(3, 12);
    Point p12(5, 12);
    Point p13(3, 3);

    Point points[13];
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
    points[4] = p5;
    points[5] = p6;
    points[6] = p7;
    points[7] = p8;
    points[8] = p9;
    points[9] = p10;
    points[10] = p11;
    points[11] = p12;
    points[12] = p13;

    dbscan(points, 13, 3, 3);

    printClusters(points, 13);
}

int main()
{
    test_dbscan();

    return 0;
}