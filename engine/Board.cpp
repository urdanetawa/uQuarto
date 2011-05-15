#include <QDebug>

#include "Board.h"

#include <ctime>

Board::Board()
{
  nPlays = 0;

  // Init board and used pieces
  for ( int i = 0; i < 16; i++ )
    board[i] = -1, usedPieces[i] = -1;

  // Init pieces
  // Id, isTall, isBlack, isSquare, isHollow
  // Piece 0
  Piece piece0( 0, true, false, true, false );
  // Piece 1
  Piece piece1( 1, true, false, true, true );
  // Piece 2
  Piece piece2( 2, false, false, true, false );
  // Piece 3
  Piece piece3( 3, false, false, true, true );
  // Piece 4
  Piece piece4( 4, true, false, false, false );
  // Piece 5
  Piece piece5( 5, true, false, false, true );
  // Piece 6
  Piece piece6( 6, false, false, false, false );
  // Piece 7
  Piece piece7( 7, false, false, false, true );
  // Piece 8
  Piece piece8( 8, true, true, true, false );
  // Piece 9
  Piece piece9( 9, true, true, true, true );
  // Piece 10
  Piece piece10( 10, false, true, true, false );
  // Piece 11
  Piece piece11( 11, false, true, true, true );
  // Piece 12
  Piece piece12( 12, true, true, false, false );
  // Piece 13
  Piece piece13( 13, true, true, false, true );
  // Piece 14
  Piece piece14( 14, false, true, false, false );
  // Piece 15
  Piece piece15( 15, false, true, false, true );

  pieces.push_back( piece0 );
  pieces.push_back( piece1 );
  pieces.push_back( piece2 );
  pieces.push_back( piece3 );
  pieces.push_back( piece4 );
  pieces.push_back( piece5 );
  pieces.push_back( piece6 );
  pieces.push_back( piece7 );
  pieces.push_back( piece8 );
  pieces.push_back( piece9 );
  pieces.push_back( piece10 );
  pieces.push_back( piece11 );
  pieces.push_back( piece12 );
  pieces.push_back( piece13 );
  pieces.push_back( piece14 );
  pieces.push_back( piece15 );
}

void Board::getChild( int & pieceId, int & boardPositionId )
{
  // Getting the piece
  vector<int> unusedPieces;
  //srand(time(NULL));
  for ( int i = 0; i < 16; i++ )
    if ( usedPieces[i] == -1 )
      unusedPieces.push_back( i );

  int position = rand() % unusedPieces.size();
  int pieceIdTemp = unusedPieces[position];

  // Getting the board position
  vector<int> emptySpaces;

  for ( int i = 0; i < 16; i++ )
    if ( board[i] == -1 )
       emptySpaces.push_back( i );

  position = rand() % emptySpaces.size();
  int boardPositionIdTemp = emptySpaces[position];

  pieceId = pieceIdTemp;
  boardPositionId = boardPositionIdTemp;
}

void Board::makeMovement( int pieceId, int boardPositionId, int aux )
{
  if ( ( pieceId >= 0 ) && ( pieceId < 16 ) && ( boardPositionId >= 0 ) && ( boardPositionId < 16 ) )
  {
    usedPieces[ pieceId ] = 1;
    board[ boardPositionId ] = pieceId;

    //if ( aux )
      //qDebug() << "Movement, pieceId: " << pieceId << " boardPositionId: " << boardPositionId;

    nPlays++;
  }
}

int Board::getNumberPlays()
{
  return nPlays;
}

bool Board::isWinningState()
{
  // check horizontal lines
  int k = 0;
  for ( int i = 0; i < 4; i++ )
  {
    // Checking each row with 4 elements
    if ( ( board[k] != -1 ) && ( board[k+1] != -1 ) && ( board[k+2] != -1 ) && ( board[k+3] != -1 ) )
    {      
      // Checking tall property
      if ( (pieces.at( board[k] )).getIsTall() && (pieces.at( board[k+1] )).getIsTall() && (pieces.at( board[k+2] )).getIsTall() && (pieces.at( board[k+3] )).getIsTall() )
      {
        //qDebug() << "Wins tall";
        return true;
      }
      // Checking short property
      if ( !(pieces.at( board[k] )).getIsTall() && !(pieces.at( board[k+1] )).getIsTall() && !(pieces.at( board[k+2] )).getIsTall() && !(pieces.at( board[k+3] )).getIsTall() )
      {
        //qDebug() << "Wins short";
        return true;
      }

      // Checking black property
      if ( (pieces.at( board[k] )).getIsBlack() && (pieces.at( board[k+1] )).getIsBlack() && (pieces.at( board[k+2] )).getIsBlack() && (pieces.at( board[k+3] )).getIsBlack() )
      {
        //qDebug() << "Wins black";
        return true;
      }
      // Checking white property
      if ( !(pieces.at( board[k] )).getIsBlack() && !(pieces.at( board[k+1] )).getIsBlack() && !(pieces.at( board[k+2] )).getIsBlack() && !(pieces.at( board[k+3] )).getIsBlack() )
      {
        //qDebug() << "Wins white";
        return true;
      }

      // Checking square property
      if ( (pieces.at( board[k] )).getIsSquare() && (pieces.at( board[k+1] )).getIsSquare() && (pieces.at( board[k+2] )).getIsSquare() && (pieces.at( board[k+3] )).getIsSquare() )
      {
        //qDebug() << "Wins square";
        return true;
      }
      // Checking round property
      if ( !(pieces.at( board[k] )).getIsSquare() && !(pieces.at( board[k+1] )).getIsSquare() && !(pieces.at( board[k+2] )).getIsSquare() && !(pieces.at( board[k+3] )).getIsSquare() )
      {
        //qDebug() << "Wins round";
        return true;
      }

      // Checking hollow property
      if ( (pieces.at( board[k] )).getIsHollow() && (pieces.at( board[k+1] )).getIsHollow() && (pieces.at( board[k+2] )).getIsHollow() && (pieces.at( board[k+3] )).getIsHollow() )
      {
        //qDebug() << "Wins hollow";
        return true;
      }
      // Checking solid property
      if ( !(pieces.at( board[k] )).getIsHollow() && !(pieces.at( board[k+1] )).getIsHollow() && !(pieces.at( board[k+2] )).getIsHollow() && !(pieces.at( board[k+3] )).getIsHollow() )
      {
        //qDebug() << "Wins solid";
        return true;
      }
    }
    k += 4;
  }

  // check vertical lines
  k = 0;
  for ( int i = 0; i < 4; i++ )
  {
    // Checking each column with 4 elements
    if ( ( board[k] != -1 ) && ( board[k+4] != -1 ) && ( board[k+8] != -1 ) && ( board[k+12] != -1 ) )
    {
      // Checking tall property
      if ( (pieces.at( board[k] )).getIsTall() && (pieces.at( board[k+4] )).getIsTall() && (pieces.at( board[k+8] )).getIsTall() && (pieces.at( board[k+12] )).getIsTall() )
      {
        //qDebug() << "Wins tall";
        return true;
      }
      // Checking short property
      if ( !(pieces.at( board[k] )).getIsTall() && !(pieces.at( board[k+4] )).getIsTall() && !(pieces.at( board[k+8] )).getIsTall() && !(pieces.at( board[k+12] )).getIsTall() )
      {
        //qDebug() << "Wins c short";
        return true;
      }

      // Checking black property
      if ( (pieces.at( board[k] )).getIsBlack() && (pieces.at( board[k+4] )).getIsBlack() && (pieces.at( board[k+8] )).getIsBlack() && (pieces.at( board[k+12] )).getIsBlack() )
      {
        //qDebug() << "Wins c black";
        return true;
      }
      // Checking white property
      if ( !(pieces.at( board[k] )).getIsBlack() && !(pieces.at( board[k+4] )).getIsBlack() && !(pieces.at( board[k+8] )).getIsBlack() && !(pieces.at( board[k+12] )).getIsBlack() )
      {
        //qDebug() << "Wins c white";
        return true;
      }

      // Checking square property
      if ( (pieces.at( board[k] )).getIsSquare() && (pieces.at( board[k+4] )).getIsSquare() && (pieces.at( board[k+8] )).getIsSquare() && (pieces.at( board[k+12] )).getIsSquare() )
      {
        //qDebug() << "Wins c square";
        return true;
      }
      // Checking round property
      if ( !(pieces.at( board[k] )).getIsSquare() && !(pieces.at( board[k+4] )).getIsSquare() && !(pieces.at( board[k+8] )).getIsSquare() && !(pieces.at( board[k+12] )).getIsSquare() )
      {
        //qDebug() << "Wins c round";
        return true;
      }

      // Checking hollow property
      if ( (pieces.at( board[k] )).getIsHollow() && (pieces.at( board[k+4] )).getIsHollow() && (pieces.at( board[k+8] )).getIsHollow() && (pieces.at( board[k+12] )).getIsHollow() )
      {
        //qDebug() << "Wins c hollow";
        return true;
      }
      // Checking solid property
      if ( !(pieces.at( board[k] )).getIsHollow() && !(pieces.at( board[k+4] )).getIsHollow() && !(pieces.at( board[k+8] )).getIsHollow() && !(pieces.at( board[k+12] )).getIsHollow() )
      {
        //qDebug() << "Wins c solid";
        return true;
      }
    }
    k++;
  }

  // check diagonals
  // First diagonal
  if ( ( board[0] != -1 ) && ( board[5] != -1 ) && ( board[10] != -1 ) && ( board[15] != -1 ) )
  {
    // Checking tall property
    if ( (pieces.at( board[0] )).getIsTall() && (pieces.at( board[5] )).getIsTall() && (pieces.at( board[10] )).getIsTall() && (pieces.at( board[15] )).getIsTall() )
      return true;
    // Checking short property
    if ( !(pieces.at( board[0] )).getIsTall() && !(pieces.at( board[5] )).getIsTall() && !(pieces.at( board[10] )).getIsTall() && !(pieces.at( board[15] )).getIsTall() )
      return true;

    // Checking black property
    if ( (pieces.at( board[0] )).getIsBlack() && (pieces.at( board[5] )).getIsBlack() && (pieces.at( board[10] )).getIsBlack() && (pieces.at( board[15] )).getIsBlack() )
      return true;
    // Checking white property
    if ( !(pieces.at( board[0] )).getIsBlack() && !(pieces.at( board[5] )).getIsBlack() && !(pieces.at( board[10] )).getIsBlack() && !(pieces.at( board[15] )).getIsBlack() )
      return true;

    // Checking square property
    if ( (pieces.at( board[0] )).getIsSquare() && (pieces.at( board[5] )).getIsSquare() && (pieces.at( board[10] )).getIsSquare() && (pieces.at( board[15] )).getIsSquare() )
    return true;
    // Checking round property
    if ( !(pieces.at( board[0] )).getIsSquare() && !(pieces.at( board[5] )).getIsSquare() && !(pieces.at( board[10] )).getIsSquare() && !(pieces.at( board[15] )).getIsSquare() )
    return true;

    // Checking hollow property
    if ( (pieces.at( board[0] )).getIsHollow() && (pieces.at( board[5] )).getIsHollow() && (pieces.at( board[10] )).getIsHollow() && (pieces.at( board[15] )).getIsHollow() )
      return true;
    // Checking solid property
    if ( !(pieces.at( board[0] )).getIsHollow() && !(pieces.at( board[5] )).getIsHollow() && !(pieces.at( board[10] )).getIsHollow() && !(pieces.at( board[15] )).getIsHollow() )
    return true;
  }

  // Second diagonal
  if ( ( board[12] != -1 ) && ( board[9] != -1 ) && ( board[6] != -1 ) && ( board[3] != -1 ) )
  {
    // Checking tall property
    if ( (pieces.at( board[12] )).getIsTall() && (pieces.at( board[9] )).getIsTall() && (pieces.at( board[6] )).getIsTall() && (pieces.at( board[3] )).getIsTall() )
      return true;
    // Checking short property
    if ( !(pieces.at( board[12] )).getIsTall() && !(pieces.at( board[9] )).getIsTall() && !(pieces.at( board[6] )).getIsTall() && !(pieces.at( board[3] )).getIsTall() )
      return true;

    // Checking black property
    if ( (pieces.at( board[12] )).getIsBlack() && (pieces.at( board[9] )).getIsBlack() && (pieces.at( board[6] )).getIsBlack() && (pieces.at( board[3] )).getIsBlack() )
      return true;
    // Checking white property
    if ( !(pieces.at( board[12] )).getIsBlack() && !(pieces.at( board[9] )).getIsBlack() && !(pieces.at( board[6] )).getIsBlack() && !(pieces.at( board[3] )).getIsBlack() )
      return true;

    // Checking square property
    if ( (pieces.at( board[12] )).getIsSquare() && (pieces.at( board[9] )).getIsSquare() && (pieces.at( board[6] )).getIsSquare() && (pieces.at( board[3] )).getIsSquare() )
    return true;
    // Checking round property
    if ( !(pieces.at( board[12] )).getIsSquare() && !(pieces.at( board[9] )).getIsSquare() && !(pieces.at( board[6] )).getIsSquare() && !(pieces.at( board[3] )).getIsSquare() )
    return true;

    // Checking hollow property
    if ( (pieces.at( board[12] )).getIsHollow() && (pieces.at( board[9] )).getIsHollow() && (pieces.at( board[6] )).getIsHollow() && (pieces.at( board[3] )).getIsHollow() )
      return true;
    // Checking solid property
    if ( !(pieces.at( board[12] )).getIsHollow() && !(pieces.at( board[9] )).getIsHollow() && !(pieces.at( board[6] )).getIsHollow() && !(pieces.at( board[3] )).getIsHollow() )
    return true;
  }

  // check squares

  return false;
}

bool Board::getWinningMovement( int selectedPiece, int & boardPositionId )
{
  for ( int i = 0; i < 4; i++ )
  {
    vector<int> missingBoardPositionIds;
    vector<int> usedBoardPositionIds;

    // Checking rows
    if ( getNumberPiecesRow( i, missingBoardPositionIds, usedBoardPositionIds ) == 3 )
    {
      qDebug() << "tree rowsww";
      qDebug() << "missing: " << missingBoardPositionIds[0] << " piece: " << selectedPiece;
      board[ missingBoardPositionIds[0] ] = selectedPiece;

      if ( isWinningState() )
      {
        // Getting the winning movement
        boardPositionId = missingBoardPositionIds[0];

        qDebug() << "WINNING STATE (rows), piece id" << selectedPiece << " board position: " << boardPositionId;
        // return to previous state
        board[ missingBoardPositionIds[0] ] = -1;

        return true;
      }
      // return to previous state
      board[ missingBoardPositionIds[0] ] = -1;
    }

    // Checking columns
    if ( getNumberPiecesColumn( i, missingBoardPositionIds, usedBoardPositionIds ) == 3 )
    {
      qDebug() << "tree columns";
      board[ missingBoardPositionIds[0] ] = selectedPiece;

      if ( isWinningState() )
      {
        qDebug() << "WINNING STATE (cols), piece id" << selectedPiece << " board position: " << boardPositionId;

        // Getting the winning movement
        boardPositionId = missingBoardPositionIds[0];

        // return to previous state
        board[ missingBoardPositionIds[0] ] = -1;

        return true;
      }

      // return to previous state
      board[ missingBoardPositionIds[0] ] = -1;
    }

    // Checking squares
  }


  return false;
}

int Board::getNumberPiecesRow( int row, vector<int> & missingBoardPositionIds, vector<int> & usedBoardPositionIds )
{
  int nPiecesRow = 0;

  if ( ( row < 0 ) || ( row > 3 ) )
    return nPiecesRow;

  vector<int> missingBoardPositionIdsTemp;
  vector<int> usedBoardPositionIdsTemp;

  for ( int i = 0; i < 4; i++ )
  {
    if ( board[ ( row * 4 ) + i ] != -1 )
    {
      nPiecesRow++;
      usedBoardPositionIdsTemp.push_back( ( row * 4 ) + i );
    }
    else
    {
      missingBoardPositionIdsTemp.push_back( ( row * 4 ) + i );
    }
  }

  missingBoardPositionIds = missingBoardPositionIdsTemp;
  usedBoardPositionIds = usedBoardPositionIdsTemp;

  return nPiecesRow;
}

int Board::getNumberPiecesColumn( int column, vector<int> & missingBoardPositionIds, vector<int> & usedBoardPositionIds )
{
  int nPiecesColumn = 0;

  if ( ( column < 0 ) || ( column > 3 ) )
    return nPiecesColumn;

  vector<int> missingBoardPositionIdsTemp;
  vector<int> usedBoardPositionIdsTemp;

  for ( int i = 0; i < 16; i += 4 )
  {
    if ( board[ column + i ] != -1 )
    {
      nPiecesColumn++;
      usedBoardPositionIdsTemp.push_back( column + i );
    }
    else
    {
      missingBoardPositionIdsTemp.push_back( column + i );
    }
  }

  missingBoardPositionIds = missingBoardPositionIdsTemp;
  usedBoardPositionIds = usedBoardPositionIdsTemp;

  return nPiecesColumn;
}

vector<int> Board::getUnusedPieces()
{
  vector<int> unusedPieces;

  for ( int i = 0; i < 16; i++ )
  {
    if ( usedPieces[ i ] == -1 )
      unusedPieces.push_back( i );
  }

  return unusedPieces;
}

vector<int> Board::getEmptyPositions()
{
  vector<int> emptyPositions;

  for ( int i = 0; i < 16; i++ )
  {
    if ( board[ i ] == -1 )
      emptyPositions.push_back( i );
  }

  return emptyPositions;

}

void Board::print()
{
  qDebug() << " " << board[0] << " " << board[1] << " " << board[2] << " " << board[3];
  qDebug() << " " << board[4] << " " << board[5] << " " << board[6] << " " << board[7];
  qDebug() << " " << board[8] << " " << board[9] << " " << board[10] << " " << board[11];
  qDebug() << " " << board[12] << " " << board[13] << " " << board[14] << " " << board[15];
  qDebug() << "--";

}
