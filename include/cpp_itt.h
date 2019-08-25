//
// Created by egi on 8/24/19.
//

#ifndef CPP_ITT_CPP_ITT_H
#define CPP_ITT_CPP_ITT_H

#include <ittnotify.h>
#include <string>

namespace cpp_itt
{

class task
{
public:
  ~task ();

private:
  task (__itt_domain *d, std::string task_name_arg);

protected:
  const std::string task_name;
  __itt_domain * const p_domain = nullptr;

  friend class domain;
};

class domain
{
public:
  domain () = delete;
  explicit domain (std::string domain_name_arg);

  task create_task (std::string task_name);
  void disable ();

private:
  const std::string domain_name;
  __itt_domain * const p_impl = nullptr;
};

class thread
{
public:
  thread () = default;
  explicit thread (std::string thread_name_arg);

  static void ignore ();

private:
  const std::string thread_name;
};

/**
 * Pause data collecting process for entire application (not only caller thread).
 * Reduce overhead of collection.
 */
void pause ();

/**
 * Resume data collection
 */
void resume ();

thread create_thread_collector ();
thread create_thread_collector (std::string str);

/**
 * Create domain with specified name (URI naming style is recommended)
 */
domain create_domain (std::string domain_name);

}

#endif // CPP_ITT_CPP_ITT_H
