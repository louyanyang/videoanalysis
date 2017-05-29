#include "libcore/internal_thread.h"
#include "libcore/syncqueue.hpp"
#include "liblog/log.h"
#include <opencv2/highgui/highgui.hpp>


namespace ocean
{
	namespace ai
	{
		namespace core
		{
			InternalThread::InternalThread()
				:m_thread()
			{
			}

			InternalThread::~InternalThread()
			{
				Stop();
			}

			bool InternalThread::is_started() const
			{
				return m_thread && m_thread->joinable();
			}

			bool InternalThread::must_stop()
			{
				return m_thread && m_thread->interruption_requested();
			}

			void InternalThread::Start()
			{
				if (is_started())
					return;

				try
				{
					m_thread = boost::make_shared<boost::thread>(&InternalThread::entry,this);
				}
				catch (boost::thread_exception& e)
				{
					LOG_FATAL << e.what();
				}
				catch (std::exception& e)
				{
					LOG_FATAL << e.what();
				}
			}

			void InternalThread::Stop()
			{
				if (is_started())
				{
					m_thread->interrupt();

					try
					{
						if (m_thread->joinable())
							m_thread->join();
					}
					catch (boost::thread_interrupted &)
					{
						//std::cout << "thread interrupt!" << std::endl;
					}
					catch (std::exception &e)
					{
						LOG_FATAL << e.what();
					}
				}

			}

			void InternalThread::entry()
			{
				InternalThreadEntry();
			}

			void InternalThread::InternalThreadEntry()
			{
			}

		}/*core*/
	}/*ai*/
}/*ocean*/

