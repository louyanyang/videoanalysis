#include "ocean_ai_va_interface.h"
#include "ocean_ai_va_scheduler.h"
#include "libcore/configure.h"
#include "liblog/log.h"



namespace ocean
{
	namespace ai
	{
		namespace va
		{
			VideoAnalysisInterface::VideoAnalysisInterface(const int& channel_id,
				const int& device_id,
				const InitParams& init_params,
				const VideoAnalysisResultCallback& callback)
				:m_task_type(init_params.task_type),
				m_device_id(device_id),
				m_channel_id(channel_id)
			{

				LOG_INFO << "Channel_id: " << m_channel_id << " | "
					     << "Device_id: " << m_device_id
					     << "  <<<<<<<<<<<<<<<<  CREATING VIDEOANALYZER  >>>>>>>>>>>>>>>>>>>>";

				try
				{
					m_impl = AnalyzerScheduler::Instance()->CreateAnalyzer(channel_id, device_id, init_params, callback);
				}
				catch (std::exception  &e)
				{
					LOG_FATAL << e.what();
				}
				catch (...)
				{
					LOG_FATAL<< "unknown error!";
				}
				
			}
			VideoAnalysisInterface::~VideoAnalysisInterface()
			{
				LOG_INFO << "Channel_id: " << m_channel_id << " | "
					     << "Device_id: " << m_device_id
					     << "  <<<<<<<<<<<<<<<<  DESTROYING VIDEOANALYZER  >>>>>>>>>>>>>>>>>>>>";

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
				std::string global_path;
				if (path.empty())
					global_path = ".";
				else if (path[path.length() -1 ] == '/')
				{
					global_path = path.substr(0, path.length() - 1);
				}
				else
				{
					global_path = path;
				}

				core::Configure::GlobalInit(global_path);				

				std::string filename = core::Configure::Instance()->GetRunTimeParams()->log_file();
				log::SLog::LogInit(global_path + "/" + filename);

				LOG_INFO << AnalyzerScheduler::GetAlgoVersion();
				LOG_INFO << core::Configure::Instance()->Debug_toString();
				//AnalyzerScheduler::GlobalInit(path);			
			}

			void GlobalRelease()
			{

			}

			std::string GetVersion()
			{
				return AnalyzerScheduler::GetAlgoVersion();
			}

		

		}/*va*/
	}/*ai*/
}/*ocean*/