/*
给定一个由 '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量。
一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。
你可以假设网格的四个边均被水包围。

示例 1:

输入:
11110
11010
11000
00000

输出: 1
示例 2:

输入:
11000
11000
00100
00011

输出: 3

https://zhuanlan.zhihu.com/p/133390668
*/
#include <iostream>
#include <vector>

using namespace std;

void dfs_2(vector<vector<int>>& grid, int i, int j, int row, int col)
{
    if (!(i >= 0 && i < row && j >= 0 && j < col))
        return;

    if (grid[i][j] != 1)
        return;

    grid[i][j] = 0;
    // 上
    dfs_2(grid, i - 1, j, row, col);
    // 下
    dfs_2(grid, i + 1, j, row, col);
    // 左
    dfs_2(grid, i, j - 1, row, col);
    // 右
    dfs_2(grid, i, j + 1, row, col);
}

void dfs_1(vector<vector<int>>& grid, int i, int j, int row, int col)
{
    if (grid[i][j] == 0)
        return;

    grid[i][j] = 0;
    // 上
    if (i - 1 >= 0 && grid[i - 1][j] == 1)
        dfs_1(grid, i - 1, j, row, col);
    // 下
    if (i + 1 < row && grid[i + 1][j] == 1)
        dfs_1(grid, i + 1, j, row, col);
    // 左
    if (j - 1 >= 0 && grid[i][j - 1] == 1)
        dfs_1(grid, i, j - 1, row, col);
    // 右
    if (j + 1 < col && grid[i][j + 1] == 1)
        dfs_1(grid, i, j + 1, row, col);
}

int islandNumber(vector<vector<int>>& grid)
{
    if (grid.size() == 0)
        return 0;

    int count = 0;
    int row = grid.size();
    int col = grid[0].size();
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 1) {
                count++;
                // dfs_1(grid, i, j, row, col);
                dfs_2(grid, i, j, row, col);
            }
        }
    }

    return count;
}
void test_islandNumber()
{
    vector<vector<int>> v1({{1, 1, 1, 1, 0}, {1, 1, 0, 1, 0}, {1, 1, 0, 0, 0}, {0, 0, 0, 0, 0}});

    int count = islandNumber(v1);
    cout << "v1 island count: " << count << endl;

    vector<vector<int>> v2 = {{1, 1, 0, 0, 0}, {1, 1, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 1, 1}};

    count = islandNumber(v2);
    cout << "v2 island count: " << count << endl;
}

int main()
{
    test_islandNumber();

    return 0;
}