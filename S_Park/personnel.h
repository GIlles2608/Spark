#ifndef PERSONNEL_H
#define PERSONNEL_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <qcustomplot.h>
class Personnel
{
private:
    QString nom,prenom,ville,adresse;
    int age;
    long int cin,tel,cin_admin;
    QDate date_naissance;
    bool admin;
public:
    Personnel();
    Personnel(QString,QString,int,QDate,QString,QString,int,int);
    Personnel(QString,QString,int,QDate,QString,QString,int,int,int);
   //getters
    QString getNom(){return  nom;}
    QString getPrenom(){return  prenom;}
    int getCin(){return  cin;}
    int getCin_admin(){return  cin_admin;}
    int getTel(){return tel;}
    QDate getDate(){return  date_naissance;}
    QString getVille(){return  ville;}
    QString getAdresse(){return adresse;}
   // QString getType(){return  type;}
    int getAge(){return age;}
    bool getAdmin(){return admin;}
    //setters
    void setNom(QString n){nom = n;};
    void setPrenom(QString n){prenom = n;};
    void setCin(int n){cin = n;};
    void setCin_admin(int n){cin_admin = n;};
    void setDate(QDate n){date_naissance = n;};
    void setVille(QString n){ville = n;};
    void setAdresse(QString n){adresse = n;};
    //void setType(QString n){type = n;};
    void setAge(int n){age = n;};
    void setTel(int t){tel = t;}
    void setAdmin(bool v){admin = v;}
    //Crud(fonction bassique)
    bool ajouter();
    bool ajouter_Admin();
    bool modifier(int);
    bool modifier_Admin(int);
    bool supprimer(int);
    QSqlQueryModel *rechercher(QString);
    QSqlQueryModel *afficher();
    QSqlQueryModel *Trie_Nom_A();
    QSqlQueryModel *Trie_age_A();
    QSqlQueryModel *Trie_cin_A();
    QSqlQueryModel *Trie_Nom_D();
    QSqlQueryModel *Trie_age_D();
    QSqlQueryModel *Trie_cin_D();
    void stat(QCustomPlot *customPlot);
};

#endif // PERSONNEL_H
