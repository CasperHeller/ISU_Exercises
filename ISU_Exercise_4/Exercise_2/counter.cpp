#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

// Global variables
unsigned int shared;

// Prototypes
void *printThread(void*);
void *incrementThread(void*);

int main ()
{
  pthread_t threadRead, threadInc;
  unsigned int shareduint;
  
  cout << "Creating threads..." << endl;
  if ( pthread_create(&threadRead, NULL, printThread, NULL) ||
       pthread_create(&threadInc, NULL, incrementThread, NULL) )
  {
    cout << "Could not create thread ID" << endl;
    cout << "Now terminating..." << endl;
    return 1;
  }

  pthread_join(threadRead, NULL);
  pthread_join(threadInc, NULL);
  
  return 0;
}

void *printThread(void* arg)
{
  while(shared < 10)
  {
    cout << "Reading the value " << shared << endl;
    sleep(1);
  }
  
  cout << "Terminating printThread" << endl;
  pthread_exit(NULL);
}

void *incrementThread(void* arg)
{
  while(shared < 10)
  {
    shared++;
    sleep(1);
  }
  
  cout << "Terminating incrementThread " << endl;
  pthread_exit(NULL);
}

