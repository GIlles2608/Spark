#ifndef PERSONNEL_H
#define PERSONNEL_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Personnel
{
private:
    QString nom,prenom,ville,adresse;
    int age,cin;

public:
    Personnel();
    Personnel(QString,QString,int,QString,QString,int);
   //getters
    QString getNom(){return  nom;}
    QString getPrenom(){return  prenom;}
    int getCin(){return  cin;}
   // QString getDate(){return  date;}
    QString getVille(){return  ville;}
    QString getAdresse(){return adresse;}
    int getAge(){return age;}
    //setters
    void setNom(QString n){nom = n;};
    void setPrenom(QString n){prenom = n;};
    void setCin(int n){cin = n;};
   // void setDate(QString n){date = n;};
    void setVille(QString n){ville = n;};
    void setAdresse(QString n){adresse = n;};
    void setAge(int n){age = n;};
    //Crud(fonction bassique)
    bool ajouter();
    QSqlQueryModel *afficher();
    bool modifier(int);
    bool supprimer(int);
};

#endif // PERSONNEL_H
