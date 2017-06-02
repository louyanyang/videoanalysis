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


			STATUS VideoAnalysisStructure::AsyncRun(const boost::uint64_t time_stamp, const core::vMat& img, const VideoAnalysisResultCallback& callback)
			{
			    
			}



		}
	}/*ai*/
}/*ocean*/