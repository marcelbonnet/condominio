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
    int naturezaId;
    int grupoId;
    QString natureza;
    QString grupo;

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

    void setNaturezaId(int naturezaId){
            this->naturezaId = naturezaId;
    }

    int getNaturezaId(){
            return this->naturezaId;
    }
    void setGrupoId(int grupoId){
            this->grupoId = grupoId;
    }

    int getGrupoId(){
            return this->grupoId;
    }
    void setNatureza(QString natureza){
            this->natureza = natureza;
    }

    QString getNatureza(){
            return this->natureza;
    }
    void setGrupo(QString grupo){
            this->grupo = grupo;
    }

    QString getGrupo(){
            return this->grupo;
    }

};

#endif // DESPESA_H
