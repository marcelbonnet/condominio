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
    Despesa d;
    d.setDataDespesa( ui->data->date() );
    d.setMemo(ui->memo->toPlainText());
    double val = ui->valor->value()*100;
    d.setValor( static_cast<int>(val) );
    d.setNota(this->nota);

    try {
        DAO::incluirDespesa(d);
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Erro", e.what() );
    }
}
