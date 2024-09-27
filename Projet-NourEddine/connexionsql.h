#ifndef CONNEXIONSQL_H
#define CONNEXIONSQL_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
class connexionSQL
{
private:
    QSqlDatabase db;
public:
    connexionSQL();
    bool ouvrirConnexion();
    void fermerConnexion();
};
#endif // CONNEXIONSQL_H
