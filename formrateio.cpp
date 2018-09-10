#include "formrateio.h"
#include "ui_formrateio.h"
#include "entidade/rateio.h"
#include "entidade/despesa.h"
#include "DAO.h"
#include <QDate>
#include <QMessageBox>

FormRateio::FormRateio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormRateio)
{
    ui->setupUi(this);

    QDate primeiroDia = QDate::currentDate();
    primeiroDia.setDate(primeiroDia.year(), primeiroDia.month(), 1);
    QDate ultimoDia = QDate::currentDate();
    ultimoDia.setDate(ultimoDia.year(), ultimoDia.month(), ultimoDia.currentDate().daysInMonth());

    ui->dataIni->setDate(primeiroDia);
    ui->dataFim->setDate(ultimoDia);

    ui->despesas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->despesas->setSelectionMode(QAbstractItemView::SingleSelection);

}

FormRateio::~FormRateio()
{
    delete ui;
}

void FormRateio::on_dataIni_dateChanged(const QDate &date)
{
    atualizarDespesas(ui->dataIni->date(), ui->dataFim->date());
}

void FormRateio::on_dataFim_dateChanged(const QDate &date)
{
    atualizarDespesas(ui->dataIni->date(), ui->dataFim->date());
}

void FormRateio::atualizarDespesas(QDate de, QDate ate){
    try {
        disconnect( ui->despesas, SIGNAL( itemSelectionChanged() ), this, SLOT( on_despesas_itemSelectionChanged()) ) ;
        QList<Despesa> lista = DAO::listarDespesasPeriodo(de, ate);

        QTableWidget* table = ui->despesas;
        table->clear();
        table->setRowCount(lista.count());
        table->setColumnCount(6);
        QStringList header;
        header << "#" << "Em" << "R$" << "Natureza" << "Grupo" << "Memo";
        table->setHorizontalHeaderLabels(header);

        for(int i=0; i<lista.count(); i++){
            Despesa d = lista.at(i);
            table->setItem(i,0, new QTableWidgetItem( QString::number(d.getId()) ));
            table->setItem(i,1, new QTableWidgetItem(d.getDataDespesa().toString("dd/MM/yyyy") ) );
            table->setItem(i,2, new QTableWidgetItem( QString::number(d.getValor()) ));
            table->setItem(i,3, new QTableWidgetItem( QString::number(d.getNatureza()) ));
            table->setItem(i,4, new QTableWidgetItem( QString::number(d.getGrupo()) ));
            table->setItem(i,5, new QTableWidgetItem( d.getMemo() ));
        }
        table->resizeColumnsToContents();
        connect( ui->despesas, SIGNAL( itemSelectionChanged() ), this, SLOT( on_despesas_itemSelectionChanged()) ) ;
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Erro", e.what() );
    }
}

void FormRateio::atualizarRateios(){

}

void FormRateio::on_rateio_changed(const QTableWidgetItem *item){
    QTableWidget* table = ui->rateios;
    int row = table->currentRow();
    QTableWidgetItem* itemId = table->item(row, 0);

    /*

    Rateio rateio;
    rateio.setId(itemId->text().toInt());

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
    */
}

void FormRateio::on_despesas_itemSelectionChanged()
{
    atualizarRateios();
}
