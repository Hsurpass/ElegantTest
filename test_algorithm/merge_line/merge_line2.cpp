#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <limits>
#include <queue>
#include <unordered_map>
#include <cassert>
#include <memory>

// 定义点结构体
struct Point
{
    double x;
    double y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y)
    {}

    bool operator==(const Point& other)
    {
        return this->x == other.x && this->y == other.y;
    }
};

enum LineConnectType
{
    LineConnectType_None = 0,
    LineConnectType_Start = 1 << 0,
    LineConnectType_End = 1 << 1,
    LineConnectType_Bidirection = LineConnectType_Start | LineConnectType_End
};

std::string LineConnectType_toString(int type)
{
    std::string r;
    switch (type) {
    case LineConnectType_None:
        r = "LineConnectType_None";
        break;
    case LineConnectType_Start:
        r = "LineConnectType_Start";
        break;
    case LineConnectType_End:
        r = "LineConnectType_End";
        break;
    case LineConnectType_Bidirection:
        r = "LineConnectType_Bidirection";
        break;
    }

    return r;
}

// 计算两点之间的欧几里得距离
double distance(const Point& p1, const Point& p2)
{
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// // 连接信息结构体
// struct Connection
// {
//     int lineId;        // 当前线段的ID
//     int nextLineId;    // 下一条线段的ID
//     std::string connectionType; // 连接类型："to_start" 或 "to_end"
// };

class Line
{
public:
    Line(const std::string& id) : m_id(id), m_visited(false)
    {}

    Line(const std::string& id, const std::vector<Point>& points) : m_id(id), m_visited(false)
    {
        m_points.reserve(points.size());
        m_points.assign(points.begin(), points.end());
    }

    // std::string& get_id()
    // {
    //     return m_id;
    // }

    // const std::vector<Point>& get_points() const
    // {
    //     return m_points;
    // }

    // 添加一个点到线段中
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

    std::unordered_map<std::string, std::pair<LineConnectType, LineConnectType>>& getPredLine()
    {
        return m_pred_line;
    }

    std::unordered_map<std::string, std::pair<LineConnectType, LineConnectType>>& getNextLine()
    {
        return m_next_line;
    }

    std::string m_id; // 线段的序号
    std::vector<Point> m_points;
    LineConnectType m_connect_type;
    bool m_visited;
private:
    std::unordered_map<std::string, std::pair<LineConnectType, LineConnectType>> m_pred_line;
    std::unordered_map<std::string, std::pair<LineConnectType, LineConnectType>> m_next_line;
};

std::shared_ptr<Line> findNotVisited(const std::vector<std::shared_ptr<Line>>& lines)
{
    if (lines.empty()) {
        return nullptr;
    }

    for (const auto& line : lines) {
        if (!line->m_visited) {
            return line;
        }
    }

    return nullptr;
}

int findIndex(const std::string& id, const std::deque<std::string>& orderd_ids)
{
    for (int i = 0; i < orderd_ids.size(); ++i) {
        if (orderd_ids[i] == id) {
            return i;
        }
    }

    return -1;
}

void mergelines(std::vector<std::shared_ptr<Line>>& lines,
                double threshold,
                std::vector<Point>& mergedlines,
                std::deque<std::string>& orderd_ids)
{
    std::vector<std::shared_ptr<Line>> tmp_lines(lines);
    std::vector<std::shared_ptr<Line>> unconnected_lines;
    // std::vector<Point> mergedlines;
    // std::deque<std::string> orderd_ids;

    std::queue<std::shared_ptr<Line>> queue;
    std::shared_ptr<Line> first_line = tmp_lines.front();
    first_line->m_connect_type = LineConnectType_Bidirection;
    first_line->m_visited = true;
    queue.emplace(first_line);
    // tmp_lines.pop_back();
    int visited = 1;

    mergedlines.assign(first_line->m_points.begin(), first_line->m_points.end());
    orderd_ids.push_back(first_line->m_id);

    while (!queue.empty() || visited < tmp_lines.size()) {
        std::shared_ptr<Line> curr_line;
        if (queue.empty()) {
            curr_line = findNotVisited(tmp_lines);
            if (!curr_line) {
                assert(curr_line != nullptr);
            }
            curr_line->m_connect_type = LineConnectType_Bidirection;
            curr_line->m_visited = true;
            ++visited;
        }
        else {
            curr_line = queue.front();
            queue.pop();
        }

        Point start1 = curr_line->getStart();
        Point end1 = curr_line->getEnd();

        bool curr_end_merged = false;
        bool curr_start_merged = false;
        for (auto it = tmp_lines.begin(); it != tmp_lines.end(); ++it) {
            std::shared_ptr<Line> other_line = *it;
            if (other_line->m_visited) {
                continue;
            }

            Point start2 = other_line->getStart();
            Point end2 = other_line->getEnd();

            if (curr_line->m_connect_type & LineConnectType_End) {
                if (distance(end1, start2) < threshold && !other_line->m_visited) {
                    assert(curr_end_merged != true);
                    curr_end_merged = true;

                    if (end1 == mergedlines.back()) {
                        curr_line->getNextLine().emplace(other_line->m_id,
                                                         std::make_pair(LineConnectType_End, LineConnectType_Start));

                        mergedlines.insert(mergedlines.end(), other_line->m_points.begin(), other_line->m_points.end());
                        orderd_ids.push_back(other_line->m_id);

                        other_line->getPredLine().emplace(curr_line->m_id,
                                                          std::make_pair(LineConnectType_Start, LineConnectType_End));
                    }
                    else if (end1 == mergedlines.front()) {
                        curr_line->getPredLine().emplace(other_line->m_id,
                                                         std::make_pair(LineConnectType_End, LineConnectType_Start));

                        mergedlines.insert(mergedlines.begin(),
                                           other_line->m_points.rbegin(),
                                           other_line->m_points.rend());
                        orderd_ids.push_front(other_line->m_id);

                        other_line->getNextLine().emplace(curr_line->m_id,
                                                          std::make_pair(LineConnectType_Start, LineConnectType_End));
                    }
                    else {
                        abort();
                    }

                    other_line->m_connect_type = LineConnectType_End;
                    other_line->m_visited = true;
                    queue.emplace(other_line);
                    ++visited;
                }
                else if (distance(end1, end2) < threshold && !other_line->m_visited) {
                    assert(curr_end_merged != true);
                    curr_end_merged = true;
                    if (end1 == mergedlines.back()) {
                        curr_line->getNextLine().emplace(other_line->m_id,
                                                         std::make_pair(LineConnectType_End, LineConnectType_End));

                        mergedlines.insert(mergedlines.end(),
                                           other_line->m_points.rbegin(),
                                           other_line->m_points.rend());
                        orderd_ids.push_back(other_line->m_id);

                        other_line->getPredLine().emplace(curr_line->m_id,
                                                          std::make_pair(LineConnectType_End, LineConnectType_End));
                    }
                    else if (end1 == mergedlines.front()) {
                        curr_line->getPredLine().emplace(other_line->m_id,
                                                         std::make_pair(LineConnectType_End, LineConnectType_End));

                        mergedlines.insert(mergedlines.begin(),
                                           other_line->m_points.begin(),
                                           other_line->m_points.end());
                        orderd_ids.push_back(other_line->m_id);

                        other_line->getNextLine().emplace(curr_line->m_id,
                                                          std::make_pair(LineConnectType_End, LineConnectType_End));
                    }
                    else {
                        abort();
                    }

                    other_line->m_connect_type = LineConnectType_Start;
                    other_line->m_visited = true;
                    queue.emplace(other_line);
                    ++visited;
                }
            }

            if (curr_line->m_connect_type & LineConnectType_Start) {
                if (distance(start1, end2) < threshold && !other_line->m_visited) {
                    assert(curr_start_merged != true);
                    curr_start_merged = true;

                    if (start1 == mergedlines.back()) {
                        mergedlines.insert(mergedlines.end(),
                                           other_line->m_points.rbegin(),
                                           other_line->m_points.rend());
                        orderd_ids.push_back(other_line->m_id);
                        curr_line->getNextLine().emplace(other_line->m_id,
                                                         std::make_pair(LineConnectType_Start, LineConnectType_End));

                        other_line->getPredLine().emplace(curr_line->m_id,
                                                          std::make_pair(LineConnectType_End, LineConnectType_Start));
                    }
                    else if (start1 == mergedlines.front()) {
                        mergedlines.insert(mergedlines.begin(),
                                           other_line->m_points.begin(),
                                           other_line->m_points.end());
                        orderd_ids.push_front(other_line->m_id);

                        curr_line->getPredLine().emplace(other_line->m_id,
                                                         std::make_pair(LineConnectType_Start, LineConnectType_End));
                        other_line->getNextLine().emplace(curr_line->m_id,
                                                          std::make_pair(LineConnectType_End, LineConnectType_Start));
                    }
                    else {
                        abort();
                    }

                    other_line->m_connect_type = LineConnectType_Start;
                    other_line->m_visited = true;
                    queue.emplace(other_line);
                    ++visited;
                }
                else if (distance(start1, start2) < threshold && !other_line->m_visited) {
                    assert(curr_start_merged != true);
                    curr_start_merged = true;

                    if (start1 == mergedlines.back()) {
                        mergedlines.insert(mergedlines.end(), other_line->m_points.begin(), other_line->m_points.end());
                        orderd_ids.push_back(other_line->m_id);
                        curr_line->getNextLine().emplace(other_line->m_id,
                                                         std::make_pair(LineConnectType_Start, LineConnectType_Start));

                        other_line->getPredLine().emplace(curr_line->m_id,
                                                          std::make_pair(LineConnectType_Start, LineConnectType_Start));
                    }
                    else if (start1 == mergedlines.front()) {

                        mergedlines.insert(mergedlines.begin(),
                                           other_line->m_points.rbegin(),
                                           other_line->m_points.rend());
                        orderd_ids.push_front(other_line->m_id);

                        curr_line->getPredLine().emplace(other_line->m_id,
                                                         std::make_pair(LineConnectType_Start, LineConnectType_Start));

                        other_line->getNextLine().emplace(curr_line->m_id,
                                                          std::make_pair(LineConnectType_Start, LineConnectType_Start));
                    }
                    else {
                        abort();
                    }

                    other_line->m_connect_type = LineConnectType_End;
                    other_line->m_visited = true;
                    queue.emplace(other_line);
                    ++visited;
                }
            }
        }

        int connect_type = 0;
        if (curr_end_merged) {
            connect_type |= LineConnectType_End;
        }
        if (curr_start_merged) {
            connect_type |= LineConnectType_Start;
        }

        curr_line->m_connect_type = (LineConnectType)connect_type;
        if (curr_line->m_connect_type == LineConnectType_None && curr_line->getNextLine().empty() &&
            curr_line->getPredLine().empty()) {
            curr_line->m_visited = true;
            unconnected_lines.emplace_back(curr_line);
        }
    }

    if (!unconnected_lines.empty()) {
        std::cout << "id: ";
        for (const auto& line : unconnected_lines) {
            std::cout << line->m_id << " ";
        }
        std::cout << std::endl;
        assert(unconnected_lines.empty());
    }
}

int main()
{
    // 示例：初始化一些线段
    std::vector<std::shared_ptr<Line>> lines;
    // std::vector<Connection> connections;

    // std::shared_ptr<Line> line1(new Line("1"));
    // line1->addPoint(Point(0.0, 0.0));
    // line1->addPoint(Point(1.0, 0.0));

    // std::shared_ptr<Line> line2(new Line("2"));
    // // line2->addPoint(Point(1.05, 0.0));
    // // line2->addPoint(Point(1.5, 0.0));

    // line2->addPoint(Point(1.5, 0.0));
    // line2->addPoint(Point(1.05, 0.0));

    // std::shared_ptr<Line> line3(new Line("3"));
    // line3->addPoint(Point(1.55, 0.0));
    // // line3->addPoint(Point(1.2, 0.0));
    // line3->addPoint(Point(3.0, 0.0));

    std::shared_ptr<Line> line1(new Line("1"));
    line1->addPoint(Point(1.05, 0.0));
    line1->addPoint(Point(1.5, 0.0));

    std::shared_ptr<Line> line2(new Line("2"));
    line2->addPoint(Point(0.0, 0.0));
    line2->addPoint(Point(1.0, 0.0));

    std::shared_ptr<Line> line3(new Line("3"));
    line3->addPoint(Point(1.55, 0.0));
    line3->addPoint(Point(3.0, 0.0));

    // std::shared_ptr<Line> line1(new Line("1"));
    // line1->addPoint(Point(0.0, 0.0));
    // line1->addPoint(Point(1.0, 0.0));

    // std::shared_ptr<Line> line2(new Line("2"));
    // line2->addPoint(Point(1.55, 0.0));
    // line2->addPoint(Point(3.0, 0.0));

    // std::shared_ptr<Line> line3(new Line("3"));
    // line3->addPoint(Point(1.05, 0.0));
    // line3->addPoint(Point(1.5, 0.0));

    lines.push_back(line1);
    lines.push_back(line2);
    lines.push_back(line3);

    std::unordered_map<std::string, std::shared_ptr<Line>> line_map;
    line_map.emplace("1", line1);
    line_map.emplace("2", line2);
    line_map.emplace("3", line3);

    std::vector<Point> mergedlines;
    std::deque<std::string> orderd_ids;

    mergelines(lines, 0.1, mergedlines, orderd_ids);

    for (const auto& id : orderd_ids) {
        std::cout << id << " ";
    }
    std::cout << std::endl;

    for (const auto& id : orderd_ids) {
        if (!line_map[id]->getNextLine().empty()) {
            std::cout << id << ": " << line_map[id]->getNextLine().begin()->first << ", "
                      << LineConnectType_toString(line_map[id]->getNextLine().begin()->second.first) << ", "
                      << LineConnectType_toString(line_map[id]->getNextLine().begin()->second.second) << " -> ";
        }
    }
    std::cout << std::endl;

    for (const auto& id : orderd_ids) {
        std::cout << "id: " << id << ", connect_type: " << LineConnectType_toString(line_map[id]->m_connect_type)
                  << " | ";
    }
    std::cout << std::endl;

    for (const auto& p : mergedlines) {
        std::cout << "(" << p.x << ", " << p.y << ") ";
    }
    std::cout << std::endl;
}