#include <QDebug>

#include "PlayGame.h"

#include <ctime>

PlayGame::PlayGame()
{
  board = new Board();

  isHumanFirstPlayer = false;
  isHumanTurn = true;

  humanPlayed = false;
  computerPieceSelected = false;
}

void PlayGame::run()
{

  srand(time(NULL));

  int moveNumber = 0;
  while ( moveNumber < 15 )
  {
    // Human turn
    if ( isHumanTurn )
    {
      // Next turn computer
      isHumanTurn = false;

      // Select human piece
      MCTS mcts;
      mcts.setBoard( board );
      mcts.setHumanMovesFirst( true );

      int n = 10;
      for ( int i = 0; i < n; i++ )
      {
        mcts.expand2();
        mcts.search();
      }

      int pieceIdTemp, boardPositionIdTemp;
      mcts.getNextMovement( pieceIdTemp, boardPositionIdTemp );
      emit humanPieceSelected( pieceIdTemp );

      // Wait for the human player to play
      while ( !humanPlayed );
      mutex.lock();
      humanPlayed = false;
      mutex.unlock();
    }

    // Computer turn
    else
    {
      // Next turn human
      isHumanTurn = true;

      // Wait for the human player to chose the piece
      while ( !computerPieceSelected );
      mutex.lock();
      computerPieceSelected = false;
      mutex.unlock();

      int pieceIdTemp, boardPositionIdTemp;

      MCTS mcts;
      mcts.setBoard( board );
      mcts.setHumanMovesFirst( false );
      mcts.setSelectedPieceId( pieceSelected );
      mcts.expand();

      if ( !mcts.getWinningMovement( boardPositionIdTemp ) )
      {
        int n = 1;
        for ( int i = 0; i < n; i++ )
          mcts.search();

        mcts.getNextMovement( pieceIdTemp, boardPositionIdTemp );
      }
      board->makeMovement( pieceSelected, boardPositionIdTemp, 1 );
      board->print();

      if ( board->isWinningState() )
      {
        qDebug() << "Computer wins";
        qDebug() << "Game over!!!";
      }

      for( int i = 0; i < 10000; i++ );

      emit computerPlayed( pieceSelected, boardPositionIdTemp );
    }
    moveNumber++;
  }
}

void PlayGame::setFirstPlayer( bool value )
{
  isHumanFirstPlayer = value;
  isHumanTurn = true;
}

void PlayGame::getNextMovement( int & pieceId, int & boardPositionId, int moveNumber )
{
}

void PlayGame::humanPlay( int pieceId, int boardPositionId )
{
  board->makeMovement( pieceId, boardPositionId, 1 );
  board->print();

  if ( board->isWinningState() )
  {
    qDebug() << "Human wins";
    qDebug() << "Game over!!!";
  }

  mutex.lock();
  humanPlayed = true;
  mutex.unlock();
}

void PlayGame::computerPieceSelect( int pieceId )
{
  pieceSelected = pieceId;

  mutex.lock();
  computerPieceSelected = true;
  mutex.unlock();
}

