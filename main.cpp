#include <iostream> // fuer Konsolenausgaben
using namespace std;

#include <time.h>  // fuer Zufallswerte

// Qt
#include <QtGui>
#include <QApplication>
#include <QString>

#include "QtInformationstag.h"

int main(int argc, char *argv[]) {

    srand( (unsigned)time( NULL ) ); // neue Zufallswerte erstellen

    QApplication a(argc, argv);

    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    
    QtInformationstag fenster;
    
    fenster.show();
    
    return a.exec();
}
