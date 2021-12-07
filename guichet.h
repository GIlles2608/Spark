#ifndef GUICHET_H
#define GUICHET_H

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlQueryModel>

class guichet
{
public:
    guichet();
    guichet(int,QString,QString,QString);
    int get_id();
    QString get_nom();
    QString get_description();
    QString get_categorie();
    bool ajouter();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel * afficher();
    QSqlQueryModel * stats();
    QSqlQueryModel *affichercatId();
    QSqlQueryModel *Tri(int);
    int nbr_aide(int);
    QSqlQueryModel *recherche(QString);


private:
int id;
QString nom,description,categorie;

};

#endif // GUICHET_H
