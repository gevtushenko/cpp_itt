//
// Created by egi on 8/25/19.
//

#include "cpp_itt.h"

#include <chrono>
#include <vector>
#include <thread>

int main ()
{
  auto thread_profiler = cpp_itt::create_thread_collector ("Main thread");
  thread_profiler.ignore ();

  std::vector<std::thread> threads;
  for (unsigned int thread_id = 0; thread_id < std::thread::hardware_concurrency (); thread_id++)
    threads.emplace_back ([=] () {
      auto thread_profiler = cpp_itt::create_thread_collector ("Calc thread " + std::to_string (thread_id));
      auto load_domain = cpp_itt::create_domain ("main.load");

      auto duration = cpp_itt::create_event_duration ("Event duration");
      for (unsigned int step = 0; step < 100; step++)
      {
        {
          auto task = load_domain.create_task ("first_task");
          std::this_thread::sleep_for (std::chrono::milliseconds (42));
        }

        cpp_itt::create_event ("In the middle of two tasks");

        {
          auto task = load_domain.create_task ("second_task");
          std::this_thread::sleep_for (std::chrono::milliseconds (24));
        }
      }
    });

  for (auto &thread: threads)
    thread.join ();

  {
    cpp_itt::quiet_region region; /// Don't profile this code block
    std::this_thread::sleep_for (std::chrono::milliseconds (42));
  }
}