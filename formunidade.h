#ifndef FORMUNIDADE_H
#define FORMUNIDADE_H

#include <QWidget>

namespace Ui {
class FormUnidade;
}

class FormUnidade : public QWidget
{
    Q_OBJECT

public:
    explicit FormUnidade(QWidget *parent = 0);
    ~FormUnidade();

private slots:
    void on_pushButton_clicked();
private:
    Ui::FormUnidade *ui;

    void atualizarTabela();
};

#endif // FORMUNIDADE_H
