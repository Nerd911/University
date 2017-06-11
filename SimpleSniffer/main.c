//
// Created by Mikołaj Słupiński on 08.01.16.
//
#include <stdio.h>
#include "snifferInit.h"
#include "packetCapturing.h"
#include <getopt.h>
#include <string.h>
#include <stdlib.h>

#define PATH_SIZE 100
#define FILTER_SIZE 100

void printHelp(char* path);

int main(int argc, char* argv[]){
    char errbuff[PCAP_ERRBUF_SIZE];
    char interface[10] = "";
    char outputMode[] = "w";
    char filePath[PATH_SIZE];
    char protocol[PROTOCOLS_LIST_SIZE] = "all";
    char filterExpression[FILTER_SIZE] = "";
    struct bpf_program filter;
    int n = -1;

    strcpy(filePath, getenv("HOME"));
    strcat(filePath, "/SnifferOutput.txt");
    printf("%s \n", filePath);

    int option = 0;
    while((option = getopt(argc, argv, "ad:hi:n:o:p:s:P:"))!=-1){
        switch(option){
            case 'a': //sets file mode to "append"
                outputMode[0] = 'a';
                break;

            case 'd': //changes the destination host
                if (filterExpression[0] != '\0') strcat(filterExpression, " and ");
                strcat(filterExpression, "dst host ");
                strcat(filterExpression, optarg);
                break;

            case 'h': //prints help
                printHelp(argv[0]);
                return 0;

            case 'i': //changes the interface
                strcpy(interface, optarg);
                break;

            case 'n': //changes the limit of iterations
                n = atoi(optarg);
                break;

            case 'o': //changes the output file path
                strcpy(filePath, optarg);
                break;

            case 'p': //changes the protocol
                strcpy(protocol, optarg);
                break;

            case 's': //changes the source host
                if (filterExpression[0] != '\0') strcat(filterExpression, " and ");
                strcat(filterExpression, "src host ");
                strcat(filterExpression, optarg);
                break;

            case 'P': // changes the port
                if(filterExpression[0] != '\0') strcat(filterExpression, " and ");
                strcat(filterExpression, "port ");
                strcat(filterExpression, optarg);
                break;

            default:
                printf("\n");
                printHelp(argv[0]);
                return 0;
        }
    }

    int parsingResult = parseProtocols(protocol);

    if (parsingResult == -1){ //checks if protocols defined by user exist, if not returns error and quits
        fprintf(stderr, "Error: wrong protocol. Available protocols are TCP, ICMP and UDP.\n");
        return 1;
    }

    if (parsingResult == -2){ //checks whether the protocol had an accurate size, if not returns error and quits
        fprintf(stderr, "Error: protocols names are too long.\n");
        return 1;
    }

    if (filterExpression[0] != '\0') strcat(filterExpression, " and ");
    strcat(filterExpression, protocol);
    FILE* output = fopen(filePath, outputMode);

    if (output == NULL){ //checks whether the file was opened, if not returns error and quits
        fprintf(stderr, "Unable to open the file.");
        return 2;
    }

    setOutput(output);

    if(interface[0] == '\0'){ //if interface is unspecified looks for available interfaces
        int interfaceFound = findInterface(interface, errbuff);
        switch(interfaceFound){
            case -1:
                fprintf(stderr, "Error: %s\n", errbuff);
                return 3;

            case -2:
                fprintf(stderr, "Error: Could not find any devices.\n");
                return 3;
        }
    }

    bpf_u_int32 net, mask;
    if(pcap_lookupnet(interface, &net, &mask, errbuff) == -1){
        fprintf(stderr, "Warning: Couldn't get mask for the device.\n");
        fprintf(stderr, "         %s", errbuff);
        net = 0;
        mask = 0;
    }

    pcap_t *handle = pcap_create(interface, errbuff);

    if(handle == NULL){
        fprintf(stderr, "Cannot open %s\n", interface);
        fprintf(stderr, "Error: %s\n", errbuff);
        return 3;
    }

    int activated = pcap_activate(handle);
    switch(activated){
        case PCAP_WARNING:
            pcap_perror(handle, "Warning: ");
            break;

        case PCAP_WARNING_PROMISC_NOTSUP:
            fprintf(stderr, "Warning: Promiscuous mode not supported.\n");
            break;

        case PCAP_ERROR_ACTIVATED:
            fprintf(stderr, "Error: handle ha been already activated.\n");
            return 4;

        case PCAP_ERROR_NO_SUCH_DEVICE:
            fprintf(stderr, "Error: the device doesn't exist.\n");
            return 4;

        case PCAP_ERROR_PERM_DENIED:
            fprintf(stderr, "Error: the process doesn't have permission to open the capture source.\n");
            return 4;

        case PCAP_ERROR:
            pcap_perror(handle, "Error: ");
            return 4;
    }

    if(pcap_compile(handle, &filter, filterExpression, 0, net) == -1){
        fprintf(stderr, "Error: Couldn't parse filter expression: %s.\n", filterExpression);
        pcap_perror(handle, "       ");
        return 5;
    }

    if(pcap_setfilter(handle, &filter) == -1){
        fprintf(stderr, "Error: Couldn't apply filter expression: %s.\n", filterExpression);
        pcap_perror(handle, "       ");
        return 5;
    }
    printf("%s", filterExpression);


    pcap_loop(handle, n, processPacket, NULL); //enters the main sniffing loop

    return 0;
}

void printHelp(char* path) {
    printf("SimpleSniffer\n\n");
    printf("SimpleSniffer is a simple web sniffer. By default it captures TCP, ICMP and UDP packets and saves them to the file \"~/SnifferOutput.txt\". The program ands when it receives a SYGINT signal or when it captures the number of packets defined by user.\n\n");

    printf("Usage:\n");
    printf("%s [-ah] [-d host] [-i interface] [-n limit] [-o file] [-p tcp/udp/icmp] [-s host] [-P port]\n\n", path);
    printf("Options:\n\n");
    printf("-a                 Appends output of the file instead of overwriting it.\n");
    printf("-d host            Captures only the packets from the destination host defined by user.\n");
    printf("-h                 Prints this help screen and then terminates the program.\n");
    printf("-i interface       Sets the interface to the one defined by user. By default interface is set to the first interface that program encounters on interface list.\n");
    printf("-n limit           Captures the number of packets defined by user.\n");
    printf("-o file            Sets the file path to the one defined by user. String must be an absolute path. By default program saves its output to \"~/SnifferOutput.txt\"\n");
    printf("-p tcp/udp/icmp    Sets the protocol to the one defined by user. User can select multiple protocols separating them with slashes. By default captures UCP, TCP and ICMP packets.\n");
    printf("-s host            Captures only the packets from the source host defined by user.\n");
    printf("-P port            Captures only the packets from the destination port defined by user.\n");
}
