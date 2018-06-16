#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>

#define FORKS_NUM 5
#define THOUGHTS_NUM 5
#define RIGHT(x) ((x + 1) % FORKS_NUM)
sem_t* left_fork;
sem_t* right_fork;

static char thoughts[THOUGHTS_NUM][20] = {
  "sensie życia",
  "spaghetti",
  "komunizmie",
  "religii",
  "równości"
};

char* name;
static int i;

void take_forks() {
	if (i > (i+1)%FORKS_NUM) {
		sem_wait(left_fork);
		fprintf(stdout, "%s bierze widelec nr %d\n", name, i);
		sem_wait(right_fork);
		fprintf(stdout, "%s bierze widelec nr %d\n", name, RIGHT(i));
	} else {
		sem_wait(right_fork);
		fprintf(stdout, "%s bierze widelec nr %d\n", name, RIGHT(i));
		sem_wait(left_fork);
		fprintf(stdout, "%s bierze widelec nr %d\n", name, i);
	}
}

void put_forks() {
	if (i > (i+1)%FORKS_NUM) {
		sem_post(right_fork);
		fprintf(stdout, "%s odkłada widelec nr%d\n", name, RIGHT(i));
		sem_post(left_fork);
		fprintf(stdout, "%s odkłada widelec nr%d\n", name, i);
	} else {
		sem_post(left_fork);
		fprintf(stdout, "%s odkłada widelec nr%d\n ", name, i);
		sem_post(right_fork);
		fprintf(stdout, "%s odkłada widelec nr%d\n", name, RIGHT(i));
	}
}

void think()
{
  size_t subjectNr = rand() % THOUGHTS_NUM;
  printf("%s rozmyśla o %s.\n", name, thoughts[subjectNr]);
	usleep(rand()%250000);
}

void eat()
{
  printf("%s je spaghetti.\n", name);
	usleep(rand()%100000);
}

int main(int argc, char** argv) {
	if (argc < 3) {
		printf("Należy dostarczyć 2 argumenty: nr i imię filozofa");
		exit(EXIT_FAILURE);
	}
	left_fork = sem_open(argv[1], O_RDWR);
	i = atoi(argv[1]);
	name = argv[2];
	char tmp[1];
	sprintf(tmp, "%d", RIGHT(i));
	right_fork = sem_open(tmp, O_RDWR);
	printf("i=%d\n", i);
	srand(time(NULL));
	while(1) {
		think();
		take_forks();
		fprintf(stdout, "%s próbuje wziąć swoje widelce\n", name);
		eat();
		put_forks();
		fprintf(stdout, "%s odkłada swoje widelce\n", name);
	}
	return 0;
}
