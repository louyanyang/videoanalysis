#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "ocean_ai_va_scheduler.h"



namespace ocean
{
	namespace ai
	{



		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		Analyzer::Analyzer(const int& channel_id, const int& device_id, const VideoAnalysisResultCallback& callback,const TaskType& task_type)
			:m_channel_id(channel_id), m_device_id(device_id), m_callback(callback)
		{
		
		
		}

		Analyzer::~Analyzer()
		{
		
		}

		STATUS Analyzer::AsyncRun(const boost::uint64_t& time_stamp, const cv::gpu::GpuMat& frame, const VideoAnalysisResultCallback& callback /* = 0 */)
		{
		

			return STATUS::SUCCESS;
		}



		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		boost::shared_ptr<AnalyzerScheduler> AnalyzerScheduler::m_scheduler;
		boost::once_flag AnalyzerScheduler::init_flag;
		std::string AnalyzerScheduler::algo_version = "OCEAN_AI_VERSION_D00";

		AnalyzerScheduler::AnalyzerScheduler()
		{
		    
		}

		AnalyzerScheduler::analyzer_type AnalyzerScheduler::CreateAnalyzer(const int& channel_id,
			                                                               const int& device_id,																		   
																		   const InitParams& init_params,
																		   const VideoAnalysisResultCallback& callback)
		{

			switch (init_params.task_type)
			{
			case TaskType::ABSTRACT:
				return boost::make_shared<Analyzer>(channel_id, device_id, callback, init_params.task_type);
			case TaskType::SYNOPSIS:
			case TaskType::SEARCH:
			default:
				;
			}
		}

		AnalyzerScheduler::scheduler_type AnalyzerScheduler::Instance()
		{
			boost::call_once(AnalyzerScheduler::init, init_flag);
			return m_scheduler;
		}

		void AnalyzerScheduler::init()
		{
			m_scheduler = boost::shared_ptr<AnalyzerScheduler>(new AnalyzerScheduler);
		}


		std::string AnalyzerScheduler::GetAlgoVersion()
		{
			return algo_version;
		}








	}/*ai*/
}/*ocean*/