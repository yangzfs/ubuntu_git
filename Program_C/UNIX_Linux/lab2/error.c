#include "lab2.h"
int main(int argc, char const *argv[]) {
  int i = open("/usr/src/s.t",0);
  perror(argv[0]);
  printf(strerror(errno));
  printf("\n");
  return 0;
}
