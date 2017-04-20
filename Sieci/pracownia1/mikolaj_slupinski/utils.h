//Mikołaj Słupiński (280025)

#ifndef UTILS_H
#define UTILS_H 1

#include <stdbool.h>
#include <stdint.h>
#include <netinet/ip_icmp.h>
#include <time.h>

bool isValidIpAddress(char *ipAddress);
u_int16_t compute_icmp_checksum (const void *buff, int length);
int deltaTime(struct timespec* ts);


#endif
