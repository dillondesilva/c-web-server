#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT_NUM 8080

int main(int argc, char **argv) {
    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    int activeSocket;
    char host[256];
    struct sockaddr_in addrinfo;
    addrinfo.sin_family = AF_INET;
    addrinfo.sin_port = htons(PORT_NUM);
    addrinfo.sin_addr.s_addr = htonl(INADDR_ANY);

    /* Getting host IP address as a 32 bit unsigned int */
    inet_aton("127.0.0.1", &addrinfo.sin_addr);
    printf ("Address: %s\n", inet_ntoa (addrinfo.sin_addr));
    printf ("Port: %hu\n", addrinfo.sin_port);
    int lenAddr = sizeof(struct sockaddr_in);

    printf("%d\n", AF_INET);
    printf("%u\n", gethostname(host, sizeof(host)));
    if (socket_desc == -1)
    {   
        printf("Could not create socket\n");
    } else 
    {
        printf("Socket successfully created\n");
        int sock_bind = bind(socket_desc, (struct sockaddr *) &addrinfo, sizeof(addrinfo));

        if (sock_bind == -1)
        {
            printf("Error binding socket to port\n");
        } else
        {
            printf("Socket binded to port\n");
        }
        
        listen(socket_desc, 4);

        for (;;) {
            activeSocket = accept(socket_desc, (struct sockaddr *)&addrinfo, (socklen_t *)&lenAddr);
            sleep(1);
            printf("yo");
            close(activeSocket);
            sleep(1);
        }

    }

    return 0;
}