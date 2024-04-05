#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef uint8_t u8;
typedef uint32_t u32;

#define count(a) (sizeof(a) / sizeof(a[0]))

uint8_t table[12][12];

void init(){
  for (u32 i = 0; i < count(table); i++) {
    for (u32 j = 0; j < count(table[i]); j++) {
      table[i][j] = 129;
    }
  }
}

void print_table() {
  for (u32 i = 0; i < count(table); i++) {
    for (u32 j = 0; j < count(table[i]); j++) {
      printf("   %c", (table[i][j] & 128) ? 'x' : table[i][j]);
    }
    printf("  %02d\n", i);
  }
  for (u32 i = 0; i < count(table); i++){
    printf("  %02d", i);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  srand(time(NULL));
  init();
  print_table();
  return 0;
}
