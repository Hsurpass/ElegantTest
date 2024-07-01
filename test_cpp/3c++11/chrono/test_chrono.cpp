#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <time.h>

using namespace std;

void getLocalTime()
{
    // 获取本地时间当前时间点
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    // 将当前时间点转换成时间戳
    std::time_t timestamp = std::chrono::system_clock::to_time_t(now);
    cout << "local timestamp :" << timestamp << endl;
    // 将时间戳转换成tm格式
    std::tm* local_tm = std::localtime(&timestamp);
    // 格式化打印本地时间
    std::cout << "Local time is: " << std::put_time(local_tm, "%Y-%m-%d %H:%M:%S") << std::endl; // 2023-12-04 10:30:24
    cout << std::ctime(&timestamp) << endl; // Mon Dec  4 10:30:24 2023
    cout << std::asctime(local_tm);

    // std::chrono::system_clock::from_time_t()

    //     std::chrono::steady_clock::time_point steady_now = std::chrono::steady_clock::now();
    //     std::chrono::system_clock::time_point system_now =
    //         std::chrono::time_point_cast<std::chrono::system_clock::duration>(steady_now);
    //     // 将当前时间点转换成时间戳
    //     std::time_t now_c = std::chrono::system_clock::to_time_t(system_now);
    //     cout << "local timestamp :" << now_c << endl;
    //     // 将时间戳转换成tm格式
    //     std::tm* local_tm1 = std::localtime(&now_c);
    //     // 格式化打印本地时间
    //     std::cout << "Local time is: " << std::put_time(local_tm1, "%Y-%m-%d %H:%M:%S") << std::endl; // 2023-12-04 10:30:24
    //     cout << std::ctime(&now_c) << endl; // Mon Dec  4 10:30:24 2023
}

int main()
{
    // getLocalTime();

    auto dur = std::chrono::seconds::max();
    // dur.

    return 0;
}