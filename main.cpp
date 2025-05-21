#include <iostream>

#include "utils/Worker.h"
#include "utils/SharedQueue.h"

int main() {
   constexpr std::uint64_t ProductionCount = 1'000'000;
   constexpr std::uint64_t Participants = 10;

   // setup shared data
   std::size_t sum = 0;
   SharedQueue<int> queue;

   // setup producer function
   auto produce = [&queue] {
      for (int i = 0; i < ProductionCount; ++i) {
         queue.push(i);
      }
   };

   // setup consumer function
   auto consume = [&queue, &sum] {
      for (int i = 0; i < ProductionCount; ++i) {
         const int data = queue.pop();
         sum += data;
      }
   };

   // create producer and consumer threads
   std::vector producers(Participants, Worker(produce));
   std::vector consumers(Participants, Worker(consume));

   // start producer and consumer threads
   for (auto& producer : producers) {
      producer.start();
   }
   for (auto& consumer : consumers) {
      consumer.start();
   }

   // wait for all threads to finish
   producers.clear();
   consumers.clear();

   // cout the results
   std::cout << "Sum = " << sum << std::endl;
   std::cout << "Expected Sum = " << Participants * (ProductionCount * (ProductionCount - 1)) / 2 << std::endl;
}
