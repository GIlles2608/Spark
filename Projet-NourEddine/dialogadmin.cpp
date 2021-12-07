#include "dialogadmin.h"
#include "ui_dialogadmin.h"
#include "statistiques.h"
#include  <QDesktopServices>
#include <QPdfWriter>
#include <QPrinter>
#include "QPrintDialog"
Dialogadmin::Dialogadmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogadmin)
{
    // constructeur user interface ui -> setpUi(this dialog)
    ui->setupUi(this);
    // initialisation du programme
    // 1) remplissage des tableu guichet + ticket + achat
    ui->guichetList->setModel(g.afficher()); // / table guichetList va presenter le model guichet.afficher
    ui->ticketList->setModel(t.afficher()); // / table ticketList va presenter le model ticket.afficher
    ui->achatsList->setModel(a.afficher()); // table achatsList va presenter le model achat.afficher
    // 2) controle de saisie des lineEdits
    ui->g_categorie_edit->hide();
    ui->t_id_e->setValidator(new QIntValidator(0,9999999,this));
    ui->t_prix_e->setValidator(new QIntValidator(0,9999999,this));
    ui->t_quantite_e->setValidator(new QIntValidator(0,9999999,this));
    ui->g_id_add->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie lineedit va accepter juste les nombre de 0 a 9999999
    ui->t_id_add->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie
    ui->g_id_add->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie
    ui->t_prix_add->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie
    ui->t_quantite_add->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie
    ui->g_nom_edit->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));// controle de saisie lineedit va accepter juste les lettres miniscules + majuscules
    ui->g_description_edit->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
    ui->g_nom_add->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
    // Remplissage du combobox guichet_id ( ajout du ticket au guichet X )
    ui->t_guichet_id_add->setModel(g.affichercatId());
    // Les lineEdit + buttons invisibles :
    hideElements();


}

Dialogadmin::~Dialogadmin()
{
    // destructeur user interface ui
    delete ui;
}

// ajout guichet
void Dialogadmin::on_g_add_clicked()
{
    int id = ui->g_id_add->text().toInt();
    QString nom = ui->g_nom_add->text();
    QString description = ui->g_description_add->toPlainText();
     QString categorie =ui->g_cat_combo->currentText();
    guichet s(id,nom,description,categorie);
    bool test = s.ajouter();
    if(test)
    {
        ui->ticketList->setModel(t.afficher());
        ui->t_guichet_id_add->setModel(g.affichercatId());
        ui->t_guichet_id_e->setModel(g.affichercatId());

        QMessageBox::information(nullptr, QObject::tr("GUICHET ADD "),
                                      QObject::tr("GUICHET ADDED SUCCESSFULLY.\n"), QMessageBox::Ok);
        ui->guichetList->setModel(g.afficher());
         ui->g_id_add->clear();
         ui->g_nom_add->clear();
        ui->g_description_add->clear();
        hideElements();


    }
    else{
        QMessageBox::information(nullptr, QObject::tr("GUICHET ADD "),
                                      QObject::tr("NOM ALREADY IN USE.\n"), QMessageBox::Ok);

}

}
// selection d'un guichet pour modifer / supprimer
void Dialogadmin::on_guichetList_activated(const QModelIndex &index)
{
    QString val=ui->guichetList->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("Select id,nom,description from guichet where  id='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {
                        ui->g_id_edit->setText(qry.value(0).toString());
                        ui->g_nom_edit->setText(qry.value(1).toString());
                        ui->g_description_edit->setText(qry.value(2).toString());
                        ui->g_id_edit->show();
                        ui->t_guichet_id_e->setModel(g.affichercatId());
                        ui->g_id_edit->setEnabled(false);
                        ui->g_nom_edit->show();
                        ui->g_description_edit->show();
                        ui->edit_g->show();
                        ui->delete_g->show();
                        ui->g_categorie_edit->show();
                    }
        }
}
// modifier guichet
void Dialogadmin::on_edit_g_clicked()
{
    int id= ui->g_id_edit->text().toInt();
    QString nom = ui->g_nom_edit->text();
    QString description= ui->g_description_edit->text();
    QString cateogrie=ui->g_categorie_edit->currentText();
     bool test = false;
     if(cateogrie == "CATEGORIE"){
         QMessageBox::critical(nullptr, QObject::tr("GUICHET MODIFY"),
                                       QObject::tr("SELECT A CATEGORY !\n"), QMessageBox::Cancel);
     }
     else{


     guichet cp(id,nom,description,cateogrie);
    test = cp.modifier(id);
    if(test){
        ui->t_guichet_id_add->setModel(g.affichercatId()); // combobox  (guichet)  ajout ticket refresh
        hideElements();
        ui->guichetList->setModel(g.afficher());
        QMessageBox::information(nullptr, QObject::tr("GUICHET MODIFY"),
                                      QObject::tr("GUICHET MODIFIED SUCCESSFULY .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        ui->guichetList->setModel(g.afficher());
        hideElements();

        QMessageBox::information(nullptr, QObject::tr("GUICHET MODIFY"),
                                      QObject::tr("ERROR !\n"), QMessageBox::Cancel);

    }
        }

}
// supp guichet + ( les ticket de cet guichet automatiquement )
void Dialogadmin::on_delete_g_clicked()
{
    // suppression des guichet
    int id=ui->g_id_edit->text().toInt();

    bool test2=g.supprimer(id);
    if(test2){
        hideElements();
        //la constrainte foreign key (id_guichet dans ticket ) a un reglage on delete cascade si on sup un guichet leur ticket vont etres sup aussi
        ui->t_guichet_id_add->setModel(g.affichercatId());
        ui->guichetList->setModel(g.afficher());
        // refresh du table ticket list d'ils-ya des ticket supprimer after deleting the guichet
        ui->ticketList->setModel(t.afficher());
        QMessageBox::information(nullptr, QObject::tr("GUICHET DELETE"),
                                      QObject::tr("GUICHET DELETED SUCCESSFULY .\n" "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        ui->guichetList->setModel(g.afficher());
        hideElements();

        QMessageBox::information(nullptr, QObject::tr("GUICHET DELETE"),
                                      QObject::tr("ERROR !\n"), QMessageBox::Cancel);

    }
}
// //////////////////////////////////// menu /////////////////////////////////////
// menu page 1  gestion ticket
void Dialogadmin::on_routeTicket_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
// menu page 2 gestion achat
void Dialogadmin::on_routeGuichet_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
// menu page 0 gestion guichet
void Dialogadmin::on_backGuichet_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
// menu page 0 gestion guichet
void Dialogadmin::on_nextrouteUser_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
// menu page 0 gestion ticket
void Dialogadmin::on_backrouteAchat_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



// ajouter ticket
void Dialogadmin::on_t_add_selected_clicked()
{
     ui->user_management_stacked_2->setCurrentIndex(1);
}

void Dialogadmin::on_t_add_clicked()
{
 // on va prendre les values saisies par l'utilisateur
    int id = ui->t_id_add->text().toInt();
    int guichet_id = ui->t_guichet_id_add->currentText().toInt();
    int prix = ui->t_prix_add->text().toInt();
    int quantite = ui->t_quantite_add->text().toInt();
    if (id<=0){
        QMessageBox::information(nullptr, QObject::tr("TICKET ADD "),
                                      QObject::tr("INVALID ID.\n"), QMessageBox::Ok);

    }
    else if(prix<=0){
        QMessageBox::information(nullptr, QObject::tr("TICKET ADD "),
                                      QObject::tr("INVALID PRIX.\n"), QMessageBox::Ok);

    }
    else if(quantite<0){
        QMessageBox::information(nullptr, QObject::tr("TICKET ADD "),
                                 QObject::tr("INVALID QUANTITE.\n"), QMessageBox::Ok);

    }
    else{
 // creation d'un object avec ses valeurs
    ticket s(id,guichet_id,prix,quantite);
    // test ajout ticket s
    bool test =(s.ajouter());
    if(test)
    {
        // ticket ajouté
        QMessageBox::information(nullptr, QObject::tr("TICKET ADD "),
                                      QObject::tr("TICKET ADDED SUCCESSFULLY.\n"), QMessageBox::Ok);
        // refresh table + clear lineedits
        ui->ticketList->setModel(t.afficher());
        // back to ticket tableview
        ui->user_management_stacked_2->setCurrentIndex(0);
         ui->t_id_add->clear();
         ui->t_prix_add->clear();
        ui->t_quantite_add->clear();


    }
    else{
        // ticket non ajouter
        QMessageBox::information(nullptr, QObject::tr("TICKET ADD "),
                                      QObject::tr("ID / NAME ALREADY IN USE.\n"), QMessageBox::Ok);

}
    }
}
// lorsque on double click sur un iD d'un ticket du tableau
void Dialogadmin::on_ticketList_activated(const QModelIndex &index)
{
    // val = id du ticket selectionée
    QString val=ui->ticketList->model()->data(index).toString();
        QSqlQuery qry;
        // recupérer les information de cet ticket du base de données
        qry.prepare("Select id,prix,quantite from ticket where  id='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {

                        ui->t_id_e->setText(qry.value(0).toString());
                        ui->t_prix_e->setText(qry.value(1).toString());
                        ui->t_quantite_e->setText(qry.value(2).toString());
                        ui->t_id_e->show();
                        ui->t_id_e->setEnabled(false);
                        ui->t_quantite_e->show();
                        ui->t_prix_e->show();
                        ui->edit_g->show();
                        ui->delete_g->show();
                        ui->t_edit->show();
                        ui->t_delete->show();
                        ui->t_guichet_id_e->show();
                        ui->t_guichet_id_e->setModel(g.affichercatId());
                    }
        }
}

void Dialogadmin::on_t_edit_clicked()
{
    // on va prendre les values saisies par l'utilisateur
    int id= ui->t_id_e->text().toInt();
    int quantity= ui->t_quantite_e->text().toInt();
    int prix= ui->t_prix_e->text().toInt();
    // valeur du comobox ( choix du id categorie pour une ticket)
    int catID =ui->t_guichet_id_e->currentText().toInt();
     bool test = false;
     // creation d'un object du class ticket avec les valeurs saisie par l'user
     ticket cp(id,catID,prix,quantity);
     // test de modification du ticket qui a id = int id= ui->t_id_e->text().toInt();
    test = cp.modifier(id);
    if(test){
        //MOdification success
        // remplissage du table ticket aprees la modification ( refresh table)
        ui->ticketList->setModel(t.afficher());
        //  //Methode pour mettres des buttons , lineedits invisible dans des cas ...
        hideElements();
        QMessageBox::information(nullptr, QObject::tr("TICKET MODIFY"),
                                      QObject::tr("TICKET MODIFIED SUCCESSFULY .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        //modification failed
        // refresh table ticketlist
        ui->ticketList->setModel(t.afficher());
          //Methode pour mettres des buttons , lineedits invisible dans des cas ...
        hideElements();
            //
        QMessageBox::critical(nullptr, QObject::tr("TICKET MODIFY"),
                                      QObject::tr("ERROR !\n"), QMessageBox::Cancel);

    }


}
void Dialogadmin::hideElements(){
    //Methode pour mettres des buttons , lineedits invisible dans des cas ...
    ui->g_id_edit->hide();
    ui->g_categorie_edit->hide();
    ui->g_nom_edit->hide();
    ui->g_description_edit->hide();
    ui->edit_g->hide();
    ui->delete_g->hide();
    ui->t_id_e->hide();
    ui->t_quantite_e->hide();
    ui->t_prix_e->hide();
    ui->edit_g->hide();
    ui->delete_g->hide();
    ui->t_edit->hide();
    ui->t_delete->hide();
    ui->t_guichet_id_e->hide();

}

void Dialogadmin::on_t_delete_clicked()
{
    int id = ui->t_id_e->text().toInt();
    bool test  = t.supprimer(id);
    if(test){
          //Methode pour mettres des buttons , lineedits invisible dans des cas ...
        hideElements();
        //refresh table ticketlist
        ui->ticketList->setModel(t.afficher());

        QMessageBox::information(nullptr, QObject::tr("TICKET Delete"),
                                      QObject::tr("TICKET deleted SUCCESSFULY .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);



    }
    else{
        //Methode pour mettres des buttons , lineedits invisible dans des cas ...
      hideElements();
      //refresh table ticketlist
        ui->ticketList->setModel(t.afficher());

        QMessageBox::critical(nullptr, QObject::tr("TICKET delete"),
                                      QObject::tr("ERROR .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);


    }
}

void Dialogadmin::on_stat_btn_clicked()
{
    dial = new statistiques();
    dial->start_stat();
    dial->exec();
}

void Dialogadmin::on_lineEdit_textChanged(const QString &arg1)
{
    ui->guichetList->setModel(g.recherche(arg1));
}

void Dialogadmin::on_t_recherche_textChanged(const QString &arg1)
{
    ui->ticketList->setModel(t.recherche(arg1));
}

void Dialogadmin::on_guichetPDF_clicked()
{
    QPdfWriter pdf("C:/Users/nourdine/Desktop/guichet.pdf");
                      QPainter painter(&pdf);
                     int i = 4000;
                          painter.setPen(Qt::blue);
                          painter.setFont(QFont("Arial", 30));
                          painter.drawText(2300,1200,"Liste Des guichet");
                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Arial", 50));
                         // painter.drawText(1100,2000,afficheDC);
                          painter.drawRect(1500,200,7300,2600);
                          //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                          painter.drawRect(0,3000,9600,500);
                          painter.setFont(QFont("Arial", 9));
                          painter.drawText(300,3300,"ID");
                          painter.drawText(2300,3300,"NOM");
                          painter.drawText(4300,3300,"DESCRIPTION");
                          painter.drawText(6300,3300,"CATEGORIE");



                          QSqlQuery query;
                          query.prepare("select * from guichet");
                          query.exec();
                          while (query.next())
                          {
                              painter.drawText(300,i,query.value(0).toString());
                              painter.drawText(2300,i,query.value(1).toString());
                              painter.drawText(4300,i,query.value(2).toString());
                              painter.drawText(6300,i,query.value(3).toString());



                             i = i +500;
                          }
                          int reponse = QMessageBox::question(this, "CREATION PDF", "PDF SAVED OPEN PDF?", QMessageBox::Yes |  QMessageBox::No);
                              if (reponse == QMessageBox::Yes)
                              {
                                  QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/nourdine/Desktop/guichet.pdf"));

                                  painter.end();
                              }
                              if (reponse == QMessageBox::No)
                              {
                                   painter.end();
                              }
}

void Dialogadmin::on_comboBox_currentIndexChanged(int index)
{
    ui->guichetList->setModel(g.Tri(index));
}

void Dialogadmin::on_pushButton_clicked()
{
    QPrinter printer;
    QPrintDialog dialog(&printer,this);
    dialog.setWindowTitle("Print Document");
    dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if( dialog.exec() != QDialog::Accepted){
        return;
    }
}
