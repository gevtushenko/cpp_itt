//
// Created by egi on 8/24/19.
//

#ifndef CPP_ITT_CPP_ITT_H
#define CPP_ITT_CPP_ITT_H

#ifdef VTUNE_FOUND
#include <ittnotify.h>
#endif

#include <string>

namespace cpp_itt
{

class quiet_region
{
public:
  quiet_region ();
  ~quiet_region ();
};

class event_duration
{
public:
  event_duration () = delete;
  explicit event_duration (std::string event_name_arg);
  ~event_duration ();

private:
  const std::string event_name;

#ifdef VTUNE_FOUND
  __itt_event impl;
#endif
};

class task
{
public:
  ~task ();

private:
  task () = default;
#ifdef VTUNE_FOUND
  task (__itt_domain *d, std::string task_name_arg);
#endif

protected:
  const std::string task_name;

#ifdef VTUNE_FOUND
  __itt_domain * const p_domain = nullptr;
#endif

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

#ifdef VTUNE_FOUND
  __itt_domain * const p_impl = nullptr;
#endif
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

void create_event (const std::string &event_name);
event_duration create_event_duration (std::string event_name);

}

#endif // CPP_ITT_CPP_ITT_H
