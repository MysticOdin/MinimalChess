#ifndef KING_H
#define KING_H

#include "IPiece.h"



class King : public IPiece
{
public:
    King(side_t c_side, Place* place, Board* c_board);
    char getPieceLetter();
    bool isCheckedPlace(Place* place);
    // IPiece interface
private:
    MoveType checkMoveAllowed(Place *place);

};

#endif // KING_H
