#include "DAO.h"
#include <QFile>
#include <QDebug>

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
    const char* sql = "INSERT INTO despesas (dt_evento, valor, memo, dt_inclusao, nota, fkNatureza) VALUES (?, ?, ?, ?, ?, ?)";
    SQLite::Database db(getDbPath().toUtf8().data(), SQLite::OPEN_READWRITE );
    SQLite::Statement   query(db, sql);


    d.setDataInclusao(QDate().currentDate());
    QFile nota(d.getNota());

    char* data = NULL;
    if(!d.getNota().isEmpty()){
        if(!nota.open(QIODevice::ReadOnly))
            throw new std::exception();

        data = nota.readAll().data();
    }

    query.bind(1, d.getDataDespesa().toString("yyyy-MM-dd").toUtf8().data() );
    query.bind(2, d.getValor());
    query.bind(3, d.getMemo().toUtf8().data());
    query.bind(4, d.getDataInclusao().toString("yyyy-MM-dd").toUtf8().data());
    query.bind(5, data, nota.size());
    query.bind(6, d.getNatureza());
    query.exec();

    return DAO::getLastInsertRowId();
}

QList<Unidade> DAO::listarUnidades() throw (std::exception){
    SQLite::Database db(getDbPath().toUtf8().data());
    SQLite::Statement   query(db, "SELECT id, numero, resp_financeiro, resp_financeiro_email, resp_financeiro_telefone FROM unidades  ORDER BY numero ASC");
    QList<Unidade> rs;
    while (query.executeStep())
    {
        int id = query.getColumn(0);
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

int DAO::incluirNaturezaDespesa(NaturezaDespesa nd) throw (std::exception){
    const char* sql = "INSERT INTO natureza_despesas (natureza) VALUES (?)";
    SQLite::Database db(getDbPath().toUtf8().data(), SQLite::OPEN_READWRITE );
    SQLite::Statement   query(db, sql);

    query.bind(1, nd.getNatureza().toUtf8().data());
    query.exec();

    return DAO::getLastInsertRowId();
}

void DAO::updateNaturezaDespesa(NaturezaDespesa nd) throw (std::exception){
    SQLite::Database db(getDbPath().toUtf8().data(), SQLite::OPEN_READWRITE );

    if( ! nd.getNatureza().isEmpty() ){
        const char* sql = "UPDATE natureza_despesas SET natureza=? WHERE id = ?";
        SQLite::Statement   query(db, sql);
        query.bind(1, nd.getNatureza().toUtf8().data());
        query.bind(2, nd.getId());
        query.exec();
    }

    if( nd.getGrupo() > 0 ){
        const char* sql = "UPDATE natureza_despesas SET fkGrupo=? WHERE id = ?";
        SQLite::Statement   query(db, sql);
        query.bind(1, nd.getGrupo());
        query.bind(2, nd.getId());
        query.exec();
    }

}

QList<NaturezaDespesa> DAO::listarNaturezaDespesas() throw (std::exception){
    SQLite::Database db(getDbPath().toUtf8().data());
    SQLite::Statement   query(db, "SELECT id, natureza, fkGrupo FROM natureza_despesas ORDER BY natureza ASC");
    QList<NaturezaDespesa> rs;
    while (query.executeStep())
    {
        int id = query.getColumn(0);
        const char* natureza   = query.getColumn(1);
        int fkGrupo = query.getColumn(2);

        NaturezaDespesa nd;
        nd.setId(id);
        nd.setNatureza(QString(natureza));
        nd.setGrupo(fkGrupo);

        rs.append(nd);
    }
    return rs;
}


int DAO::incluirGrupoDespesa(GrupoDespesa gd) throw (std::exception){
    const char* sql = "INSERT INTO grupo_despesas (grupo) VALUES (?)";
    SQLite::Database db(getDbPath().toUtf8().data(), SQLite::OPEN_READWRITE );
    SQLite::Statement   query(db, sql);

    query.bind(1, gd.getGrupo().toUtf8().data());
    query.exec();

    return DAO::getLastInsertRowId();
}

void DAO::updateGrupoDespesa(GrupoDespesa gd) throw (std::exception){
    const char* sql = "UPDATE grupo_despesas SET grupo=? WHERE id = ?";
    SQLite::Database db(getDbPath().toUtf8().data(), SQLite::OPEN_READWRITE );
    SQLite::Statement   query(db, sql);

    query.bind(1, gd.getGrupo().toUtf8().data());
    query.bind(2, gd.getId());
    query.exec();
}

QList<GrupoDespesa> DAO::listarGrupoDespesas() throw (std::exception){
    SQLite::Database db(getDbPath().toUtf8().data());
    SQLite::Statement   query(db, "SELECT id, grupo FROM grupo_despesas ORDER BY grupo ASC");
    QList<GrupoDespesa> rs;
    while (query.executeStep())
    {
        int id = query.getColumn(0);
        const char* grupo   = query.getColumn(1);

        GrupoDespesa gd;
        gd.setId(id);
        gd.setGrupo(QString(grupo));

        rs.append(gd);
    }
    return rs;
}
