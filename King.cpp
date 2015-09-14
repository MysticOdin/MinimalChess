#include "stdlib.h"
#include "King.h"
#include "Board.h"
#include "Place.h"
King::King(side_t c_side, Place* place, Board* c_board)
    : IPiece(c_side, place, c_board, false)
{
}

char King::getPieceLetter()
{
    return 'K';
}

bool King::isCheckedPlace(Place *place)
{
    bool returned = false;
    coord_t this_row = piecePlace->getRow();
    coord_t this_column = piecePlace->getColumn();
    coord_t next_row = place->getRow();
    coord_t next_column = place->getColumn();
    coord_t diff_column = abs(next_column - this_column);
    coord_t diff_row = abs(next_row - this_row);
    if((diff_column <= 1) && (diff_row <= 1))
    {
        returned = true;
    }
    return returned;
}

MoveType King::checkMoveAllowed(Place *place)
{
    MoveType returned = NOT_ALLOWED;
    if(board->isPlaceChecked(place, this->side) == false)
    {
        coord_t this_row = piecePlace->getRow();
        coord_t this_column = piecePlace->getColumn();
        coord_t next_row = place->getRow();
        coord_t next_column = place->getColumn();
        coord_t diff_column = abs(next_column - this_column);
        coord_t diff_row = abs(next_row - this_row);
        if(isCheckedPlace(place) == true)
        {
            returned = ALLOWED;
        }
        else if (  (diff_column == 2)
                 &&(diff_row == 0)
                 &&(isFirstMove == true)
                 &&(board->isPlaceChecked(piecePlace, this->side) == false))
        {
            coord_t middle_column = (this_column+next_column)/2;
            Place* middle_place = board->getPlaceByCoord(
                        this_row, middle_column);
            if(  (middle_place->getOccupyingPiece() == nullptr)
               &&(board->isPlaceChecked(middle_place, this->side) == false))
            {
                IPiece * castling_piece = nullptr;
                if(middle_column == COLUMN_G) //right castle
                {
                    castling_piece =
                            board->getPlaceByCoord(this_row, COLUMN_H)
                                 ->getOccupyingPiece();
                }
                else // left castle
                {
                    if(board->getPlaceByCoord(this_row, COLUMN_B)
                             ->getOccupyingPiece() == nullptr)
                    {
                        castling_piece =
                                board->getPlaceByCoord(this_row, COLUMN_A)
                                     ->getOccupyingPiece();
                    }
                }
                if(  (castling_piece != nullptr)
                   &&(castling_piece->isPieceFirstMove() == true))
                {
                    returned = CASTLE;
                }

            }
        }
    }
    return returned;
}
