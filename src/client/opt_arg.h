//
// Created by sergeyampo on 06.06.2020.
//

#include <getopt.h>
#include <limits.h>
#include <stdint.h>


#ifndef TCPSERVERCLIENT_SRC_SERVER_OPT_ARG_H_
#define TCPSERVERCLIENT_SRC_SERVER_OPT_ARG_H_

struct Server {
  char ip[32 + 1];
  unsigned port;
};

int handle_options(int, char**, struct option[], const int, uint64_t*, struct Server*);

#endif //TCPSERVERCLIENT_SRC_SERVER_OPT_ARG_H_