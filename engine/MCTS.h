#ifndef MCTS_H
#define MCTS_H

#include "Board.h"

#include <cmath>
#include <vector>
using namespace std;

class MCTS
{
  private :
    MCTS *mcts;

    Board *board;

    int boardPositionId;
    int pieceId;
    int selectedPieceId;
    bool humanMovesFirst;

    int nActions;
    double epsilon;

    vector<MCTS *> children;
    double nVisits, totValue;

    MCTS * select();

  public :
    MCTS();

    void setBoard( Board *board );

    void setPieceId( int pieceId );
    void setBoardPositionId( int boardPositionId );
    void setSelectedPieceId( int selectedPieceId );

    void search();
    void expand();
    void expand2();
    double rollOut( MCTS * expandedNode );
    void updateStats( double value );

    void getNextMovement( int & pieceId, int & boardPositionId );
    bool getWinningMovement( int & boardPositionId );

    void setHumanMovesFirst( bool value );
};

#endif // MCTS_H
