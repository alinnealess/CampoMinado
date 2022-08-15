#ifndef TYPES
#define TYPES

typedef enum {
  notMine,
  isMine,
} Mine;

typedef enum {
  closed,
  opened,
} Status;

typedef enum {
  stoped,
  win,
  lost,
  notFinish,
} EndCondition;

typedef enum {
  outMatrix,
  alreadyOpen,
  notError,
} ErrorCondition;

typedef struct {
  Mine mine;
  int aroundMines;
  Status status;
} Cell;

typedef struct {
  char stoped[50];
  char win[50];
  char lost[50];
} EndMsg;

#endif