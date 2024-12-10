#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Point
{
    double x;
    double y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y)
    {}
  // 重载 == 运算符
    bool operator==(const Point& other) const
    {
        return (x == other.x && y == other.y);
    }
};

double distance(const Point& p1, const Point& p2)
{
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

enum LineConnectType
{
    LineConnectType_None = 0,
    LineConnectType_Start = 1 << 0,
    LineConnectType_End = 1 << 1,
    LineConnectType_Bidirection = LineConnectType_Start | LineConnectType_End
};

class Line
{
public:
    Line(std::string id) : id(id)
    {}

    Line(std::string id, std::vector<Point>& points) : id(id)
    {
        m_points.reserve(points.size());
        m_points.assign(points.begin(), points.end());
    }

    void addPoint(const Point& p)
    {
        m_points.push_back(p);
    }

  // 获取线段的起点
    const Point& getStart() const
    {
        return m_points.front();
    }

  // 获取线段的终点
    const Point& getEnd() const
    {
        return m_points.back();
    }

    const std::string& getId() const
    {
        return id;
    }

    const std::vector<Point>& getPoints() const
    {
        return m_points;
    }

    void setConnectType(const std::string& otherId, LineConnectType thisType, LineConnectType otherType)
    {
        m_next_line[otherId] = {thisType, otherType};
    }
  // 获取连接关系
    const std::unordered_map<std::string, std::pair<LineConnectType, LineConnectType>>& getConnections() const
    {
        return m_next_line;
    }

private:
    std::string id;
    std::vector<Point> m_points;
    std::unordered_map<std::string, std::pair<LineConnectType, LineConnectType>> m_next_line;
};

/*
试着实现一下这个接口，把多根线连接起来，连接规则是首尾点距离小于0.1,
返回合并后的merged_line和从第一根到最后一根线ids: orderd_ids,
同时记录连接的两根线是首尾，首首，尾首，还是尾尾连接的*/
void connect_lines(std::vector<Line>& lines,
                   std::vector<Point>& mergedlines,
                   std::vector<std::string>& ordered_ids,
                   double threshold)
{
    if (lines.empty()) {
        return;
    }

    std::unordered_set<int> visited;
    mergedlines.clear();
    ordered_ids.clear();

    for (size_t i = 0; i < lines.size(); ++i) {
        if (visited.count(i))
            continue; // 跳过已访问过的线

        Line& line = lines[i];
        std::vector<Point> current_line_points = line.getPoints();
        std::vector<std::string> current_ids = {line.getId()};
        visited.insert(i);

        bool merged = true;

        std::string merged_line_start_point_id = line.getId();
        LineConnectType merged_line_start_point_type = LineConnectType_Start;
        Line* startLine = &lines[i];

        std::string merged_line_end_point_id = line.getId();
        LineConnectType merged_line_end_point_type = LineConnectType_End;
        Line* endLine = &lines[i];

        while (merged) {
            merged = false;
            for (size_t j = 0; j < lines.size(); ++j) {
                if (visited.count(j) || i == j)
                    continue; // 跳过已访问或相同的线

                Line& other = lines[j];
                const Point& start1 = current_line_points.front();
                const Point& end1 = current_line_points.back();
                const Point& start2 = other.getStart();
                const Point& end2 = other.getEnd();

                // 计算四种距离
                double d_tail_to_head = distance(end1, start2);
                double d_head_to_tail = distance(start1, end2);
                double d_tail_to_tail = distance(end1, end2);
                double d_head_to_head = distance(start1, start2);

                // 找到最小的距离并判断是否可以连接
                double min_distance = std::min({d_tail_to_head, d_head_to_tail, d_tail_to_tail, d_head_to_head});
                if (min_distance < threshold) {
                // 连接类型
                    if (min_distance == d_tail_to_head) {
                        current_line_points.insert(current_line_points.end(),
                                                   other.getPoints().begin(),
                                                   other.getPoints().end());
                        current_ids.push_back(other.getId());
                        endLine->setConnectType(other.getId(),
                                                merged_line_end_point_type,
                                                LineConnectType::LineConnectType_Start);
                        other.setConnectType(merged_line_end_point_id,
                                             LineConnectType::LineConnectType_Start,
                                             merged_line_end_point_type);
                        merged_line_end_point_id = other.getId();
                        merged_line_end_point_type = LineConnectType_End;
                        endLine = &other;
                    }
                    else if (min_distance == d_head_to_tail) {
                        current_line_points.insert(current_line_points.begin(),
                                                   other.getPoints().begin(),
                                                   other.getPoints().end());
                        current_ids.insert(current_ids.begin(), other.getId());
                        startLine->setConnectType(other.getId(),
                                                  merged_line_start_point_type,
                                                  LineConnectType::LineConnectType_End);
                        other.setConnectType(merged_line_start_point_id,
                                             LineConnectType::LineConnectType_End,
                                             merged_line_start_point_type);
                        merged_line_start_point_id = other.getId();
                        merged_line_start_point_type = LineConnectType_Start;
                        startLine = &other;
                    }
                    else if (min_distance == d_tail_to_tail) {
                        std::vector<Point> reversed_points = other.getPoints();
                        std::reverse(reversed_points.begin(), reversed_points.end());
                        current_line_points.insert(current_line_points.end(),
                                                   reversed_points.begin(),
                                                   reversed_points.end());
                        current_ids.push_back(other.getId());
                        endLine->setConnectType(other.getId(),
                                                merged_line_end_point_type,
                                                LineConnectType::LineConnectType_End);
                        other.setConnectType(merged_line_end_point_id,
                                             LineConnectType::LineConnectType_End,
                                             merged_line_end_point_type);
                        merged_line_end_point_id = other.getId();
                        merged_line_end_point_type = LineConnectType_Start;
                        endLine = &other;
                    }
                    else if (min_distance == d_head_to_head) {
                        std::vector<Point> reversed_points = other.getPoints();
                        std::reverse(reversed_points.begin(), reversed_points.end());
                        current_line_points.insert(current_line_points.begin(),
                                                   reversed_points.begin(),
                                                   reversed_points.end());
                        current_ids.insert(current_ids.begin(), other.getId());

                        startLine->setConnectType(other.getId(),
                                                  merged_line_start_point_type,
                                                  LineConnectType::LineConnectType_Start);
                        other.setConnectType(merged_line_start_point_id,
                                             LineConnectType::LineConnectType_Start,
                                             merged_line_start_point_type);
                        merged_line_start_point_id = other.getId();
                        merged_line_start_point_type = LineConnectType_End;
                        startLine = &other;
                    }
                    visited.insert(j);
                    merged = true; // 标记为已合并
                    break; // 找到合适的连接后退出循环
                }
            }
        }

        // 合并完成后，将结果添加到最终的合并列表中
        if (current_ids.size() > 1) {
            mergedlines = std::move(current_line_points); // 更新合并结果
            ordered_ids = std::move(current_ids); // 更新合并的 ID 列表
            break; // 一旦找到合并，跳出循环
        }
    }

    // 如果仍有未合并的线，返回空
    if (ordered_ids.size() <= 1 || visited.size() < lines.size()) {
        mergedlines.clear();
        ordered_ids.clear();
    }
}

void test_connect_lines()
{
    std::cout << "test16" << std::endl;

    Point p11(0, 0);
    Point p12(0, 0.1);
    Point p13(0, 0.12);
    Point p14(0, 0.4);
    Point p15(0, 1);

    Point p21(0, 2);
    Point p22(0, 1.8);
    Point p23(0, 1.7);
    Point p24(0, 1.4);
    Point p25(0, 1.09);

    Point p31(0, 2.05);
    Point p32(0, 2.2);
    Point p33(0, 2.3);
    Point p34(0, 2.4);
    Point p35(0, 2.5);

    std::vector<Point> points1 = {p11, p12, p13, p14, p15};
    std::vector<Point> points2 = {p21, p22, p23, p24, p25};
    std::vector<Point> points3 = {p31, p32, p33, p34, p35};

    std::vector<Line> lines = {
        Line("line1", points1),
        Line("line2", points2),
        Line("line3", points3),
    };

    std::vector<Point> mergedlines;
    std::vector<std::string> ordered_ids;

  // 设置阈值
    double threshold = 0.1;

  // 调用连接函数
    connect_lines(lines, mergedlines, ordered_ids, threshold);

    // 打印合并后的线段点
    std::cout << "并后的点：" << std::endl;
    for (const auto& point : mergedlines) {
        std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
    }

    // 打印连接的线段ID
    std::cout << "连接的线ID: " << std::endl;
    for (const auto& id : ordered_ids) {
        std::cout << id << std::endl;
    }

  // 打印每条线的连接关系
    std::cout << "连接关系信息：" << std::endl;
    for (const auto& line : lines) {
        const auto& connections = line.getConnections();
        std::cout << "线ID: " << line.getId() << std::endl;
        for (const auto& conn : connections) {
            std::cout << "  连接线ID: " << conn.first << ", 当前线连接类型: " << conn.second.first
                      << ", 另一线连接类型: " << conn.second.second << std::endl;
        }
    }
}
