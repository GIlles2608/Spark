#ifndef LOGIN_H
#define LOGIN_H


#include <QSqlQuery>
#include <QtDebug>
#include <QFileInfo>
#include <QString>





class login
{

public:
    login();
    login(QString,QString);
    bool connecter();
    bool creer_utilsateur(int cin);
    bool modifier_Compte();
    bool getAdmin(){return admin;}
    void setAdmin(bool a){admin = a;}
    QString getUsername(){return username;}
    QString getPassword(){return password;}
    void setUsername(QString u){username = u;}
    void setPassword(QString u){password = u;}

    ~login();


private:
    bool admin;
    QString password;
    QString username;
};

#endif // LOGIN_H
