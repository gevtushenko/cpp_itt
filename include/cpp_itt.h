//
// Created by egi on 8/24/19.
//

#ifndef CPP_ITT_CPP_ITT_H
#define CPP_ITT_CPP_ITT_H

#include <ittnotify.h>
#include <string>

#define DISABLE_CPP_ITT \
  #define INTEL_NO_ITTNOTIFY_API

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
};

class domain
{
public:
  domain () = delete;

  void disable ();

protected:
  explicit domain (std::string domain_name_arg);

private:
  const std::string domain_name;
  __itt_domain * const p_impl = nullptr;

  friend class thread;
};

class thread
{
public:
  thread () = default;
  explicit thread (std::string thread_name_arg);

  static void ignore ();

  /**
   * Create domain with specified name (URI naming style is recommended)
   */
  static domain create_domain (std::string domain_name);

private:
  const std::string thread_name;
};

/**
 * Pause data collecting process for entire application (not only caller thread).
 * Reduce overhead of collection.
 */
static void pause ();

/**
 * Resume data collection
 */
void resume ();

thread create_thread_collector () { return {}; }
thread create_thread_collector (std::string str);
}

#endif // CPP_ITT_CPP_ITT_H
