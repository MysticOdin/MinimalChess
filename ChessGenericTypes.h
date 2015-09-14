#ifndef CHESSGENERICTYPES
#define CHESSGENERICTYPES
#include <stdint.h>

typedef int coord_t;
typedef int side_t;

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

typedef enum
{
    NOT_ALLOWED,
    ALLOWED,
    CASTLE,
    EN_PASSANT
} MoveType;

#endif // CHESSGENERICTYPES

