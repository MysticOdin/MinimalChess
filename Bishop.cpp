#include "stdlib.h"
#include "Bishop.h"
#include "Board.h"
#include "Place.h"

Bishop::Bishop(side_t c_side, Place* place, Board* c_board)
    : IPiece(c_side, place, c_board, false)
{
}

char Bishop::getPieceLetter()
{
    return 'B';
}

MoveType Bishop::checkMoveAllowed(Place *place)
{
    MoveType returned = NOT_ALLOWED;
    coord_t this_row = piecePlace->getRow();
    coord_t this_column = piecePlace->getColumn();
    coord_t next_row = place->getRow();
    coord_t next_column = place->getColumn();
    coord_t diff_column = abs(next_column - this_column);
    coord_t diff_row = abs(next_row - this_row);
    if(diff_column == diff_row)
    {
        if(board->isPathClear(piecePlace, place))
        {
            returned = ALLOWED;
        }
    }
    return returned;
}
