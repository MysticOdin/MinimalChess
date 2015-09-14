#include "IPiece.h"
#include "Place.h"
#include "Board.h"

IPiece::~IPiece()
{
    piecePlace->setOccupyingPiece(nullptr);
}

MoveType IPiece::isMoveAllowed(Place* place)
{
    MoveType returned = NOT_ALLOWED;
    IPiece * pieceInPlace = place->getOccupyingPiece();
    if((pieceInPlace == nullptr) || (pieceInPlace->side != this->side))
    {
        returned = this->checkMoveAllowed(place);
    }
    return returned;
}

bool IPiece::isPiecePawn()
{
    return isPawn;
}

bool IPiece::isPieceFirstMove()
{
    return isFirstMove;
}

side_t IPiece::getPieceSide()
{
    return side;
}

void IPiece::resetPiece(Place *place)
{
    movePiece(place);
    isFirstMove = true;
}


IPiece::IPiece(side_t c_side, Place* place, Board* c_board, bool c_isPawn)
             : side(c_side), piecePlace(place), board(c_board), isPawn(c_isPawn)
{
    isFirstMove = true;
}

void IPiece::movePiece(Place* place)
{
    piecePlace->setOccupyingPiece(nullptr);
    piecePlace = place;
    piecePlace->setOccupyingPiece(this);
    isFirstMove = false;
}

