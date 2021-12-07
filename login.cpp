#include "login.h"

login::login()
{

}

login::~login()
{

}

login::login(QString u,QString p)
{
  username = u;
  password = p;
}

bool login::connecter()
{
    QSqlQuery query;
      query.prepare("select * from gs_personnels where username =: username,password =:password");
      query.bindValue(":username",username);
      query.bindValue(":password",password);

      if (query.size() > 0)
      {
          // You login a user here
        //  QString name = query.value(1).toString();
        //  qDebug() << name << "is logged in";

          return true;
      }
      else
      {
          qDebug() << "Login failed. Invalid username or password.";

          return false;
      }


}



bool login::creer_utilsateur(int cin)
{
    QSqlQuery query;
     QString res = QString::number(cin);
    query.prepare("Update gs_personnels set username=:username,password=:password where cin =:cin");
    query.bindValue(":username",username);
    query.bindValue(":cin",res);
    query.bindValue(":password",password);

    return query.exec();
}

bool login::modifier_Compte()
{
    QSqlQuery query;
    query.prepare("Update gs_personnels set username=:username,password=:password");
    query.bindValue(":username",username);
    query.bindValue(":password",password);

    return query.exec();
}
