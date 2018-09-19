#ifndef FORMCOBRANCA_H
#define FORMCOBRANCA_H

#include <QWidget>

namespace Ui {
class FormCobranca;
}

class FormCobranca : public QWidget
{
    Q_OBJECT

public:
    explicit FormCobranca(QWidget *parent = 0);
    ~FormCobranca();

private slots:
    void on_btnGerarCobrancas_clicked();

private:
    Ui::FormCobranca *ui;

signals:
    void emitirMensagem(QString);
};

#endif // FORMCOBRANCA_H
