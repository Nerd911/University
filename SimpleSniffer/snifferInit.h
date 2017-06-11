//
// Created by Mikołaj Słupiński on 08.01.16.
//

#ifndef SIMPLESNIFFER_SNIFFERINIT_H
#define SIMPLESNIFFER_SNIFFERINIT_H

#include <pcap/pcap.h>

#define PROTOCOLS_LIST_SIZE 20

int findInterface(char* devName, char *errbuf);
int parseProtocols(char* protocols);

#endif //SIMPLESNIFFER_SNIFFERINIT_H
