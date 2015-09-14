#ifndef PAWN_H
#define PAWN_H
#include "IPiece.h"

class Pawn : public IPiece
{
public:
    Pawn(side_t c_side, Place* place, Board* c_board);
    char getPieceLetter();
    // IPiece interface
private:
    MoveType checkMoveAllowed(Place *place) override;
};

#endif // PAWN_H
