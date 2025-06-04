#include "Worker.h"

Worker::Worker(std::function<void()> func)
   : m_func(std::move(func)) {
}

Worker::Worker(const Worker& copy)
	: m_func(copy.m_func)
{
	
}

Worker::~Worker()
{
	//m_thread->join();
}

void Worker::start()
{
	m_thread = std::make_unique<std::thread>(m_func);
}

void Worker::join()
{
	m_thread->join();
}
