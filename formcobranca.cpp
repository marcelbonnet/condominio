#include "formcobranca.h"
#include "ui_formcobranca.h"
#include "DAO.h"
#include <QDate>
#include <QMessageBox>

FormCobranca::FormCobranca(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCobranca)
{
    ui->setupUi(this);

    ui->dataVcto->setDate(QDate::currentDate());
}

FormCobranca::~FormCobranca()
{
    delete ui;
}

void FormCobranca::on_btnGerarCobrancas_clicked()
{
    try{
        DAO::gerarCobrancasComVencimentoEm(ui->dataVcto->date().year(), ui->dataVcto->date().month(), ui->dataVcto->date().day());
        emit emitirMensagem("Cobranças geradas.");
    } catch (std::exception &e){
        QMessageBox::warning(this,"Erro", e.what());
    }
}
