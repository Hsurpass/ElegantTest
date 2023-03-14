#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
3个色子：4面体色子，6面体色子，8面体色子。
投出的观测序列是：2 6 4  求每次投出点数最可能使用的色子。

已知4面体色子观测概率是1/4，6面体色子观测概率是1/6, 8面体色子观测概率是1/8。[0.25, 0.167, 0.125]
转换概率：和上一次选择是同一个的概率是1/2， 和上一次选择不一样的概率是1/4
转换概率矩阵：
        0     1     2
        4     6     8
    0 4 0.5  0.25 0.25
    1 6 0.25 0.5  0.25
    2 8 0.25 0.25 0.5

初始化概率：每个色子被选中的概率是1/3，再乘以各自的观测概率，则初始概率为[0.3*0.125, 0.3*0.167, 0.3*0.125]。

每次抛色子都有三个状态可选，也就是序列中每个值对应三个状态。
    4   4   4
    6   6   6
    8   8   8

*/

void dice_viterbi()
{
    // 每行代表一个状态，每列代表一次抛掷
    int row = 3, col = 4;
    // 观测序列：2 6 4 6
    // 观测概率
    double observation[row][col] = {
        {0.25,      0,  0.25,     0},
        {0.167, 0.167, 0.167, 0.167},
        {0.125, 0.125, 0.125, 0.125}
    };
    //转移概率矩阵
    double transition[row][row] = {
                /*0     1     2*/
                /*4     6     8*/
        /*0 4*/ {0.5, 0.25, 0.75},
        /*1 6*/ {0.25, 0.5, 0.25},
        /*2 8*/ {0.75, 0.25, 0.5}
    };

    // 存储每个状态的概率
    double delta[row][col] = {0};
    // 存储每个状态的父状态
    int path[row][col] = {-1};
    // 初始化起始概率
    cout << "init: " << endl;
    for (int i = 0; i < row; i++)
    {
        delta[i][0] = 0.3 * observation[i][0];
        cout << delta[i][0] << " ";
    }
    cout << endl;

    for (int j = 1; j < col; j++)
    {
        for (int k = 0; k < row; k++)   // 遍历每个状态
        {
            double max=0;
            int parent=-1;
            // 当前状态概率 = 上一状态概率*转换状态概率*当前状态观测概率
            for (int i = 0; i < row; i++)
            {
                double tmp = delta[i][j - 1] * transition[i][k] * observation[k][j] * 1000;
                cout << "curr: " << tmp << " pre state probability: " <<  delta[i][j - 1] << " transition: " << transition[i][k] << " emission: " << observation[k][j] << endl;                
                if(tmp > max)
                {
                    max = tmp;
                    parent = i;
                }
            }
            cout << "------------------------" << endl;       
            delta[k][j] = max;
            path[k][j] = parent;
        }
        cout << "#############################" << endl;
    }

    double maxProbability = 0;
    int endIdx=-1;
    for (int i = 0; i < row; i++)
    {
        if(delta[i][col - 1] > maxProbability)
        {
            maxProbability = delta[i][col - 1];
            endIdx = i;
        }
    }

    cout << "max probability: " << maxProbability << endl;    
    // 回溯，输出路径
    vector<int> viterbiPath;
    for(int j = col-1; j >=0; j--)
    {
        viterbiPath.push_back(endIdx);
        endIdx = path[endIdx][j];
    }
    std::reverse(viterbiPath.begin(), viterbiPath.end());
    cout << "path: ";
    for (auto &x:viterbiPath)
    {
        cout << x << " ";
    }
    cout << endl;
}

int main()
{
    dice_viterbi();

    return 0;
}