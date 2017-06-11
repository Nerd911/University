//
// Created by Mikołaj Słupiński on 08.01.16.
//

#include <pcap/pcap.h>
#include "packetCapturing.h"
#include "packetPrinting.h"
#include <net/ethernet.h>
#include <netinet/ip.h>

void setOutput(FILE* f){
    output = f;
}

void processPacket(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer){
    int s = header->len;
    struct iphdr *IPHdr = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    
         if (IPHdr->protocol == TCP_HDR)  printTCP(buffer, s, output, &addresses.source, &addresses.destination);
    else if (IPHdr->protocol == UDP_HDR)  printUDP(buffer, s, output, &addresses.source, &addresses.destination);
    else if (IPHdr->protocol == ICMP_HDR) printICMP(buffer, s, output, &addresses.source, &addresses.destination);
}
