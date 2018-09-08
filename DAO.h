#ifndef DAO_H
#define DAO_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <QMap>
#include "entidade/unidade.h"
#include "entidade/despesa.h"
#include <QMap>
#include <QList>

class DAO
{
public:
    DAO();

    static QString getDbPath();
    static int getLastInsertRowId() throw (std::exception);
    static int incluirUnidade(Unidade u) throw (std::exception);
    static int incluirDespesa(Despesa d) throw (std::exception);
    static QList<Unidade> listarUnidades() throw (std::exception);

};

#endif // DAO_H
