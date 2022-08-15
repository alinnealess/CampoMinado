#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./types.h"
#include "./constants.h"
#include "./strings.h"
#include "./interfaces/checkers.h"
#include "./interfaces/counters.h"
#include "./interfaces/inits.h"
#include "./interfaces/io.h"
#include "./interfaces/recursion.h"

int main() {
  system("clear");
  Cell mineMatrix[LINES][COL];
  initMines(mineMatrix);
  aroundMinesCounter(mineMatrix);
  initClosedCells(mineMatrix);
  int closedCells = LINES * COL;
  time_t begin_time, end_time;
  int ellapsed_time;
  int startedGame = 0;
  EndCondition endEnum = notFinish;
  ErrorCondition errorEnum = notError;
  int colToOpen, lineToOpenOrStopCmd;
  
  do {
    printBoard(mineMatrix);
    switch (errorEnum) {
      case outMatrix: printf("\n.... Célula fora dos limites! ....\n"); break;
      case alreadyOpen: printf("\n.... Célula já aberta ¬¬\' ....\n"); break;
      case notError: break;
    }
    errorEnum = notError;
    
    printf("\nCuidado! O campo contém %d minas.\n\n", countMinesInField(mineMatrix));
    printf("Qual célula deseja revelar?\n");
    printf("Linha (-1 sai): ");
    scanf("%d", &lineToOpenOrStopCmd);
    lineToOpenOrStopCmd--;
    if (startedGame == 0) {
      startedGame = 1;
      begin_time = time(NULL);
    }
    if (lineToOpenOrStopCmd != -2) {
      printf("Coluna: ");
      scanf("%d", &colToOpen);
      colToOpen--;
    }

    system("clear");

    if (!insideMatrixCheck(lineToOpenOrStopCmd, colToOpen)) {
      errorEnum = outMatrix;
    }
    else {
      if (mineMatrix[lineToOpenOrStopCmd][colToOpen].status == opened) {
        errorEnum = alreadyOpen;
      }
    }

    if (errorEnum == notError) {
      if (mineMatrix[lineToOpenOrStopCmd][colToOpen].mine == isMine) {
        mineMatrix[lineToOpenOrStopCmd][colToOpen].status = opened;
        closedCells--;
        endEnum = lost;
        break;
      } else {
        if (mineMatrix[lineToOpenOrStopCmd][colToOpen].aroundMines != 0) {
          mineMatrix[lineToOpenOrStopCmd][colToOpen].status = opened;
          closedCells--;
        } else {
          openCellsWithoutAroundMines(mineMatrix, lineToOpenOrStopCmd, colToOpen, &closedCells);
        }
        if (closedCells == MINES) {
          endEnum = win;
          break;
        }
      }
    }
  } while (lineToOpenOrStopCmd != -2); // -2 e não -1, já que houve um decremento para ajuste de índice na matriz
  // pós game
  if (lineToOpenOrStopCmd == -2) endEnum = stoped;
  printBoard(mineMatrix);
  end_time = time(NULL);
  ellapsed_time = end_time - begin_time;
  printf("\nTempo decorrido: %d segundos\n", ellapsed_time);
  switch (endEnum) {
    case stoped: printf("%s", end_msg.stoped); break;
    case win: printf("%s", end_msg.win); break;
    case lost: printf("%s", end_msg.lost); break;
    case notFinish: break;
  }
  return 0;
}
