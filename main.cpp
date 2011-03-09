#include <QApplication>
#include "mainwindow.h"
#include <QMdiArea>
#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QLabel>
#include <QPixmap>
#include <QBitmap>
#include <QSplashScreen>
#include "MyThread.h"
#include <QCleanlooksStyle>
#include <QFont>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(application);

    QApplication app(argc, argv);
    QApplication::setStyle(new QCleanlooksStyle());
	QApplication::setPalette(QApplication::style()->standardPalette());

    QSplashScreen *splash = new QSplashScreen;
    QPixmap pixmap = QPixmap(":/screen.png");
    splash->setPixmap(pixmap);
    splash->setMask(pixmap.mask());
    splash->show();
    //splash->showMessage("Reading Application Data.",Qt::AlignLeft | Qt::AlignBottom, Qt::white);

    MyThread::sleep(1);
    MainWindow* mainWin = new MainWindow;

    //mainWin->resize(1000, 680);
    mainWin->setWindowTitle("GEOSM");
    mainWin->setGeometry(100,50,1000,680);

    //QFont sansFont(mainWin->tr("微軟正黑體 [Helvetica, Cronyx]"));
	QFont sansFont(QApplication::font());
	sansFont.setFamily("Helvetica [Cronyx]");
    sansFont.setStyleHint(QFont::SansSerif);
    sansFont.setStyleStrategy(QFont::PreferAntialias);
    QApplication::setFont(sansFont);
    //mainWin->setFont(sansFont);
    mainWin->showMaximized();
    splash->finish(mainWin);
    delete splash;
    return app.exec();

}
