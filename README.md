# C++ VTune APIs Wrapper

## Integration

[`cpp_itt.h`](https://github.com/senior-zero/cpp_itt/blob/master/include/cpp_itt.h) is the single required file to include
in your source file. You need to add

```cpp
#include "cpp_itt.h"

void foo ()
{
    auto domain = cpp_itt::create_domain ("test.domain.name");
    auto task = domain.create_task ("task_name");

    // tasks's body
}
```

to the functions you want to profile. Also you can use cpp_itt in your CMake project:

```cmake
add_subdirectory(external/cpp_itt)
target_link_libraries(${CMAKE_PROJECT_NAME})
```

## Examples
With this library, you are able to:

- give threads meaningful names
- tag trace data for different modules by creating domains
- create logical units of work performed by a particular thread
- observe when demarcated events occur in your application
- control the way VTune collects data for your application

```cpp
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
```

[![VTune example](https://raw.githubusercontent.com/senior-zero/cpp_itt/master/doc/vtune.png)]()
