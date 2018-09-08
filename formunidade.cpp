#include "formunidade.h"
#include "ui_formunidade.h"
#include "entidade/unidade.h"
#include <QMessageBox>
#include "DAO.h"
#include <QList>

FormUnidade::FormUnidade(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormUnidade)
{
    ui->setupUi(this);


    atualizarTabela();

}

FormUnidade::~FormUnidade()
{
    delete ui;
}

void FormUnidade::atualizarTabela(){
    try {
        QList<Unidade> lista = DAO::listarUnidades();

        QTableWidget* table = ui->tabela;
        table->clear();
        table->setRowCount(lista.count());
        table->setColumnCount(5);
        QStringList header;
        header << "#" << "Apto" << "Nome" << "E-mail" << "Telefone";
        table->setHorizontalHeaderLabels(header);

        for(int i=0; i<lista.count(); i++){
            Unidade u = lista.at(i);
            table->setItem(i,0, new QTableWidgetItem(u.getId()));
            table->setItem(i,1, new QTableWidgetItem(u.getNumero()));
            table->setItem(i,2, new QTableWidgetItem(u.getNome()));
            table->setItem(i,3, new QTableWidgetItem(u.getEmail()));
            table->setItem(i,4, new QTableWidgetItem(u.getTelefone()));
        }
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Erro", e.what() );
    }
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
        atualizarTabela();
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Erro", e.what() );
    }

}
