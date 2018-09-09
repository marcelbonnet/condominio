#ifndef FORMGRUPODESPESA_H
#define FORMGRUPODESPESA_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class FormGrupoDespesa;
}

class FormGrupoDespesa : public QWidget
{
    Q_OBJECT

public:
    explicit FormGrupoDespesa(QWidget *parent = 0);
    ~FormGrupoDespesa();

private slots:
    void onGrupoChanged(QTableWidgetItem * item);

    void on_btnIncluirGrupo_clicked();

private:
    Ui::FormGrupoDespesa *ui;

    void atualizarTabela();
};

#endif // FORMGRUPODESPESA_H
