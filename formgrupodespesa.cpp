#include "formgrupodespesa.h"
#include "ui_formgrupodespesa.h"
#include "entidade/grupodespesa.h"
#include <QDebug>
#include <QMessageBox>
#include "DAO.h"

FormGrupoDespesa::FormGrupoDespesa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormGrupoDespesa)
{
    ui->setupUi(this);

    connect( ui->table, SIGNAL( itemChanged (QTableWidgetItem *) ), this, SLOT( onGrupoChanged(QTableWidgetItem*)) ) ;
    atualizarTabela();
}

FormGrupoDespesa::~FormGrupoDespesa()
{
    delete ui;
}

void FormGrupoDespesa::on_btnIncluirGrupo_clicked()
{
    GrupoDespesa gd;
    gd.setGrupo(ui->grupo->text());

    try{
        DAO::incluirGrupoDespesa(gd);
        ui->grupo->setText("");
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Erro", e.what() );
    }

    atualizarTabela();
}


void FormGrupoDespesa::onGrupoChanged(QTableWidgetItem *item)
{
        QTableWidget* table = ui->table;
        int row = table->currentRow();
        int col = table->currentColumn();
        QTableWidgetItem* itemId = table->item(row, 0);
        //QTableWidgetItem* itemGrupo = table->item(row, 1);

        GrupoDespesa gd;
        gd.setId(itemId->text().toInt());
        gd.setGrupo(item->text());

        try{
            DAO::updateGrupoDespesa(gd);
        } catch (std::exception &e) {
            QMessageBox::warning(this, "Erro", e.what() );
        }

        atualizarTabela();
}

void FormGrupoDespesa::atualizarTabela(){
    try {
        disconnect( ui->table, SIGNAL( itemChanged (QTableWidgetItem *) ), this, SLOT( onGrupoChanged(QTableWidgetItem*)) ) ;
        QList<GrupoDespesa> lista = DAO::listarGrupoDespesas();

        QTableWidget* table = ui->table;
        table->clear();
        table->setRowCount(lista.count());
        table->setColumnCount(2);
        QStringList header;
        header << "#" << "Grupo";
        table->setHorizontalHeaderLabels(header);

        for(int i=0; i<lista.count(); i++){
            GrupoDespesa gd = lista.at(i);
            table->setItem(i,0, new QTableWidgetItem( QString::number(gd.getId()) ));
            table->setItem(i,1, new QTableWidgetItem( gd.getGrupo() ) );
        }
        table->resizeColumnsToContents();
        connect( ui->table, SIGNAL( itemChanged (QTableWidgetItem *) ), this, SLOT( onGrupoChanged(QTableWidgetItem*)) ) ;
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Erro", e.what() );
    }
}
