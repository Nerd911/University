//
// Created by Mikołaj Słupiński on 11.01.16.
//

#include <string.h>
#include "packetPrinting.h"
#include <arpa/inet.h>
#include <netinet/udp.h>      //Declarations for UDP header
#include <netinet/tcp.h>      //Declarations for TCP header
#include <netinet/ip.h>       //Declarations for IP header
#include <netinet/ip_icmp.h>  //Declarations for ICMP header
#include <net/ethernet.h>     //Declarations for Ethernet header

void printEthernetHeader(const unsigned char* buffer, FILE* output){
    /*
     *This function prints the content of Ethernet header.
     */
    struct ethhdr *ethHdr = (struct ethhdr *)buffer;

    fprintf(output, "\n");
    fprintf(output, "ETHERNET HEADER\n");
    fprintf(output, "    >Destination MAC Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", ethHdr->h_dest[0], ethHdr->h_dest[1], ethHdr->h_dest[2], ethHdr->h_dest[3], ethHdr->h_dest[4], ethHdr->h_dest[5] );
    fprintf(output, "    >Source MAC Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", ethHdr->h_source[0], ethHdr->h_source[1], ethHdr->h_source[2], ethHdr->h_source[3], ethHdr->h_source[4], ethHdr->h_source[5] );
    fprintf(output, "    >Protocol                : %u \n", (unsigned short)ethHdr->h_proto);
}

void printIPHeader(const unsigned char* buffer, FILE* output, struct sockaddr_in *source, struct sockaddr_in *destination){
    /*
     *This function prints the content of an IP Header.
     */
    printEthernetHeader(buffer, output);

    struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr) );

    memset(source, 0, sizeof(*source));
    source->sin_addr.s_addr = iph->saddr;

    memset(destination, 0, sizeof(*destination));
    destination->sin_addr.s_addr = iph->daddr;

    fprintf(output, "\n");
    fprintf(output, "IP Header\n");
    fprintf(output, "    >IP Version              : %u\n",(unsigned int)iph->version);
    fprintf(output, "    >IP Header Length        : %u Bytes\n",((unsigned int)(iph->ihl))*4);
    fprintf(output, "    >Type Of Service         : %u\n",(unsigned int)iph->tos);
    fprintf(output, "    >IP Total Length         : %u  Bytes\n",ntohs(iph->tot_len));
    fprintf(output, "    >Identification          : %u\n",ntohs(iph->id));
    fprintf(output, "    >TTL                     : %u\n",(unsigned int)iph->ttl);
    fprintf(output, "    >Protocol                : %u\n",(unsigned int)iph->protocol);
    fprintf(output, "    >Checksum                : %u\n",ntohs(iph->check));
    fprintf(output, "    >Source IP               : %s\n" , inet_ntoa(source->sin_addr) );
    fprintf(output, "    >Destination IP          : %s\n" , inet_ntoa(destination->sin_addr) );
}

void printTCP(const u_char* buffer, int size, FILE* output, struct sockaddr_in *source, struct sockaddr_in *destination){
    /*
     *This function prints the content of a TCP packet.
     */
    struct iphdr *IPHdr = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    unsigned IPHeaderLen = IPHdr->ihl*4;

    struct tcphdr *TCPHdr =(struct tcphdr*)(buffer + IPHeaderLen + sizeof(struct ethhdr));

    int headerSize =  sizeof(struct ethhdr) + IPHeaderLen + TCPHdr->doff * 4;

    fprintf(output, "\n\n************************TCP PACKET**************************\n");

    printIPHeader(buffer, output, source, destination);

    fprintf(output, "\nTCP Header\n");
    fprintf(output, "    >Source Port             : %u\n", ntohs(TCPHdr->source));
    fprintf(output, "    >Destination Port        : %u\n", ntohs(TCPHdr->dest));
    fprintf(output, "    >Sequence Number         : %u\n", ntohl(TCPHdr->seq));
    fprintf(output, "    >Acknowledge Number      : %u\n", ntohl(TCPHdr->ack_seq));
    fprintf(output, "    >Header Length           : %u Bytes\n", (unsigned int) TCPHdr->doff * 4);
    fprintf(output, "    >Urgent Flag             : %u\n", (unsigned int) TCPHdr->urg);
    fprintf(output, "    >Acknowledgement Flag    : %u\n", (unsigned int) TCPHdr->ack);
    fprintf(output, "    >Push Flag               : %u\n", (unsigned int) TCPHdr->psh);
    fprintf(output, "    >Reset Flag              : %u\n", (unsigned int) TCPHdr->rst);
    fprintf(output, "    >Synchronise Flag        : %u\n", (unsigned int) TCPHdr->syn);
    fprintf(output, "    >Finish Flag             : %u\n", (unsigned int) TCPHdr->fin);
    fprintf(output, "    >Window                  : %u\n", ntohs(TCPHdr->window));
    fprintf(output, "    >Checksum                : %u\n", ntohs(TCPHdr->check));
    fprintf(output, "    >Urgent Pointer          : %d\n", TCPHdr->urg_ptr);
    fprintf(output, "\n");
    fprintf(output, "                        DATA Dump                         ");
    fprintf(output, "\n");

    fprintf(output, "IP Header\n");
    printHexData(buffer,IPHeaderLen, output);

    fprintf(output, "TCP Header\n");
    printHexData(buffer+IPHeaderLen, TCPHdr->doff * 4, output);

    fprintf(output, "Data Payload\n");
    printHexData(buffer + headerSize, size - headerSize, output);

    fprintf(output, "\n************************************************************");
}

void printUDP(const u_char* buffer, int size, FILE* output, struct sockaddr_in *source, struct sockaddr_in *destination){
    /*
     *This function prints the content of an UDP packet.
     */
    struct iphdr *IPHdr = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    unsigned IPHeaderLen = IPHdr->ihl*4;

    struct udphdr *UDPHdr = (struct udphdr*)(buffer + IPHeaderLen  + sizeof(struct ethhdr));

    int headerSize =  sizeof(struct ethhdr) + IPHeaderLen + sizeof(UDPHdr);

    fprintf(output, "\n\n************************UDP PACKET**************************\n");

    printIPHeader(buffer, output, source, destination);

    fprintf(output, "\nUDP Header\n");
    fprintf(output, "    >Source Port             : %u\n", ntohs(UDPHdr->source));
    fprintf(output, "    >Destination Port        : %u\n", ntohs(UDPHdr->dest));
    fprintf(output, "    >UDP Length              : %u\n", ntohs(UDPHdr->len));
    fprintf(output, "    >UDP Checksum            : %u\n", ntohs(UDPHdr->check));

    fprintf(output, "\n");
    fprintf(output, "IP Header\n");
    printHexData(buffer, IPHeaderLen, output);

    fprintf(output, "UDP Header\n");
    printHexData(buffer+IPHeaderLen, sizeof(UDPHdr), output);

    fprintf(output, "Data Payload\n");

    printHexData(buffer + headerSize, size - headerSize, output);

    fprintf(output, "\n************************************************************");
}

void printHexData(const u_char* data, int size, FILE* output){
    /*
     * Prints the data contained in a captured package.
     * Left column consists of the hex values and the right one presents printable characters.
     */
    int i, j;
    for(i=0; i < size; ++i){
        if( i && !(i%16)){
            fprintf(output, "         ");
            for(j=i - 16; j<i; ++j){
                if(data[j] >= 32 && data[j] <= 128)
                    fprintf(output, "%c", data[j]); //if its a printable character

                else fprintf(output, "."); //otherwise print a dot
            }
            fprintf(output, "\n");
        }

        if(!(i%16)) fprintf(output, "   ");
        fprintf(output, " %02X", (unsigned int)data[i]);

        if(i == size - 1){
            for(j=0; j < 15 - i%16; ++j)
                fprintf(output, "   ");

            fprintf(output, "         ");

            for(j = i - i%16; j <= i; ++j){
                if(data[j]>=32 && data[j]<=128)
                    fprintf(output, "%c", data[j]);
                else
                    fprintf(output, ".");
            }
            fprintf(output, "\n" );
        }
    }
}

void printICMP(const u_char* buffer, int size, FILE* output, struct sockaddr_in *source, struct sockaddr_in *destination){
    /*
     *This function prints the content of an ICMP package.
     */
    struct iphdr *IPHdr = (struct iphdr *)(buffer  + sizeof(struct ethhdr));
    unsigned IPHeaderLen = IPHdr->ihl * 4;

    struct icmphdr *ICMPHdr = (struct icmphdr *)(buffer + IPHeaderLen  + sizeof(struct ethhdr));

    int headerSize =  sizeof(struct ethhdr) + IPHeaderLen + sizeof ICMPHdr;

    fprintf(output , "\n\n***********************ICMP PACKET*************************\n");

    printIPHeader(buffer, output, source, destination);

    fprintf(output , "\n");

    fprintf(output, "ICMP Header\n");
    fprintf(output, "    >Type                    : %d",(unsigned int)(ICMPHdr->type));

    if ((unsigned int)(ICMPHdr->type) == 11)
        fprintf(output, " (TTL Expired)");

    else if ((unsigned int)(ICMPHdr->type) == ICMP_ECHOREPLY)
        fprintf(output, " (ICMP Echo Reply)");


    fprintf(output, "\n");
    fprintf(output, "    >Code                    : %d\n",(unsigned int)(ICMPHdr->code));
    fprintf(output, "    >Checksum                : %d\n",ntohs(ICMPHdr->checksum));
    fprintf(output, "\n");

    fprintf(output, "IP Header\n");
    printHexData(buffer, IPHeaderLen, output);

    fprintf(output, "UDP Header\n");
    printHexData(buffer + IPHeaderLen , sizeof(ICMPHdr), output);

    fprintf(output, "Data Payload\n");

    printHexData(buffer + headerSize , (size - headerSize), output);

    fprintf(output, "\n************************************************************");

}