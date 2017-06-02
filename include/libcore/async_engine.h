#ifndef __ASYNC_ENGINE_H__
#define __ASYNC_ENGINE_H__

#include <boost/noncopyable.hpp>
#include "libcore/internal_thread.h"


namespace ocean
{
	namespace ai
	{
		namespace core
		{

			class TaskRunCondition
			{
			public:
				TaskRunCondition();
				~TaskRunCondition();
			private:

			};

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			class AsyncEngine : public InternalThread , public boost::noncopyable
			{
			public:
				AsyncEngine(const int& channel_id,const int& device_id);
				virtual ~AsyncEngine();

			public:

				virtual void InternalThreadEntry() override;

			private:

				const int m_channel_id;
				const int m_device_id;

			};

		}
	}
}




#endif