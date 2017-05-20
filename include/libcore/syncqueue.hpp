#ifndef __SYNCQUEUE_HPP__
#define __SYNCQUEUE_HPP__

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <list>

namespace ocean
{
	namespace core
	{
		template<typename T>
		class SyncQueue
		{
		public:
			
			explicit SyncQueue(const int& max_size = 10)
				:m_queue(), m_max_size(10)
			{}
			~SyncQueue()
			{}

		public:
			SyncQueue() = delete;
			SyncQueue(const SyncQueue&) = delete;
			SyncQueue& operator = (const SyncQueue&) = delete;


		public:
			void put(const T& new_value)
			{
				boost::unique_lock(boost::mutex) lck(m_mtx);
				m_cond_p.wait(lck, [this]{return m_queue.size() < m_max_size; });
				m_queue.push_back(new_value);
				m_cond_g.notify_one();
			}
			bool try_put(const T& new_value)
			{
				boost::unique_lock<boost::mutex> lck(m_mtx);
				if (m_queue.size() >= m_max_size)
					return false;
				m_queue.push_back(new_value);
				m_cond_g.notify_one();
				return true;
			}

			template<typename Rep,typename Period>
			bool put_for(const T& new_value)
			{
				boost::unique_lock<boost::mutex> lck(m_mtx);
				if (!m_cond_p.wait_for(lck, boost::chrono::duration<Rep, period>, [this]{m_queue.size() <= m_max_size; }))
					return false;
				m_queue.push_back(new_value);
				m_cond_g.notify_one();
				return true;
			}

			T get() const
			{
				boost::unique_lock<boost::mutex> lck(m_mtx);
				m_cond_g.wait(lck, [this]{ return !m_queue.empty(); });
				auto value = std::move(m_queue.front());
				m_queue.pop_front();
				m_cond_p.notify_one();
				return value;
			}

			bool try_get(T& value) const
			{
				boost::unique_lock<boost::mutex> lck(m_mtx);
				if (m_queue.empty())
					return false;
				value = std::move(m_queue.front());
				m_queue.pop_front();
				m_cond_p.notify_one();
				return true;
			}

			template<typename Rep, typename Period>
			bool get_for(T& value) const
			{
				boost::unique_lock<boost::mutex> lck(m_mtx);
				if (!m_cond_g.wait_for(lck, boost::chrono::duration<Rep, period>, [this]{m_queue.size() <= m_max_size; }))
					return false;
				value = std::move(m_queue.front());
				m_cond_p.notify_one();
				return true;
			}

			bool empty() const
			{
				boost::unique_lock<boost::mutex> lck(m_mtx);
				return m_queue.empty();
			}

			size_t size() const
			{
				boost::unique_lock<boost::mutex> lck(m_mtx);
				return m_queue.size();
			}

	    private:
			std::list<T> m_queue;
			const int m_max_size;
			mutable boost::mutex m_mtx;
			boost::condition_variable_any m_cond_p;
			boost::condition_variable_any m_cond_g;
		};



	}/*core*/
}/*ocean*/

#endif