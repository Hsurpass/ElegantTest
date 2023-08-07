/*
给你一个大小为 m x n 的二进制矩阵 grid 。
岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在 水平或者竖直的四个方向上 相邻。
你可以假设 grid 的四个边缘都被 0（代表水）包围着。
岛屿的面积是岛上值为 1 的单元格的数目。
计算并返回 grid 中最大的岛屿面积。如果没有岛屿，则返回面积为 0 。
示例 1：
输入：grid = 
    [[0,0,1,0,0,0,0,1,0,0,0,0,0],
     [0,0,0,0,0,0,0,1,1,1,0,0,0],
     [0,1,1,0,1,0,0,0,0,0,0,0,0],
     [0,1,0,0,1,1,0,0,1,0,1,0,0],
     [0,1,0,0,1,1,0,0,1,1,1,0,0],
     [0,0,0,0,0,0,0,0,0,0,1,0,0],
     [0,0,0,0,0,0,0,1,1,1,0,0,0],
     [0,0,0,0,0,0,0,1,1,0,0,0,0]
    ]
输出：6 
解释：答案不应该是11 ，因为岛屿只能包含水平或垂直这四个方向上的 1 。

示例 2：
输入：grid = [[0,0,0,0,0,0,0,0]]
输出：0

提示：
    m == grid.length 
    n == grid[i].length
    1 <= m, n <= 50
    grid[i][j] 为 0 或 1
*/
#include <iostream>
#include <vector>

using namespace std;

void dfs(const std::vector<std::vector<int>>& grid, std::vector<vector<bool>>& visited, int i, int j, int& count)
{
    if (visited[i][j])
        return;

    if (grid[i][j] == 0) {
        visited[i][j] = true;
        return;
    }

    visited[i][j] = true;
    count++;

    int m = grid.size();    // 行
    int n = grid[i].size(); // 列
    // 上
    if (i - 1 >= 0 && !visited[i - 1][j] && grid[i - 1][j] == 1)
        dfs(grid, visited, i - 1, j, count);
    // 下
    if (i + 1 < m && !visited[i + 1][j] && grid[i + 1][j] == 1)
        dfs(grid, visited, i + 1, j, count);
    // 左
    if (j - 1 >= 0 && !visited[i][j - 1] && grid[i][j - 1] == 1)
        dfs(grid, visited, i, j - 1, count);
    // 右
    if (j + 1 < n && !visited[i][j + 1] && grid[i][j + 1] == 1)
        dfs(grid, visited, i, j + 1, count);
}

int maxAreaOfIsland(std::vector<std::vector<int>>& grid)
{
    std::vector<vector<bool>> visited;
    int m = grid.size();
    visited.resize(m);
    for (int i = 0; i < m; i++) {
        int n = grid[i].size();
        visited[i].resize(n, false);
    }

    int maxcount = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {

            int count = 0;
            dfs(grid, visited, i, j, count);
            if (count > maxcount) {
                maxcount = count;
            }
        }
    }

    return maxcount;
}

int main()
{
    std::vector<std::vector<int>> grid = {{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                                          {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
                                          {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};

    std::vector<std::vector<int>> grid1 = {{0, 0, 0, 0, 0, 0, 0, 0}};

    int count = maxAreaOfIsland(grid);
    cout << count << endl;
    count = maxAreaOfIsland(grid1);
    cout << count << endl;
}