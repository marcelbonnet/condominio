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

QList<Unidade> DAO::listarUnidades() throw (std::exception){
    SQLite::Database db(getDbPath().toUtf8().data());
    SQLite::Statement   query(db, "SELECT id, numero, resp_financeiro, resp_financeiro_email, resp_financeiro_telefone FROM unidades  ORDER BY numero ASC");
    QList<Unidade> rs;
    while (query.executeStep())
    {
        const int id = query.getColumn(0);
        const char* numero   = query.getColumn(1);
        const char* nome   = query.getColumn(2);
        const char* email = query.getColumn(3);
        const char* telefone = query.getColumn(4);

        Unidade u;
        u.setId(id);
        u.setEmail(QString(email));
        u.setNome(QString(nome));
        u.setNumero(QString(numero));
        u.setTelefone(telefone);

        rs.append(u);
    }
    return rs;
}
