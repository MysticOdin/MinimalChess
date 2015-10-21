#include "stdlib.h"
#include "Place.h"
#include "Board.h"
#include "Pawn.h"

Pawn::Pawn(side_t c_side, Place* place, Board* c_board) : IPiece(c_side, place, c_board, true)
{
}

char Pawn::getPieceLetter()
{
    return 'P';
}

MoveType Pawn::checkMoveAllowed(Place *place)
{
    MoveType returned = NOT_ALLOWED;
    coord_t this_row = piecePlace->getRow();
    coord_t this_column = piecePlace->getColumn();
    coord_t next_row = place->getRow();
    coord_t next_column = place->getColumn();
    coord_t diff_column = abs(next_column - this_column);
    coord_t diff_row;
    coord_t en_passant_row;
    if(side == WHITE_SIDE)
    {
        diff_row = next_row - this_row;
        en_passant_row = ROW_5;
    }
    else
    {
        diff_row = this_row - next_row;
        en_passant_row = ROW_4;
    }
    if(diff_column == 0)
    {
        if(  (place->getOccupyingPiece() == nullptr)
           &&(  (diff_row == 1)
              ||((diff_row == 2) && (isFirstMove == true) && (board->isPathClear(piecePlace, place) == true))))
        {
            returned = ALLOWED;
        }
    }
    else if((diff_column == 1) && (diff_row == 1))
    {
        if(place->getOccupyingPiece() != nullptr)
        {
            returned = ALLOWED;
        }
        else if(this_row == en_passant_row)
        {
            coord_t last_move_row;
            coord_t last_move_column;
            board->getLastMoveCoord(&last_move_column, &last_move_row);
            if((this_row == last_move_row) && (next_column == last_move_column))
            {
                /* in this case adjacent piece cannot be a nullptr since it's in the last move coordinate, unless it's
                 * the first move, and if it's the first move the pawn can't be in the en-passant row */
                IPiece * adjacent_piece = board->getPlaceByCoord(next_column, this_row)->getOccupyingPiece();
                if((adjacent_piece->isPiecePawn() == true) && (adjacent_piece->isPieceFirstMove() == true))
                {
                    returned = EN_PASSANT;
                }
            }
        }
    }
    return returned;
}


