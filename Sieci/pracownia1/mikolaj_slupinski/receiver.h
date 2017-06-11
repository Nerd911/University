//Mikołaj Słupiński (280025)

#ifndef RECEIVER_H
#define RECEIVER_H 1
#include <sys/select.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>


struct Config{
  int sockfd;
  fd_set fd;
};

struct Packet{
  char ipAddr[20];
  int ttl;
  int sequence;
  int id;
  int timeval;
  int type;
};

int getPacket(int sockfd, u_int8_t buffer[], struct Packet* result);
bool isValidPacket(struct Packet packet, int pid, int seq);
struct Config getConfig(int sockfd);
int waitForReply(struct Config cfg, int waittime);
#endif
