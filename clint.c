#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<time.h>

int main(int argc , char *argv[]) {

    //socket的建立
    int sockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1) {
        printf("Fail to create a socket.");
    }

    //socket的连线
    struct sockaddr_in info;
    bzero(&info, sizeof(info));
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = inet_addr("127.0.0.1");//or INADDR_ANY
    info.sin_port = htons(30003);

    int err = connect(sockfd, (struct sockaddr *)&info, sizeof(info));
    if (err == -1) {
        printf("Connection error\n");
    }

    //Send and receive a message
    char message[] = {"Hi, I am client1111."};
    char receive_message[100] = {};
    sleep(5);
    int s = send(sockfd, message, sizeof(message), 0);
    if (s == -1) printf("send data failed\n");
    int r = recv(sockfd, receive_message, sizeof(receive_message), 0);
    if (r == -1) printf("receive data failed\n");

    printf("received=%s\n", receive_message);
    printf("send data size=%d, receive data size=%d\n", s, r);
    printf("close Socket\n");
    close(sockfd);
    return 0;
}
