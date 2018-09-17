#include "formrateio.h"
#include "ui_formrateio.h"
#include "entidade/rateio.h"
#include "entidade/despesa.h"
#include "DAO.h"
#include <QDate>
#include <QMessageBox>
#include <QDebug>

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
        table->setColumnCount(8);
        QStringList header;
        header << "#" << "Em" << "R$" << "Natureza" << "Grupo" << "Memo" << "NaturezaId" << "GrupoId";
        table->setHorizontalHeaderLabels(header);

        for(int i=0; i<lista.count(); i++){
            Despesa d = lista.at(i);
            table->setItem(i,0, new QTableWidgetItem( QString::number(d.getId()) ));
            table->setItem(i,1, new QTableWidgetItem(d.getDataDespesa().toString("dd/MM/yyyy") ) );
            table->setItem(i,2, new QTableWidgetItem( QString::number(d.getValor()) ));
            table->setItem(i,3, new QTableWidgetItem( d.getNatureza() ));
            table->setItem(i,4, new QTableWidgetItem( d.getGrupo() ));
            table->setItem(i,5, new QTableWidgetItem( d.getMemo() ));
            table->setItem(i,6, new QTableWidgetItem( QString::number(d.getNaturezaId()) ));
            table->setItem(i,7, new QTableWidgetItem( QString::number(d.getGrupoId()) ));
        }
        table->resizeColumnsToContents();
        connect( ui->despesas, SIGNAL( itemSelectionChanged() ), this, SLOT( on_despesas_itemSelectionChanged()) ) ;
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Erro", e.what() );
    }
}

void FormRateio::atualizarRateios(){
    try {
        disconnect( ui->rateios, SIGNAL( itemChanged(QTableWidgetItem*) ), this, SLOT( on_rateio_changed(  QTableWidgetItem*)) ) ;
        QTableWidget* tableDespesas = ui->despesas;
        int despesaId = tableDespesas->item(tableDespesas->currentRow(), 0)->text().toInt();
        int despesaValor = tableDespesas->item(tableDespesas->currentRow(), 2)->text().toInt();
        QList<Rateio> lista = DAO::listarRateioPorDespesa(despesaId);

        QTableWidget* table = ui->rateios;
        table->clear();
        table->setRowCount(lista.count());
        table->setColumnCount(8);
        QStringList header;
        header << "UnidadeID" << "Unidade" << "RateioID" << "Valor" << "Parcelas" << "Cota" << "Vcto" << "DespesaId";
        table->setHorizontalHeaderLabels(header);

        for(int i=0; i<lista.count(); i++){
            Rateio rateio = lista.at(i);

            //qDebug() << rateio.getId() << rateio.getUnidade() << rateio.getParcela() << rateio.getRazao() << rateio.getValor();

            int valor = despesaValor;
            QString dataVcto = rateio.getDataVencimento().toString("dd/MM/yyyy");
            if(dataVcto.length() == 0)
                dataVcto = ui->dataIni->date().addDays(15).addMonths(1).toString("dd/MM/yyyy");
            int parcelas = 1;
            int grupo = tableDespesas->item(tableDespesas->currentRow(), 7)->text().toInt();
            /*
             * FIXME
             * 1 Manutenção 1/8
             * 2 Garagem : 4 unidades, 1/4 : 11,12,32,42
             * 3 Despesas : 1/7, 22 não paga
             * */
            float cota = (float)1/8;

            table->setItem(i,0, new QTableWidgetItem( QString::number(rateio.unidadeId) ));
            table->setItem(i,1, new QTableWidgetItem(rateio.unidadeNumero ) );
            table->setItem(i,2, new QTableWidgetItem( QString::number(rateio.getId()) ));
            table->setItem(i,6, new QTableWidgetItem( dataVcto ));
            table->setItem(i,7, new QTableWidgetItem( QString::number(despesaId) ));

            if(grupo == 3){
                cota = (float)1/7;

                //FIXME : síndico deve ser registrado numa tabela de configurações
                if(rateio.unidadeNumero.compare("22") == 0){
                    parcelas = 0;
                } else {
                    if(rateio.getParcela() > 0)
                        parcelas = rateio.getParcela();
                    if(rateio.getRazao() > 0)
                        cota = rateio.getRazao();
                }

                table->setItem(i,4, new QTableWidgetItem( QString::number(parcelas) ));
                table->setItem(i,5, new QTableWidgetItem( QString::number(cota) ));
            } else if(grupo == 2){
                cota = 0;

                //FIXME : registrar numa tabela de configurações
                if( rateio.unidadeNumero.compare("11") == 0
                        || rateio.unidadeNumero.compare("12") == 0
                        || rateio.unidadeNumero.compare("32") == 0
                        || rateio.unidadeNumero.compare("42") == 0
                ){
                    if(rateio.getParcela() > 0)
                        parcelas = rateio.getParcela();

                    cota = (float)1/4;

                }

                if(rateio.getRazao() > 0)
                    cota = rateio.getRazao();

                table->setItem(i,4, new QTableWidgetItem( QString::number(parcelas) ));
                table->setItem(i,5, new QTableWidgetItem( QString::number(cota) ));
            } else if (grupo == 1){
                cota = (float)1/8;

                if(rateio.getParcela() > 0)
                    parcelas = rateio.getParcela();
                if(rateio.getRazao() > 0)
                    cota = rateio.getRazao();

                table->setItem(i,4, new QTableWidgetItem( QString::number(parcelas) ));
                table->setItem(i,5, new QTableWidgetItem( QString::number(cota) ));

            }

            //por fim, calcula o valor do rateio com base em parcelas e cotas:
            if(rateio.getValor() > 0)
                valor = rateio.getValor();
            else
                valor = (valor * cota)/parcelas;

            if(valor<0) valor=0;

            table->setItem(i,3, new QTableWidgetItem(QString::number(valor) ) );

        }
        table->resizeColumnsToContents();
        connect( ui->rateios, SIGNAL( itemChanged (QTableWidgetItem *) ), this, SLOT( on_rateio_changed(  QTableWidgetItem*)) ) ;
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Erro", e.what() );
    }
}

void FormRateio::on_rateio_changed( QTableWidgetItem *item){
    persistir(item->row());
    atualizarRateios();
}


void FormRateio::on_despesas_itemSelectionChanged()
{
    atualizarRateios();
}

void FormRateio::persistir(int row){
    QTableWidget* table = ui->rateios;

//    for(int row=0; row<table->rowCount(); row++){

        QTableWidgetItem* unidadeId = table->item(row, 0);
        QTableWidgetItem* rateioId = table->item(row, 2);
        QTableWidgetItem* valor = table->item(row, 3);
        QTableWidgetItem* parcelas = table->item(row, 4);
        QTableWidgetItem* cota = table->item(row, 5);
        QTableWidgetItem* itemVcto = table->item(row, 6);
        QDate dataVencimento = QDate::fromString(itemVcto->text(), "dd/MM/yyyy");
        QTableWidgetItem* despesaId = table->item(row, 7);

        Rateio rateio;
        rateio.setUnidade(unidadeId->text().toInt());
        rateio.setId(rateioId->text().toInt());
        rateio.setValor( parcelas->text().toInt() == 0 ? 0 : valor->text().toInt()/parcelas->text().toInt());
        rateio.setParcela(parcelas->text().toInt());
        rateio.setRazao(cota->text().toFloat());
        rateio.setDespesa(despesaId->text().toInt());
        rateio.setDataVencimento(dataVencimento);

        try{
            if(rateio.getId() <= 0){
                for(int i=1; i<=rateio.getParcela(); i++){
                    rateio.setDataVencimento(dataVencimento.addMonths(i-1));
                    DAO::incluirRateio(rateio);
                }
            } else
                DAO::updateRateio(rateio);
        } catch (std::exception &e) {
            QMessageBox::warning(this, "Erro", e.what() );
        }

//    } // fim for


}


void FormRateio::on_btnAceitarValoresPadrao_clicked()
{
    QTableWidget* table = ui->despesas;
    for(int row=0; row<table->rowCount(); row++){
        table->selectRow(row);
        QTableWidget* tableRateios = ui->rateios;
        for(int linha=0; linha<tableRateios->rowCount(); linha++){
            persistir(linha);
        }
    }
}
