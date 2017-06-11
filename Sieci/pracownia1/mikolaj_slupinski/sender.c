//Mikołaj Słupiński (280025)

#include "sender.h"
#include <strings.h>
#include <arpa/inet.h>

int sendPacket(int sockfd, int ttl, char* ipAddr, int id,  int sequence){
  struct sockaddr_in recipient = getRecipient(ipAddr);
  struct icmphdr icmp_header = createICMPHeader(id, sequence);
  setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));
  ssize_t bytes_sent = sendto(sockfd, &icmp_header, sizeof(icmp_header), 0, (struct sockaddr*) &recipient, sizeof(recipient));
  return -(bytes_sent < 0);
}

struct sockaddr_in getRecipient(char* ipAddr){
  struct sockaddr_in recipient;
  bzero(&recipient, sizeof(recipient));
  recipient.sin_family = AF_INET;
  inet_pton(AF_INET, ipAddr, &recipient.sin_addr);
  return recipient;
}

struct icmphdr createICMPHeader(int id, int sequence){
  struct icmphdr icmp_header;
  icmp_header.type = ICMP_ECHO;
  icmp_header.code = 0;
  icmp_header.un.echo.id = id;
  icmp_header.un.echo.sequence = sequence;
  icmp_header.checksum = 0;
  icmp_header.checksum = compute_icmp_checksum((u_int16_t*)&icmp_header, sizeof(icmp_header));
  return icmp_header;
}
