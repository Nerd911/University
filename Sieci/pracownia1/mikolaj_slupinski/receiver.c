//Mikołaj Słupiński (280025)

#include "receiver.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stddef.h>

int getPacket(int sockfd, u_int8_t buffer[], struct Packet* result){
  struct sockaddr_in sender;
  socklen_t senderLen = sizeof(sender);
  u_int8_t* buffPtr = buffer;
  ssize_t packLen = recvfrom(sockfd, buffer, IP_MAXPACKET, MSG_DONTWAIT, (struct sockaddr*)&sender, &senderLen);
  if(packLen < 0)
    return -1;

  inet_ntop(AF_INET, &(sender.sin_addr), result->ipAddr, sizeof(result->ipAddr));

  struct iphdr* ipHdr = (struct iphdr*)buffPtr;
  buffPtr += 4 * ipHdr->ihl + 8;

  struct ip* recPck = (struct ip*)buffPtr;
  buffPtr += recPck->ip_hl * 4;

  struct icmp* recICMP = (struct icmp*) buffPtr;

  u_int8_t* icmpPckt = buffer + 4 * ipHdr->ihl;
  struct icmphdr* icmpHeader = (struct icmphdr*)icmpPckt;

  result->type = icmpHeader->type;

  if(icmpHeader->type == ICMP_TIME_EXCEEDED){
    result->sequence = recICMP->icmp_seq;
    result->id = recICMP->icmp_id;
    result->ttl = result->sequence / 3 + 1;
  }

  else if(icmpHeader->type == ICMP_ECHOREPLY){
    result->sequence = icmpHeader->un.echo.sequence;
    result->id = icmpHeader->un.echo.id;
    result->ttl = result->sequence / 3 + 1;
  }

  return 0;
}

bool isValidPacket(struct Packet packet, int pid, int seq){
  return packet.id == pid && packet.sequence >= seq;
}

struct Config getConfig(int sockfd){
  struct Config res;
  res.sockfd = sockfd;
  FD_ZERO(&res.fd);
  FD_SET(res.sockfd, &res.fd);
  return res;
}

int waitForReply(struct Config cfg, int waittime){
	struct timeval wait;
	wait.tv_sec = waittime/10000000; wait.tv_usec = waittime%10000000;

	return select(cfg.sockfd+1, &cfg.fd, NULL, NULL, &wait);
}
