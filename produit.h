#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QSqlQueryModel>

class GS_ANIMAUX
{
public:
    GS_ANIMAUX();
    GS_ANIMAUX(QString,QString,int,QString,int);
    QString getref();
     QString getintitule();
     int getquantite();
     QString getcategorie();
     int getprix();
     void setref(QString);
     void setintitule(QString);
     void setquantite(int);
     void setcategorie(QString);
     void setprix(int);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool modifier(QString ID_A);
private:
    QString ID_A;
    QString NOM;
    int PRENOM;
    QString SEXE;
    int CLASSE;
};

#endif // PRODUIT_H
