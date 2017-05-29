#include "libinstance/ocean_ai_va_instance.h"



namespace ocean
{
	namespace ai
	{
		namespace va
		{
			VideoAnalysisInstance::VideoAnalysisInstance(const int& channel_id, const int& device_id)
				:m_channel_id(channel_id), m_device_id(device_id)
			{
			}

			VideoAnalysisInstance::~VideoAnalysisInstance()
			{}

		}
		

	}
}