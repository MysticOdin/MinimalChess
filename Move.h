#ifndef MOVE_H
#define MOVE_H

#include "ChessGenericTypes.h"
class IPiece;
typedef struct
{
    coord_t  startRow;
    coord_t  startColumn;
    coord_t  endRow;
    coord_t  endColumn;
    bool     firstMove;
    IPiece * capturedPiece;
    MoveType mvType;
} Move;

#endif // MOVE_H
