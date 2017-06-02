#ifndef __OCEAN_AI_VIDEOANALYSIS_INSTANCE_STRUCTURE_H__
#define __OCEAN_AI_VIDEOANALYSIS_INSTANCE_STRUCTURE_H__

#include "libinstance/ocean_ai_va_instance.h"
#include "ocean_ai_va_common.h"
#include "libcore/vMat.h"
#include "libcore/buffers_manager.h"



namespace ocean
{
	namespace ai
	{
		namespace va
		{
			class VideoAnalysisStructure :public VideoAnalysisInstance
			{
			public:
				VideoAnalysisStructure(const int& channel_id, const int& device_id, const InitParams& init_params);
				virtual ~VideoAnalysisStructure();

			public:

				STATUS AsyncRun(const boost::uint64_t time_stamp, const core::vMat& img, const VideoAnalysisResultCallback& callback);

			private:

				core::BuffersManager m_buffers;
				bool m_buffers_initialized;

			};


		}
		

	}
}


#endif