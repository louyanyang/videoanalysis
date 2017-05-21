#ifndef __LOG_H__
#define __LOG_H__


#include <string>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/common.hpp>



namespace ocean
{
	namespace log
	{
		enum SeverityLevel
		{
			Debug = 0,
			Info,
			Warning,
			Error,
			Fatal
		};


		class SLog
		{
			typedef boost::log::sources::severity_channel_logger<SeverityLevel> logger_type;
		public:
			SLog();
			~SLog();
		public:
			static void LogInit(const std::string& filename = std::string());

			static void SetLevel(const SeverityLevel& lv);

			static void ReleaseLog();

		public:

			static logger_type logger;

		};

#define OCEAN_LOG(log_lv) BOOST_LOG_FUNCTION();\
BOOST_LOG_CHANNEL_SEV(ocean::log::SLog::logger,std::string(""),log_lv)

#define OCEANCHAN_LOG(log_lv,chan) BOOST_LOG_FUNCTION();\
BOOST_LOG_CHANNEL_SEV(ocean::log::SLog::logger,std::to_string(chan),log_lv)

#define LOG_DEBUG OCEAN_LOG(ocean::log::SeverityLevel::Debug)
#define LOG_INFO OCEAN_LOG(ocean::log::SeverityLevel::Info)
#define LOG_WARNING OCEAN_LOG(ocean::log::SeverityLevel::Warning)
#define LOG_ERROR OCEAN_LOG(ocean::log::SeverityLevel::Error)
#define LOG_FATAL OCEAN_LOG(ocean::log::SeverityLevel::Fatal)

#define LOGCHAN_DEBUG(chan) OCEANCHAN_LOG(ocean::log::SeverityLevel::Debug,chan)
#define LOGCHAN_INFO(chan) OCEANCHAN_LOG(ocean::log::SeverityLevel::Info,chan)
#define LOGCHAN_WARNING(chan) OCEANCHAN_LOG(ocean::log::SeverityLevel::Warning,chan)
#define LOGCHAN_ERROR(chan) OCEANCHAN_LOG(ocean::log::SeverityLevel::Error,chan)
#define LOGCHAN_FATAL(chan) OCEANCHAN_LOG(ocean::log::SeverityLevel::Fatal,chan)


	}/*log*/
}/*ocean*/



#endif