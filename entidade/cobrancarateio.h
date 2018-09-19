#ifndef COBRANCARATEIO_H
#define COBRANCARATEIO_H

class CobrancaRateio
{
private:
    int cobranca;
    int rateio;

public:
    void setCobranca(int cobranca){
        this->cobranca = cobranca;
    }

    int getCobranca(){
        return this->cobranca;
    }
    void setRateio(int rateio){
        this->rateio = rateio;
    }

    int getRateio(){
        return this->rateio;
    }
};

#endif // COBRANCARATEIO_H
