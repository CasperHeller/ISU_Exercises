#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include "Vector.hpp"
#include "ScopedLocker.hpp"

using namespace std;

// Global variables
Vector data;
pthread_mutex_t lock;

// Prototypes
void *writer(void* tid);

int main ()
{
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
	  cout << "Could not init mutex" << endl;
    cout << "Now terminating..." << endl;
    return EXIT_FAILURE;
	}

  int threadAmount = 0;
  
  while(threadAmount > 100 || threadAmount < 1)
  {
    cout << "Enter an amount of threads (1-100): ";
    cin >> threadAmount;
  }
  
  pthread_t threads[threadAmount];
  int tid[threadAmount];  

  cout << "Creating " << threadAmount << " threads..." << endl;
  for(int i = 0; i < threadAmount; i++)
  {
    tid[i] = i;
    if ( pthread_create(&threads[i], NULL, writer, (void*)(tid+i)) )
    {
      cout << "Could not create thread ID" << endl;
      cout << "Now terminating..." << endl;
      return EXIT_FAILURE;
    }
  }

  for(int i = 0; i < threadAmount; i++)
  {
    pthread_join(threads[i], NULL);
  }

	if (pthread_mutex_destroy(&lock) != 0)
	{
	  cout << "Could not destroy mutex" << endl;
    cout << "Now terminating..." << endl;
    return EXIT_FAILURE;
	}

  return EXIT_SUCCESS;
}

void *writer(void* tid)
{
  int threadID = *(int*)(tid);
  
  for(int i = 0; i < 5; i++)
  {
		int err;
		{
			ScopedLocker scopeLock(&lock);
			err = data.setAndTest(threadID);
		}
		
    if (err)
      cout << threadID << ": All set properly." << endl;
    else
      cout << threadID << ": inconsistenty detected!" << endl;
    
    sleep(1);
  }
  
  cout << "Terminating writerThread" << endl;
  pthread_exit(NULL);
}
