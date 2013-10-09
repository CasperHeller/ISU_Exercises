#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <semaphore.h>

using namespace std;

// Forward declaration
void *carFunc(void* carID);
void *entryFunc(void*);
void *exitFunc(void*);

// Constants
const int CAR_AMOUNT    = 5;  // Amount of car threads
const int SLEEP_TIME    = 15;  // Maximum sleeping time (seconds)
const int PARKING_SPOTS = 3;  // Amount of spots in the parking lot

// Global variables
pthread_mutex_t entryLock, exitLock, entrySpot, exitSpot;
sem_t semParking;
pthread_cond_t entrySignal, exitSignal;

bool entryWaiting = false;
bool exitWaiting = false;
bool entryIsOpen = false;
bool exitIsOpen = false;

int main()
{
    cout << "PLCS started." << endl;

    // Error variable
    int err = 0;

	// Seed rand() with time()
	srand (time(NULL));

    // Initializing mutexes and semaphores
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
    if ( (err = pthread_mutex_init(&entrySpot, NULL)) )
    {
        cout << "Could not initialize entrySpot, ERROR: " << err << endl;
        return EXIT_FAILURE;
    }
    if ( (err = pthread_mutex_init(&exitSpot, NULL)) )
    {
        cout << "Could not initialize exitSpot, ERROR: " << err << endl;
        return EXIT_FAILURE;
    }
    if ( (err = sem_init(&semParking, 0, PARKING_SPOTS)) )
    {
        cout << "Could not initialize semParking, ERROR: " << err << endl;
        return EXIT_FAILURE;
    }


    // Initializing cond signals
    if ( (err = pthread_cond_init(&entrySignal, NULL)) )
    {
        cout << "Could not initialize cond signal entry, ERROR: " << err << endl;
        return EXIT_FAILURE;
    }
    if ( (err = pthread_cond_init(&exitSignal, NULL)) )
    {
        cout << "Could not initialize cond signal exit, ERROR: " << err << endl;
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
        carID[i] = i+1; //ID should start at 1 not 0
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
        if ( (err = pthread_join(carThread[i], NULL)) )
        {
            cout << "Could not join carThread with ID " << carID+i << ", ERROR: " << err << endl;
            return EXIT_FAILURE;
        }
    }

    // Destroying mutexes and semaphores
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
    if ( (err = pthread_mutex_destroy(&entrySpot)) )
    {
        cout << "Could not destroy entrySpot, ERROR: " << err << endl;
        return EXIT_FAILURE;
    }
    if ( (err = pthread_mutex_destroy(&exitSpot)) )
    {
        cout << "Could not destroy exitSpot, ERROR: " << err << endl;
        return EXIT_FAILURE;
    }
    if ( (err = sem_destroy(&semParking)) )
    {
        cout << "Could not destroy semParking, ERROR: " << err << endl;
        return EXIT_FAILURE;
    }

    // Destroying cond signals
    if ( (err = pthread_cond_destroy(&entrySignal)) )
    {
        cout << "Could not destroy entrySignal, ERROR: " << err << endl;
        return EXIT_FAILURE;
    }
    if ( (err = pthread_cond_destroy(&exitSignal)) )
    {
        cout << "Could not destroy exitSignal, ERROR: " << err << endl;
        return EXIT_FAILURE;
    }

    cout << "PLCS ended." << endl;
    return EXIT_SUCCESS;
}

void *carFunc(void* carID)
{
    // Get the ID of the car
    int ID = *((int*)carID);

    // Loop it, the car should always try to reenter
    for (;;)
    {
        pthread_mutex_lock(&entrySpot);
        // Entry
        cout << "> Car " << ID << " is approaching entry gate." << endl;
        pthread_mutex_lock(&entryLock);
        entryWaiting = true;
        pthread_cond_signal(&entrySignal);
        while(!entryIsOpen)
        {
            pthread_cond_wait(&entrySignal, &entryLock);
        }
        cout << "> Car " << ID << " is now inside the parking lot." << endl;
        entryWaiting = false;
        pthread_cond_signal(&entrySignal);
        pthread_mutex_unlock(&entryLock);
        // Entry done
        pthread_mutex_unlock(&entrySpot);

        // Now sleep before exiting
        sleep(rand()%SLEEP_TIME+1);

        pthread_mutex_lock(&exitSpot);
        // Exit
        cout << "> Car " << ID << " is approaching exit gate." << endl;
        pthread_mutex_lock(&exitLock);
        exitWaiting = true;
        pthread_cond_signal(&exitSignal);
        while(!exitIsOpen)
        {
            pthread_cond_wait(&exitSignal, &exitLock);
        }
        cout << "> Car " << ID << " is now outside the parking lot." << endl;
        exitWaiting = false;
        pthread_cond_signal(&exitSignal);
        pthread_mutex_unlock(&exitLock);
        // Exit done
        pthread_mutex_unlock(&exitSpot);

        // Now sleep before reentry
        sleep(rand()%SLEEP_TIME+1);
    }
    pthread_exit((void*)&ID);
}

void *entryFunc(void*)
{
    // Loop so we can handle unlimited amount of requests
    for (;;)
    {
        sem_wait(&semParking);
        pthread_mutex_lock(&entryLock);
        while(!entryWaiting)
        {
            pthread_cond_wait(&entrySignal, &entryLock);
        }
        cout << "The entry gate is now open, because ";
        int carsInParking;
        sem_getvalue(&semParking, &carsInParking);
        cout << carsInParking+1 << " parking spaces are available." << endl;

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
    pthread_exit(NULL);
}

void *exitFunc(void*)
{
    // Loop so we can handle unlimited amount of requests
    for (;;)
    {
        pthread_mutex_lock(&exitLock);
        while(!exitWaiting)
        {
            pthread_cond_wait(&exitSignal, &exitLock);
        }
        cout << "The exit gate is now open." << endl;
        exitIsOpen = true;
        pthread_cond_signal(&exitSignal);
        while(exitWaiting)
        {
            pthread_cond_wait(&exitSignal, &exitLock);
        }
        cout << "The exit gate is now closed." << endl;

        int carsInParking;
        sem_getvalue(&semParking, &carsInParking);
        cout << carsInParking+1 << " parking spaces are now available." << endl;
        exitIsOpen = false;

        pthread_mutex_unlock(&exitLock);
        sem_post(&semParking);
    }
    pthread_exit(NULL);
}
