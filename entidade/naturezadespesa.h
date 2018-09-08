#ifndef NATUREZADESPESA_H
#define NATUREZADESPESA_H

#include <QString>

class NaturezaDespesa
{
private:
    int id;
    QString natureza;
public:
    NaturezaDespesa() {}

    void setId(int id){
            this->id = id;
    }

    int getId(){
            return this->id;
    }
    void setNatureza(QString natureza){
            this->natureza = natureza;
    }

    QString getNatureza(){
            return this->natureza;
    }
};

#endif // NATUREZADESPESA_H
