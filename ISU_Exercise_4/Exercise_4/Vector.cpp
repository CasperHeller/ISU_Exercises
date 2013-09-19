#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "Vector.hpp"

using namespace std;

// Global variables
Vector data;
int msSleep;

// Prototypes
void *writer(void* tid);

int main ()
{
  int threadAmount;
  
  while(threadAmount > 100 || threadAmount < 1)
  {
    cout << "Enter an amount of threads (1-100): ";
    cin >> threadAmount;
  }
  
  while(msSleep > 1000 || msSleep < 1)
  {
    cout << "Enter an sleep time for threads (1-1000) specified in ms: ";
    cin >> msSleep;
  }
  
  pthread_t threads[threadAmount];
  
  cout << "Creating " << threadAmount << " threads..." << endl;
  for(int i = 0; i < threadAmount; i++)
  {
    if ( pthread_create(&threads[i], NULL, writer, (void*)i) )
    {
      cout << "Could not create thread ID" << endl;
      cout << "Now terminating..." << endl;
      return 1;
    }
  }

  for(int i = 0; i < threadAmount; i++)
  {
    pthread_join(threads[i], NULL);
  }

  return 0;
}

void *writer(void* tid)
{
  int threadID = (int)(tid);
  
  for(;;)
  {
    if (data.setAndTest(threadID))
      cout << threadID << ": All set properly." << endl;
    else
      cout << threadID << ": inconsistenty detected!" << endl;
    
    usleep(msSleep*1000);
  }
  
  cout << "Terminating writerThread" << endl;
  pthread_exit(NULL);
}
