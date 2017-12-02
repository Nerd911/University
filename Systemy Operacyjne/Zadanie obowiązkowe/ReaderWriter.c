#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define PHILOSOPHERS_NUM 5
#define LEFT(x) ((x + PHILOSOPHERS_NUM - 1) % PHILOSOPHERS_NUM)
#define RIGHT(x) ((x + 1) % PHILOSOPHERS_NUM)
#define THINKING 1
#define EATING 2
#define HUNGRY 3

static char philosophers[PHILOSOPHERS_NUM][20] = {
  "Marks",
  "Sokrates",
  "Nietzsche",
  "Volter",
  "Schopenhauer"
};

static char thoughts[PHILOSOPHERS_NUM][20] = {
  "sensie życia",
  "spaghetti",
  "komunizmie",
  "religii",
  "równości"
};

typedef struct parameters {
  int counter;
  int pos;
  sem_t* forks;
  sem_t* lockPtr;
} Parameters;

void think(int position)
{
  size_t subjectNr = rand() % PHILOSOPHERS_NUM;
  printf("%s rozmyśla o %s.\n", philosophers[position], thoughts[subjectNr]);
}

void eat(int position)
{
  printf("%s je spaghetti.\n", philosophers[position]);
}

void initSemaphores(sem_t forks[], sem_t* lockPtr, size_t forksNum) {
  size_t i;
  for (i = 0; i < forksNum; ++i)
    sem_init(forks + i, 0, 1);
  sem_init(lockPtr, 0, forksNum - 1);
}

void* philosopher(void* parameters) {
  size_t i;
  Parameters* self = (Parameters*)parameters;
  for(i = 0; i < 3; ++i){
    sem_wait(self->lockPtr);
    sem_wait(self->forks + self->pos);
    sem_wait(self->forks + RIGHT(self->pos));
    eat(self->pos);
    sem_post(self->forks + self->pos);
    sem_post(self->forks + RIGHT(self->pos));
    sem_post(self->lockPtr);
  }
  think(self->pos);
  pthread_exit(NULL);
}

void runAll(pthread_t threads[], sem_t forks[], sem_t* lockPtr,
            size_t philosophersNum) {
  size_t sizeOfParameters = sizeof(Parameters);
  size_t i;
  for (i = 0; i < philosophersNum; ++i) {
    Parameters* parameters = (Parameters*)malloc(sizeOfParameters);
    parameters->counter = philosophersNum;
    parameters->pos = i;
    parameters->lockPtr = lockPtr;
    parameters->forks = forks;

    pthread_create(threads + i, NULL, philosopher, (void*)parameters);
  }
}

int main() {
  sem_t lock;
  sem_t forks[PHILOSOPHERS_NUM];
  pthread_t threads[PHILOSOPHERS_NUM];

  initSemaphores(forks, &lock, PHILOSOPHERS_NUM);
  runAll(threads, forks, &lock, PHILOSOPHERS_NUM);
  pthread_exit(NULL);
}
