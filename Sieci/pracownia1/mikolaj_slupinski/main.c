//Mikołaj Słupiński (280025)
#include "receiver.h"
#include "utils.h"
#include "sender.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void printHelp(char *progName){
  printf("\nUSAGE:\n");
  printf("%s host\n", progName);
  printf("\nArguments:\n");
  printf("host\tThe host to traceroute to\n");
  printf("\nExample:\n");
  printf("%s 192.168.1.1\n", progName);

}

int checkArguments(int argc, char* argv[], char* errmsg){
  if(argc == 1){
		strcpy(errmsg, "Too few arguments.");
		return EINVAL;
	}

	if(!isValidIpAddress(argv[1])){
		strcpy(errmsg, "IP adress of host is not valid.");
		return EINVAL;
	}
  return 0;
}

int print(struct Packet packets[], int pcntr){
  if(pcntr == 0){
    printf("*\n");
    return 0;
  }

  char *addr0 = packets[0].ipAddr;
  char *addr1 = packets[1].ipAddr;
  char *addr2 = packets[2].ipAddr;

  int average;

  printf("%s ", addr0);

  if(pcntr > 1 && strcmp(addr0, addr1))
    printf("%s ", addr1);

  if(pcntr > 2 && strcmp(addr0, addr2) && strcmp(addr1, addr2))
    printf("%s ", addr2);

  if(pcntr < 3)
    printf("???\n");
  else if(pcntr == 3){
    average = (packets[0].timeval + packets[1].timeval + packets[2].timeval)/3;
    printf("%dms\n", average);
  }

  return 0;
}

void collectPackets(int sockfd, struct Packet packets[], int pid, int seq, int* pcntr, struct timespec* ts){
  u_int8_t buffer[IP_MAXPACKET+1];
  do{
    if(getPacket(sockfd, buffer, &packets[*pcntr]) == -1)
      break;
    if(!isValidPacket(packets[*pcntr], pid, seq))
      continue;
    packets[(*pcntr)++].timeval = deltaTime(ts) / 1000000;
    if(*pcntr > 2)
      break;
  }while(deltaTime(ts) < 1000000000);
}

int getResponse(int sockfd, int pid, int seq){
  struct Packet packets[3];
  int pcntr = 0;
  int count;
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC_RAW, &ts);

  do{
    struct Config cfg = getConfig(sockfd);
    count = waitForReply(cfg, 1000000 - deltaTime(&ts)/1000);
    if(count < 0)
      return -1;
    if (count == 0)
      break;
    collectPackets(sockfd, packets, pid, seq, &pcntr, &ts);
    if (pcntr == 3)
      break;
  }while (deltaTime(&ts) < 1000000000);

  print(packets, pcntr);
  return packets[0].type == ICMP_ECHOREPLY;
}

int trace(int sockfd, char* ipAddr, int pid, int seq, int ttl){
  for(int i = 0; i < 3; ++i)
    sendPacket(sockfd, ttl, ipAddr, pid, seq+i);
  return getResponse(sockfd, pid, seq);
}

int traceroute(char* ipAddr){
  int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

  if (sockfd < 0) {
		return EXIT_FAILURE;
	}
  int pid = getpid();
  int seq = 0;
  int ttl;
  for(ttl = 1; ttl <= 30; ++ttl){
    printf("%d. ", ttl);
    if(trace(sockfd, ipAddr, pid, seq, ttl) == 1)
      return 0;
    seq += 3;
  }
  return 0;
}

int main(int argc, char* argv[]){
  char errmsg[200];
  if(checkArguments(argc, argv, errmsg) != 0){
    fprintf(stderr, "Error: %s\n", errmsg);
    printHelp(argv[0]);;
    return EXIT_FAILURE;
  }

  char* addr = argv[1];

  int tr = traceroute(addr);
  if(tr != 0){
    fprintf(stderr, "Error: %s\n", strerror(errno));
    return tr;
  }

	return EXIT_SUCCESS;
}
