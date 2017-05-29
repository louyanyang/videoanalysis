#include "libimpl/ocean_ai_va_impl.h"



namespace ocean
{
	namespace ai
	{
		namespace va
		{

			VideoAnalysisImpl::VideoAnalysisImpl(const int& channel_id, const int& device_id)
				:m_device_id(device_id), m_channel_id(channel_id)
			{
			
			}

			VideoAnalysisImpl::~VideoAnalysisImpl()
			{
			
			}

		}/*va*/
	}/*ai*/
}/*ocean*/