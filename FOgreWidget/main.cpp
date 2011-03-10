#include <QtGui/QApplication>

#include "FOgreWidget.h"
//#include "OgreView.h"
#include <QVBoxLayout>
#pragma comment( lib, "OgreMain_d.lib")
#pragma comment( lib, "OIS_d.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

 QWidget widget ;
 widget.setGeometry (10,10,640,480) ;

 FOgreWidget ogreWidget(&widget,QString("ogrehead")) ;
 ogreWidget.setGeometry (10,10,340,280) ;
 //ogreWidget.setup() ;
 ogreWidget.Initialize() ;

 FOgreWidget ogreWidget1(&widget,QString("razor")) ;
 ogreWidget1.setGeometry (110,110,540,480) ;
  //ogreWidget1.setup() ;
 ogreWidget1.Initialize() ;


 QVBoxLayout *layout = new QVBoxLayout ;

 layout->addWidget(&ogreWidget);
 layout->addWidget(&ogreWidget1);
 widget.setLayout(layout);


 widget.show() ;
 //QWidget widget ;
 //widget.show() ;
 //ogreWidget.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    return a.exec();
}
