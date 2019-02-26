/***********************************************************************************************
			created: 		2019-02-25

			author:			chensong

			purpose:		threadpool

			later tasks:	null
************************************************************************************************/
#ifndef _C_THREADPOOL_H_
#define _C_THREADPOOL_H_
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <atomic>
#include <list>
#include <queue>
#include <iostream>
#include "cnoncopyable.h"
template<typename T>
class cthread_pool :public cnoncopyable
{
public:
	explicit	cthread_pool() :m_thread_num(0), m_max_requests(0),  m_stop(false){}
	virtual ~cthread_pool();
public:
	/*参数thread_number是线程池中线程的数量，max_requests是请求队列中最多允许的、
	等待处理的请求的数量*/
	bool init(int thread_number = 8, int max_requests = 65535);
	void Destroy();
	/*工作线程运行的函数，它不断从工作队列中取出任务并执行之*/
	void _work_thread();
	/*往请求队列中添加任务*/
	bool append(T * request);
	bool _start();
private:
	int										m_thread_num;/*线程池中的线程数*/
	int										m_max_requests;  /*请求队列中允许的最大请求数*/
	std::mutex								m_lock;         /*保护请求队列的互斥锁*/
	std::condition_variable					m_condition;    /*是否有任务需要处理*/
	std::list<T*>							m_task;  /*请求队列或者任务队列*/
	std::vector<std::thread>				m_pthread; /*描述线程池的数组，其大小为m_pthread*/
	bool									m_stop;    /*是否结束线程*/
};


template<typename T>
inline cthread_pool<T>::~cthread_pool()
{
}

template<typename T>
inline bool cthread_pool<T>::init(int thread_number, int max_requests)
{
	if (thread_number <= 0 || max_requests <= 0)
	{
		std::cout << "pthread_sum and requests queqe big" << std::endl;
		return false;
	}
	// create pthread
	m_max_requests = max_requests;
	m_thread_num = thread_number;
	return true;
}

template<typename T>
inline void cthread_pool<T>::Destroy()
{
	{
		std::lock_guard<std::mutex> lock(m_lock);
		if (m_stop)
		{
			return;
		}
		m_stop = true;
	}
	m_condition.notify_all();
	//printf("[%s] thread = %d\n", __FUNCTION__, m_pthread.size());
	for (std::vector<std::thread>::iterator it = m_pthread.begin(); it != m_pthread.end(); ++it)
	{
	//	printf("[%s]\n", __FUNCTION__);
		if (it->joinable())
		{
			it->join();
		}
	}
	m_pthread.clear();
}

template<typename T>
inline void cthread_pool<T>::_work_thread()
{
	T* task = NULL;
	while (!m_stop)
	{
		{
			std::unique_lock<std::mutex> lock(m_lock);
			m_condition.wait(lock, [this]() {return m_task.size() > 0; });
		}
		while (!m_task.empty())
		{
			{
				std::lock_guard<std::mutex> lock{ m_lock };
				task = m_task.front();
				m_task.pop_front();
			}
			if (!task)
			{
				continue;
			}
			task->process();
		}	
	}
}

template<typename T>
inline bool cthread_pool<T>::append(T * request)
{
	m_lock.lock();
	if (m_task.size() > m_max_requests)
	{
		m_lock.unlock();
		std::cout << "task queue size max" << std::endl;
		return false;
	}
	//std::cout << "m_task === " << m_task.size() << std::endl;
	//std::cout << "pthread_id ==" << std::thread::get_id() << "\n";
	
	m_task.push_back(request);
	m_lock.unlock();
	m_condition.notify_one();
	return true;
}

template<typename T>
inline bool cthread_pool<T>::_start()
{
	for (int i = 0; i < m_thread_num; ++i)
	{

		m_pthread.emplace_back(&cthread_pool::_work_thread, this);
	}

	return true;
}



#endif  //_C_THREADPOOL_H_


