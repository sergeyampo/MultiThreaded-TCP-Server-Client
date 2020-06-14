//
// Created by khrushv on 13.06.2020.
//
#include <stdio.h>


int check_tnum(unsigned int* tnum) {
  if (*tnum <= 0) {
	printf("tnum must be a positive number\n");
	return 1;
  }
  return 0;
}