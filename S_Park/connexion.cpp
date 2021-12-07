#include "connexion.h"

Connexion::Connexion()
{

}

bool Connexion::createconnexion()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test = false;
    db.setDatabaseName("Gilles_Base");
    db.setUserName("coffa");
    db.setPassword("william");

    if(db.open())
        test = true;

    return test;
}

void Connexion::closeconnexion()
{
    db.close();
}
