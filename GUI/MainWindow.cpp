#include "MainWindow.h"
#include "QPiece.h"

#include <QDebug>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  isHumanTurnToChoose = false;
  isHumanTurnToPutPiece = true;

  isPieceSelected = false;
  isBoardPositionSelected = false;

  currentPieceId = -1;
  currentBoardPositionId = -1;

  // Main Widget of the MainWindow
  QWidget *widget = new QWidget;
  setCentralWidget( widget );

  // Board layout
  boardLayout = new QGridLayout;
  //boardLayout->setVerticalSpacing ( 0 );
  //boardLayout->setColumnMinimumWidth( 8 );
  //boardLayout->setRowMinimumHeight( 8 );

  // Init the board
  initBoard();

  // Piece layout
  pieceLayout = new QGridLayout;
  // init the piece layout
  initPieces();

  // Right layout controls
  selectPieceButton = new QPushButton( "Select piece" );
  selectPieceButton->setDisabled( true );
  connect( selectPieceButton, SIGNAL( clicked() ), this, SLOT( clickSelectButton() ) );

  selectedPiece = new QLabel();
  selectedPiece->setFrameStyle( QFrame::Panel | QFrame::Sunken );

  // Layout where is shown the selected piece
  QHBoxLayout *selectedPieceLayout = new QHBoxLayout;
  selectedPieceLayout->addWidget( selectPieceButton );
  selectedPieceLayout->addWidget( selectedPiece );

  // Right layout
  QVBoxLayout *rightLayout = new QVBoxLayout;
  rightLayout->addLayout(pieceLayout);
  rightLayout->addLayout(selectedPieceLayout);

  QFrame *verticalLine = new QFrame;
  verticalLine->setFrameStyle( QFrame::VLine | QFrame::Sunken );

  // Main layout
  QHBoxLayout *mainLayout = new QHBoxLayout;
  //mainLayout->setMargin(5);
  mainLayout->addLayout(boardLayout);
  mainLayout->addWidget(verticalLine);
  mainLayout->addLayout(rightLayout);

  widget->setLayout(mainLayout);

  // Setting some properties of the main window
  setWindowTitle( tr("uQuarto") );
  setMinimumSize( 640, 480 );
  resize( 640, 480 );
}

MainWindow::~MainWindow()
{

}

void MainWindow::initBoard()
{
  int k = 0;
  for ( int i = 0; i < 4; i++ )
  {
    for ( int j = 0; j < 4; j++ )
    {
      QPiece *piece = new QPiece( k, ":/images/p00.jpg" );
      boardLayout->addWidget( piece, i, j );

      connect( piece, SIGNAL( clicked(int) ), SLOT( selectBoardPosition( int ) ) );

      boardPieces.push_back( piece );

      k++;
    }
  }
}

void MainWindow::initPieces()
{
  int k = 0;
  for ( int i = 0; i < 4; i++ )
  {
    for ( int j = 0; j < 4; j++ )
    {
      stringstream ss;
      ss << k;

      string s = ":/images/p";
      s.append( ss.str() );
      s.append( ".jpg" );

      QPiece *piece = new QPiece( k, s );
      pieceLayout->addWidget( piece, i, j );

      connect( piece, SIGNAL( clicked(int) ), SLOT(selectPiece(int) ) );

      pieces.push_back( piece );

      k++;
    }
  }
}

void MainWindow::selectPiece( int pieceId )
{
  if ( isHumanTurnToChoose )
  {
    isHumanTurnToChoose = false;

    // update current piece selected id
    currentPieceId = pieceId;

    // update pieces used
    QPiece *piece = pieces[ pieceId ];
    piece->setImage( ":/images/p00.jpg" );
    piece->updateImage();

    // previsualize selected piece
    string imageName = getImageName( pieceId );
    QPixmap pixMap( imageName.c_str() );
    selectedPiece->setPixmap( pixMap );

    // emit signal to allow the computer play
    emit computerPieceSelected( pieceId );
  }
}

void MainWindow::selectBoardPosition( int boardPositionId )
{
  if ( isHumanTurnToPutPiece )
  {
    isHumanTurnToPutPiece = false;

    // allow the user to choose a piece
    isHumanTurnToChoose = true;

    // updating current board position id
    currentBoardPositionId = boardPositionId;

    // update board
    QPiece *piece = boardPieces[ currentBoardPositionId ];
    piece->setImage( getImageName( currentPieceId ) );
    piece->updateImage();

    // update pieces used
    piece = pieces[ currentPieceId ];
    piece->setImage( ":/images/p00.jpg" );
    piece->updateImage();

    // update current piece selected
    QPixmap pixMap( "" );
    selectedPiece->setPixmap( pixMap );

    // emit signal to indicate the human just played
    emit humanPlayed( currentPieceId, currentBoardPositionId );
  }
}
void MainWindow::updateSelectButton()
{
}

void MainWindow::clickSelectButton()
{
  // emit signal to allow the computer play
  emit computerPieceSelected( currentPieceId );

  // disable button to select piece
  selectPieceButton->setDisabled( true );
}

void MainWindow::computerPlay( int pieceId, int boardPositionId )
{
  if ( ( pieceId < boardPieces.size() ) &&
     ( boardPositionId < pieces.size() ) )
  {
    QPiece *piece = boardPieces[ boardPositionId ];
    piece->setImage( getImageName( pieceId ) );
    piece->updateImage();

    piece = pieces[ pieceId ];
    piece->setImage( ":/images/p00.jpg" );
    piece->updateImage();

    QPixmap pixMap( "" );
    selectedPiece->setPixmap( pixMap );
  }
}

void MainWindow::humanPieceSelect( int pieceId )
{
  currentPieceId = pieceId;

  string imageName = getImageName( pieceId );
  QPixmap pixMap( imageName.c_str() );
  selectedPiece->setPixmap( pixMap );

  isHumanTurnToPutPiece = true;
}


