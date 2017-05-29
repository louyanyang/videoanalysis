
#include <cuda_runtime.h>
#include "libcore/async_engine.h"
#include "liblog/log.h"



namespace ocean
{
	namespace ai
	{
		namespace core
		{

			AsyncEngine::AsyncEngine(const int& channel_id,const int& device_id)
				:m_channel_id(channel_id), m_device_id(device_id)
			{
				Start();
			}

			AsyncEngine::~AsyncEngine()
			{
				Stop();
			}

			void AsyncEngine::InternalThreadEntry()
			{
				LOG_INFO << "Channel_id: " << m_channel_id << " | "
					     << "Device_id: " << m_device_id << " AsyncEngine has alreadly been started";

				cudaSetDevice(m_device_id);

				try
				{
					while (!must_stop())
					{



					}

				}
				catch (boost::thread_interrupted &)
				{
					//
				}
				catch (std::exception &e)
				{
					LOG_FATAL << "Channel_id: " << m_channel_id << " | "
						      << "Device_id: " << m_device_id << "AsyncEngine std error!";
				}
				catch (cv::Exception &e)
				{
					LOG_FATAL << "Channel_id: " << m_channel_id << " | "
						<< "Device_id: " << m_device_id << "AsyncEngine opencv error!";
				}
				catch (...)
				{
					LOG_FATAL << "Channel_id: " << m_channel_id << " | "
						<< "Device_id: " << m_device_id << "AsyncEngine unknown error!";
				}

			}


		}
	}
}