#ifndef __OCEAN_AI_VA_IMPL_SEARCH_H__
#define __OCEAN_AI_VA_IMPL_SEARCH_H__

#include "ocean_ai_va_common.h"
#include "libimpl/ocean_ai_va_impl.h"

namespace ocean
{
	namespace ai
	{
		namespace va
		{
			class VideoAnalysisImplSearch : public VideoAnalysisImpl
			{
			public:
				VideoAnalysisImplSearch(const int& channel_id,const int& device_id,const InitParams& init_params);
				virtual ~VideoAnalysisImplSearch();

			private:

			};

		} /*va*/
	}/*ai*/
}/*ocean*/


#endif