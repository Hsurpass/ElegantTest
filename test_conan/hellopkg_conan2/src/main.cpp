#include <fmt/core.h>
#include <spdlog/spdlog.h>

int main()
{
    fmt::print("Hello, {}!\n", "world");
    spdlog::info("This is an info message from spdlog");
    return 0;
}
