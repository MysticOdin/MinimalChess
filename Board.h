#ifndef BOARD_H
#define BOARD_H

#include "ChessGenericTypes.h"
#include "Move.h"
#include <list>

class Place;
class Pawn;
class King;

class Board
{
public:
    Board(void);
    ~Board(void);
    bool movePiece(Place* src, Place* dist);
    bool isPathClear(Place* place1, Place* place2);
    bool isPlaceChecked(Place* place, side_t side);
    bool promote(Place* place, Pawn* pawn);
    Place* getPlaceByCoord(coord_t column, coord_t row);
    void getLastMoveCoord(coord_t* column, coord_t* row);
    const std::list<Move> * getMoveList(void);
    bool atEnd(void);
    bool atStart(void);
    bool moveNext(void);
    bool movePrevious(void);
private:
    void appendMove(Place* src,
                    Place* dist,
                    IPiece* capturedPiece,
                    MoveType mvType);
    Place* board[8][8];
    King* kings[2];
    side_t turn;
    std::list<Move> moveList;
    std::list<Move>::iterator currentMove;
};

#endif // BOARD_H
