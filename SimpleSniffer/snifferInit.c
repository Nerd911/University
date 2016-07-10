//
// Created by Mikołaj Słupiński on 08.01.16.
//

#include "snifferInit.h"
#include <pcap/pcap.h>
#include <string.h>
#include <malloc.h>

int findInterface(char* devName, char *errbuf){
    pcap_if_t *dev;

    if(pcap_findalldevs(&dev, errbuf)){
        pcap_freealldevs(dev);
        return -1;
    }
    if(dev == NULL) return -2;

    strcpy(devName, dev->name);
    pcap_freealldevs(dev);
    return 0;
}

int parseProtocols(char* protocols){
    char temp[20] = "(";

    if (!strcmp(protocols, "all")) {
        strcpy(protocols, "(tcp or udp or icmp)");
        return 0;
    }

    int i;
    int s = 1;
    int pos;
    size_t len;

    for (i = 1; protocols[i-1]!='\0' && i != PROTOCOLS_LIST_SIZE; ++i){
        if (protocols[i] == '/' || protocols[i] == '\0'){
            pos = i - s;
            len = s*sizeof(char);

            if (!strncmp(protocols + pos, "tcp", len)  || !strncmp(protocols + pos, "TCP", len)
                || !strncmp(protocols + pos, "udp", len)  || !strncmp(protocols + pos, "UDP", len)
                || !strncmp(protocols + pos, "icmp", len) || !strncmp(protocols + pos, "ICMP", len)){
                if(pos != 0) strcat(temp, " or ");
                strncat(temp, protocols + pos, len);
            }
            else return -1;

            s = 0;
        }
        else ++s;
    }

    if (i == PROTOCOLS_LIST_SIZE && protocols[i-1] != '\0') return -2;
    strcat(temp, ")");
    strcpy(protocols, temp);
    return 0;
}