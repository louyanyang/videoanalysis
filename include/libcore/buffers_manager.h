#ifndef __BUFFERS_MANAGER_H__
#define __BUFFERS_MANAGER_H__

#include "libcore/vMat.h"
#include <boost/circular_buffer.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace ocean
{
	namespace ai
	{
		namespace core
		{
			class BuffersManager : public boost::enable_shared_from_this<BuffersManager>
			{
			public:
				BuffersManager();
				~BuffersManager();

			public:
				bool Initialize(const int buffers_size,const DataType& data_type,const int rows,const int cols,const int type);

				void GetOneBuffer(vMat& buffer);

				bool TryGetOneBuffer(vMat& buffer);

			private:

				void release();

			private:

				boost::mutex m_buffers_mtx;
				boost::condition_variable_any m_cond_g;

				boost::circular_buffer<vMat> m_buffers;

				bool m_initialized;
				int m_buffers_size;
				int m_rows;
				int m_cols;
				DataType m_data_type;

			};



		}/*core*/
	}/*ai*/
}/*ocean*/




#endif