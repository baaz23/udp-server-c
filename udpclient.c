// udp_client.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Winsock Library

#define SERVER "127.0.0.1"  // IP address of the server
#define BUFLEN 512  // Max length of buffer
#define PORT 8080   // The port on which to send data

int main() {
    struct sockaddr_in si_other;
    int s, slen = sizeof(si_other);
    char buf[BUFLEN];
    WSADATA wsa;

    // Initialise winsock
   // printf("Initialising Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code: %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    //printf("Initialised.\n");

    // Create a socket
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket: %d\n", WSAGetLastError());
    }
    printf("Client connected.\n");

    // Setup address structure
    memset((char *)&si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

    // Start communication
    while (1) {
        printf("Enter message: ");
        gets(buf);

        // Send the message
        if (sendto(s, buf, strlen(buf), 0, (struct sockaddr *)&si_other, slen) == SOCKET_ERROR) {
            printf("sendto() failed with error code: %d\n", WSAGetLastError());
            exit(EXIT_FAILURE);
        }
    }

    closesocket(s);
    WSACleanup();

    return 0;
}
