#ifndef FORMRATEIO_H
#define FORMRATEIO_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class FormRateio;
}

class FormRateio : public QWidget
{
    Q_OBJECT

public:
    explicit FormRateio(QWidget *parent = 0);
    ~FormRateio();

private slots:
    void on_dataIni_dateChanged(const QDate &date);

    void on_dataFim_dateChanged(const QDate &date);

    //depois que um rateio for alterado na Tabela
    void on_rateio_changed(QTableWidgetItem *item);
    //quando uma despesa for selecionada
    void on_despesas_itemSelectionChanged();
    void on_btnAceitarValoresPadrao_clicked();

signals:
    void emitirMensagem(QString);

private:
    Ui::FormRateio *ui;

    void atualizarDespesas(QDate de, QDate ate);
    void atualizarRateios();
    void persistir(int row);
};

#endif // FORMRATEIO_H
