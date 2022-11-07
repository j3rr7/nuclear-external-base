#include "pThread.h"

void pThread::Enable()
{
	_is_on = true;
}

void pThread::Disable()
{
	_is_on = false;
}

void pThread::Destroy()
{
	_die = true;
}

void pThread::SetInterval(int64_t miliseconds)
{
	_interval = miliseconds;
}
