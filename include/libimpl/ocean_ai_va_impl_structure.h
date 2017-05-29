#ifndef __OCEAN_AI_VA_IMPL_STRUCTURE_H__
#define __OCEAN_AI_VA_IMPL_STRUCTURE_H__

#include "ocean_ai_va_common.h"
#include "libimpl/ocean_ai_va_impl.h"
#include "liblog/log.h"

namespace ocean
{
	namespace ai
	{
		namespace va
		{
			class VideoAnalysisImplStructure : public VideoAnalysisImpl
			{
			public:
				VideoAnalysisImplStructure(const int& channel_id,const int& device_id,const InitParams& init_params);
				virtual ~VideoAnalysisImplStructure();

			private:

			};

		}/*va*/
	}/*ai*/
} /*ocean*/



#endif