#include "stdlib.h"
#include "Board.h"
#include "Place.h"
#include "IPiece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

Board::Board(void)
{
    turn = WHITE_SIDE;
    currentMove = moveList.end();
    for(int temp_row = 0; temp_row < 8; temp_row++)
    {
        for(int temp_column = 0; temp_column < 8; temp_column++)
        {
            board[temp_row][temp_column] = new Place(temp_column, temp_row);
        }
    }
    // white pawns
    for(int i = 0; i < 8; i++)
    {
        board[ROW_2][i]->setOccupyingPiece(
                    new Pawn(WHITE_SIDE, board[ROW_2][i], this));
    }
    // black pawns
    for(int i = 0; i < 8; i++)
    {
        board[ROW_7][i]->setOccupyingPiece(
                    new Pawn(BLACK_SIDE, board[ROW_7][i], this));
    }

    // Rooks
    board[ROW_1][COLUMN_A]->setOccupyingPiece(
                new Rook(WHITE_SIDE, board[ROW_1][COLUMN_A], this));
    board[ROW_1][COLUMN_H]->setOccupyingPiece(
                new Rook(WHITE_SIDE, board[ROW_1][COLUMN_H], this));
    board[ROW_8][COLUMN_A]->setOccupyingPiece(
                new Rook(BLACK_SIDE, board[ROW_8][COLUMN_A], this));
    board[ROW_8][COLUMN_H]->setOccupyingPiece(
                new Rook(BLACK_SIDE, board[ROW_8][COLUMN_H], this));

    // Knights
    board[ROW_1][COLUMN_B]->setOccupyingPiece(
                new Knight(WHITE_SIDE, board[ROW_1][COLUMN_B], this));
    board[ROW_1][COLUMN_G]->setOccupyingPiece(
                new Knight(WHITE_SIDE, board[ROW_1][COLUMN_G], this));
    board[ROW_8][COLUMN_B]->setOccupyingPiece(
                new Knight(BLACK_SIDE, board[ROW_8][COLUMN_B], this));
    board[ROW_8][COLUMN_G]->setOccupyingPiece(
                new Knight(BLACK_SIDE, board[ROW_8][COLUMN_G], this));

    // Bishops
    board[ROW_1][COLUMN_C]->setOccupyingPiece(
                new Bishop(WHITE_SIDE, board[ROW_1][COLUMN_C], this));
    board[ROW_1][COLUMN_F]->setOccupyingPiece(
                new Bishop(WHITE_SIDE, board[ROW_1][COLUMN_F], this));
    board[ROW_8][COLUMN_C]->setOccupyingPiece(
                new Bishop(BLACK_SIDE, board[ROW_8][COLUMN_C], this));
    board[ROW_8][COLUMN_F]->setOccupyingPiece(
                new Bishop(BLACK_SIDE, board[ROW_8][COLUMN_F], this));

    // Queens
    board[ROW_1][COLUMN_D]->setOccupyingPiece(
                new Queen(WHITE_SIDE, board[ROW_1][COLUMN_D], this));
    board[ROW_8][COLUMN_D]->setOccupyingPiece(
                new Queen(BLACK_SIDE, board[ROW_8][COLUMN_D], this));

    // Kings
    this->kings[WHITE_SIDE] =
                new King(WHITE_SIDE, board[ROW_1][COLUMN_E], this);
    board[ROW_1][COLUMN_E]->setOccupyingPiece(kings[WHITE_SIDE]);

    this->kings[BLACK_SIDE] =
                new King(BLACK_SIDE, board[ROW_8][COLUMN_E], this);
    board[ROW_8][COLUMN_E]->setOccupyingPiece(kings[BLACK_SIDE]);
}

Board::~Board()
{
    for(int temp_row = 0; temp_row < 8; temp_row++)
    {
        for(int temp_column = 0; temp_column < 8; temp_column++)
        {
            delete board[temp_row][temp_column];
        }
    }
    for(std::list<Move>::iterator i = moveList.begin(); i != currentMove; i++)
    {
        if(i->capturedPiece != nullptr)
        {
            delete i->capturedPiece;
        }
    }
}
void Board::appendMove(Place* src, Place* dist, IPiece* capturedPiece, MoveType mt)
{
    Move move;
    IPiece* movedPiece = src->getOccupyingPiece();
    move.startRow = src->getRow();
    move.startColumn = src->getColumn();
    move.endRow = dist->getRow();
    move.endColumn = dist->getColumn();
    move.capturedPiece = capturedPiece;
    move.mvType = mt;
    move.firstMove = movedPiece->isPieceFirstMove();
    moveList.erase(currentMove,moveList.end());
    moveList.push_back(move);
    movedPiece->movePiece(dist);
    currentMove = moveList.end();
    turn = (turn + 1) & 1;
}

bool Board::checkKingAndAppendMove(Place* src, Place* dist, Place* capturedPiecePlace, MoveType mt)
{
    bool returned = false;
    if(willKingBeChecked(src, dist, capturedPiecePlace) == true)
    {
        returned = false;
    }
    else
    {
        appendMove(src,dist,capturedPiecePlace->getOccupyingPiece(),mt);
        returned = true;
    }
    return returned;
}

bool Board::movePiece(Place* src, Place* dist)
{
    bool returned = false;
    Place * capturedPawnPlace;
    IPiece* movedPiece = src->getOccupyingPiece();
    if((movedPiece != nullptr) && (movedPiece->getPieceSide() == turn))
    {
        MoveType mt = movedPiece->isMoveAllowed(dist);
        switch(mt)
        {
        case ALLOWED:
            returned = checkKingAndAppendMove(src, dist, dist, mt);
            break;
        case EN_PASSANT:
            capturedPawnPlace = board[src->getRow()][dist->getColumn()];
            returned = checkKingAndAppendMove(src, dist, capturedPawnPlace, mt);
            if(returned == true)
            {
                capturedPawnPlace->setOccupyingPiece(nullptr);
            }
            break;
        case RIGHT_CASTLE:
            appendMove(src, dist, nullptr, mt);
            board[src->getRow()][COLUMN_H]
                        ->getOccupyingPiece()
                        ->movePiece(board[src->getRow()][COLUMN_F]);
            returned = true;
            break;
        case LEFT_CASTLE:
            appendMove(src, dist, nullptr, mt);
            board[src->getRow()][COLUMN_A]
                        ->getOccupyingPiece()
                        ->movePiece(board[src->getRow()][COLUMN_D]);
            returned = true;
        default:
            break;
        }
    }
    return returned;
}

bool Board::willKingBeChecked(Place* src, Place* dist, Place* capturedPiecePlace)
{
    bool returned = false;
    IPiece * capturedPiece = capturedPiecePlace->getOccupyingPiece();
    IPiece * movedPiece = src->getOccupyingPiece();
    bool isPieceFirstMove = movedPiece->isPieceFirstMove();
    capturedPiecePlace->setOccupyingPiece(nullptr);
    movedPiece->movePiece(dist);
    returned = this->isPlaceChecked(kings[turn]->getPiecePlace());
    if(isPieceFirstMove == true)
    {
        movedPiece->resetPiece(src);
    }
    else
    {
        movedPiece->movePiece(src);
    }
    capturedPiecePlace->setOccupyingPiece(capturedPiece);
    return returned;
}

bool Board::isPathClear(Place *place1, Place *place2)
{
    bool returned = false;
    coord_t this_row = place1->getRow();
    coord_t this_column = place1->getColumn();
    coord_t next_row = place2->getRow();
    coord_t next_column = place2->getColumn();
    coord_t diff_column = abs(next_column - this_column);
    coord_t diff_row = abs(next_row - this_row);
    coord_t row_increment = 1;
    coord_t column_increment = 1;
    if (diff_column == 0)
    {
        column_increment = 0;
    }
    if (diff_row == 0)
    {
        row_increment = 0;
    }
    if(  ((diff_column == 0)||(diff_row == 0))
       ||(diff_column == diff_row))
    {

        returned = true;
        if((this_row + diff_row) != next_row)
        {
            row_increment = (coord_t)(-1);
        }
        if((this_column + diff_column) != next_column)
        {
            column_increment = (coord_t)(-1);
        }
        this_row = this_row + row_increment;
        this_column = this_column + column_increment;
        while(  (returned == true)
              &&((this_row != next_row) || (this_column != next_column)))
        {
            if(board[this_row][this_column]->getOccupyingPiece() != nullptr)
            {
                returned = false;
            }
            this_row = this_row + row_increment;
            this_column = this_column + column_increment;
        }
    }
    return returned;
}

bool Board::isPlaceChecked(Place *place)
{
    bool returned = false;
    bool created_dummy = false;
    if(place->getOccupyingPiece() == nullptr)
    {
        place->setOccupyingPiece(new Pawn(turn, place, this));
        created_dummy = true;
    }
    for(int i = 0; (i < 8) && (returned == false); i++)
    {
        for(int j = 0; (j < 8) && (returned == false); j++)
        {
            IPiece * tested_piece = board[i][j]->getOccupyingPiece();
            if(  (tested_piece != nullptr)
               &&(tested_piece->getPieceSide() != turn))
            {
                if(tested_piece == kings[BLACK_SIDE])
                {
                    returned = kings[BLACK_SIDE]->isCheckedPlace(place);
                }
                else if(tested_piece == kings[WHITE_SIDE])
                {
                    returned = kings[WHITE_SIDE]->isCheckedPlace(place);
                }
                else if(tested_piece->isMoveAllowed(place) != NOT_ALLOWED)
                {
                     returned = true;
                }
            }
        }
    }
    if (created_dummy == true)
    {
        delete place->getOccupyingPiece();
        place->setOccupyingPiece(nullptr);
    }
    return returned;
}

bool Board::promote(Place *place, Pawn *pawn)
{
    bool returned = false;
    return returned;
}

Place *Board::getPlaceByCoord(coord_t column, coord_t row)
{
    return board[row][column];
}

void Board::getLastMoveCoord(coord_t *column, coord_t *row)
{
    std::list<Move>::iterator previousMove = currentMove;
    previousMove--;
    *column = (previousMove)->endColumn;
    *row = (previousMove)->endRow;
}

const std::list<Move> *Board::getMoveList()
{
    return &moveList;
}

bool Board::atEnd()
{
    bool returned = false;
    if(currentMove == moveList.end())
    {
        returned = true;
    }
    return returned;
}

bool Board::atStart()
{
    bool returned = false;
    if(currentMove == moveList.begin())
    {
        returned = true;
    }
    return returned;
}

bool Board::moveNext()
{
    bool returned = false;
    if(atEnd() == false)
    {
        Place* currentPlace = getPlaceByCoord(currentMove->startColumn,
                                              currentMove->startRow);
        Place* nextPlace = getPlaceByCoord(currentMove->endColumn,
                                           currentMove->endRow);
        currentPlace->getOccupyingPiece()->movePiece(nextPlace);
        switch(currentMove->mvType)
        {
        case EN_PASSANT:
            getPlaceByCoord(currentMove->endColumn,
                            currentMove->startRow)->setOccupyingPiece(nullptr);
            break;
        case RIGHT_CASTLE:
            board[currentPlace->getRow()][COLUMN_H]
                           ->getOccupyingPiece()
                           ->movePiece(board[currentPlace->getRow()][COLUMN_F]);
            break;
        case LEFT_CASTLE:
            board[currentPlace->getRow()][COLUMN_A]
                           ->getOccupyingPiece()
                           ->movePiece(board[currentPlace->getRow()][COLUMN_D]);
            break;
        default:
            break;
        }
        currentMove++;
        turn = (turn + 1) & 1;
        returned = true;
    }
    return returned;
}

bool Board::movePrevious()
{
    bool returned = false;
    if(atStart() == false)
    {
        currentMove--;
        Place* currentPlace = getPlaceByCoord(currentMove->endColumn, currentMove->endRow);
        Place* nextPlace = getPlaceByCoord(currentMove->startColumn, currentMove->startRow);
        if(currentMove->firstMove == true)
        {
            currentPlace->getOccupyingPiece()->resetPiece(nextPlace);
        }
        else
        {
            currentPlace->getOccupyingPiece()->movePiece(nextPlace);
        }
        if(currentMove->capturedPiece != nullptr)
        {
            if(currentMove->mvType == EN_PASSANT)
            {
                currentPlace = getPlaceByCoord(currentMove->endColumn, currentMove->startRow);
            }
            currentPlace->setOccupyingPiece(currentMove->capturedPiece);
        }
        else if(currentMove->mvType == RIGHT_CASTLE)
        {
            board[nextPlace->getRow()][COLUMN_F]
                        ->getOccupyingPiece()
                        ->movePiece(board[nextPlace->getRow()][COLUMN_H]);
        }
        else if(currentMove->mvType == LEFT_CASTLE)
        {
            board[nextPlace->getRow()][COLUMN_D]
                        ->getOccupyingPiece()
                        ->movePiece(board[nextPlace->getRow()][COLUMN_A]);
        }
        turn = (turn + 1) & 1;
        returned = true;
    }
    return returned;
}

check_status_t Board::getCheckStatus()
{
    check_status_t returned = NOT_CHECKED;
    if(isPlaceChecked(kings[turn]->getPiecePlace()))
    {
        returned = CHECKMATE;
        for(int temp_row = 0; (temp_row < 8) && (returned == CHECKMATE); temp_row++)
        {
            for(int temp_column = 0; (temp_column < 8) && (returned == CHECKMATE); temp_column++)
            {
                Place * src = board[temp_row][temp_column];
                IPiece * currentPiece = src->getOccupyingPiece();
                if((currentPiece != nullptr) && (currentPiece->getPieceSide() == turn))
                {
                    for(int row = 0; (row < 8) && (returned == CHECKMATE); row++)
                    {
                        for(int column = 0; (column < 8) && (returned == CHECKMATE); column++)
                        {
                            Place * dist = board[row][column];
                            MoveType mt = currentPiece->isMoveAllowed(dist);
                            if(mt != NOT_ALLOWED)
                            {
                                if(currentPiece == kings[turn])
                                {
                                    /* to avoid having to call willKingBeChecked and the loop inside isPlaceChecked for
                                     * no reason */
                                    returned = CHECK;
                                }
                                else
                                {
                                    Place * capturedPiecePlace = dist;
                                    if(mt == EN_PASSANT)
                                    {
                                        capturedPiecePlace = board[src->getRow()][dist->getColumn()];
                                    }
                                    if(willKingBeChecked(src, dist, capturedPiecePlace) == false)
                                    {
                                        returned = CHECK;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return returned;
}

