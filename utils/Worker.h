#pragma once

#include <functional>
#include <thread>
#include <memory>

/// @brief A class that represents a worker thread.
/// @details This class encapsulates a thread and provides a simple interface for starting
///          the thread with a given function. It also handles the thread's lifecycle.
class Worker {
public:
   /// @brief Constructs a Worker with a given function.
   Worker(std::function<void()> func);

   /// @brief Starts the worker thread.
   void start();

private:
   std::function<void()> m_func;
   std::unique_ptr<std::thread> m_thread;
};
