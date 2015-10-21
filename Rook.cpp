#include "Rook.h"
#include "Board.h"
#include "Place.h"
Rook::Rook(side_t c_side, Place* place, Board* c_board) : IPiece(c_side, place, c_board, false)
{
}

char Rook::getPieceLetter()
{
    return 'R';
}

MoveType Rook::checkMoveAllowed(Place *place)
{
    MoveType returned = NOT_ALLOWED;
    coord_t this_row = piecePlace->getRow();
    coord_t this_column = piecePlace->getColumn();
    coord_t next_row = place->getRow();
    coord_t next_column = place->getColumn();
    coord_t diff_column = next_column - this_column;
    coord_t diff_row = next_row - this_row;
    if((diff_column == 0)||(diff_row == 0))
    {
        if(board->isPathClear(piecePlace, place))
        {
            returned = ALLOWED;
        }
    }
    return returned;
}

