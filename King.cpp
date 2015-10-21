#include "stdlib.h"
#include "King.h"
#include "Board.h"
#include "Place.h"
King::King(side_t c_side, Place* place, Board* c_board) : IPiece(c_side, place, c_board, false)
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

Place *King::getPiecePlace()
{
    return piecePlace;
}

MoveType King::checkMoveAllowed(Place *place)
{
    MoveType returned = NOT_ALLOWED;
    if(board->isPlaceChecked(place) == false)
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
                 &&(board->isPlaceChecked(piecePlace) == false))
        {
            coord_t middle_column = (this_column + next_column)/2;
            Place* middle_place = board->getPlaceByCoord(middle_column, this_row);
            if((middle_place->getOccupyingPiece() == nullptr) && (board->isPlaceChecked(middle_place) == false))
            {
                IPiece * castling_piece = nullptr;
                if(middle_column == COLUMN_F) //right castle
                {
                    castling_piece = board->getPlaceByCoord(COLUMN_H, this_row)->getOccupyingPiece();
                    if(  (castling_piece != nullptr)
                       &&(castling_piece->isPieceFirstMove() == true))
                    {
                        returned = RIGHT_CASTLE;
                    }
                }
                else // left castle
                {
                    if(board->getPlaceByCoord(COLUMN_B, this_row)
                             ->getOccupyingPiece() == nullptr)
                    {
                        castling_piece = board->getPlaceByCoord(COLUMN_A, this_row)->getOccupyingPiece();
                        if((castling_piece != nullptr) && (castling_piece->isPieceFirstMove() == true))
                        {
                            returned = LEFT_CASTLE;
                        }
                    }
                }
            }
        }
    }
    return returned;
}
