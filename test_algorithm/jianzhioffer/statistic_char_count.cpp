#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// 统计一个字符串不同字符出现的次数
std::unordered_map<char, int> statistic_char_count(const std::string& str)
{
    std::unordered_map<char, int> char_map;

    for (char c : str) {
        if (char_map.find(c) != char_map.end()) {
            char_map[c]++;
        }
        else {
            char_map[c] = 1;
        }
    }

    return char_map;
}

int main()
{
    std::string input = "hello world";
    std::unordered_map<char, int> result = statistic_char_count(input);

    std::cout << "Character statistic:" << std::endl;
    for (const auto& pair : result) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}