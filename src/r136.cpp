#include "r136.h"

AnimateStatus next_status(AnimateStatus status)
{
	return static_cast<AnimateStatus>(to_value(status) + 1);
}

AnimateStatus operator++(AnimateStatus& status, int)
{
	AnimateStatus temp = status;
	status = next_status(status);
	return temp;
}

AnimateStatus& operator++(AnimateStatus& status)
{
	status = next_status(status);
	return status;
}


// This following section is a little bit of nastiness due to major OS platforms not agreeing in 2021, on one approach to idle-wait for a number of milliseconds
#ifdef _WIN32
#include <windows.h>
void sleep_ms(int n)
{
	Sleep(n);
}
#else
#include <unistd.h>
#include <map>
void sleep_ms(int n)
{
	usleep(n * 1000, );
}

#endif
