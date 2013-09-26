#ifndef VECTOR_HPP_
#define VECTOR_HPP_
//=======================================================
// Class: Vector
// contains a size_-size vector of integers.
// Use the function setAndTest to set all elements
// of the vector to a certain value and then test that
// the value is indeed correctly set
//=======================================================
#include <semaphore.h>
#include <iostream>

using namespace std;

const int SEMAPHORE_KEYS = 1;

class Vector
{
public:
   Vector(unsigned int size = 10000) : size_(size)
      {
				 
				 if (sem_init(&lock_, 0, SEMAPHORE_KEYS) != 0)
				 {
				 	 cout << "Could not init semaphore!" << endl;
				 } 
         vector_ = new int[size_];
         set(0);
      }

   ~Vector()
      {
				 if (sem_destroy(&lock_) != 0)
				 {
				 	 cout << "Could not init semaphore!" << endl;
				 } 
         delete[] vector_;
      }

   bool setAndTest(int n)
      {
				 sem_wait(&lock_);
         set(n);
				 int testValue = test(n);
				 sem_post(&lock_);
         return testValue;
      }

private:
   void set(int n)
      {
         for(unsigned int i=0; i<size_; i++) vector_[i] = n;
      }

   bool test(int n)
      {
         for(unsigned int i=0; i<size_; i++) if(vector_[i] != n) return false;
         return true;
      }

   int*           vector_;
   unsigned int   size_;
	 sem_t					lock_;
};

#endif
