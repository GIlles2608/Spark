#include "connection.h"
#include "produit.h"
#include <QSqlDatabase>

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("animaux");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("oooooooo");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}

