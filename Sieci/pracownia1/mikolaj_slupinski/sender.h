//Mikołaj Słupiński (280025)

#ifndef SENDER_H
#define SENDER_H 1
#include "utils.h"

int sendPacket(int sockfd, int ttl, char* ipAddr, int id,  int sequence);
struct sockaddr_in getRecipient(char* ipAddr);
struct icmphdr createICMPHeader(int id, int sequence);

#endif
