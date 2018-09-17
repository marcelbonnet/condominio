#include "formdespesa.h"
#include "ui_formdespesa.h"
#include <QFileDialog>
#include "entidade/despesa.h"
#include "DAO.h"
#include <QMessageBox>

FormDespesa::FormDespesa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDespesa)
{
    ui->setupUi(this);
    ui->data->setDate(QDate().currentDate());

    try {
        QList<NaturezaDespesa> lista = DAO::listarNaturezaDespesas();
        for(int i=0; i<lista.count(); i++){
            NaturezaDespesa nd = lista.at(i);
            ui->cmbNatureza->addItem(nd.getNatureza(), QVariant::fromValue(nd.getId()));
        }
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Erro", e.what() );
    }
}

FormDespesa::~FormDespesa()
{
    delete ui;
}

void FormDespesa::on_btnEscolherNota_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Selecionar Nota",
                                                    "/tmp",
                                                    tr("Imagens (*.png *.jpg);; PDF (*pdf)"));
    this->nota = fileName;
    ui->nota->setText(fileName);
}

void FormDespesa::on_btnRemoverNota_clicked()
{
    this->nota = NULL;
    ui->nota->setText("Nenhum anexo");
}

void FormDespesa::on_btnIncluirDespesa_clicked()
{
    int naturezaId = ui->cmbNatureza->currentData().value<int>();
    Despesa d;
    d.setDataDespesa( ui->data->date() );
    d.setMemo(ui->memo->toPlainText());
    double val = ui->valor->value()*1000;
    d.setValor( static_cast<int>(val) );
    d.setNota(this->nota);
    d.setNaturezaId(naturezaId);

    try {
        DAO::incluirDespesa(d);
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Erro", e.what() );
    }
}
