//
// Created by sergeyampo on 06.06.2020.
//
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "opt_arg.h"
#include "../../lib/check_port.h"


int* handle_options(int argc,
					char** argv,
					struct option options[],
					const int options_amount,
					int (* check_callbacks[])(unsigned int*)
) {
  unsigned int* output_options = (unsigned int*)malloc(sizeof(unsigned int) * options_amount);
  for (size_t i = 0; i < options_amount; ++i)
	output_options[i] = -1;

  int option_index = 0;
  while (1) {
	int c = getopt_long(argc, argv, "", options, &option_index);

	if (c == -1)
	  break;

	///TODO replace switch-case to a loop

	switch (c) {
	  case 0: {
		switch (option_index) {
		  case 0:*output_options = atoi(optarg);
			if ((*check_callbacks[0])(output_options))
			  return 1;
			break;
		  case 1:output_options[1] = atoi(optarg);
			if ((*check_callbacks[1])(output_options + 1))
			  return 1;
			break;
		  default:printf("Index %d is out of options\n", option_index);
		}
	  }
		break;

	  case '?':printf("Unknown argument\n");
		break;
	  default:fprintf(stderr, "getopt returned character code 0%o?\n", c);
	}
  }
  return output_options;
}