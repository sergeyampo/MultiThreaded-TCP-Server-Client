//
// Created by khrushv on 13.06.2020.
//

#include "factorial.h"


uint64_t factorial(const uint64_t* n) {
  uint64_t factorial = 1;
  uint64_t r = *n;
  for (uint64_t i = 2; i <= r; ++i)
	factorial *= i;
  return factorial;
}