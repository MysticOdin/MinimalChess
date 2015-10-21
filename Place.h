#ifndef PLACE_H
#define PLACE_H

#include "ChessGenericTypes.h"

class IPiece;

class Place
{
public:
    Place(coord_t column, coord_t row);
    Place(coord_t column, coord_t row, IPiece* piece);
    ~Place(void);
    void setOccupyingPiece(IPiece* piece);
    IPiece* getOccupyingPiece(void);
    coord_t getRow(void);
    coord_t getColumn(void);
private:
    const coord_t m_column;
    const coord_t m_row;
    IPiece * occupyingPiece;

};

#endif // PLACE_H
