#ifndef ANIMAL_H
#define ANIMAL_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>

class animal
{
public:
    animal();
    animal(QString,QString,QString,QString,QString);
    QString getId(){return id;}
     QString getNom(){return nom;}
     QString classeA(){return classe;}
     QString getDateajout() {return date_ajout;}
     QString getSexe(){return sexe;}

     void setId(QString);
     void setNom(QString);
     void setClasse(QString);
     void setDateajout(QString);
     void setSexe(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherStat();
    QSqlQueryModel* afficherTri(int);
    bool supprimer(QString);
    bool modifier(QString ref);

    QSqlQueryModel *recherche(QString);
private:
    QString id;
    QString nom;
    QString classe;
    QString date_ajout;
    QString sexe;
};

#endif // ANIMAL_H
