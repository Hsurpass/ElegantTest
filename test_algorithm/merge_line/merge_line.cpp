#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_set>

/*
c++实现：把若干根由point组成的无方向的line， 把它们连接成长线，连接规则是计算首尾点的距离小于0.1m， 防止回环，记录从头到尾每根线的序号和每根线连接的下一根线是首点还是尾点，输出从头到尾每根线的序号
*/

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
    int lineId;    // 当前线段的ID
    int nextLineId; // 下一条线段的ID
    std::string connectionType; // 连接类型："to_start" 或 "to_end"
};

// 合并两条线段
void mergeLines(Line& line1, Line& line2)
{
    // 将line2的点添加到line1的末尾
    line1.points.insert(line1.points.end(), line2.points.begin(), line2.points.end());
}

// 主函数：合并线段
std::vector<Line> mergeCloseLines(std::vector<Line>& lines,
                                  std::vector<Connection>& connections,
                                  double threshold = 0.1)
{
    std::vector<Line> mergedLines;
    std::unordered_set<int> mergedIds; // 记录已合并的线段ID，防止回环

    while (!lines.empty()) {
        // 取出当前处理的线段
        Line currentLine = lines.back();
        lines.pop_back();

        // 如果当前线段已经合并过，跳过它
        if (mergedIds.count(currentLine.id))
            continue;
        mergedIds.insert(currentLine.id);

        // 查找是否有可以连接的线段
        bool merged = false;
        for (auto it = lines.begin(); it != lines.end(); ++it) {
            // 如果线段已经合并过，跳过它
            if (mergedIds.count(it->id))
                continue;

            // 获取线段的起点和终点
            Point start1 = currentLine.getStart();
            Point end1 = currentLine.getEnd();
            Point start2 = it->getStart();
            Point end2 = it->getEnd();

            // 判断是否可以合并（即首尾距离小于阈值），并记录连接信息
            if (distance(end1, start2) < threshold) {
                connections.push_back({currentLine.id, it->id, "to_start"});
                mergeLines(currentLine, *it);
                mergedIds.insert(it->id);
                lines.erase(it);
                merged = true;
                break;
            }
            else if (distance(end1, end2) < threshold) {
                std::reverse(it->points.begin(), it->points.end());
                connections.push_back({currentLine.id, it->id, "to_end"});
                mergeLines(currentLine, *it);
                mergedIds.insert(it->id);
                lines.erase(it);
                merged = true;
                break;
            }
            else if (distance(start1, end2) < threshold) {
                std::reverse(currentLine.points.begin(), currentLine.points.end());
                connections.push_back({currentLine.id, it->id, "to_end"});
                mergeLines(currentLine, *it);
                mergedIds.insert(it->id);
                lines.erase(it);
                merged = true;
                break;
            }
            else if (distance(start1, start2) < threshold) {
                std::reverse(currentLine.points.begin(), currentLine.points.end());
                connections.push_back({currentLine.id, it->id, "to_start"});
                mergeLines(currentLine, *it);
                mergedIds.insert(it->id);
                lines.erase(it);
                merged = true;
                break;
            }
        }

        // 如果没有找到可以合并的线段，则将当前线段加入结果集中
        if (!merged) {
            mergedLines.push_back(currentLine);
        }
    }

    return mergedLines;
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
    line2.addPoint(Point(1.05, 0.0));  // 与line1的末尾点距离小于0.1

    Line line3(3);
    line3.addPoint(Point(1.05, 0.0));
    line3.addPoint(Point(3.0, 0.0));

    lines.push_back(line1);
    lines.push_back(line2);
    lines.push_back(line3);

    // 合并线段
    std::vector<Line> mergedLines = mergeCloseLines(lines, connections);

    // 输出合并后的线段数量
    std::cout << "Number of merged lines: " << mergedLines.size() << std::endl;

    // 输出连接信息
    std::cout << "Connections:" << std::endl;
    for (const auto& conn : connections) {
        std::cout << "Line " << conn.lineId << " connects to line " << conn.nextLineId << " at " << conn.connectionType
                  << std::endl;
    }

    // 输出连接顺序
    std::cout << "Line sequence from start to end:" << std::endl;
    for (const auto& conn : connections) {
        std::cout << conn.lineId << " -> ";
    }
    if (!connections.empty()) {
        std::cout << connections.back().nextLineId << std::endl;
    }

    return 0;
}
