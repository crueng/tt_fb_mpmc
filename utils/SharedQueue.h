#pragma once

#include <queue>
#include <mutex>

/// @brief A thread-safe queue that allows multiple producers and consumers.
/// @tparam T The type of elements in the queue.
/// @details This class provides a simple interface for pushing and popping elements
///          from the queue. It uses a mutex and condition variable to ensure thread-safety.
template<typename T>
class SharedQueue {
public:
   /// @brief Push a value into the queue.
   void push(T value);

   /// @brief Pop a value from the queue. Blocks until a value is available.
   T pop();

private:
   std::mutex m_mutex;
   std::condition_variable m_cv;
   std::queue<T> m_queue;
};

template<typename T>
void SharedQueue<T>::push(T value) {
	std::unique_lock lock(m_mutex);
   m_queue.push(std::move(value));
	m_cv.notify_one();
}

template<typename T>
T SharedQueue<T>::pop() {
   std::unique_lock lock(m_mutex);
   m_cv.wait(lock, [this] {
      return !m_queue.empty();
   });
   T value = std::move(m_queue.front());
   m_queue.pop();
   return value;
}