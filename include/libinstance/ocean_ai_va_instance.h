#ifndef __OCEAN_AI_VIDEOANALYSIS_INSTANCE_ABSTRACT_H__
#define __OCEAN_AI_VIDEOANALYSIS_INSTANCE_ABSTRACT_H__


namespace ocean
{
	namespace ai
	{
		class VideoAnalysisInstance
		{
		public:
			VideoAnalysisInstance(const int& channel_id, const int& device_id);
			~VideoAnalysisInstance();

		protected:

			const int m_channel_id;
			const int m_device_id;

		};




	}/*ai*/
}/*coean*/

#endif