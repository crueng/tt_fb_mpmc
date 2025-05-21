#include "Worker.h"

Worker::Worker(std::function<void()> func)
   : m_func(std::move(func)) {
}

void Worker::start() {

}
