#include "QPiece.h"

#include <sstream>
using namespace std;

#include <QDebug>

QPiece::QPiece( int id, string image )
{
  this->id = id;
  this->image = image;

  QPixmap pixMap( image.c_str() );
  setPixmap( pixMap );
}

void QPiece::setId( int id )
{
  this->id = id;
}

void QPiece::setImage( string image )
{
  this->image = image;
}

void QPiece::setType( int type )
{
  this->type = type;
}

void QPiece::updateImage()
{
  QPixmap pixMap( image.c_str() );
  setPixmap( pixMap );
}

void QPiece::mousePressEvent( QMouseEvent * event )
{
  emit clicked( id );
}
