#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <limits>

// 定义点结构体
struct Point
{
    double x;
    double y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y)
    {}
};

// 计算两点之间的欧几里得距离
double distance(const Point& p1, const Point& p2)
{
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

enum LineConnectType
{
    LineConnectType_bidirection = 0,
    LineConnectType_start = 1,
    LineConnectType_end = 2
};

// 线段类，包含点的集合和线段序号
class Line
{
public:
    int id; // 线段的序号
    std::vector<Point> points;

    Line(int id) : id(id)
    {}

    // 添加一个点到线段中
    void addPoint(const Point& p)
    {
        points.push_back(p);
    }

    // 获取线段的起点
    Point getStart() const
    {
        return points.front();
    }

    // 获取线段的终点
    Point getEnd() const
    {
        return points.back();
    }
};

// 连接信息结构体
struct Connection
{
    int lineId;        // 当前线段的ID
    int nextLineId;    // 下一条线段的ID
    std::string connectionType; // 连接类型："to_start" 或 "to_end"
};

// 合并两条线段
void mergeLines(Line& line1, Line& line2)
{
    // 将line2的点添加到line1的末尾
    line1.points.insert(line1.points.end(), line2.points.begin(), line2.points.end());
}

// 查找与当前线段最近且可合并的线段
bool findClosestMerge(Line& currentLine, std::vector<Line>& lines, double threshold, Connection& connection)
{
    double minDistance = std::numeric_limits<double>::max();
    auto closestIt = lines.end();
    std::string mergeType;

    for (auto it = lines.begin(); it != lines.end(); ++it) {
        Point start1 = currentLine.getStart();
        Point end1 = currentLine.getEnd();
        Point start2 = it->getStart();
        Point end2 = it->getEnd();

        // 计算距离并寻找最短距离的合并选项
        double distToStart = distance(end1, start2);
        if (distToStart < minDistance && distToStart < threshold) {
            minDistance = distToStart;
            closestIt = it;
            mergeType = "to_start";
        }

        double distToEnd = distance(end1, end2);
        if (distToEnd < minDistance && distToEnd < threshold) {
            minDistance = distToEnd;
            closestIt = it;
            mergeType = "to_end";
        }

        double distFromStartToEnd = distance(start1, end2);
        if (distFromStartToEnd < minDistance && distFromStartToEnd < threshold) {
            minDistance = distFromStartToEnd;
            closestIt = it;
            mergeType = "to_end";
            std::reverse(currentLine.points.begin(), currentLine.points.end());
        }

        double distFromStartToStart = distance(start1, start2);
        if (distFromStartToStart < minDistance && distFromStartToStart < threshold) {
            minDistance = distFromStartToStart;
            closestIt = it;
            mergeType = "to_start";
            std::reverse(currentLine.points.begin(), currentLine.points.end());
        }
    }

    // 如果找到可合并的线段，则进行合并
    if (closestIt != lines.end()) {
        if (mergeType == "to_end") {
            std::reverse(closestIt->points.begin(), closestIt->points.end());
        }
        mergeLines(currentLine, *closestIt);
        connection = {currentLine.id, closestIt->id, mergeType};
        lines.erase(closestIt);
        return true;
    }

    return false;
}

// 主函数：合并线段
std::vector<int> mergeAllLines(std::vector<Line>& lines, std::vector<Connection>& connections, double threshold = 0.1)
{
    std::vector<int> mergeOrder;  // 保存合并顺序
    std::unordered_set<int> mergedIds; // 记录已合并的线段ID，防止回环

    while (!lines.empty()) {
        // 取出当前处理的线段
        Line currentLine = lines.back();
        lines.pop_back();

        // 如果当前线段已经合并过，跳过它
        if (mergedIds.count(currentLine.id))
            continue;
        mergedIds.insert(currentLine.id);
        mergeOrder.push_back(currentLine.id);

        // 尝试寻找可以合并的线段
        Connection connection;
        while (findClosestMerge(currentLine, lines, threshold, connection)) {
            connections.push_back(connection);
            mergedIds.insert(connection.nextLineId);
            mergeOrder.push_back(connection.nextLineId);
        }
    }

    return mergeOrder;
}

int main()
{
    // 示例：初始化一些线段
    std::vector<Line> lines;
    std::vector<Connection> connections;

    Line line1(1);
    line1.addPoint(Point(0.0, 0.0));
    line1.addPoint(Point(1.0, 0.0));

    Line line2(2);
    line2.addPoint(Point(1.05, 0.0));
    line2.addPoint(Point(1.2, 0.0));

    Line line3(3);
    line3.addPoint(Point(1.25, 0.0));
    line3.addPoint(Point(3.0, 0.0));

    lines.push_back(line1);
    lines.push_back(line2);
    lines.push_back(line3);

    // 合并线段
    std::vector<int> mergeOrder = mergeAllLines(lines, connections);

    // 输出合并后的线段数量
    std::cout << "Number of merged lines: " << mergeOrder.size() << std::endl;

    // 输出连接信息
    std::cout << "Connections:" << std::endl;
    for (const auto& conn : connections) {
        std::cout << "Line " << conn.lineId << " connects to line " << conn.nextLineId << " at " << conn.connectionType
                  << std::endl;
    }

    // 输出连接顺序
    std::cout << "Line sequence from start to end:" << std::endl;
    for (const auto& lineId : mergeOrder) {
        std::cout << lineId << " ";
    }
    std::cout << std::endl;

    return 0;
}
