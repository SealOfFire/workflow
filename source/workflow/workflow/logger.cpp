#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>

/**
 * 初始化日志
 */
void initLogger() {

#ifdef Debug
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::trace);
#else
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::trace);
#endif

    boost::log::formatter formatter = boost::log::expressions::stream
        << "["
        << boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp",
            "%Y-%m-%d %H:%M:%S.%f") /*.%f*/
        << "|"
        << boost::log::expressions::attr<boost::log::attributes::current_thread_id::value_type>("ThreadID")
        << "]["
        << boost::log::expressions::attr<boost::log::trivial::severity_level>("Severity")
        << "]"
        << boost::log::expressions::smessage
        << "    "
        << boost::log::expressions::format_named_scope("Scope",
            boost::log::keywords::format = "(%f:%l)",
            boost::log::keywords::iteration = boost::log::expressions::reverse,
            boost::log::keywords::depth = 1);

    auto consoleSink = boost::log::add_console_log();
    consoleSink->set_formatter(formatter);
    boost::log::core::get()->add_sink(consoleSink);

    boost::log::add_file_log(
        boost::log::keywords::file_name = "sample_%N.log", // 日志文件名
        boost::log::keywords::open_mode = std::ios_base::app, // 日志追加方式
        boost::log::keywords::rotation_size = 1 * 1024 * 1024, // 日志文件大小，1M
        boost::log::keywords::format = "[%TimeStamp%]:[%ThreadID%] [%Severity%] %Message%" // 日志格式
    );

    boost::log::add_common_attributes();
}