#include <iostream>
#include <pthread.h>
#include <cstdlib>

using namespace std;

// Forward declaration
void *carFunc(void*);
void *entryFunc(void*);
void *exitFunc(void*);

// Constants
const int CAR_AMOUNT = 1;
const int PARKING_SPACES = 1;

// Global variables
pthread_mutex_t entryLock, exitLock;
pthread_cond_t entrySignal, exitSignal;

bool entryWaiting = 0;
bool exitWaiting = 0;
bool entryIsOpen = 0;
bool exitIsOpen = 0;

int main()
{
    cout << "PLCS started." << endl;

    // Error variable
    int err = 0;

    // Initializing mutexes
    if ( (err = pthread_mutex_init(&entryLock, NULL)) )
    {
        cout << "Could not initialize entryLock, ERROR: " << err << endl;
        return EXIT_FAILURE;
    }
    if ( (err = pthread_mutex_init(&exitLock, NULL)) )
    {
        cout << "Could not initialize exitLock, ERROR: " << err << endl;
        return EXIT_FAILURE;
    }

    // Initializing entry and exit threads
    pthread_t entryThread, exitThread;

    if ( (err = pthread_create(&entryThread, NULL, entryFunc, NULL)) )
    {
      cout << "Could not create entryThread, ERROR: " << err << endl;
      return EXIT_FAILURE;
    }
    if ( (err = pthread_create(&exitThread, NULL, exitFunc, NULL)) )
    {
      cout << "Could not create exitThread, ERROR: " << err << endl;
      return EXIT_FAILURE;
    }

    // Initializing car threads
    pthread_t carThread[CAR_AMOUNT];
    int carID[CAR_AMOUNT];
    for (int i = 0; i < CAR_AMOUNT; i++)
    {
        carID[i] = i+1;
        if ( (err = pthread_create(&carThread[i], NULL, carFunc, (void*)(carID+i))) )
        {
            cout << "Could not create carThread with ID " << carID+i << ", ERROR: " << err << endl;
            return EXIT_FAILURE;
        }
    }

    // Join pthreads
    if ( (err = pthread_join(entryThread, NULL)) )
    {
        cout << "Could not join entryThread, ERROR: " << err << endl;
        return EXIT_FAILURE;
    }
    if ( (err = pthread_join(exitThread, NULL)) )
    {
        cout << "Could not join exitThread, ERROR: " << err << endl;
        return EXIT_FAILURE;
    }
    for (int i = 0; i < CAR_AMOUNT; i++)
    {
        if (err = pthread_join(carThread[i], NULL))
        {
            cout << "Could not join carThread with ID " << carID+i << ", ERROR: " << err << endl;
            return EXIT_FAILURE;
        }
    }

    // Destroying mutexes
    if ( (err = pthread_mutex_destroy(&entryLock)) )
    {
        cout << "Could not destroy entryLock, ERROR: " << err << endl;
        return EXIT_FAILURE;
    }
    if ( (err = pthread_mutex_destroy(&exitLock)) )
    {
        cout << "Could not destroy exitLock, ERROR: " << err << endl;
        return EXIT_FAILURE;
    }

    cout << "PLCS ended." << endl;
    return EXIT_SUCCESS;
}

void *carFunc(void*)
{
    int ID = 0;
    // Add error-handling later
    cout << "Car " << ID << " is approaching entry gate." << endl;
    pthread_mutex_lock(&entryLock);
    entryWaiting = true;
    pthread_cond_signal(&entrySignal);
    while(!entryIsOpen)
    {
        pthread_cond_wait(&entrySignal, &entryLock);
    }
    cout << "Car " << 0 << " is now inside the parking lot." << endl;
    entryWaiting = false;
    pthread_cond_signal(&entrySignal);
    pthread_mutex_unlock(&entryLock);
}

void *entryFunc(void*)
{
    // Add error-handling later
    pthread_mutex_lock(&entryLock);
    while(!entryWaiting)
    {
        pthread_cond_wait(&entrySignal, &entryLock);
    }
    cout << "The entry gate is now open." << endl;
    entryIsOpen = true;
    pthread_cond_signal(&entrySignal);
    while(entryWaiting)
    {
        pthread_cond_wait(&entrySignal, &entryLock);
    }
    cout << "The entry gate is now closed." << endl;
    entryIsOpen = false;
    pthread_mutex_unlock(&entryLock);
}

void *exitFunc(void*)
{

}
