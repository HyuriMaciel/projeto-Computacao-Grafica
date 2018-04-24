#include "primitivas.h"
#include <QApplication>
#include <QtOpenGL>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
