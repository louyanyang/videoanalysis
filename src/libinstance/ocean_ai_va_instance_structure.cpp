#include "libinstance/ocean_ai_va_instance_structure.h"



namespace ocean
{
	namespace ai
	{
		namespace va
		{
			VideoAnalysisStructure::VideoAnalysisStructure(const int& channel_id, const int& device_id, const InitParams& init_params)
				:VideoAnalysisInstance(channel_id, device_id)
			{

			}

			VideoAnalysisStructure::~VideoAnalysisStructure()
			{

			}

		}
	}/*ai*/
}/*ocean*/