#ifndef BISHOP_H
#define BISHOP_H

#include "IPiece.h"

class Bishop : public IPiece
{
public:
    Bishop(side_t c_side, Place* place, Board* c_board);
    char getPieceLetter();
    // IPiece interface
private:
    MoveType checkMoveAllowed(Place *place) override;
};

#endif // BISHOP_H
