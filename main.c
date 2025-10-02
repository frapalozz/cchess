#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>


#define BLU   "\x1B[34m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#define ROWS 8
#define COLUMNS 8

char chessBoard = 176;

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
  if (piece == 1 || piece == 7)  return "P";
  if (piece == 2 || piece == 8)  return "N";
  if (piece == 3 || piece == 9)  return "B";
  if (piece == 4 || piece == 10) return "R";
  if (piece == 5 || piece == 11) return "Q";
  if (piece == 6 || piece == 12) return "K";
  return "x";
}

/* Chess Board ROWSxCOLUMNS */
struct Board {
  unsigned char board[ROWS][COLUMNS];
};

struct Position {
  unsigned char x;
  unsigned char y;
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
  printf("\e[1;1H\e[2J");
  for(int i = 0; i < ROWS+1; i++) {
    for(int j = 0; j < COLUMNS+1; j++) {
      if(i == 0 && j == 0) printf("%c|", chessBoard);
      else if(i == 0) printf("%d|", j-1);
      else if(j == 0) printf("%d-", i-1);
      else {
        if(board->board[i-1][j-1] < 7) 
          printf(WHT "%s " RESET, getPiece(board->board[i-1][j-1]));
        else 
          printf(BLU "%s " RESET, getPiece(board->board[i-1][j-1]));
      }
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

bool validPosition(struct Position *position) {
  return (position->x < 0 || position->x >= COLUMNS || 
          position->y < 0 || position->y >= ROWS) ? false : true;
}

bool moveValidator(struct Position *from, struct Position *to, struct Board *board) {
  if(!validPosition(from) || !validPosition(to)) return false;
  unsigned char movingPiece = board->board[from->x][from->y];
  if(movingPiece == 0) return false; // Select a Piece!, not an empty position
  unsigned char replacedPiece = board->board[to->x][to->y];

  // White Pawn
  if(movingPiece == 1 && ((from->y == 6 && from->y - to->y > 2) || (from->y < 6 && from->y - to->y > 1))) return false;
  // Black Pawn
  if(movingPiece == 7 && ((from->y == 1 && to->y - from->y > 2) || (from->y > 1 && to->y - from->y > 1))) return false;
  // White Knight
  if(movingPiece == 2) return false;
  // Black Knight
  if(movingPiece == 8) return false;
  // White/Black Bishop
  if(movingPiece == 3 || movingPiece == 9) {}
  if(movingPiece == 4 || movingPiece == 10) {}
  if(movingPiece == 5 || movingPiece == 11) {}
  if(movingPiece == 6 || movingPiece == 12) {}
  return true;
}

void movePiece(struct Position *from, struct Position *to, struct Board *board) {
  if(!moveValidator(from, to, board)) {
    printf("Cannot move here\n");
    return;
  }
  char piece = board->board[from->y][from->x];
  board->board[from->y][from->x] = board->board[to->y][to->x];
  board->board[to->y][to->x] = piece;
  printBoard(board);
};

int main() 
{

  struct Board board;

  resetBoard(&board);
  printBoard(&board);
  sleep(2);
  struct Position from;
  struct Position to;
  from.x = 1;
  from.y = 1;
  to.x = 1;
  to.y = 4;
  movePiece(&from, &to, &board);
  // printf("Board: %d Bytes\n", sizeof(struct Board));

  return 0;
}
