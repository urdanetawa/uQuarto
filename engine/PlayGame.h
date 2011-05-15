#ifndef PLAYGAME_H
#define PLAYGAME_H

#include "Board.h"
#include "MCTS.h"

#include <QThread>
#include <QMutex>

class PlayGame : public QThread
{
  Q_OBJECT

  private :
    Board *board;
    bool isHumanFirstPlayer;
    bool isHumanTurn;

    bool humanPlayed;
    bool computerPieceSelected;      

    QMutex mutex;

    int pieceSelected;

  protected :
    void run();

  public :
    PlayGame();
    void setFirstPlayer( bool value );
    void getNextMovement( int & pieceId, int & boardPositionId, int moveNumber );

  public slots :
    void humanPlay( int pieceId, int boardPositionId );
    void computerPieceSelect( int pieceId );

  signals :
    void computerPlayed( int pieceId, int boardPositionId );
    void humanPieceSelected( int pieceId );
};

#endif // PLAYGAME_H
