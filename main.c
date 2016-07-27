#include <stdio.h>
#include "easy-tcp.h"
int main(int argc, char *argv[])
{
        int server_socket = create_tcp_server(5000);
        start_serving(server_socket,2,print);
        int client_socket = create_tcp_client_for_server("http://localhost/",5000);
        close(server_socket);
        close(client_socket);
}
