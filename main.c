#include <stdio.h>


#define BLU   "\x1B[34m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#define ROWS 8
#define COLUMNS 8

/* 
 * Chess Pieces 
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
char* getPiece(unsigned char piece) {
  switch (piece) {
    case 1: case 7:
      return "P";
    case 2: case 8:
      return "N";
    case 3: case 9:
      return "B";
    case 4: case 10:
      return "R";
    case 5: case 11:
      return "Q";
    case 6: case 12:
      return "K";
    default:
      return 0;
  }
  /* TODO: test switch case */

  if (piece == 1 || piece == 7)  return "P";
  if (piece == 2 || piece == 8)  return "N";
  if (piece == 3 || piece == 9)  return "B";
  if (piece == 4 || piece == 10) return "R";
  if (piece == 5 || piece == 11) return "Q";
  if (piece == 6 || piece == 12) return "K";
  return "\0";
}

/* Chess Board ROWSxCOLUMNS */
struct Board {
  unsigned char board[ROWS][COLUMNS];
};

struct Board baseBoard = {10,8 ,9 ,11,12,9 ,8 ,10,
                          7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,
                          0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                          0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                          0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                          0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                          1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,
                          4 ,2 ,3 ,5 ,6 ,3 ,2 ,4 };

/* Print chess board to terminal */
void printBoard(struct Board *board) {
  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLUMNS; j++) {
      if(board->board[i][j] < 7) 
        printf(WHT "%s " RESET, getPiece(board->board[i][j]));
      else 
        printf(BLU "%s " RESET, getPiece(board->board[i][j]));
    };
    printf("\n");
  };
}

/* Reset board pieces */
void resetBoard(struct Board *board) {
  for(int i = 0; i < ROWS; i++) 
    for(int j = 0; j < COLUMNS; j++) 
      board->board[i][j] = baseBoard.board[i][j]; 
}

int main() 
{

  struct Board board;

  resetBoard(&board);
  printBoard(&board);
  printf("Board: %d Bytes\n", sizeof(struct Board));

  return 0;
}
