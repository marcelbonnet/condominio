#ifndef DESPESA_H
#define DESPESA_H

#include <QString>
#include <QDate>


class Despesa
{
private:
    int id;
    QDate dataDespesa;
    QDate dataInclusao;
    int valor;
    QString memo;
    QString nota;
    int natureza;
    int grupo;

public:
    Despesa() {}

    void setId(int id){
        this->id = id;
    }

    int getId(){
        return this->id;
    }
    void setDataDespesa(QDate dataDespesa){
        this->dataDespesa = dataDespesa;
    }

    QDate getDataDespesa(){
        return this->dataDespesa;
    }
    void setDataInclusao(QDate dataInclusao){
        this->dataInclusao = dataInclusao;
    }

    QDate getDataInclusao(){
        return this->dataInclusao;
    }
    void setValor(int valor){
        this->valor = valor;
    }

    int getValor(){
        return this->valor;
    }
    void setMemo(QString memo){
        this->memo = memo;
    }

    QString getMemo(){
        return this->memo;
    }
    void setNota(QString nota){
        this->nota = nota;
    }

    QString getNota(){
        return this->nota;
    }

    void setNatureza(int natureza){
            this->natureza = natureza;
    }

    int getNatureza(){
            return this->natureza;
    }
    void setGrupo(int grupo){
            this->grupo = grupo;
    }

    int getGrupo(){
            return this->grupo;
    }

};

#endif // DESPESA_H
