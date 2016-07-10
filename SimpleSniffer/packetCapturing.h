//
// Created by Mikołaj Słupiński on 08.01.16.
//

#ifndef SIMPLESNIFFER_PACKETCAPTURING_H
#define SIMPLESNIFFER_PACKETCAPTURING_H

#include <stdio.h>
#include <sys/types.h>
#include <pcap.h>
#include <netinet/in.h>

#define TCP_HDR 6
#define UDP_HDR 16
#define ICMP_HDR 1

static FILE* output;
static struct{
    struct sockaddr_in source, destination;
} addresses;

void setOutput(FILE* f);
void processPacket(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer);

#endif //SIMPLESNIFFER_PACKETCAPTURING_H
