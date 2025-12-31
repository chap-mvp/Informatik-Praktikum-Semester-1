#include <time.h>
#include <stdbool.h>

time_t lockout_end = 0;

void lock_item(void)
{
    lockout_end = time(NULL) + 120; // 2 minutes = 120 seconds
}

bool is_locked(void)
{
    return time(NULL) < lockout_end;
}