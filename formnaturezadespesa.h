#ifndef FORMNATUREZADESPESA_H
#define FORMNATUREZADESPESA_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class FormNaturezaDespesa;
}

class FormNaturezaDespesa : public QWidget
{
    Q_OBJECT

public:
    explicit FormNaturezaDespesa(QWidget *parent = 0);
    ~FormNaturezaDespesa();

private slots:
    void onNaturezaChanged(QTableWidgetItem * item);

    void on_btnIncluirNatureza_clicked();

private:
    Ui::FormNaturezaDespesa *ui;

    void atualizarTabela();
};

#endif // FORMNATUREZADESPESA_H
