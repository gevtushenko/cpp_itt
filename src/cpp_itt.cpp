#include "cpp_itt.h"

namespace cpp_itt
{

task::task (__itt_domain *d, std::string task_name_arg)
  : task_name (move (task_name_arg))
  , p_domain (d)
{
  __itt_task_begin (d, __itt_null, __itt_null, __itt_string_handle_create (task_name.c_str ()));
}

task::~task ()
{
  __itt_task_end (p_domain);
}

domain::domain (std::string domain_name_arg)
  : domain_name (move (domain_name_arg))
  , p_impl (__itt_domain_create (domain_name.c_str ()))
{ }

task domain::create_task (std::string task_name)
{
  return task (p_impl, move (task_name));
}

void domain::disable ()
{
  p_impl->flags = 0;
}

thread::thread (std::string thread_name_arg)
  : thread_name (move (thread_name_arg))
{
  __itt_thread_set_name (thread_name.c_str ());
}

void thread::ignore()
{
  __itt_thread_ignore ();
}

void pause ()
{
  __itt_pause ();
}

void resume ()
{
  __itt_resume ();
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


}
