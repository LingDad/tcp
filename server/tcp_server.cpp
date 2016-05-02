#include "tcp_server.h"

using namespace std;

tcp_server::tcp_server(int listen_port) {

        if(( socket_fd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0 ){
                throw "socket() failed";
        }

        memset(&myserver,0,sizeof(myserver));
        myserver.sin_family = AF_INET;
        myserver.sin_addr.s_addr = htonl(INADDR_ANY);
        myserver.sin_port = htons(listen_port);

        if( bind(socket_fd,(sockaddr*) &myserver,sizeof(myserver)) < 0 ) {
                throw "bind() failed";
        }

        if( listen(socket_fd,10) < 0 ) {
                throw "listen() failed";
        }
}

int tcp_server::recv_msg() {

        while( 1 ) {

                socklen_t sin_size = sizeof(struct sockaddr_in);
                if(( accept_fd = accept(socket_fd,(struct sockaddr*) &remote_addr,&sin_size)) == -1 )
                {
                        throw "Accept error!";
                        continue;
                }
                printf("Received a connection from %s\n",(char*) inet_ntoa(remote_addr.sin_addr));

                if( !fork() ) {
                        char buffer[MAXSIZE];
                        memset(buffer,0,MAXSIZE);
                        if( ( read(accept_fd,buffer,MAXSIZE)) < 0 ) {
                                throw("Read() error!");
                        } else {
                                uint8_t req_msg_type;
                                memcpy(&req_msg_type, buffer+0, 1);
                                int msg_type = req_msg_type;

                                uint32_t req_msg_len;
                                memcpy(&req_msg_len, buffer+1, 4);
                                int msg_len = ntohl(req_msg_len);

                                uint32_t req_msg_port;
                                memcpy(&req_msg_port, buffer+5, 4);
                                int msg_port = ntohl(req_msg_port);

                                struct sockaddr_in req_msg_usrid;
                                memcpy(&req_msg_usrid.sin_addr.s_addr, buffer+9, 4);
                                char* msg_usrid = inet_ntoa(req_msg_usrid.sin_addr);
                                printf("Received message type: %d\n",msg_type);
                                printf("Received message length: %d\n",msg_len);
                                printf("Received message port: %d\n",msg_port);
                                printf("Received message usrid: %s\n",msg_usrid);
                                break;
                        }
                        exit(0);
                }
                close(accept_fd);
        }
        return 0;
}