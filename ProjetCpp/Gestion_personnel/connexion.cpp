#include "connexion.h"

Connexion::Connexion()
{

}

bool Connexion::createconnexion()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test = false;
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("system");
    db.setPassword("26082409Madm");

    if(db.open())
        test = true;

    return test;
}

void Connexion::closeconnexion()
{
    db.close();
}
