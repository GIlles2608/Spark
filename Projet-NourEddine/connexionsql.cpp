#include "connexionsql.h"
connexionSQL::connexionSQL()
{
}
bool connexionSQL::ouvrirConnexion()
{
    bool testOuverture=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projetqt");
    db.setUserName("projetqt");//inserer nom de l'utilisateur
    db.setPassword("projetqt");//inserer mot de passe de cet utilisateur

    if (db.open())
        testOuverture=true;
    return  testOuverture;
}
void connexionSQL::fermerConnexion()
{db.close();}
