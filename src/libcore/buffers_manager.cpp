#include "libcore/buffers_manager.h"
#include "liblog/log.h"



namespace ocean
{
	namespace ai
	{
		namespace core
		{


			BuffersManager::BuffersManager()
				:m_buffers_size(0), m_cols(0), m_rows(0), m_data_type(DataType::DATA_CPU), m_initialized(false)
			{}

			BuffersManager::~BuffersManager()
			{}

			bool BuffersManager::Initialize(const int buffers_size,const DataType& data_type, const int rows,const int cols,const int type)
			{
				if (m_initialized)
				{
					LOG_WARNING << "circular buffers is already initialized!";
					return true;
				}
				try
				{
					m_buffers.set_capacity(buffers_size);
					for (int i = 0; i < buffers_size; i++)
					{
						m_buffers.push_back(vMat(data_type, rows, cols, type, shared_from_this()));
					}

					m_buffers_size = buffers_size;
					m_rows = rows;
					m_cols = cols;
					m_data_type = data_type;
					m_initialized = true;
				}
				catch (cv::Exception &e)
				{
					LOG_FATAL << e.what();
					return false;
				}
				catch (std::exception  &e)
				{
					LOG_FATAL << e.what();
					return false;
				}
				catch (...)
				{
					LOG_FATAL << "unknown error!";
					return false;
				}
				return true;
			}

			void BuffersManager::GetOneBuffer(vMat& buffer)
			{

				boost::unique_lock<boost::mutex> lck(m_buffers_mtx);
				m_cond_g.wait(lck, [this]{return !m_buffers.empty(); });
				buffer = m_buffers.front();
				m_buffers.pop_front();
			}

			bool BuffersManager::TryGetOneBuffer(vMat& buffer)
			{
				boost::unique_lock<boost::mutex> lck(m_buffers_mtx);
				if (m_cond_g.wait_for(lck, boost::chrono::milliseconds(10), [this]{return m_buffers.empty(); }))
					return false;
				buffer = m_buffers.front();
				m_buffers.pop_front();
				return true;
			}

			void BuffersManager::release()
			{

			}

		}/*core*/

	}/*ai*/
}/*ocean*/