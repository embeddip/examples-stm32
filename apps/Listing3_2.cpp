#include "main.h"
#include <cmath>
#include <embedDIP.hpp>

using namespace std;

int application() {

  float data[1000];

  tic();
  for (uint32_t i = 0; i < 1000; i++) {
    data[i] = M_PI * M_E * i;
  }
  uint32_t elapsed = toc();

  while (1);
}