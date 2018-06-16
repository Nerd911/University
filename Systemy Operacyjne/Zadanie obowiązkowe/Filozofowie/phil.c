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
#include <semaphore.h>

#define PHILOSOPHERS_NUM 5
#define RIGHT(x) ((x + 1) % PHILOSOPHERS_NUM)
sem_t* forks[PHILOSOPHERS_NUM];
pid_t children[PHILOSOPHERS_NUM];

static char philosophers[PHILOSOPHERS_NUM][20] = {
  "Marks",
  "Sokrates",
  "Nietzsche",
  "Volter",
  "Schopenhauer"
};

void handler(int sig) {
	for (int i = 0; i < PHILOSOPHERS_NUM; i++) {
		char idx[2];
		sprintf(idx, "%d", i);
		if (sem_unlink(idx) < 0) {
			perror("Wykonanie sem_unlink zawiodło");
		}
		fprintf(stdout, "Anulowano semafor nr %d\n", i);
		if (kill(children[i], SIGINT) < 0)
    	perror("Wykonanie kill zawiodło");
		fprintf(stdout, "Proces potomny nr %d został zakończony\n", i);
	}
	exit(0);
}

int main() {
	struct sigaction act;
	act.sa_handler = handler;
	sigaction(SIGINT, &act, NULL);
	for (int i = 0; i < PHILOSOPHERS_NUM; i++){
		char idx[1];
		sprintf(idx, "%d", i);
		forks[i] = sem_open(idx, O_CREAT, S_IRWXU, 1);
	}
	for (int i = 0; i < PHILOSOPHERS_NUM; i++){
		if ((children[i] = fork()) < 0) {
			perror("Wykonanie fork zawiodło");
			exit(EXIT_FAILURE);
		}

		if (children[i] == 0) {
			char idx[1];
			sprintf(idx, "%d", i);
			char* args[] = {"./phil_child", idx, philosophers[i], (char*)0};
			if (execv("./phil_child", args) < 0) {
				perror("Wykonanie execv zawiodło");
				exit(EXIT_FAILURE);
			}
		}
	}
	while(1);
	return 0;
}
