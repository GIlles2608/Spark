#include "achat.h"

achat::achat()
{

}
achat::achat(int id,int ticket_id,int quantite,int total , int personne_id,int etat)
{
    this->id=id;
    this->ticket_id=ticket_id;
    this->quantite=quantite;
    this->total=total;
    this->personne_id=personne_id;
    this->etat=etat; // achat validé ou bien annulé
}
int achat::get_id(){return id;}
int achat::get_t_id(){return ticket_id;}
int achat::getot(){return total;}
int achat::getquantite(){return quantite;}
int achat::getp(){return personne_id;}
int achat::getetat(){return etat;}

bool achat::rechercher(int rech)
{
    QSqlQuery q;
    QString res=QString::number(rech);
    q.prepare("select id from achat where id=:id");
    q.bindValue(":id",res);
    q.exec();
    return q.next();

}
bool achat::ajouter()
{
    QSqlQuery q;
    q.prepare("insert into achat values(:id,:ticket_id,:quantite,:total,:personne_id,:etat)");
    q.bindValue(":id",id);
    q.bindValue(":ticket_id",ticket_id);
    q.bindValue(":quantite",quantite);
    q.bindValue(":total",total);
    q.bindValue(":personne_id",personne_id);
    q.bindValue(":etat",etat);
    return q.exec();
}
bool achat::supprimer(int a)
{
    QSqlQuery q;
    QString res=QString::number(a);
    q.prepare("delete from achat where id=:id");
    q.bindValue(":id",res);
    return q.exec();
}
QSqlQueryModel * achat::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select id,total from achat");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID ACHAT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX TOTAL"));
    return model;
}
QSqlQueryModel * achat::afficherFront(int id)
{
    QString res=QString::number(id);
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select id,total,ticket_id from achat where id_personne='"+res+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID ACHAT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX TOTAL"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Ticket Num"));
       return model;

}


bool achat::modifier(int rech, int qt , int tot)
{
    QSqlQuery q;
    q.prepare("update achat set quantite = :quantite, total = :total where id = :id");
    q.bindValue(":id",rech);
    q.bindValue(":quantite",qt);
    q.bindValue(":total",tot);

    return q.exec();
}
bool achat::modifierEat(int id)
{
    QSqlQuery q;
    q.prepare("update achat set etat = :etat where id = :id");
    q.bindValue(":etat",1);
    q.bindValue(":id",id);
    return q.exec();

}
QSqlQueryModel * achat::afficherRech(int id)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QString res=QString::number(id);
    model->setQuery("select * from achat where id like '"+res+"%'");
    return model;
}

QSqlQueryModel * achat::trier()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from achat order by dateachat");
    return model;
}
/*QSqlQueryModel * achat::stat()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select ticket_id,count(ticket_id) from achat group by ticket_id");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Ticket"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("achat"));

    return model;
}*/


