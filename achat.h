#ifndef ACHAT_H
#define ACHAT_H
#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlQueryModel>

class achat
{
public:
    achat();
    achat(int,int,int,int,int,int);
    int get_id();
    int get_t_id();
    int getot();
    int getquantite();
    int getp();
    int getetat();
    bool ajouter();
    bool supprimer(int);
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficherFront(int);
     QSqlQueryModel * afficherRech(int);
      QSqlQueryModel * trier();
      QSqlQueryModel * stat();
    bool rechercher(int);
    bool modifier(int,int,int );
    bool modifierEat(int);
private:
    int id;
    int ticket_id;
    int quantite;
    int total;
    int personne_id;
    int etat;
};

#endif // ACHAT_H
