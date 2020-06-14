//
// Created by khrushv on 14.06.2020.
//
#include <netinet/in.h>
void set_sockaddr_in(struct sockaddr_in* server,
				short s_port, unsigned short port, unsigned long s_addr){
	server->sin_family = s_port;
	server->sin_port = htons(port);
	server->sin_addr.s_addr = s_addr;

}