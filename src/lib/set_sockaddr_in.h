//
// Created by khrushv on 14.06.2020.
//

#ifndef TCPSERVERCLIENT_SRC_LIB_SET_SOCKADDR_IN_H_
#define TCPSERVERCLIENT_SRC_LIB_SET_SOCKADDR_IN_H_
void set_sockaddr_in(struct sockaddr_in* server,
	short s_port, unsigned short port, unsigned long s_addr);
#endif //TCPSERVERCLIENT_SRC_LIB_SET_SOCKADDR_IN_H_
