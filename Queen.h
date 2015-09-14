#ifndef QUEEN_H
#define QUEEN_H

#include "IPiece.h"



class Queen : public IPiece
{
public:
    Queen(side_t c_side, Place* place, Board* c_board);
    char getPieceLetter();
    // IPiece interface
private:
    MoveType checkMoveAllowed(Place *place) override;
};

#endif // QUEEN_H
