#include "Queen.h"
#include "Board.h"

Queen::Queen(side_t c_side, Place* place, Board* c_board)
    : IPiece(c_side, place, c_board, false)
{
}

char Queen::getPieceLetter()
{
    return 'Q';
}

MoveType Queen::checkMoveAllowed(Place *place)
{
    MoveType returned = NOT_ALLOWED;
    if(board->isPathClear(piecePlace, place))
    {
        returned = ALLOWED;
    }
    return returned;
}
