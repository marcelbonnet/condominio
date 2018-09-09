#ifndef NATUREZADESPESA_H
#define NATUREZADESPESA_H

#include <QString>

class NaturezaDespesa
{
private:
    int id;
    QString natureza;
    int grupo = 0;
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

    void setGrupo(int grupo){
            this->grupo = grupo;
    }

    int getGrupo(){
            return this->grupo;
    }
};

#endif // NATUREZADESPESA_H
