#ifndef __OCEAN_AI_VA_INSTANCE_SEARCH_H__
#define __OCEAN_AI_VA_INSTANCE_SEARCH_H__

#include "libinstance/ocean_ai_va_instance.h"
#include "ocean_ai_va_common.h"

namespace ocean
{
	namespace ai
	{
		namespace va
		{
			class VideoAnalysisSearch:public VideoAnalysisInstance
			{
			public:
				VideoAnalysisSearch(const int& channel_id,const int& device_id,const InitParams& init_params);
				virtual ~VideoAnalysisSearch();

			private:

			};
		}

	}
}


#endif