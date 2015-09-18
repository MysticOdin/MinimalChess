#ifndef CHESSGENERICTYPES
#define CHESSGENERICTYPES
#include <stdint.h>

typedef int coord_t;
typedef int side_t;
typedef int check_status_t;

#define COLUMN_A 0
#define COLUMN_B 1
#define COLUMN_C 2
#define COLUMN_D 3
#define COLUMN_E 4
#define COLUMN_F 5
#define COLUMN_G 6
#define COLUMN_H 7

#define ROW_1 0
#define ROW_2 1
#define ROW_3 2
#define ROW_4 3
#define ROW_5 4
#define ROW_6 5
#define ROW_7 6
#define ROW_8 7

#define WHITE_SIDE 0
#define BLACK_SIDE 1

#define NOT_CHECKED 0
#define CHECK       1
#define CHECKMATE   2

typedef enum
{
    NOT_ALLOWED,
    ALLOWED,
    EN_PASSANT,
    RIGHT_CASTLE,
    LEFT_CASTLE
} MoveType;

#endif // CHESSGENERICTYPES

