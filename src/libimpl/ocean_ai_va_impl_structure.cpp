#include "libimpl/ocean_ai_va_impl_structure.h"

namespace ocean
{
	namespace ai
	{
		namespace va
		{


			VideoAnalysisImplStructure::VideoAnalysisImplStructure(const int& channel_id, const int& device_id, const InitParams& init_params)
				:VideoAnalysisImpl(channel_id,device_id)
			{
			    
			}

			VideoAnalysisImplStructure::~VideoAnalysisImplStructure()
			{}



		}/*va*/
	}/*ai*/
}/*ocean*/