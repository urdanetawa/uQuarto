#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QPiece.h"

#include <vector>
#include <sstream>
//++++++++++++++++++++++
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//++++++++++++++++++++++
using namespace std;

#include <QtGui/QMainWindow>

class QGridLayout;
class QPushButton;
class QLabel;

class MainWindow : public QMainWindow
{
  Q_OBJECT

  private :
    QGridLayout *boardLayout;
    QGridLayout *pieceLayout;
    QPushButton *selectPieceButton;
    QLabel *selectedPiece;

    bool isPieceSelected;
    bool isBoardPositionSelected;

    int currentPieceId;
    int currentBoardPositionId;

    vector<QPiece *> pieces;
    vector<QPiece *> boardPieces;

    bool isHumanTurnToChoose;
    bool isHumanTurnToPutPiece;

  public :
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initBoard();
    void initPieces();

    void updateSelectButton();

    static string getImageName( int id )
    {
      stringstream ss;
      ss << id;

      string s = ":/images/p";
      s.append( ss.str() );
      s.append( ".jpg" );

      return s;
    }

  public slots :
    void selectPiece( int id );
    void selectBoardPosition( int id );
    void clickSelectButton();

    void computerPlay( int pieceId, int boardPositionId );
    void humanPieceSelect( int pieceId );

  signals :
    void humanPlayed( int pieceId, int boardPositionId );
    void computerPieceSelected( int pieceId );
};

#endif // MAINWINDOW_H
