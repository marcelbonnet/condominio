#ifndef GRUPODESPESA_H
#define GRUPODESPESA_H

#include <QString>

class GrupoDespesa
{
private:
    int id;
    QString grupo;
public:
    GrupoDespesa() {}

    void setId(int id){
            this->id = id;
    }

    int getId(){
            return this->id;
    }
    void setGrupo(QString grupo){
            this->grupo = grupo;
    }

    QString getGrupo(){
            return this->grupo;
    }
};

#endif // GRUPODESPESA_H
