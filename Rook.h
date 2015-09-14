#ifndef ROOK_H
#define ROOK_H

#include "IPiece.h"



class Rook : public IPiece
{
public:
    Rook(side_t c_side, Place* place, Board* c_board);
    char getPieceLetter();
    // IPiece interface
private:
    MoveType checkMoveAllowed(Place *place) override;
};

#endif // ROOK_H
