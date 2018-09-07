#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include "entidade/unidade.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Unidade u = Unidade();
    u.setNumero("22");
    qDebug() << u.getNumero();
}

MainWindow::~MainWindow()
{
    delete ui;
}
