#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
int create_tcp_server(int port);
void start_serving(int server_socket,int how_many_to_serve,void (*function_to_execute)(struct sockaddr_in clientaddress,socklen_t clientaddresslen,int client_socket));
void create_tcp_client_for_server(char *hostname,int port_number);
void close_socket(int socket_id);
