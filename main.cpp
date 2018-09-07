#include "mainwindow.h"
#include <QApplication>

#include "formunidade.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //w.show();

    FormUnidade* f = new FormUnidade();
    f->show();

    return a.exec();
}
