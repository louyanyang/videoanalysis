#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <sstream>
#include "ocean_ai_va_scheduler.h"
#include "libinstance/ocean_ai_va_instance_structure.h"
#include "libinstance/ocean_ai_va_instance_search.h"
#include "liblog/log.h"
#include "libcore/configure.h"





namespace ocean
{
	namespace ai
	{
		namespace va
		{
			TaskZoom::TaskZoom()
				:m_task_set()
			{}

			TaskZoom::~TaskZoom()
			{
			}

			bool TaskZoom::AddTaskSession(const int& channel_id,const int& device_id,const TaskType& task_type)
			{
				boost::unique_lock<boost::mutex> lck(m_task_mtx);

				std::string task_id = make_task_id(channel_id, device_id, task_type);
				if (m_task_set.find(task_id) != m_task_set.end())
					return false;
				m_task_set.insert(task_id);
				return true;
			}

			void TaskZoom::RemoveTaskSession(const int& channel_id,const int& device_id,const TaskType& task_type)
			{
				boost::unique_lock<boost::mutex> lck(m_task_mtx);	
				std::string task_id = make_task_id(channel_id, device_id, task_type);
				if (m_task_set.find(task_id) == m_task_set.end())
				{
					LOG_ERROR << task_id << " task already not exists";
					return;
				}
				m_task_set.erase(task_id);	
			}


			std::string TaskZoom::make_task_id(const int& channel_id, const int& device_id, const TaskType& task_type)
			{
				std::stringstream session_str;
				session_str << "channel_" << channel_id << "_device_" << device_id;
				switch (task_type)
				{
				case TaskType::ABSTRACT:
					session_str << "_ABSTRACT";
					break;
				case TaskType::SYNOPSIS:
					session_str << "SYNOPSIS";
					break;
				case TaskType::SEARCH:
					session_str << "SEARCH";
					break;
				default:
					throw std::logic_error("unknown task type!");
				}
				std::string str;
				session_str >> str;
				return str;
			}


			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			Analyzer::Analyzer(const int& channel_id, const int& device_id, instance_type instance,taskzoom_type taskzoom,const VideoAnalysisResultCallback& callback, const TaskType& task_type)
				:m_channel_id(channel_id), m_device_id(device_id), m_callback(callback), m_instance(instance), m_task_type(task_type), m_taskzoom(taskzoom)
			{

				if (!m_taskzoom->AddTaskSession(m_channel_id,m_device_id,m_task_type))
					throw std::logic_error("task already exist!");

			}

			Analyzer::~Analyzer()
			{ 
				m_taskzoom->RemoveTaskSession(m_channel_id,m_device_id,m_task_type);
			}

			STATUS Analyzer::AsyncRun(const boost::uint64_t& time_stamp, const cv::gpu::GpuMat& frame, const VideoAnalysisResultCallback& callback)
			{


				return STATUS::SUCCESS;
			}

			


			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			boost::shared_ptr<AnalyzerScheduler> AnalyzerScheduler::instance;
			boost::once_flag AnalyzerScheduler::init_flag = BOOST_ONCE_INIT;
			boost::once_flag AnalyzerScheduler::global_init_flag = BOOST_ONCE_INIT;
			std::string AnalyzerScheduler::algo_version = "OCEAN_AI_VA_VERSION_D000";
			std::string AnalyzerScheduler::scheduler_path;


			AnalyzerScheduler::AnalyzerScheduler()
			{
				m_taskzoom = boost::make_shared<TaskZoom>();
			}

			AnalyzerScheduler::analyzer_type AnalyzerScheduler::CreateAnalyzer(const int& channel_id,
				const int& device_id,
				const InitParams& init_params,
				const VideoAnalysisResultCallback& callback)
			{
				try
				{
					instance_type instance = make_instance(channel_id, device_id, init_params);

					if (!instance)
					{
						LOG_INFO << "Channel_id: " << channel_id << " | "
							<< "Device_id: " << device_id
							<< "  create instance error!";
						return nullptr;

					}

					return boost::make_shared<Analyzer>(channel_id, device_id, instance, m_taskzoom, callback, init_params.task_type);
				}
				catch (cv::Exception &e)
				{
					LOG_INFO << "Channel_id: " << channel_id << " | "
						<< "Device_id: " << device_id
						<< e.what();
					return nullptr;
				}

				catch (std::exception &e)
				{
					LOG_INFO << "Channel_id: " << channel_id << " | "
						<< "Device_id: " << device_id
						<< e.what();
					return nullptr;
					
				}
				
				catch (...)
				{

					LOG_INFO << "Channel_id: " << channel_id << " | "
						<< "Device_id: " << device_id
						<< "unknown error!";
					return nullptr;
				}

			}


			AnalyzerScheduler::instance_type AnalyzerScheduler::make_instance(const int& channel_id, const int& device_id, const InitParams& init_params)
			{
				switch (init_params.task_type)
				{
				case TaskType::ABSTRACT:
				case TaskType::SYNOPSIS:
					return boost::make_shared<VideoAnalysisStructure>(channel_id, device_id, init_params);
				case TaskType::SEARCH:
					return boost::make_shared<VideoAnalysisSearch>(channel_id, device_id, init_params);
				default:
					return nullptr;
				}
			}

			AnalyzerScheduler::scheduler_type AnalyzerScheduler::Instance()
			{
				boost::call_once(init_flag, &AnalyzerScheduler::init);
				return instance;
			}

			void AnalyzerScheduler::init()
			{
				instance = boost::shared_ptr<AnalyzerScheduler>(new AnalyzerScheduler);
			}

			std::string AnalyzerScheduler::GetAlgoVersion()
			{
				return algo_version;
			}

			void AnalyzerScheduler::GlobalInit(const std::string& path)
			{
				boost::call_once(global_init_flag, &AnalyzerScheduler::path_init, path);
				Instance();
			}

			void AnalyzerScheduler::path_init(const std::string& path)
			{
				if (path.empty())
				{
					scheduler_path = ".";
				}

				if (path[path.length() - 1] == '/')
				{
					scheduler_path = path.substr(0, path.length() - 1);
				}
				else
				{
					scheduler_path = path;
				}
			}

		}/*va*/
	}/*ai*/
}/*ocean*/