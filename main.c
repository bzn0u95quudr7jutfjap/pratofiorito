#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef uint8_t u8;
typedef uint32_t u32;

#define count(a) (sizeof(a) / sizeof(a[0]))
#define MINA '%'
#define TERRA '#'

u8 table[12][12] = {};

u8 bound_check(u32 i, u32 j) {
  return (0 <= i && i <= count(table) - 1) &&
         (0 <= j && j <= count(table[i]) - 1);
}

u32 ismina(u32 i, u32 j) { return bound_check(i, j) && table[i][j] == MINA; }

void init() {
  // Inizio
  for (u32 i = 0; i < count(table); i++) {
    for (u32 j = 0; j < count(table[i]); j++) {
      table[i][j] = '0';
    }
  }
  // Mina
  for (u32 mine = 0; mine < 24; mine++) {
    table[rand() % count(table)][rand() % count(table[0])] = MINA;
  }
  // Numera
  for (u32 i = 0; i < count(table); i++) {
    for (u32 j = 0; j < count(table[i]); j++) {
      if (table[i][j] == MINA) {
        continue;
      }
      table[i][j] = '0' + ismina(i - 1, j - 1) + ismina(i - 1, j) +
                    ismina(i - 1, j + 1) + ismina(i, j - 1) + ismina(i, j + 1) +
                    ismina(i + 1, j - 1) + ismina(i + 1, j) +
                    ismina(i + 1, j + 1);
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

void scopri_table() {
  for (u32 i = 0; i < count(table); i++) {
    for (u32 j = 0; j < count(table[i]); j++) {
      printf("   %c", table[i][j] & 127);
    }
    printf("  %02d\n", i);
  }
  for (u32 i = 0; i < count(table); i++) {
    printf("  %02d", i);
  }
  printf("\n");
}

void scopri_se_zero_su(u32 i, u32 j) {
  if (!bound_check(i, j)) {
    return;
  }
  table[i][j] &= 127;

  if ((table[i][j] & 127) != '0') {
    return;
  }
  scopri_se_zero_su(i - 1, j - 1);
  scopri_se_zero_su(i - 1, j);
  scopri_se_zero_su(i - 1, j - 1);
}

void scopri_se_zero_so(u32 i, u32 j) {
  if (!bound_check(i, j)) {
    return;
  }
  table[i][j] &= 127;

  if ((table[i][j] & 127) != '0') {
    return;
  }
  scopri_se_zero_so(i + 1, j - 1);
  scopri_se_zero_so(i + 1, j);
  scopri_se_zero_so(i + 1, j + 1);
}

void scopri_se_zero_sx(u32 i, u32 j) {
  if (!bound_check(i, j)) {
    return;
  }
  table[i][j] &= 127;

  if ((table[i][j] & 127) != '0') {
    return;
  }
  scopri_se_zero_sx(i - 1, j - 1);
  scopri_se_zero_sx(i, j - 1);
  scopri_se_zero_sx(i + 1, j - 1);
}

void scopri_se_zero_dx(u32 i, u32 j) {
  if (!bound_check(i, j)) {
    return;
  }
  table[i][j] &= 127;

  if ((table[i][j] & 127) != '0') {
    return;
  }
  scopri_se_zero_dx(i - 1, j + 1);
  scopri_se_zero_dx(i, j + 1);
  scopri_se_zero_dx(i + 1, j + 1);
}

void scopri_cella(u32 i, u32 j) {
  if (!bound_check(i, j)) {
    return;
  }
  table[i][j] &= 127;
  scopri_se_zero_su(i - 1, j - 1);
  scopri_se_zero_su(i - 1, j);
  scopri_se_zero_su(i - 1, j + 1);
  scopri_se_zero_so(i + 1, j - 1);
  scopri_se_zero_so(i + 1, j);
  scopri_se_zero_so(i + 1, j + 1);
  scopri_se_zero_sx(i - 1, j - 1);
  scopri_se_zero_sx(i, j - 1);
  scopri_se_zero_sx(i + 1, j - 1);
  scopri_se_zero_dx(i - 1, j + 1);
  scopri_se_zero_dx(i, j + 1);
  scopri_se_zero_dx(i + 1, j + 1);
}

int main(int argc, char **argv) {
  srand(time(NULL));
  init();
  // scopri_table();
  // scopri_cella(4, 1);
  // scopri_cella(4, 2);
  // scopri_cella(4, 3);
  // scopri_cella(4, 4);
  // scopri_cella(4, 5);
  scopri_cella(4, 6);
  print_table();
  return 0;
}
