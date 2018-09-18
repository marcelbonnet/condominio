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

private:
    Ui::FormCobranca *ui;
};

#endif // FORMCOBRANCA_H
