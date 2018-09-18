#include "formcobranca.h"
#include "ui_formcobranca.h"

FormCobranca::FormCobranca(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCobranca)
{
    ui->setupUi(this);
}

FormCobranca::~FormCobranca()
{
    delete ui;
}
