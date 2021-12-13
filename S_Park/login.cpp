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
      query.prepare("select * from gs_personnels where username =? and password =?");
      query.addBindValue(username);
      query.addBindValue(password);

      if (query.exec())
      {
          // You login a user here
        //  QString name = query.value(1).toString();
        //  qDebug() << name << "is logged in";
       int count = 0;
         while(query.next())
         {
             count ++;
         }

         if(count == 1)
          return true;
         else if(count<1)
          {
             qDebug() << "Login failed. Invalid username or password.";
             return  false;
          }
      }
      else
      {
             qDebug() << "Probleme de connexion dba";
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
    query.prepare("Update gs_personnels set password=:password where username=:username");
    query.bindValue(":username",username);
    query.bindValue(":password",password);

    return query.exec();
}
