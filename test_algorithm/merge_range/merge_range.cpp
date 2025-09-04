/*
有多个范围(0,0.2), (0.1,0.4), (0.6,0.8), (0.7,1) 把这些范围进行聚合返回新的范围
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Range {
    double start;
    double end;
};

vector<Range> mergeRanges(const vector<Range>& ranges) {
    if (ranges.empty()) return {};

    // Sort ranges by their start value
    vector<Range> merged = ranges;
    sort(merged.begin(), merged.end(), [](const Range& a, const Range& b) {
        return a.start < b.start;
    });

    vector<Range> result;
    Range current = merged[0];

    for (const auto& range : merged) {
        if (range.start <= current.end) {
            // Overlapping ranges, merge them
            current.end = max(current.end, range.end);
        } else {
            // Non-overlapping range, add the current range to the result
            result.push_back(current);
            current = range;
        }
    }
    result.push_back(current);
    return result;
}

int main() {
    vector<Range> ranges = {{0, 0.2}, {0.1, 0.4}, {0.6, 0.8}, {0.7, 1}};
    vector<Range> merged = mergeRanges(ranges);

    for (const auto& range : merged) {
        cout << "(" << range.start << ", " << range.end << ") ";
    }
    cout << endl;
    return 0;
}