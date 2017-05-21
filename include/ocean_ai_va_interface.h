#ifndef __OCEAN_AI_VIDEOANALYSIS_INTERFACE_H__
#define __OCEAN_AI_VIDEOANALYSIS_INTERFACE_H__

#include "ocean_ai_va_common.h"
#include <boost/shared_ptr.hpp>

namespace ocean
{
	namespace ai
	{

		class Analyzer;

		class EXPORTS_API VideoAnalysisInterface
		{
			typedef boost::shared_ptr<Analyzer> analyzer_type;

		public:
			VideoAnalysisInterface(const int& channel_id,
				                   const int& device_id,
								   const InitParams& init_params,
								   const VideoAnalysisResultCallback& callback);
			~VideoAnalysisInterface();
		public:

			STATUS PushFrame(const boost::uint64_t& time_stamp,
				             const cv::Mat& frame,
							 const VideoAnalysisResultCallback& callback = 0);

			STATUS PushFrame(const boost::uint64_t& time_stamp,
				             const cv::gpu::GpuMat& frame,
							 const VideoAnalysisResultCallback& callback = 0);

		private:

			analyzer_type m_analyzer;

			const TaskType m_task_type;
			const int m_channel_id;
			const int m_device_id;

		};


		EXPORTS_API std::string GetVersion();
		EXPORTS_API void GlobalInit(const std::string& path);
		EXPORTS_API void GlobalRelease();

	}
}




#endif