#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <getopt.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "pthread.h"
#include "../lib/thread_pool/thpool.h"
#include "../lib/check_port.h"
#include "utils/opt_arg.h"
#include "utils/factorial.h"
#include "utils/check_tnum.h"
#include "../lib/set_sockaddr_in.h"


void* socket_thread(void* arg) {
  printf("Into thread  %d\n", (int)pthread_self());
  int newSocket = *((int*)arg);
  while (true) {
	unsigned int buffer_size = sizeof(uint64_t);
	char from_client[buffer_size];
	int read = recv(newSocket, from_client, buffer_size, 0);
	if (!read)
	  break;
	if (read < 0) {
	  fprintf(stderr, "Client read failed\n");
	  break;
	}
	if (read < buffer_size) {
	  fprintf(stderr, "Client send wrong data format\n");
	  break;
	}
	uint64_t factorial_number = 0;
	memcpy(&factorial_number, from_client, sizeof(uint64_t));
	fprintf(stdout, "Receive: %lu \n", factorial_number);
	uint64_t total = factorial(&factorial_number);
	printf("Total: %lu\n", total);

	char buffer[sizeof(total)];
	memcpy(buffer, &total, sizeof(total));
	int err = send(newSocket, buffer, sizeof(total), 0);
	if (err < 0) {
	  fprintf(stderr, "Can't send data to client\n");
	  break;
	}
  }

  shutdown(newSocket, SHUT_RDWR);
  close(newSocket);
}

int main(int argc, char** argv) {
  size_t options_amount = 2;
  static struct option options[] = {{"port", required_argument, 0, 0},
									{"tnum", required_argument, 0, 0},
									{0, 0, 0, 0}};

  //Attach callbacks
  int (* callbacks[options_amount])(unsigned int*); //Array of callbacks
  callbacks[0] = check_port;
  callbacks[1] = check_tnum;
  unsigned int* handled_options = handle_options(argc, argv, options, options_amount, callbacks);
  unsigned port = handled_options[0];
  unsigned tnum = handled_options[1];
  threadpool thpool = thpool_init(tnum);

  if (port == -1) {
	fprintf(stderr, "Using: %s --port 20001 \n", argv[0]);
	return 1;
  }

  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
	fprintf(stderr, "Can not create server socket!");
	return 1;
  }

  struct sockaddr_in server;
  set_sockaddr_in(&server, AF_INET, port, INADDR_ANY);

  int opt_val = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val));

  int err = bind(server_fd, (struct sockaddr*)&server, sizeof(server));
  if (err < 0) {
	fprintf(stderr, "Can not bind to socket!");
	return 1;
  }

  err = listen(server_fd, 128);
  if (err < 0) {
	fprintf(stderr, "Could not listen on scket\n");
	return 1;
  }

  printf("Server listening at %d\n", port);

  while (true) {
	struct sockaddr_in client;
	socklen_t client_len = sizeof(client);
	int client_fd = accept(server_fd, (struct sockaddr*)&client, &client_len);

	if (client_fd < 0) {
	  fprintf(stderr, "Could not establish new connection\n");
	  continue;
	}

	thpool_add_work(thpool, (void*)socket_thread, &client_fd);
  }
  thpool_destroy(thpool);
  return 0;
}