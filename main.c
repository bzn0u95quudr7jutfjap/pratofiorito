#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char table[12][12];

int main(int argc, char ** argv){
  srand(time(NULL));
  printf("%d\n",rand());
  return 0;
}
