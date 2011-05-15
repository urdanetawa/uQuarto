#ifndef PIECE_H
#define PIECE_H

class Piece
{
  private :
    int id;

    bool isTall;
    bool isBlack;
    bool isSquare;
    bool isHollow;

  public :
    Piece( int id, bool isTall, bool isBlack, bool isSquare, bool isHollow );

    void setIsTall( bool value );
    bool getIsTall();

    void setIsBlack( bool value );
    bool getIsBlack();

    void setIsSquare( bool value );
    bool getIsSquare();

    void setIsHollow( bool value );
    bool getIsHollow();
};

#endif // PIECE_H
