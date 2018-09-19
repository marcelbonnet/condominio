#ifndef COBRANCA_H
#define COBRANCA_H

#include <QDate>

class Cobranca
{
private:
    int id;
    QDate dataVcto;
    int valor;
    int unidade;
    QDate dataPgto;
    int valorPgto;

public:
    void setId(int id){
        this->id = id;
    }

    int getId(){
        return this->id;
    }
    void setDataVcto(QDate dataVcto){
        this->dataVcto = dataVcto;
    }

    QDate getDataVcto(){
        return this->dataVcto;
    }
    void setValor(int valor){
        this->valor = valor;
    }

    int getValor(){
        return this->valor;
    }
    void setUnidade(int unidade){
        this->unidade = unidade;
    }

    int getUnidade(){
        return this->unidade;
    }
    void setDataPgto(QDate dataPgto){
        this->dataPgto = dataPgto;
    }

    QDate getDataPgto(){
        return this->dataPgto;
    }
    void setValorPgto(int valorPgto){
        this->valorPgto = valorPgto;
    }

    int getValorPgto(){
        return this->valorPgto;
    }

};

#endif // COBRANCA_H
