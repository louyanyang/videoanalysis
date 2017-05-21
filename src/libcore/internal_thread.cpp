#include "libcore/internal_thread.h"
#include "libcore/syncqueue.hpp"

#include <opencv2/highgui/highgui.hpp>


namespace ocean
{
	namespace core
	{
		InternalThread::InternalThread()
			:m_thread()
		{
		}

		InternalThread::~InternalThread()
		{
			stop();
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
				m_thread = boost::make_shared<boost::thread>(&InternalThread::entry, this);
			}
			catch (boost::thread_exception& e)
			{
				std::cout << e.what()<<std::endl;
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}		
		}

		void InternalThread::stop()
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
					std::cout << e.what()<<std::endl;
				}
			}

		}



		void InternalThread::entry()
		{
			InternalThreadEntry();
		}

		void InternalThread::InternalThreadEntry()
		{
			//while (!must_stop())
			//{
			//	std::cout << m_thread->get_id() << std::endl;
			//auto img = m_queue.get();
			///*cv::Mat img;
			//if(!m_queue.try_get(img))
			//    continue;*/
			//cv::imshow("test1", img);
			//cv::waitKey(1);
			//}
			//int xx = 0;
		}


	}/*core*/
}/*ocean*/

