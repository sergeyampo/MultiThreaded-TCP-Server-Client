//
// Created by khrushv on 13.06.2020.
//
#include "check_port.h"
#include <stdio.h>


int check_port(unsigned int* port) {
  if (*port < 1024) {
	printf("port lower than 1024 may not be free\n");
	return 1;
  }
  return 0;
}
