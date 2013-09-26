#include "ScopedLocker.hpp"	

ScopedLocker::ScopedLocker(pthread_mutex_t* mutex)
{
	lock_ = mutex;
	pthread_mutex_lock(lock_);
}

ScopedLocker::~ScopedLocker()
{
	pthread_mutex_unlock(lock_);
}
