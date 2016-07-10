//
// Created by Nerd911 on 11.01.16.
//

#ifndef SIMPLESNIFFER_PACKETPRINTING_H
#define SIMPLESNIFFER_PACKETPRINTING_H

#include <stdio.h>
#include <netinet/in.h>
#include <pcap.h>
#include <sys/socket.h>

void printEthernetHeader(const u_char* buffer, FILE* output);
void printIPHeader(const u_char* buffer, FILE* output, struct sockaddr_in *source, struct sockaddr_in *destination);
void printTCP(const u_char* buffer, int size, FILE* output, struct sockaddr_in *source, struct sockaddr_in *destination);
void printUDP(const u_char* buffer, int size, FILE* output, struct sockaddr_in *source, struct sockaddr_in *destination);
void printICMP(const u_char* buffer, int size, FILE* output, struct sockaddr_in *source, struct sockaddr_in *destination);
void printHexData(const u_char* data, int size, FILE* output);
#endif //SIMPLESNIFFER_PACKETPRINTING_H
