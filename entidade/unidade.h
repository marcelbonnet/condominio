#ifndef UNIDADE_H
#define UNIDADE_H

#include <QString>

class Unidade
{
private:
    int id;
    QString numero;
    QString nome;
    QString email;
    QString email2;
    QString telefone;

public:
    Unidade() {}

    void setId(int id){
        this->id = id;
    }

    int getId(){
        return this->id;
    }
    void setNumero(QString numero){
        this->numero = numero;
    }

    QString getNumero(){
        return this->numero;
    }
    void setNome(QString nome){
        this->nome = nome;
    }

    QString getNome(){
        return this->nome;
    }
    void setEmail(QString email){
        this->email = email;
    }

    QString getEmail(){
        return this->email;
    }
    void setTelefone(QString telefone){
        this->telefone = telefone;
    }

    QString getTelefone(){
        return this->telefone;
    }

    void setEmail2(QString email2){
        this->email2 = email2;
    }

    QString getEmail2(){
        return this->email2;
    }

};

#endif // UNIDADE_H
