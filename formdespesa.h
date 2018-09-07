#ifndef FORMDESPESA_H
#define FORMDESPESA_H

#include <QWidget>
#include "entidade/despesa.h"
#include <QString>

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
    void on_btnEscolherNota_clicked();

    void on_btnRemoverNota_clicked();

    void on_btnIncluirDespesa_clicked();

private:
    Ui::FormDespesa *ui;
    QString nota = NULL;
};

#endif // FORMDESPESA_H
