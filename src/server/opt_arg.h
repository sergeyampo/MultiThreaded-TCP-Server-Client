//
// Created by sergeyampo on 06.06.2020.
//

#include <getopt.h>


#ifndef TCPSERVERCLIENT_SRC_SERVER_OPT_ARG_H_
#define TCPSERVERCLIENT_SRC_SERVER_OPT_ARG_H_

int* handle_options(int, char**, struct option[], const int, int (* [])(int));

#endif //TCPSERVERCLIENT_SRC_SERVER_OPT_ARG_H_