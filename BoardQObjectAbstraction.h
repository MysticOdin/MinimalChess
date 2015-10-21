#ifndef BOARDQOBJECTABSTRACTION_H
#define BOARDQOBJECTABSTRACTION_H

#include <QObject>
#include "ChessGenericTypes.h"
#include <QUrl>

class Board;
class Place;
class BoardQObjectAbstraction : public QObject
{
    Q_OBJECT
public:
    explicit BoardQObjectAbstraction(QObject *parent = nullptr);
    ~BoardQObjectAbstraction();
    Q_INVOKABLE void stopGame(void);
    Q_INVOKABLE bool selectSquare(int column, int row);
    Q_INVOKABLE void startANew(void);
    Q_INVOKABLE bool getPieceLetterAndSide(int column, int row, QObject *square);
    Q_INVOKABLE void saveGame(QObject *obj);
    Q_INVOKABLE bool loadGame(QObject *obj);
    Q_INVOKABLE bool canMoveNext(void);
    Q_INVOKABLE bool canMovePrevious(void);
    Q_INVOKABLE bool issueMoveNext(void);
    Q_INVOKABLE bool issueMovePrevious(void);
    Q_INVOKABLE int getCheckStatus(void);
    template<typename T,typename V>
    bool selectSquare(T,V) = delete;

signals:

public slots:
private:
    Board* board;
    Place* selectedPlace;
};

#endif // BOARDQOBJECTABSTRACTION_H
