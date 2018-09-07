#include "formdespesa.h"
#include "ui_formdespesa.h"
#include <QFileDialog>

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

}
