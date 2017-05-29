#ifndef __INTERNAL_THREAD_H__
#define __INTERNAL_THREAD_H__

#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <opencv2/core/core.hpp>
#include "libcore/syncqueue.hpp"


namespace ocean
{
	namespace ai
	{

		namespace core
		{
			/**
			* Virtual class encapsulate boost::thread for use in base class
			* The child class will acquire the ability to run a single thread,
			* by reimplementing the virtual function InternalThreadEntry.
			*/

			class InternalThread
			{

			public:
				InternalThread();
				virtual ~InternalThread();

			public:
				//Start() should be called by your subclass
				void Start();

				//Stop() should be called by your subclass
				void Stop();

			protected:

				//implement this method in your subclass 
				//with the code you want your thread to run  
				virtual void InternalThreadEntry();

				bool must_stop();

			private:

				void entry();

				bool is_started() const;

			private:

				boost::shared_ptr<boost::thread> m_thread;
			};
		}/*core*/
	}/*ai*/
}/*ocean*/



#endif