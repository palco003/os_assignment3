#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define PTHREAD_SYNC

int SharedVariable = 0;
pthread_mutex_t lock;
pthread_barrier_t barr;

void SimpleThread(int which) {
  int num, val;
  for(num = 0; num < 20; num++) {
    if (random() > RAND_MAX / 2){
      usleep(10);
    }
    val = SharedVariable;
    printf("*** thread %d sees value %d\n", which, val);
    SharedVariable = val + 1;
  }
  val = SharedVariable;
  printf("Thread %d sees final value %d\n", which, val);

}

/*
 * The main function validates command line input
 * It will exit if given the wrong number or type of argument
 * It then creates the number of threads specified
 * Finally, it waits for the threads to finish
 * Credit: borrowed some ideas from the provided website
 * http://pages.cs.wisc.edu/~travitch/pthreads_primer.html
 */
int main(int argc, char const *argv[])
{
  int threads = 0;
  pthread_t thread_ID;

  if(argc != 2)
  {
    perror("Wrong number of arguments.\n");
    exit(1);
  } 
  else 
  {
    if (sscanf(argv[1], "%d", &threads) != 1)
    {
      perror("Invalid input\n");
      exit(1);
    } 
    pthread_t thr[threads];

    if(pthread_barrier_init(&barr, NULL, threads))
    {
      printf("Could not create a barrier\n");
      return -1;
    }
    
    for(int i = 0; i < threads; i++)
    {
      if(pthread_create(&thr[i], NULL, (void *) SimpleThread, (void *)(intptr_t) i))
      {
        printf("Could not create thread %d\n", i);
        return -1;
      }
    }
    for(int i = 0; i < threads; i++)
    {
      if(pthread_join(thr[i], NULL))
      {
        printf("Could not join thread %d\n", i);
        return -1;
      }
    }
  }
  return 0;
}