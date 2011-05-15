#include "Piece.h"

Piece::Piece( int id, bool isTall, bool isBlack, bool isSquare, bool isHollow )
{
  this->id = id;
  this->isTall = isTall;
  this->isBlack = isBlack;
  this->isSquare = isSquare;
  this->isHollow = isHollow;
}

void Piece::setIsTall( bool value )
{
  isTall = value;
}

bool Piece::getIsTall()
{
  return isTall;
}

void Piece::setIsBlack( bool value )
{
  isBlack = value;
}

bool Piece::getIsBlack()
{
  return isBlack;
}

void Piece::setIsSquare( bool value )
{
  isSquare = value;
}

bool Piece::getIsSquare()
{
  return isSquare;
}

void Piece::setIsHollow( bool value )
{
  isHollow = value;
}

bool Piece::getIsHollow()
{
  return isHollow;
}

