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
    query.bind(6, d.getNaturezaId());
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

QList<Despesa> DAO::listarDespesasPeriodo(QDate de, QDate ate) throw (std::exception){
    SQLite::Database db(getDbPath().toUtf8().data());
    SQLite::Statement   query(db, "SELECT id, dt_evento, valor, memo, dt_inclusao, naturezaId, grupoId, natureza, grupo FROM view_despesas WHERE dt_evento >= ? AND dt_evento <= ? ORDER BY dt_evento, valor ASC");
    QList<Despesa> rs;

    query.bind(1, de.toString("yyyy-MM-dd").toUtf8().data());
    query.bind(2, ate.toString("yyyy-MM-dd").toUtf8().data());

    while (query.executeStep())
    {
        int id                  = query.getColumn(0);
        const char* dt_evento   = query.getColumn(1);
        int valor               = query.getColumn(2);
        const char* memo        = query.getColumn(3);
        const char* dt_inclusao = query.getColumn(4);
        int naturezaId          = query.getColumn(5);
        int grupoId             = query.getColumn(6);
        const char* naturezaNome        = query.getColumn(7);
        const char* grupoNome        = query.getColumn(8);

        Despesa d;
        d.setId(id);
        d.setDataDespesa(QDate().fromString(dt_evento,"yyyy-MM-dd") );
        d.setValor(valor);
        d.setMemo(memo);
        d.setDataInclusao(QDate().fromString(dt_inclusao,"yyyy-MM-dd"));
        d.setNaturezaId(naturezaId);
        d.setGrupoId(grupoId);
        d.setNatureza(naturezaNome);
        d.setGrupo(grupoNome);
        rs.append(d);
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


int DAO::incluirRateio(Rateio rateio) throw (std::exception){
    const char* sql = "INSERT INTO rateios (fk_unidade, parcela, valor, dt_vcto, razao, fkDespesa) VALUES (?, ?, ?, ?, ?, ?)";
    SQLite::Database db(getDbPath().toUtf8().data(), SQLite::OPEN_READWRITE );
    SQLite::Statement   query(db, sql);

    query.bind(1, rateio.getUnidade());
    query.bind(2, rateio.getParcela());
    query.bind(3, rateio.getValor());
    query.bind(4, rateio.getDataVencimento().toString("yyyy-MM-dd").toUtf8().data());
    query.bind(5, rateio.getRazao());
    query.bind(6, rateio.getDespesa());
    query.exec();

    return DAO::getLastInsertRowId();
}

void DAO::updateRateio(Rateio rateio) throw (std::exception){
    SQLite::Database db(getDbPath().toUtf8().data(), SQLite::OPEN_READWRITE );

    if( ! rateio.getUnidade() > -1 ){
        const char* sql = "UPDATE rateios SET fk_unidade=? WHERE id = ?";
        SQLite::Statement   query(db, sql);
        query.bind(1, rateio.getUnidade());
        query.bind(2, rateio.getId());
        query.exec();
    }

    if( rateio.getValor() > -1 ){
        const char* sql = "UPDATE rateios SET valor=? WHERE id = ?";
        SQLite::Statement   query(db, sql);
        query.bind(1, rateio.getValor());
        query.bind(2, rateio.getId());
        query.exec();
    }

    if( rateio.getParcela() > -1 ){
        const char* sql = "UPDATE rateios SET parcela=? WHERE id = ?";
        SQLite::Statement   query(db, sql);
        query.bind(1, rateio.getParcela());
        query.bind(2, rateio.getId());
        query.exec();
    }

    if( rateio.getRazao() > -1 ){
        const char* sql = "UPDATE rateios SET razao=? WHERE id = ?";
        SQLite::Statement   query(db, sql);
        query.bind(1, rateio.getRazao());
        query.bind(2, rateio.getId());
        query.exec();
    }
}

QList<Rateio> DAO::listarRateio() throw (std::exception){
    SQLite::Database db(getDbPath().toUtf8().data());
    SQLite::Statement   query(db, "SELECT rateioId, fk_unidade, parcela, valor, dt_vcto, razao, fkDespesa, unidadeId, numero FROM view_rateios ORDER BY fk_unidade,dt_vcto ASC");
    QList<Rateio> rs;
    while (query.executeStep())
    {
        int id          = query.getColumn(0);
        int unidade     = query.getColumn(1);
        int parcela     = query.getColumn(2);
        int valor       = query.getColumn(3);
        const char* vcto= query.getColumn(4);
        double razao    = query.getColumn(5);
        int despesaId   = query.getColumn(6);

        Rateio rateio;
        rateio.setId(id);
        rateio.setUnidade(unidade);
        rateio.setParcela(parcela);
        rateio.setValor(valor);
        rateio.setDataVencimento(QDate().fromString(vcto, "yyyy-MM-dd") );
        rateio.setDespesa(despesaId);
        rs.append(rateio);
    }
    return rs;
}

QList<Rateio> DAO::listarRateioPorDespesa(int despesaId) throw (std::exception){
    SQLite::Database db(getDbPath().toUtf8().data());
    SQLite::Statement   query(db, "SELECT u.id AS unidadeId, u.numero, r.id AS rateioId, r.fk_unidade, r.parcela, r.razao, r.valor, r.fkDespesa, r.dt_vcto FROM unidades u LEFT OUTER JOIN rateios r ON u.id = r.fk_unidade AND (fkDespesa = ? OR fkDespesa IS NULL)");
    query.bind(1, despesaId);
    QList<Rateio> rs;
    while (query.executeStep())
    {
        int unidadeId       = query.getColumn(0);
        const char* unidadeNumero= query.getColumn(1);
        int unidade     = query.getColumn(3);
        int rateioId          = query.getColumn(2);
        int parcela     = query.getColumn(4);
        double razao    = query.getColumn(5);
        int valor       = query.getColumn(6);
        const char* vcto= query.getColumn(8);
        int despesaId   = query.getColumn(7);

        Rateio rateio;
        rateio.setId(rateioId);
        rateio.setUnidade(unidade);
        rateio.setParcela(parcela);
        rateio.setValor(valor);
        rateio.setRazao((float)razao);
        rateio.setDataVencimento(QDate().fromString(vcto, "yyyy-MM-dd") );
        rateio.setDespesa(despesaId);
        rateio.unidadeId = unidadeId;
        rateio.unidadeNumero = unidadeNumero;
        rs.append(rateio);
    }
    return rs;
}
