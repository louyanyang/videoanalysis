#ifndef __OCEAN_AI_VIDEOANALYSIS_INSTANCE_ABSTRACT_H__
#define __OCEAN_AI_VIDEOANALYSIS_INSTANCE_ABSTRACT_H__


#include <boost/noncopyable.hpp>

namespace ocean
{
	namespace ai
	{
		namespace va
		{

			class VideoAnalysisInstance:public boost::noncopyable
			{
			public:
				VideoAnalysisInstance(const int& channel_id, const int& device_id);
				virtual ~VideoAnalysisInstance();

			protected:

				const int m_channel_id;
				const int m_device_id;

			};



		}
	}/*ai*/
}/*coean*/

#endif