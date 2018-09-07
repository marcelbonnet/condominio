#include "formunidade.h"
#include "ui_formunidade.h"
#include "entidade/unidade.h"
#include <QMessageBox>
#include "DAO.h"

FormUnidade::FormUnidade(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormUnidade)
{
    ui->setupUi(this);
}

FormUnidade::~FormUnidade()
{
    delete ui;
}

void FormUnidade::on_pushButton_clicked()
{
    Unidade u;
    u.setNome(ui->nome->text());
    u.setNumero(ui->numero->text());
    u.setTelefone(ui->telefone->text());
    u.setEmail(ui->email->text());

    try {
        DAO::incluirUnidade(u);
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Erro", e.what() );
    }

}
