#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

#include <vector>
using namespace std;

class Board
{
  private :
    double board[ 16 ];
    int usedPieces[ 16 ];
    int nPlays;

    vector<Piece> pieces;

  public :
    Board();

    void getChild( int & pieceId, int & boardPositionId );
    void makeMovement( int pieceId, int boardPositionId, int board = 0 );
    int getNumberPlays();
    bool isWinningState();

    bool getWinningMovement( int selectedPiece, int & boardPositionId );

    int getNumberPiecesRow( int row,
                            vector<int> & missingBoardPositionIds, vector<int> & usedBoardPositionIds );
    int getNumberPiecesColumn( int column,
                               vector<int> & missingBoardPositionIds, vector<int> & usedBoardPositionIds );

    vector<int> getUnusedPieces();
    vector<int> getEmptyPositions();

    void print();
};

#endif // BOARD_H
