#ifndef __OCEAN_AI_VIDEOANALYSIS_INSTANCE_STRUCTURE_H__
#define __OCEAN_AI_VIDEOANALYSIS_INSTANCE_STRUCTURE_H__

#include "libinstance/ocean_ai_va_instance.h"
#include "ocean_ai_va_common.h"



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



			};


		}
		

	}
}


#endif