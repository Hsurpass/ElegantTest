// g++ log1.cpp -DBOOST_LOG_DYN_LINK -lboost_log_setup -lboost_log -lboost_system -lboost_thread -lpthread

#include <boost/log/core/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/support/date_time.hpp>
#include <string>
#include <thread>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

BOOST_LOG_ATTRIBUTE_KEYWORD(_timestamp, "TimeStamp", boost::posix_time::ptime)
// BOOST_LOG_ATTRIBUTE_KEYWORD(_scope, "Scope", attrs::named_scope::value_type)

void init_log()
{
    // 写入到文件
    // boost::log::add_file_log("server.log");  // 无格式
    // 格式化文件名和日志头
    boost::log::add_file_log(
        boost::log::keywords::file_name = "sample_%N.log",
        boost::log::keywords::rotation_size = 10 * 1024 * 1024,
        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
        //  boost::log::keywords::format = "[%TimeStamp%]: %Message%"
        // boost::log::keywords::format =
        //     boost::log::expressions::format("[%1%] [%2%] [%3%] [%4%] %5%") %
        //     expr::format_date_time(_timestamp, "%Y-%m-%d, %H:%M:%S.%f") %
        //     boost::log::expressions::attr< boost::log::attributes::current_thread_id::value_type >("ThreadID") %
        //     boost::log::expressions::attr< unsigned int >("LineID") %
        //     boost::log::trivial::severity %
        //     expr::message

        keywords::format =
            expr::stream << "[" << expr::format_date_time(_timestamp, "%Y-%m-%d, %H:%M:%S.%f") << "] ["
                         << boost::log::trivial::severity << "] ["
                         << boost::log::expressions::attr< boost::log::attributes::current_thread_id::value_type >(
                                "ThreadID")
                         << "] [" << boost::log::expressions::attr< unsigned int >("LineID") << "] "
                         << boost::log::expressions::smessage
        //                      //  << expr::message

    );

    // boost::log::add_common_attributes();
    // boost::log::sources::severity_logger<boost::log::trivial::severity_level> lg;

    // 设置日志级别
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
}

int main()
{
    BOOST_LOG_TRIVIAL(info) << "main thread id: " << std::this_thread::get_id();
    init_log();

    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

    boost::log::add_common_attributes();
    boost::log::sources::severity_logger<boost::log::trivial::severity_level> lg;

    BOOST_LOG_SEV(lg, boost::log::trivial::trace) << "A trace severity message";
    BOOST_LOG_SEV(lg, boost::log::trivial::severity_level::debug) << "A debug severity message";
    using namespace boost::log::trivial;
    BOOST_LOG_SEV(lg, info) << "An informational severity message";
    BOOST_LOG_SEV(lg, warning) << "A warning severity message";
    BOOST_LOG_SEV(lg, error) << "An error severity message";
    BOOST_LOG_SEV(lg, fatal) << "A fatal severity message";

    return 0;
}