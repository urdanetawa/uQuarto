#ifndef QPIECE_H
#define QPIECE_H

#include <string>
using namespace std;

#include <QLabel>

class QPiece : public QLabel
{
  Q_OBJECT

  private :
    int id;
    int type;
    string image;

  protected :
    void mousePressEvent( QMouseEvent * event );

  public :
    QPiece( int id, string image );
    void setId( int id );
    void setImage( string image );
    void setType( int type );
    void updateImage();

  signals:
    void clicked( int id );
};

#endif // QPIECE_H
