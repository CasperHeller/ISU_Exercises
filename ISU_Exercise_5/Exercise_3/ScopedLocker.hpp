#pragma once
#include <pthread.h>

class ScopedLocker
{
public:
	ScopedLocker(pthread_mutex_t* mutex);
	~ScopedLocker();
private:
	pthread_mutex_t* lock_;
};
