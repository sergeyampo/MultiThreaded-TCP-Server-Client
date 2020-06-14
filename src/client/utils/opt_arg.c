//
// Created by sergeyampo on 06.06.2020.
//
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include "opt_arg.h"
#include "extract_ip_port_from_string.h"
#include "../../lib/check_port.h"


int handle_options(int argc,
				   char** argv,
				   struct option options[],
				   const int options_amount,
				   uint64_t* factorial,
				   struct Server* ip_port
) {
  char server[255] = {'\0'};

  int option_index = 0;
  while (1) {
	int c = getopt_long(argc, argv, "", options, &option_index);

	if (c == -1)
	  break;

	switch (c) {
	  case 0: {
		switch (option_index) {
		  case 0: *factorial = atoi(optarg);
			if (*factorial < 0 || *factorial > 20) {
			  printf('Factorial cannot be more than 20 and less than 0!');
			  return 1;
			}
			break;
		  case 1: memcpy(server, optarg, strlen(optarg));
			extract_ip_port_from_string(server, ':', ip_port);
			if (check_port(&ip_port->port))
			  return 1;
			break;
		  default:printf("Index %d is out of options\n", option_index);
		}
	  }
		break;

	  case '?':printf("Arguments error\n");
		break;
	  default:fprintf(stderr, "getopt returned character code 0%o?\n", c);
	}
  }
  return 0;
}