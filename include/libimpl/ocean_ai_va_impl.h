#ifndef __OCEAN_AI_VIDEOANALYSIS_IMPL_H__
#define __OCEAN_AI_VIDEOANALYSIS_IMPL_H__


#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace ocean
{
	namespace ai
	{
		namespace va
		{
			class VideoAnalysisImpl : public boost::noncopyable ,public boost::enable_shared_from_this<VideoAnalysisImpl>
			{
			public:
				VideoAnalysisImpl(const int& channel_id,const int& device_id);
				virtual ~VideoAnalysisImpl();

			public:


			private:

				const int m_channel_id;
				const int m_device_id;

			};

		}/*va*/
	}/*ai*/
}/*ocean*/


#endif