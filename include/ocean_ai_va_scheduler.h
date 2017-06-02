#ifndef __OCEAN_AI_VIDEOANALYZER_SCHEDULER_H__
#define __OCEAN_AI_VIDEOANALYZER_SCHEDULER_H__

#include <boost/thread/once.hpp>
#include <boost/thread.hpp>
#include <boost/unordered_set.hpp>
#include "ocean_ai_va_common.h"
#include "libinstance/ocean_ai_va_instance.h"


namespace ocean
{
	namespace ai
	{
		namespace va
		{

			class TaskZoom
			{
			public:
				TaskZoom();
				~TaskZoom();

			public:

				bool AddTaskSession(const int& channel_id,const int& device_id,const TaskType& task_type);
				void RemoveTaskSession(const int& channel_id,const int& device_id,const TaskType& task_type);

			private:

				static std::string 	make_task_id(const int& channel_id, const int& device_id, const TaskType& task_type);

			public:
				boost::mutex m_task_mtx;
				boost::unordered_set<std::string> m_task_set;

			};


			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			class Analyzer
			{

				typedef boost::shared_ptr<VideoAnalysisInstance> instance_type;
				typedef boost::shared_ptr<TaskZoom> taskzoom_type;

			public:
				Analyzer(const int& channel_id, const int& device_id, instance_type instance,taskzoom_type taskzoom,const VideoAnalysisResultCallback& callback, const TaskType& task_type);
				~Analyzer();

			public:
				STATUS AsyncRun(const boost::uint64_t& time_stamp, const cv::gpu::GpuMat& frame, const VideoAnalysisResultCallback& callback);

			private:

				VideoAnalysisResultCallback m_callback;

				const TaskType m_task_type;
				const int m_device_id;
				const int m_channel_id;

				instance_type m_instance;
				taskzoom_type m_taskzoom;

			};


			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			class AnalyzerScheduler
			{
				typedef boost::shared_ptr<AnalyzerScheduler> scheduler_type;
				typedef boost::shared_ptr<Analyzer> analyzer_type;
				typedef boost::shared_ptr<VideoAnalysisInstance> instance_type;
				typedef boost::shared_ptr<TaskZoom> taskzoom_type;

			public:
				static scheduler_type Instance();

				static void GlobalInit(const std::string& path);

				static std::string GetAlgoVersion();

			public:
				analyzer_type CreateAnalyzer(const int& channel_id,
					const int& device_id,
					const InitParams& init_params,
					const VideoAnalysisResultCallback& callback);
				

			private:
				AnalyzerScheduler();

				static void init();

				static void path_init(const std::string& path);

				instance_type make_instance(const int& channel_id, const int& device_id, const InitParams& init_params);

			private:
				static scheduler_type instance;
				static boost::once_flag init_flag;
				static boost::once_flag global_init_flag;
				static std::string algo_version;
				static std::string scheduler_path;
				taskzoom_type m_taskzoom;
			};


		}/*va*/
	}/*ai*/
}/*ocean*/

#endif