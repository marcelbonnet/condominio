#include "formnaturezadespesa.h"
#include "ui_formnaturezadespesa.h"
#include "entidade/naturezadespesa.h"
#include <QDebug>
#include <QMessageBox>
#include "DAO.h"

FormNaturezaDespesa::FormNaturezaDespesa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormNaturezaDespesa)
{
    ui->setupUi(this);

    connect( ui->table, SIGNAL( itemChanged (QTableWidgetItem *) ), this, SLOT( onNaturezaChanged(QTableWidgetItem*)) ) ;
    atualizarTabela();

}

FormNaturezaDespesa::~FormNaturezaDespesa()
{
    delete ui;
}

void FormNaturezaDespesa::atualizarTabela(){
    try {
        disconnect( ui->table, SIGNAL( itemChanged (QTableWidgetItem *) ), this, SLOT( onNaturezaChanged(QTableWidgetItem*)) ) ;
        QList<NaturezaDespesa> lista = DAO::listarNaturezaDespesas();

        QTableWidget* table = ui->table;
        table->clear();
        table->setRowCount(lista.count());
        table->setColumnCount(3);
        QStringList header;
        header << "#" << "Natureza" << "Grupo";
        table->setHorizontalHeaderLabels(header);

        for(int i=0; i<lista.count(); i++){
            NaturezaDespesa nd = lista.at(i);
            table->setItem(i,0, new QTableWidgetItem( QString::number(nd.getId()) ));
            table->setItem(i,1, new QTableWidgetItem(nd.getNatureza()) );
            table->setItem(i,2, new QTableWidgetItem(QString::number(nd.getGrupo())));
        }
        table->resizeColumnsToContents();
        connect( ui->table, SIGNAL( itemChanged (QTableWidgetItem *) ), this, SLOT( onNaturezaChanged(QTableWidgetItem*)) ) ;
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Erro", e.what() );
    }
}

void FormNaturezaDespesa::onNaturezaChanged(QTableWidgetItem *item)
{
        QTableWidget* table = ui->table;
        int row = table->currentRow();
        QTableWidgetItem* itemId = table->item(row, 0);

        NaturezaDespesa nd;
        nd.setId(itemId->text().toInt());

        switch (item->column()) {
        case 1:
            nd.setNatureza(item->text());
            break;
        case 2:
            nd.setGrupo(item->text().toInt());
            break;
        default:
            break;
        }

        try{
            DAO::updateNaturezaDespesa(nd);
        } catch (std::exception &e) {
            QMessageBox::warning(this, "Erro", e.what() );
        }

        atualizarTabela();
}

void FormNaturezaDespesa::on_btnIncluirNatureza_clicked()
{
    NaturezaDespesa nd;
    nd.setNatureza(ui->natureza->text());

    try{
        DAO::incluirNaturezaDespesa(nd);
        ui->natureza->setText("");
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Erro", e.what() );
    }

    atualizarTabela();

}
