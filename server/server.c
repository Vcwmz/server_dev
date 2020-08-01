#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc , char *argv[]) {
    pid_t pid;
    //socket的建立
    char receive_message[256] = {};
    char message[] = {"Hi, I am server."};
    int s_sockfd = 0, c_sockfd = 0;
    s_sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (s_sockfd == -1) {
        printf("Fail to create a socket.");
    }

    //允许绑定的本地地址可以被复用
//    int opt;
//    setsockopt(s_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    //socket的连线
    struct sockaddr_in s_addr, c_addr;
    int addrlen = sizeof(struct sockaddr_in);
    bzero(&s_addr, sizeof(struct sockaddr_in));

    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//or INADDR_ANY
    s_addr.sin_port = htons(30003);
    if (bind(s_sockfd, (struct sockaddr *)&s_addr, sizeof(s_addr)) == -1) {
        printf("bind() failed!");
        exit(0);
    }


    if (listen(s_sockfd, 5) == -1) {
        printf("listen() failed!");
        exit(0);
    }

    while(1){
        c_sockfd = accept(s_sockfd, (struct sockaddr*) &c_addr, (socklen_t *)&addrlen);
        if(pid = fork() == 0)
        {
            int s = send(c_sockfd, message, sizeof(message), 0);
            if (s == -1) printf("send data failed\n");
            int r = recv(c_sockfd, receive_message, sizeof(receive_message), 0);
            if (r == -1) printf("receive data failed\n");
            printf("received=%s\n", receive_message);
            printf("send data size=%d, receive data size=%d\n", s, r);
        }
        printf("if you do not see this word,it is because there still something running");bn

    }
    return 0;
}
