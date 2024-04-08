#include <curses.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef uint8_t u8;
typedef uint32_t u32;

#define RIGHE 12
#define COLONNE 12

#define MINA '%'
#define TERRA '.'
#define VUOTO ' '

#define NMINE 24

#define count(a) (sizeof(a) / sizeof(a[0]))

u8 table[RIGHE][COLONNE] = {};
WINDOW *wnd;
u8 d, r = 0, c = 0;

u8 bound_check(u32 i, u32 j) {
  return (0 <= i && i <= RIGHE - 1) && (0 <= j && j <= COLONNE - 1);
}

u32 ismina(u32 i, u32 j) { return bound_check(i, j) && table[i][j] == MINA; }

void init() {
  // Inizio
  for (u32 i = 0; i < RIGHE; i++) {
    for (u32 j = 0; j < COLONNE; j++) {
      table[i][j] = VUOTO;
    }
  }
  // Mina
  for (u32 mine = 0; mine < NMINE; mine++) {
    table[rand() % RIGHE][rand() % COLONNE] = MINA;
  }
  // Numera
  for (u32 i = 0; i < RIGHE; i++) {
    for (u32 j = 0; j < COLONNE; j++) {
      if (table[i][j] == MINA) {
        continue;
      }
      table[i][j] = '0' + ismina(i - 1, j - 1) + ismina(i - 1, j) +
                    ismina(i - 1, j + 1) + ismina(i, j - 1) + ismina(i, j + 1) +
                    ismina(i + 1, j - 1) + ismina(i + 1, j) +
                    ismina(i + 1, j + 1);
      table[i][j] = table[i][j] == '0' ? VUOTO : table[i][j];
    }
  }
  // Maschera
  for (u32 i = 0; i < RIGHE; i++) {
    for (u32 j = 0; j < COLONNE; j++) {
      table[i][j] += 128;
    }
  }
}

void print_table() {
  for (u32 i = 0; i < RIGHE; i++) {
    for (u32 j = 0; j < COLONNE; j++) {
      move(i, j);
      printw("%c", (table[i][j] & 128) > 0 ? TERRA : table[i][j]);
    }
  }
  move(r, c);
}

u8 scopri_cella(u32 i, u32 j) {
  if (!(bound_check(i, j) && table[i][j] & 128)) {
    return EOF;
  }
  u8 scoperta = table[i][j] & 127;
  if (scoperta == MINA) {
    return scoperta;
  }
  table[i][j] = scoperta;
  if (scoperta != VUOTO) {
    return scoperta;
  }
  (void)scopri_cella(i - 1, j - 1);
  (void)scopri_cella(i - 1, j);
  (void)scopri_cella(i - 1, j + 1);
  (void)scopri_cella(i, j - 1);
  (void)scopri_cella(i, j + 1);
  (void)scopri_cella(i + 1, j - 1);
  (void)scopri_cella(i + 1, j);
  (void)scopri_cella(i + 1, j + 1);
  return scoperta;
}

void gamemain() {
  srand(time(NULL));
  init();
  while (1) {
    u32 i, j;
    scanf("%d", &i);
    scanf("%d", &j);
    if (scopri_cella(i, j) == MINA) {
      printw("BOOM!\n");
      for (u32 i = 0; i < RIGHE; i++) {
        for (u32 j = 0; j < COLONNE; j++) {
          if ((table[i][j] & 127) == MINA) {
            table[i][j] &= 127;
          }
        }
      }
      print_table();
      break;
    }
    u32 end = 1;
    for (u32 i = 0; i < RIGHE; i++) {
      for (u32 j = 0; j < COLONNE; j++) {
        if ((table[i][j] & 128) && (table[i][j] & 127) == MINA) {
          end = 0;
        }
      }
    }
    if (end == 1) {
      printw("VITTORIA\n");
      break;
    }
    print_table();
  }
}

int main(int argc, char **argv) {
  srand(time(NULL));
  wnd = initscr();
  init();
  noecho();
  while (1) {
    clear();
    refresh();
    print_table();
    d = getch();
    move(r, c);
    if (d == 'q') {
      break;
    } else if (d == 'h') {
      move(r, --c);
    } else if (d == 'j') {
      move(++r, c);
    } else if (d == 'k') {
      move(--r, c);
    } else if (d == 'l') {
      move(r, ++c);
    } else if (d == 'x') {
      u32 i, j;
      getyx(wnd, i, j);
      if (scopri_cella(i, j) == MINA) {
        for (u32 i = 0; i < RIGHE; i++) {
          for (u32 j = 0; j < COLONNE; j++) {
            if ((table[i][j] & 127) == MINA) {
              table[i][j] &= 127;
            }
          }
        }
        clear();
        refresh();
        print_table();
        move(RIGHE + 2, 0);
        printw("BOOM!!!");
        for (u32 d = 0; d != 'q';) {
          d = getch();
        }
        break;
      }
    }
  }

  endwin();
  return 0;
}
