#include "ticket.h"

ticket::ticket()
{

}
ticket::ticket(int id,int guichet_id,int prix,int quantite){
    this->id=id;
    this->guichet_id=guichet_id;
    this->prix=prix;
    this->quantite=quantite;
}
int ticket::get_id(){return id;}
int ticket::get_guichet_id(){return guichet_id;}
int ticket::get_quantite(){return quantite;}
int ticket::get_prix(){return prix;}

bool ticket::ajouter(){
    QSqlQuery q;
    q.prepare("insert into ticket values(:id,:guichet_id,:prix,:quantite)");
    q.bindValue(":id",id);
    q.bindValue(":guichet_id",guichet_id);
    q.bindValue(":prix",prix);
    q.bindValue(":quantite",quantite);
    return q.exec();
}
bool ticket::supprimer(int a)
{
    QSqlQuery q;
    QString res=QString::number(a);
    q.prepare("delete from ticket where id=:id");
    q.bindValue(":id",res);
    return q.exec();
}
bool ticket::modifier(int id)
{

    QSqlQuery q;

    q.prepare("update ticket set id=:id,id_guichet=:guichet_id,prix=:prix,quantite=:quantite where id=:id");
    q.bindValue(":id",id);
    q.bindValue(":guichet_id",guichet_id);
    q.bindValue(":prix",prix);
    q.bindValue(":quantite",quantite);
   return q.exec();


}
QSqlQueryModel * ticket::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from ticket");

    return model;
}
QSqlQueryModel * ticket::afficherParId(int id)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QString res=QString::number(id);
    model->setQuery("select * from ticket where guichet_id='"+res+"'");

    return model;
}

QSqlQueryModel * ticket::recherche(QString res)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM ticket where id like'"+res+"%' or id_guichet like'"+res+"%' or prix like'"+res+"%' or quantite like'"+res+"%' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("GUICHET"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
    return model;
}
