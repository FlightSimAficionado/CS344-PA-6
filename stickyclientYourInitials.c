#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// CLIENT PROGRAM
// Created by hseel on 4/17/2025.
//
//
#define BUFSIZE 1024    // Buffer size for data

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <IP(ipv4)> <Port #>\n", argv[0]);
        return 0;
    }

    char ipv4[16];  // IPv4 address can be max 15 chars + /0
    strncpy(ipv4, argv[1], sizeof(ipv4) - 1);
    ipv4[sizeof(ipv4) - 1] = '\0';
