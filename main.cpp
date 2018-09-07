#include "mainwindow.h"
#include <QApplication>

#include "formunidade.h"
#include "formdespesa.h"
#include "entidade/despesa.h"
#include "entidade/unidade.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //w.show();

    Unidade u;
    u.setId(2342);

    Despesa d;
    d.setMemo("teste");

    FormUnidade* f = new FormUnidade();
    f->show();

    FormDespesa* fd = new FormDespesa();
    fd->show();

    return a.exec();
}
