#include <sys/time.h>
#include <time.h>

long gettime_millis() {
  struct timeval now;
  gettimeofday(&now, NULL);

  long millis = (long)(now.tv_sec * 1000) + (long)(now.tv_usec / 1000);
  return millis;
}