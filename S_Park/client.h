#ifndef CLIENT_H
#define CLIENT_H
#include <QSqlQueryModel>
#include <QString>

class client
{
public:
    client();
    client(int,QString,QString,int,QString,QString);
    int getCin(){return cin;}
    QString getNom(){return nom;}
     QString getPrenom(){return prenom;}
      QString getDateNaissance(){return datedenaissance;}
    int getTel(){return numtel;}
    bool ajouter();
    bool modifier(int);
    bool supprimer(int);
    QSqlQueryModel * afficher();
    QSqlQueryModel * Tri(int);
    QSqlQueryModel *afficherRech(QString res);
    QSqlQueryModel * afficher_2();
    QSqlQueryModel * Tri_2(int);
    QSqlQueryModel *afficherRech_2(QString res);



private:
    int cin,numtel;
    QString nom,prenom,datedenaissance,sexe;
};

#endif // CLIENT_H
