#ifndef DAO_H
#define DAO_H

#include <SQLiteCpp/SQLiteCpp.h>

#include "entidade/unidade.h"
#include "entidade/despesa.h"
#include "entidade/naturezadespesa.h"
#include "entidade/grupodespesa.h"
#include "entidade/rateio.h"
#include <QDate>
#include <QMap>
#include <QList>

class DAO
{
public:
    DAO();

    static QString getDbPath();
    static int getLastInsertRowId() throw (std::exception);

    static int incluirUnidade(Unidade u) throw (std::exception);
    static QList<Unidade> listarUnidades() throw (std::exception);

    static int incluirDespesa(Despesa d) throw (std::exception);
    static QList<Despesa> listarDespesasPeriodo(QDate de, QDate ate) throw (std::exception);

    static int incluirNaturezaDespesa(NaturezaDespesa nd) throw (std::exception);
    static void updateNaturezaDespesa(NaturezaDespesa nd) throw (std::exception);
    static QList<NaturezaDespesa> listarNaturezaDespesas() throw (std::exception);

    static int incluirGrupoDespesa(GrupoDespesa gd) throw (std::exception);
    static void updateGrupoDespesa(GrupoDespesa gd) throw (std::exception);
    static QList<GrupoDespesa> listarGrupoDespesas() throw (std::exception);

    static int incluirRateio(Rateio rateio) throw (std::exception);
    static void updateRateio(Rateio rateio) throw (std::exception);
    static QList<Rateio> listarRateio() throw (std::exception);

};

#endif // DAO_H
