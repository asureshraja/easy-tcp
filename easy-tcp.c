#include "easy-tcp.h"
int create_tcp_server(int port){
        int server_socket;
        socklen_t addrlen;
        struct sockaddr_in address, clientaddress;
        memset((void *) &address, (int) '\0', sizeof(address));

        //creating server sokect
        if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0) {
                printf("The socket has been created\n");
        }
        int opt = 1;
        setsockopt(server_socket, IPPROTO_TCP, TCP_NODELAY, (void *) &opt, sizeof(opt));
        setsockopt(server_socket, IPPROTO_TCP, TCP_QUICKACK, (void *) &opt, sizeof(opt));
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_LINGER, &opt, sizeof(opt));
        //binding socket to port and address
        if (bind(server_socket, (struct sockaddr *) &address, sizeof(address)) == 0) {
                printf("Server is binded to the port %d \n", port);
        } else {
                printf("Binding to port %d Failed\n", port);
                exit(75);
        }
        listen(server_socket,10000);
        return server_socket;
}
void start_serving(int server_socket,int how_many_to_serve,void (*function_to_execute)(struct sockaddr_in clientaddress,socklen_t clientaddresslen,int client_socket)){
        unsigned int i=0;
        socklen_t clientaddresslen;
        struct sockaddr_in clientaddress;
        memset((void *) &clientaddress, (int) '\0', sizeof(clientaddress));
        int client_socket;
        for (i = 0; i != how_many_to_serve; i++) {
                clientaddresslen = sizeof(clientaddress);
                if ((client_socket = accept4(server_socket, (struct sockaddr *) &clientaddress, &clientaddresslen,
                                             SOCK_NONBLOCK)) < 0) {
                        perror("server: accept");
                        exit(1);
                }
                function_to_execute(struct sockaddr_in clientaddress,socklen_t clientaddresslen,int client_socket);
        }
}
void print(struct sockaddr_in clientaddress,socklen_t clientaddresslen,int client_socket){
        printf("%d\n", client_socket);
}
void create_tcp_client_for_server(char *hostname,int port_number){
        int sockfd, portno, n;
        struct sockaddr_in serv_addr;
        struct hostent *server;

        char buffer[256];
        if (argc < 3) {
           fprintf(stderr,"usage %s hostname port\n", argv[0]);
           exit(0);
        }
        portno = port_number;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            error("ERROR opening socket");
        server = gethostbyname(hostname);
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr,
             (char *)&serv_addr.sin_addr.s_addr,
             server->h_length);
        serv_addr.sin_port = htons(portno);
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
            error("ERROR connecting");

        return sockfd;
}
void close_socket(int socket_id){
        close(socket_id);
}
