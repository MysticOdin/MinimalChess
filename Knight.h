#ifndef KNIGHT_H
#define KNIGHT_H

#include "IPiece.h"

class Knight : public IPiece
{
public:
    Knight(side_t c_side, Place* place, Board * c_board);
    char getPieceLetter();
    // IPiece interface
private:
    MoveType checkMoveAllowed(Place* place) override;
};

#endif // KNIGHT_H
