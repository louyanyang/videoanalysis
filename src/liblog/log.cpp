#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/support/date_time.hpp>
//#include <iomanip>
//#include <iostream>
#include "liblog/log.h"

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

namespace ocean
{
	namespace log
	{

		template<typename CharT, typename TraitsT>
		inline std::basic_ostream<CharT, TraitsT>& operator<<(
			std::basic_ostream<CharT, TraitsT> & strm, SeverityLevel lv)
		{
			static const char* const str[] =
			{
				"DEBUG",
				"INFO",
				"WARNING",
				"ERROR",
				"FATAL",
			};
			if (static_cast<std::size_t>(lv) < (sizeof(str) / sizeof(*str)))
				strm << str[lv];
			else
				strm << static_cast<int>(lv);
			return strm;
		}

		BOOST_LOG_ATTRIBUTE_KEYWORD(log_timestamp, "TimeStamp", boost::posix_time::ptime);
		BOOST_LOG_ATTRIBUTE_KEYWORD(log_thread_id, "ThreadID", attrs::current_thread_id::value_type);
		BOOST_LOG_ATTRIBUTE_KEYWORD(log_scope, "Scope", attrs::named_scope::value_type);
		BOOST_LOG_ATTRIBUTE_KEYWORD(log_severity, "Severity", SeverityLevel);
		BOOST_LOG_ATTRIBUTE_KEYWORD(log_channel, "Channel", std::string);



		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		SLog::logger_type SLog::logger;

		SLog::SLog(){}
		SLog::~SLog(){}

		void SLog::LogInit(const std::string& filename /* = std::string() */)
		{
			logging::formatter formatter = expr::stream
				<< "[" << expr::format_date_time(log_timestamp, "%Y-%m-%d %H:%M:%S") << "]"
				<< "[" << log_thread_id << "]"
				<< "[" << std::setw(7)<<std::setfill(' ')<<log_severity << "]"
				<< expr::if_(log_channel != "")
				[
					expr::stream << "[  " << std::setw(5) <<std::setiosflags(std::ios::left)<< std::setfill(' ') 
					<< log_channel << "]"
				]
				<< expr::if_(log_severity >= Warning)
				[
					expr::stream << expr::format_named_scope(log_scope,keywords::format = "%n[%f:%l]",
					keywords::iteration = expr::reverse,keywords::depth = 2)
				]
			    << expr::smessage;

				auto console_sink = logging::add_console_log();
				console_sink->set_formatter(formatter);

				auto file_sink = logging::add_file_log(
					keywords::file_name = filename + "_COMMON" + "_%Y-%m-%d_%H-%M-%S.log",
					keywords::rotation_size = 10 * 1024 * 1024,
					//keywords::time_based_rotation = sinks::file::rotation_at_time_point(0,0,0),
					keywords::open_mode = std::ios::app,
					keywords::auto_flush = true);
				file_sink->set_formatter(formatter);
				file_sink->locked_backend()->set_file_collector(sinks::file::make_collector(
					keywords::target = filename + "_Logs",
					keywords::max_size = 60 * 1024 * 1024,
					keywords::min_free_space = 100 * 1024 * 1024));
				file_sink->locked_backend()->scan_for_files();

				file_sink->set_filter(log_channel == "");			


				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				auto channel_file_sink = logging::add_file_log(
					keywords::file_name = filename + "_CHANNEL" + "_%Y-%m-%d_%H-%M-%S.log",
					keywords::rotation_size = 10 * 1024 * 1024,
					//keywords::time_based_rotation = sinks::file::rotation_at_time_point(0,0,0),
					keywords::open_mode = std::ios::app,
					keywords::auto_flush = true);
				channel_file_sink->set_formatter(formatter);
				channel_file_sink->locked_backend()->set_file_collector(sinks::file::make_collector(
					keywords::target = filename + "_Logs",
					keywords::max_size = 60 * 1024 * 1024,
					keywords::min_free_space = 100 * 1024 * 1024));
				channel_file_sink->locked_backend()->scan_for_files();

				channel_file_sink->set_filter(log_channel != "");

				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				logging::core::get()->add_sink(console_sink);
				logging::core::get()->add_sink(file_sink);
				logging::core::get()->add_sink(channel_file_sink);

				logging::add_common_attributes();
				logging::core::get()->add_global_attribute("Scope", attrs::named_scope());

		}

		void SLog::SetLevel(const SeverityLevel& lv)
		{
			logging::core::get()->set_filter(log_severity >= lv);
		}

		void SLog::ReleaseLog()
		{
			logging::core::get()->remove_all_sinks();
		}
	}
}