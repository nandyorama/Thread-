#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include<iostream>
using namespace std;
#define max 11
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;
void *odd(void *p);
void *even(void *p);

// Print odd numbers
void *even(void *p)
{
  for(int j=2;j<max;j+=2) {
    pthread_mutex_lock( &count_mutex );
    pthread_cond_wait( &condition_var, &count_mutex );
    printf("Even--: %d\n",j);
    pthread_cond_signal( &condition_var );
    pthread_mutex_unlock( &count_mutex );
 }
}

// print even numbers
void *odd(void *p)
{
  for(int j=1;j<max;j+=2) {
    pthread_mutex_lock( &count_mutex );
    printf("Odd-: %d\n",j);
    pthread_cond_signal( &condition_var );
    pthread_cond_wait( &condition_var, &count_mutex );
    pthread_mutex_unlock( &count_mutex );
 }
}

int main()
{
 pthread_t thread1, thread2;
 pthread_create( &thread1, NULL, &odd, NULL);
 pthread_create( &thread2, NULL, &even, NULL);
 pthread_join( thread1, NULL);
 pthread_join( thread2, NULL);
 return 0;
}
