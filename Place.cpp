#include "Place.h"
#include "IPiece.h"

Place::Place(coord_t column, coord_t row) : m_column(column), m_row(row)
{
    occupyingPiece = nullptr;
}
Place::Place(coord_t column, coord_t row, IPiece* piece) : m_column(column), m_row(row)
{
    occupyingPiece = piece;
}

Place::~Place()
{
    if(occupyingPiece != nullptr)
    {
        delete occupyingPiece;
    }
}

void Place::setOccupyingPiece(IPiece * piece)
{
    occupyingPiece = piece;
}

IPiece* Place::getOccupyingPiece(void)
{
    return occupyingPiece;
}

coord_t Place::getRow(void)
{
    return this->m_row;
}

coord_t Place::getColumn(void)
{
    return this->m_column;
}
