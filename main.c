#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef uint8_t u8;
typedef uint32_t u32;

#define count(a) (sizeof(a) / sizeof(a[0]))
#define MINA '%'
#define TERRA '#'

uint8_t table[12][12];

void init() {
  // Inizio
  for (u32 i = 0; i < count(table); i++) {
    for (u32 j = 0; j < count(table[i]); j++) {
      table[i][j] = '0';
    }
  }
  // Mina
  for (u32 i = 0; i < count(table); i++) {
    for (u32 j = 0; j < count(table[i]); j++) {
      if ((rand() % 10) < 3) {
        table[i][j] = MINA;
      }
    }
  }
  // Numera
  for (u32 i = 0; i < count(table); i++) {
    for (u32 j = 0; j < count(table[i]); j++) {
      if(table[i][j] == MINA){
        continue;
      }
      u8 mine = 0;
      mine += i > 0                && j > 0                   && table[i-1][j-1] == MINA;
      mine += i > 0                &&                            table[i-1][j  ] == MINA;
      mine += i > 0                && j > count(table[i]) - 1 && table[i-1][j+1] == MINA;
      mine += i < count(table) - 1 && j > 0                   && table[i+1][j-1] == MINA;
      mine += i < count(table) - 1 &&                            table[i+1][j  ] == MINA;
      mine += i < count(table) - 1 && j > count(table[i]) - 1 && table[i+1][j+1] == MINA;
      mine +=                         j > 0                   && table[i  ][j-1] == MINA;
      mine +=                         j > count(table[i]) - 1 && table[i  ][j+1] == MINA;
      table[i][j] = '0' + mine;
    }
  }
  // Maschera
  for (u32 i = 0; i < count(table); i++) {
    for (u32 j = 0; j < count(table[i]); j++) {
      table[i][j] += 128;
    }
  }
}

void print_table() {
  for (u32 i = 0; i < count(table); i++) {
    for (u32 j = 0; j < count(table[i]); j++) {
      printf("   %c", (table[i][j] & 128) ? TERRA : table[i][j]);
    }
    printf("  %02d\n", i);
  }
  for (u32 i = 0; i < count(table); i++) {
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
