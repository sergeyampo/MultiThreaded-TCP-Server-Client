#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "utils/opt_arg.h"
#include "../lib/set_sockaddr_in.h"


int main(int argc, char** argv) {
  uint64_t factorial = -1;
  struct Server ip_port;

  static struct option options[] = {{"factorial", required_argument, 0, 0},
									{"server", required_argument, 0, 0},
									{0, 0, 0, 0}};
  printf("afrt sockaddr");
  if (handle_options(argc, argv, options, 2, &factorial, &ip_port)) {
	return 1;
  }
  printf("afrt sockaddr");
  if (factorial == -1 || !strlen(ip_port.ip)) {
	fprintf(stderr, "Using: %s --factorial n --server 127.0.0.1:20001\n",
			argv[0]);
	return 1;
  }

  struct hostent* hostname = gethostbyname(&ip_port.ip);
  if (hostname == NULL) {
	fprintf(stderr, "gethostbyname failed with %s\n", ip_port.ip);
	exit(1);
  }

  struct sockaddr_in server;
  set_sockaddr_in(&server, AF_INET, ip_port.port,
  	*((unsigned long*)hostname->h_addr));
  printf("afrt sockaddr");
  int sck = socket(AF_INET, SOCK_STREAM, 0);
  if (sck < 0) {
	fprintf(stderr, "Socket creation failed!\n");
	exit(1);
  }

  if (connect(sck, (struct sockaddr*)&server, sizeof(server)) < 0) {
	fprintf(stderr, "Connection failed\n");
	exit(1);
  }

  char task[sizeof(uint64_t)];
  memcpy(task, &factorial, sizeof(uint64_t));

  if (send(sck, task, sizeof(task), 0) < 0) {
	fprintf(stderr, "Send failed\n");
	exit(1);
  }

  char response[sizeof(uint64_t)];
  if (recv(sck, response, sizeof(response), 0) < 0) {
	fprintf(stderr, "Recieve failed\n");
	exit(1);
  }

  uint64_t answer = 0;
  memcpy(&answer, response, sizeof(uint64_t));
  printf("answer: %lu\n", answer);

  close(sck);

  return 0;
}