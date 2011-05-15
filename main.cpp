#include <QtGui/QApplication>

#include "MainWindow.h"
#include "PlayGame.h"
#include <QDebug>

int main(int argc, char *argv[])
{
  // Main application
  QApplication application(argc, argv);

  // Loading resources (images...)
  Q_INIT_RESOURCE( uQuarto );

  // ** Game GUI **
  // Renders the board, the pieces, and provides interaction with the user
  MainWindow *mainWindow = new MainWindow();
  mainWindow->show();
  bool isHumanFirstPlayer = true;
  // bool firstPlayer = mainWindows.getFirstPlayer();

  //
  PlayGame *playGame = new PlayGame();
  playGame->setFirstPlayer( isHumanFirstPlayer );
  playGame->start();

  // Connecting signal that interconects the GUI with the engine
  QObject::connect( mainWindow, SIGNAL( humanPlayed( int, int ) ), playGame, SLOT( humanPlay( int, int ) ) );
  QObject::connect( playGame, SIGNAL( computerPlayed( int, int ) ), mainWindow, SLOT( computerPlay( int, int ) ) );

  // Signal to indicate that the piece for the human has been selected
  QObject::connect( playGame, SIGNAL( humanPieceSelected( int ) ), mainWindow, SLOT( humanPieceSelect( int ) ) );
  QObject::connect( mainWindow, SIGNAL( computerPieceSelected( int ) ), playGame, SLOT( computerPieceSelect( int ) ) );

  return application.exec();
}
