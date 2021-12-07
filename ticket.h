#ifndef TICKET_H
#define TICKET_H
#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlQueryModel>


class ticket
{
public:
    ticket();
    ticket(int,int,int,int);
    int get_id();
    int get_guichet_id();
    int get_prix();
    int get_quantite();
    bool ajouter();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel * afficher();
    QSqlQueryModel *   afficherParId(int);
    QSqlQueryModel * recherche(QString);
private :
    int id, quantite,prix,guichet_id;

};

#endif // TICKET_H
