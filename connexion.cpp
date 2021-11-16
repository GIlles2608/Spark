#include "connexion.h"

connexion::connexion()
{

}
bool connexion::ouvrirConnexion()
{
    bool testOuverture=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("oussema");
    db.setUserName("oussema");
    db.setPassword("oussema");
    if (db.open())
        testOuverture=true;
    return  testOuverture;
}
void connexion::fermerConnexion()
{db.close();}
