#include "DAO.h"
#include <QFile>

DAO::DAO()
{
    //construtor
}

QString DAO::getDbPath(){
    return (QString(getenv("XDG_CONFIG_HOME")) + "/Condominio/condominio.db");
}

int DAO::getLastInsertRowId() throw (std::exception){
    const char* sql = "SELECT last_insert_rowid()";
    SQLite::Database db(getDbPath().toUtf8().data(), SQLite::OPEN_READONLY );
    SQLite::Statement   query(db, sql);

    while(query.executeStep()){
        int id = query.getColumn(0);
        return id;
    }

}

int DAO::incluirUnidade(Unidade u) throw (std::exception){
    const char* sql = "INSERT INTO unidades (numero, resp_financeiro, resp_financeiro_email, resp_financeiro_telefone) VALUES (?, ?, ?, ?)";
    SQLite::Database db(getDbPath().toUtf8().data(), SQLite::OPEN_READWRITE );
    SQLite::Statement   query(db, sql);

    query.bind(1, u.getNumero().toUtf8().data());
    query.bind(2, u.getNome().toUtf8().data());
    query.bind(3, u.getEmail().toUtf8().data());
    query.bind(4, u.getTelefone().toUtf8().data());
    query.exec();

    return DAO::getLastInsertRowId();
}

int DAO::incluirDespesa(Despesa d) throw (std::exception){
    const char* sql = "INSERT INTO despesas (dt_evento, valor, memo, dt_inclusao, nota) VALUES (?, ?, ?, ?, ?)";
    SQLite::Database db(getDbPath().toUtf8().data(), SQLite::OPEN_READWRITE );
    SQLite::Statement   query(db, sql);

    //testar se não tiver nota
    d.setDataInclusao(QDate());
    QFile nota(d.getNota());

    if(!nota.open(QIODevice::ReadOnly))
        throw new std::exception();

    char* data = nota.readAll().data();

    query.bind(1, d.getDataDespesa().toString("yyyy-MM-dd").toUtf8().data() );
    query.bind(2, d.getValor());
    query.bind(3, d.getMemo().toUtf8().data());
    query.bind(4, d.getDataInclusao().toString("yyyy-MM-dd").toUtf8().data());
    query.bind(5, data, nota.size());
    query.exec();

    return DAO::getLastInsertRowId();
}
