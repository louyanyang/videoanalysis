#ifndef __OCEAN_AI_VIDEOANALYZER_SCHEDULER_H__
#define __OCEAN_AI_VIDEOANALYZER_SCHEDULER_H__

#include <boost/thread/once.hpp>
#include "ocean_ai_va_common.h"

namespace ocean
{
	namespace ai
	{


		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		class Analyzer
		{
		public:
			Analyzer(const int& channel_id,const int& device_id,const VideoAnalysisResultCallback& callback,const TaskType& task_type);
			~Analyzer();

		public:
			STATUS AsyncRun(const boost::uint64_t& time_stamp,const cv::gpu::GpuMat& frame,const VideoAnalysisResultCallback& callback = 0);

		private:

			VideoAnalysisResultCallback m_callback;
			TaskType m_task_type;

			const int m_device_id;
			const int m_channel_id;


		};


		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		class AnalyzerScheduler
		{
			typedef boost::shared_ptr<AnalyzerScheduler> scheduler_type;
			typedef boost::shared_ptr<Analyzer> analyzer_type;

		public:
			static scheduler_type Instance();

			analyzer_type CreateAnalyzer(const int& channel_id,
				                         const int& device_id,
										 const InitParams& init_params,
										 const VideoAnalysisResultCallback& callback);

			static std::string GetAlgoVersion();

		private:
			static void init();
			AnalyzerScheduler();

		private:
			static scheduler_type m_scheduler;

			static boost::once_flag init_flag;
			static std::string algo_version;
		};



	}/*ai*/
}/*ocean*/

#endif