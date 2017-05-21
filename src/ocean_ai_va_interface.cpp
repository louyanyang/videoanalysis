#include "ocean_ai_va_interface.h"
#include "ocean_ai_va_scheduler.h"



namespace ocean
{
	namespace ai
	{


		VideoAnalysisInterface::VideoAnalysisInterface(const int& channel_id,
			                                           const int& device_id,
			                                           const InitParams& init_params,
			                                           const VideoAnalysisResultCallback& callback)
													   :m_task_type(init_params.task_type), 
													   m_device_id(device_id),
													   m_channel_id(channel_id)
		{
			AnalyzerScheduler::Instance()->CreateAnalyzer(channel_id,device_id,init_params,callback);


		    
		}
		VideoAnalysisInterface::~VideoAnalysisInterface()
		{
		}

		STATUS VideoAnalysisInterface::PushFrame(const boost::uint64_t& time_stamp,
		   	                                     const cv::Mat& frame,
			                                     const VideoAnalysisResultCallback& callback /* = 0 */)
		{
			return STATUS::SUCCESS;
		}


		STATUS VideoAnalysisInterface::PushFrame(const boost::uint64_t& time_stamp,
			                                     const cv::gpu::GpuMat& frame,
			                                     const VideoAnalysisResultCallback& callback /* = 0 */)
		{
			return STATUS::SUCCESS;
		}

		void GlobalInit(const std::string& path)
		{

		}

		void GlobalRelease()
		{
		    
		}

		std::string GetVersion()
		{
			return "";
		}

	}
}