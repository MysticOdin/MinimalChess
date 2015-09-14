#include "BoardQObjectAbstraction.h"
#include "Board.h"
#include "IPiece.h"
#include "Place.h"
#include <QVariant>
#include <QUrl>
#include <fstream>
#include "Serialization.h"

BoardQObjectAbstraction::BoardQObjectAbstraction
                                             (QObject *parent) : QObject(parent)
{
    this->board = nullptr;
    this->selectedPlace = nullptr;
}

BoardQObjectAbstraction::~BoardQObjectAbstraction()
{
    if(this->board != nullptr)
    {
        delete this->board;
    }
}

void BoardQObjectAbstraction::stopGame()
{
    if(this->board != nullptr)
    {
        delete this->board;
        this->board = nullptr;
    }
    this->selectedPlace = nullptr;
}

bool BoardQObjectAbstraction::selectSquare(int column, int row)
{
    bool moveAccepted = false;
    Place * tempPlace = selectedPlace;
    if(this->board != nullptr)
    {
        selectedPlace = board->getPlaceByCoord(column, row);
        if(  (tempPlace != nullptr)
           &&(tempPlace->getOccupyingPiece() != nullptr))
        {
            moveAccepted = board->movePiece(tempPlace, this->selectedPlace);
        }
        if(  (selectedPlace->getOccupyingPiece() == nullptr)
           ||(moveAccepted == true))
        {
            selectedPlace = nullptr;
        }
    }
    return moveAccepted;
}

void BoardQObjectAbstraction::startANew()
{
    if(this->board != nullptr)
    {
        delete this->board;
    }
    this->board = new Board();
    this->selectedPlace = nullptr;
}

bool BoardQObjectAbstraction::getPieceLetterAndSide(const int column,
                                                    const int row,
                                                    QObject* square)
{
    bool returned = false;
    if(this->board != nullptr)
    {
        IPiece* piece = board->getPlaceByCoord(column,row)->getOccupyingPiece();
        if(piece != nullptr)
        {
            char pieceLetter = piece->getPieceLetter();
            side_t pieceSide = piece->getPieceSide();

            square->setProperty("pieceLetter", &pieceLetter);
            square->setProperty("pieceSide", pieceSide);
            returned = true;
        }
        else
        {
            square->setProperty("pieceLetter", "");
        }
    }
    else
    {
        square->setProperty("pieceLetter", "");
    }
    return returned;
}
void BoardQObjectAbstraction::saveGame(QObject* obj)
{
    std::ofstream fs(obj->property("fileUrl")
                         .toUrl()
                         .toLocalFile()
                         .toStdString());
    if(fs.is_open())
    {
        serializeMoveList(board->getMoveList(), &fs);
        fs.close();
    }
}

bool BoardQObjectAbstraction::loadGame(QObject *obj)
{
    bool returned = false;
    std::ifstream fs(obj->property("fileUrl")
                         .toUrl()
                         .toLocalFile()
                         .toStdString());
    if(fs.is_open())
    {
        std::list<Move> l;
        returned = deSerializeMoveList(&l, &fs);
        fs.close();
        if (returned == true)
        {
            std::list<Move>::iterator i = l.begin();
            this->startANew();
            while((returned == true) && (i != l.end()))
            {
                returned = board->movePiece(
                                board->getPlaceByCoord(i->startColumn,
                                                       i->startRow),
                                board->getPlaceByCoord(i->endColumn,
                                                       i->endRow));
                i++;
            }
            while(board->atStart() != true)
            {
                board->movePrevious();
            }
        }
    }

    return returned;
}

bool BoardQObjectAbstraction::canMoveNext()
{
    bool returned = false;
    if((board != nullptr) && (board->atEnd() == false))
    {
        returned = true;
    }
    return returned;
}

bool BoardQObjectAbstraction::canMovePrevious()
{
    bool returned = false;
    if((board != nullptr) && (board->atStart() == false))
    {
        returned = true;
    }
    return returned;
}

bool BoardQObjectAbstraction::issueMoveNext()
{
    bool returned = false;
    if(board->atEnd() == false)
    {
        returned = board->moveNext();
    }
    return returned;
}

bool BoardQObjectAbstraction::issueMovePrevious()
{
    bool returned = false;
    if(board->atStart() == false)
    {
        returned = board->movePrevious();
    }
    return returned;
}

