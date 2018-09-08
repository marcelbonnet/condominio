#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include "formunidade.h"
#include "formdespesa.h"
#include "formnaturezadespesa.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    MainWindow::showMaximized();
    ui->setupUi(this);

    FormUnidade* frmUnidade = new FormUnidade();
    FormDespesa* frmDespesa = new FormDespesa();
    FormNaturezaDespesa* frmNaturezaDespesa = new FormNaturezaDespesa();

    ui->tabWidget->addTab(frmUnidade, "Unidade");
    ui->tabWidget->addTab(frmDespesa, "Despesa");
    ui->tabWidget->addTab(frmNaturezaDespesa, "Natureza Despesa");
}

MainWindow::~MainWindow()
{
    delete ui;
}
