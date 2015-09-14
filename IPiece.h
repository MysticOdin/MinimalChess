#ifndef IPIECE_H
#define IPIECE_H

#include <ChessGenericTypes.h>

class Place;
class Board;

class IPiece
{
public:
    virtual ~IPiece() = 0;
    MoveType isMoveAllowed(Place* place);
    void movePiece(Place* place);
    bool isPiecePawn(void);
    bool isPieceFirstMove(void);
    side_t getPieceSide(void);
    void resetPiece(Place* place);
    virtual char getPieceLetter(void) = 0;
protected:
    const side_t side;
    Place * piecePlace;
    Board * const board;
    const bool isPawn;
    bool  isFirstMove;
    IPiece(side_t c_side, Place* place, Board* c_board, bool c_isPawn);
private:
    virtual MoveType checkMoveAllowed(Place* place) = 0;
};

#endif // IPIECE_H
