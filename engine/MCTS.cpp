#include <QDebug>

#include "MCTS.h"

#include <cstdlib>
#include <limits>
#include <ctime>
using namespace std;

MCTS::MCTS()
{
  nVisits = 0.0;
  totValue = 0.0;

  nActions = 5;
  epsilon = 0.0000001;
}

void MCTS::setHumanMovesFirst( bool value )
{
  humanMovesFirst = value;
}

void MCTS::setBoard( Board * board )
{
  this->board = board;
}

void MCTS::setPieceId( int pieceId )
{
  this->pieceId = pieceId;
}

void MCTS::setSelectedPieceId( int pieceId )
{
  selectedPieceId = pieceId;
}

void MCTS::setBoardPositionId( int boardPositionId )
{
  this->boardPositionId = boardPositionId;
}

void MCTS::expand()
{
  vector<int> emptyBoardPositions =  board->getEmptyPositions();
  vector<int>::iterator itr;

  for ( itr = emptyBoardPositions.begin(); itr != emptyBoardPositions.end(); itr++ )
  {
    mcts = new MCTS();
    mcts->setPieceId( selectedPieceId );
    mcts->setBoardPositionId( *itr );
//qDebug() << "available: " << *itr;
    children.push_back( mcts );
  }
}

void MCTS::expand2()
{
  for ( int i=0; i < 1; i++ )
  {
    int pieceId;
    int boardPositionId;

    board->getChild( pieceId, boardPositionId );
    qDebug() << "==" << pieceId <<  " + " << "==" << boardPositionId;

    // Check for duplicated children
    bool existChild = false;
    vector<MCTS *>::iterator itr;
    for ( itr = children.begin(); itr != children.end(); itr++ )
    {
      MCTS *childNode = *itr;
      if ( ( childNode->pieceId == pieceId ) && ( childNode->boardPositionId == boardPositionId ) )
      {
        existChild = true;
        break;
      }
    }

    if ( !existChild )
    {
      mcts = new MCTS();
      mcts->setPieceId( pieceId );
      mcts->setBoardPositionId( boardPositionId );

      children.push_back( mcts );
    }
  }
}

void MCTS::search()
{
  // vector of visited nodes
  vector<MCTS *> visited;

  // Select new node
  MCTS *newNode = select();
  visited.push_back( newNode );

  double value = rollOut( newNode );
  qDebug() << "value: " << value;

  vector<MCTS *>::iterator itr;
  for ( itr = visited.begin(); itr != visited.end(); itr++ )
  {
    MCTS *node = *itr;
    //qDebug() << "adding value: " << value;
    node->updateStats( value );
  }
}

MCTS * MCTS::select()
{
  MCTS *selectedNode;
  double bestValue = -numeric_limits<double>::max();

  vector<MCTS *>::iterator itr;
  for ( itr = children.begin(); itr != children.end(); itr++ )
  {
    MCTS *c = *itr;

    double randomValue = ( (double) rand() / (double) RAND_MAX );

    double uctValue = c->totValue / ( c->nVisits + epsilon ) +
                      sqrt( log( nVisits + 1 ) / ( c->nVisits + epsilon ) ) +
                      randomValue * epsilon;

     // small random number to break ties randomly in unexpanded nodes
    qDebug() << "uctValue: " << uctValue << " randomValue: " << randomValue;
     if ( uctValue > bestValue )
     {
       selectedNode = c;
       bestValue = uctValue;
     }
   }

   return selectedNode;
}

double MCTS::rollOut( MCTS * expandedNode )
{
  // Create a temporal board where the simulation will be rolled out
  Board boardTemp = *board;

  int nPlays = boardTemp.getNumberPlays();

  for ( int i = 0; i < ( 16 - nPlays ); i++ )
  {
    // Make the movement of the expandedNode
    if ( i == 0 )
      boardTemp.makeMovement( expandedNode->pieceId, expandedNode->boardPositionId );
    else
    {
      int boardPositionIdTemp;
      int pieceIdTemp;

      boardTemp.getChild( pieceIdTemp, boardPositionIdTemp );
      boardTemp.makeMovement( pieceIdTemp, boardPositionIdTemp );
    }

    if( boardTemp.isWinningState() )
    {
      if ( humanMovesFirst )
      {
        // Human player wins
        if ( (int)( i % 2 ) != 0 )
        {
          //qDebug() << "compu winsssssss";
          return 1.0;
        }
        // Computer player wins
        else
        {
          ////qDebug() << "human winsssssss";
          return -1.0;
        }
      }
      else
      {
        // Computer player wins
        if ( (int)( i % 2 ) == 0 )
          return 1.0;
        // Human player wins
        else
          return -1.0;
      }
    }
  }

  // For draw returns 0.0
  return 0.0;
}

void MCTS::updateStats( double value )
{
  nVisits++;
  totValue += value;
}

void MCTS::getNextMovement( int & pieceId, int & boardPositionId )
{
  if ( !children.empty() )
  {
    MCTS *bestChildNode = children.at(0);

    //qDebug() << "CHILD ID: " << bestChildNode->pieceId  << " VALUE: " << bestChildNode->totValue;
    vector<MCTS *>::iterator itr;
    for ( itr = children.begin()+1; itr != children.end(); itr++ )
    {
      MCTS *childNode = *itr;

      //qDebug() << "PIECE ID: " << childNode->pieceId << " VALUE: " << childNode->totValue;

      if ( childNode->totValue > bestChildNode->totValue )
        bestChildNode = childNode;
    }

    pieceId = bestChildNode->pieceId;
    boardPositionId = bestChildNode->boardPositionId;
  }
}

bool MCTS::getWinningMovement( int & boardPositionId )
{
  int boardPositionIdTemp;
  bool value = board->getWinningMovement( selectedPieceId, boardPositionIdTemp );

  boardPositionId = boardPositionIdTemp;

  return value;
}
