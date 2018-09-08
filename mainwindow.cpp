#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include "formunidade.h"
#include "formdespesa.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    FormUnidade* frmUnidade = new FormUnidade();
    FormDespesa* frmDespesa = new FormDespesa();

    ui->tabWidget->addTab(frmUnidade, "Unidade");
    ui->tabWidget->addTab(frmDespesa, "Despesa");

}

MainWindow::~MainWindow()
{
    delete ui;
}
