//
// Created by sergeyampo on 10.06.2020.
//

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "extract_ip_port_from_string.h"
#include "opt_arg.h"


unsigned int convert(char* st) {
  char* x;
  for (x = st; *x; x++) {
	if (!(*x))
	  return 0L;
  }
  return (strtoul(st, 0L, 10));
}

struct Server* extract_ip_port_from_string(char* str, const char* separator, struct Server* ip_port) {
  const size_t size = strlen(str);

  char* token;
  token = strsep(&str, ":");
  strcpy(&ip_port->ip, token);

  token = strsep(&str, ":");
  ip_port->port = convert(token);

  return ip_port;
}