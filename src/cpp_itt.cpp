#include "cpp_itt.h"

namespace cpp_itt
{

quiet_region::quiet_region ()
{
  pause ();
}

quiet_region::~quiet_region ()
{
  resume ();
}

event_duration::event_duration (std::string event_name_arg)
  : event_name (move (event_name_arg))
#ifdef VTUNE_FOUND
  , impl (__itt_event_create (event_name.c_str (), event_name.size ()))
#endif
{
#ifdef VTUNE_FOUND
  __itt_event_start (impl);
#endif
}

event_duration::~event_duration ()
{
#ifdef VTUNE_FOUND
  __itt_event_end (impl);
#endif
}

#ifdef VTUNE_FOUND
task::task (__itt_domain *d, std::string task_name_arg)
  : task_name (move (task_name_arg))
  , p_domain (d)
{
  __itt_task_begin (d, __itt_null, __itt_null, __itt_string_handle_create (task_name.c_str ()));
}
#endif

task::~task ()
{
#ifdef VTUNE_FOUND
  __itt_task_end (p_domain);
#endif
}

domain::domain (std::string domain_name_arg)
  : domain_name (move (domain_name_arg))
#ifdef VTUNE_FOUND
  , p_impl (__itt_domain_create (domain_name.c_str ()))
#endif
{ }

task domain::create_task (std::string task_name)
{
#ifdef VTUNE_FOUND
  return task (p_impl, move (task_name));
#else
  return {};
#endif
}

void domain::disable ()
{
#ifdef VTUNE_FOUND
  p_impl->flags = 0;
#endif
}

thread::thread (std::string thread_name_arg)
  : thread_name (move (thread_name_arg))
{
#ifdef VTUNE_FOUND
  __itt_thread_set_name (thread_name.c_str ());
#endif
}

void thread::ignore()
{
#ifdef VTUNE_FOUND
  __itt_thread_ignore ();
#endif
}

void pause ()
{
#ifdef VTUNE_FOUND
  __itt_pause ();
#endif
}

void resume ()
{
#ifdef VTUNE_FOUND
  __itt_resume ();
#endif
}

thread create_thread_collector () { return {}; }

thread create_thread_collector (std::string str)
{
  return thread (move (str));
}

domain create_domain (std::string domain_name)
{
  return domain (move (domain_name));
}

void create_event (const std::string &event_name)
{
#ifdef VTUNE_FOUND
  auto event = __itt_event_create (event_name.c_str (), event_name.size ());
  __itt_event_start (event);
#endif
}

event_duration create_event_duration (std::string event_name)
{
  return event_duration (move (event_name));
}

}
