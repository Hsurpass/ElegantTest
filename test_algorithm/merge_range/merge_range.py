'''
有多个范围(0,0.2), (0.1,0.4), (0.6,0.8), (0.7,1) 把这些范围进行聚合返回新的范围
'''

def merge_range(ranges):
    if not ranges:
        return []

    # 先按起始位置排序
    ranges.sort(key=lambda x: x[0])
    
    merged = [ranges[0]]

    for current in ranges[1:]:
        last_merged = merged[-1]
        # 如果当前范围的起始位置小于等于上一个合并范围的结束位置，说明有重叠
        if current[0] <= last_merged[1]:
            # 合并范围，更新结束位置为较大的结束位置
            merged[-1] = (last_merged[0], max(last_merged[1], current[1]))
        else:
            # 没有重叠，直接添加当前范围
            merged.append(current)
    return merged

def merge_ranges(ranges):
    if not ranges:
        return []
    # 按照范围的起始值排序
    ranges.sort(key=lambda x: x[0])
    merged = []
    curr_start, curr_end = ranges[0]

    for range in ranges[1:]:
        next_start, next_end = range
        # 如果当前范围与下一个范围重叠或相邻
        if next_start <= curr_end:
             # 更新当前范围的end值为最大值
            curr_end = max(curr_end, next_end)
        else:
            # 没有重叠，将当前范围添加到结果中
            merged.append((curr_start, curr_end))
            curr_start, curr_end = next_start, next_end
    # 添加最后一个范围
    merged.append((curr_start, curr_end))
    return merged

if __name__ == "__main__":
    ranges = [(0.1, 0.4), (0, 0.2), (0.1, 0.3), (0.1, 0.5), (0.6, 0.8), (0.7, 1), (0.55, 0.75)]
    # merged = merge_range(ranges)
    merged = merge_ranges(ranges)
    print(merged)
