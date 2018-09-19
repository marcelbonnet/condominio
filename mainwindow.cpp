#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include "formunidade.h"
#include "formdespesa.h"
#include "formnaturezadespesa.h"
#include "formgrupodespesa.h"
#include "formrateio.h"
#include "formcobranca.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    MainWindow::showMaximized();
    ui->setupUi(this);

    FormUnidade* frmUnidade = new FormUnidade();
    FormDespesa* frmDespesa = new FormDespesa();
    FormNaturezaDespesa* frmNaturezaDespesa = new FormNaturezaDespesa();
    FormGrupoDespesa* frmGrupoDespesa = new FormGrupoDespesa();
    FormRateio* frmRateio = new FormRateio();
    FormCobranca* frmCobranca = new FormCobranca();

    ui->tabWidget->addTab(frmUnidade, "Unidade");
    ui->tabWidget->addTab(frmDespesa, "Despesa");
    ui->tabWidget->addTab(frmNaturezaDespesa, "Natureza Despesa");
    ui->tabWidget->addTab(frmGrupoDespesa, "Grupo Despesa");
    ui->tabWidget->addTab(frmRateio, "Rateio");
    ui->tabWidget->addTab(frmCobranca,"Cobrança");

    //recebe sinal para mostrar mensagens na status bar
    connect(frmRateio, SIGNAL(emitirMensagem(QString)), this, SLOT(onReceberMensagem(QString)));
    connect(frmCobranca, SIGNAL(emitirMensagem(QString)), this, SLOT(onReceberMensagem(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReceberMensagem(QString msg){
    statusBar()->showMessage(msg, 7000);
}
