#ifndef RATEIO_H
#define RATEIO_H

#include <QDate>

class Rateio {

private:
    int id = -1;
    int unidade = -1;
    int valor = -1;
    int parcela = -1;
    QDate dataVencimento;
    double razao = -1;
    int despesa = -1;

public:
    Rateio(){}

    void setId(int id){
            this->id = id;
    }

    int getId(){
            return this->id;
    }
    void setUnidade(int unidade){
            this->unidade = unidade;
    }

    int getUnidade(){
            return this->unidade;
    }
    void setValor(int valor){
            this->valor = valor;
    }

    int getValor(){
            return this->valor;
    }
    void setParcela(int parcela){
            this->parcela = parcela;
    }

    int getParcela(){
            return this->parcela;
    }
    void setDataVencimento(QDate dataVencimento){
            this->dataVencimento = dataVencimento;
    }

    QDate getDataVencimento(){
            return this->dataVencimento;
    }
    void setRazao(double razao){
            this->razao = razao;
    }

    double getRazao(){
            return this->razao;
    }

    void setDespesa(int despesa){
            this->despesa = despesa;
    }

    int getDespesa(){
            return this->despesa;
    }
};

#endif // RATEIO_H
