#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

// Constants
const int THREAD_AMOUNT = 2;

// Prototypes
void *printThread(void* tid);

int main ()
{
  pthread_t threads[THREAD_AMOUNT];

  for(int i = 0; i < THREAD_AMOUNT; i++)
  {
    cout << "Creating thread with ID: " << i << endl;
    if (pthread_create(&threads[i], NULL, printThread, (void*)(i))) 
    {
      cout << "Could not create thread ID: " << i << endl;
      cout << "Now terminating..." << endl;
      return 1;
    }
  }
  
  for(int i = 0; i < THREAD_AMOUNT; i++)
  {
    pthread_join(threads[i], NULL);
  }
  
  return 0;
}

void *printThread(void* tid)
{
  
  int threadID = (int)(tid);
  
  for(int i = 0; i < 10; i++)
  {
    cout << "Hello #" << i << " from thread " << threadID << endl;
    sleep(1);
  }
  
  cout << "Terminating thread " << threadID << endl;
  pthread_exit(NULL);
}

