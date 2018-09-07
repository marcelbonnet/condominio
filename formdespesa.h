#ifndef FORMDESPESA_H
#define FORMDESPESA_H

#include <QWidget>
#include "entidade/despesa.h"

namespace Ui {
class FormDespesa;
}

class FormDespesa : public QWidget
{
    Q_OBJECT

public:
    explicit FormDespesa(QWidget *parent = 0);
    ~FormDespesa();

private slots:
    QString nota = NULL;

    void on_btnEscolherNota_clicked();

    void on_btnRemoverNota_clicked();

    void on_btnIncluirDespesa_clicked();

private:
    Ui::FormDespesa *ui;
};

#endif // FORMDESPESA_H
