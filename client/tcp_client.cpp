#include "tcp_client.h"
using namespace std;

tcp_client::tcp_client(char* server_ip,char* server_port)
{
       if( (socket_fd = socket(AF_INET,SOCK_STREAM,0)) < 0 ) {
                printf("create socket error: %s(errno:%d)\n)",strerror(errno),errno);
                exit(0);
        }

        memset(&server_addr,0,sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(atoi(server_port));

        if( inet_pton(AF_INET,server_ip,&server_addr.sin_addr) <=0 ) {
                printf("inet_pton error for %s\n",server_ip);
                exit(0);
        }

        if( connect(socket_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0) {
                printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
                exit(0);
        }

        char buffer[13];
        uint8_t req_msg_type = 1;
        memcpy(buffer+0, &req_msg_type, 1);
        uint32_t req_msg_len = htonl(8); //8byte
        memcpy(buffer+1, &req_msg_len, 4);
        uint32_t req_msg_port = htonl(9999);
        memcpy(buffer+5, &req_msg_port, 4);
        struct sockaddr_in req_msg_usrid;   
        req_msg_usrid.sin_addr.s_addr = inet_addr("192.168.3.121");
        memcpy(buffer+9, &req_msg_usrid.sin_addr.s_addr, 4);

        if( send(socket_fd,buffer,sizeof(buffer),0) < 0 ) {
                printf("send message error\n");
                exit(0);
        }

        close(socket_fd);
        exit(0);

}