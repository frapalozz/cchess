#include <stdio.h>
#include <stdbool.h>

#define ROWS 8
#define COLUMNS 8

/* 
 * Chess Piece Struct 
 * =============================
 *           WHITE    BLACK
 * Pawn:       1        7
 * Knight:     2        8
 * Bishop:     3        9
 * Rook:       4        10
 * Queen:      5        11
 * King:       6        12
 * Empty:      0        0
 * =============================
 * */
struct Piece {
  unsigned char type;
};

/* Chess Board ROWSxCOLUMNS */
struct Board {
  struct Piece *board[ROWS][COLUMNS];
};

/* Print chess board to terminal */
void printBoard(struct Board *board) {
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLUMNS; j++) {
      printf("%d  ", board->board[i][j]->type);
    };
    printf("\n");
  };
}

/* Reset board pieces */
void resetBoard(struct Board *board) {
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLUMNS; j++) {
      struct Piece pezzo = {0};
      board->board[i][j] = &pezzo;
    };
  };
}

int main() 
{

  struct Board board;

  resetBoard(&board);
  printBoard(&board);
  printf("Piece: %d Bytes\n", sizeof(struct Piece));
  printf("Board: %d Bytes\n", sizeof(struct Board));

  return 0;
}
