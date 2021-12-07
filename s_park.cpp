#include "s_park.h"
#include "ui_s_park.h"

S_park::S_park(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::S_park)
{
    ui->setupUi(this);
    refresh();

    // Animaux
    QPieSeries *series = new QPieSeries();
       QSqlQuery q("select sexe,count(*) from animal group by sexe");


        while(q.next())
        {series->append(q.value(0).toString()+": "+q.value(1).toString(),q.value(1).toInt());}
       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->setTitle("Statistiques");
       chart->setBackgroundBrush(Qt::transparent);
       QChartView *chartview = new QChartView(chart);
       chartview->setRenderHint(QPainter::Antialiasing);
       chartview->setParent(ui->horizontalFrame);
       chartview->resize(400,300);

       chart->setAnimationOptions(QChart::AllAnimations);
       chart->legend()->setVisible(true);
       chart->legend()->setAlignment(Qt::AlignRight);
       series->setLabelsVisible(true);
       /*int ret=a.connect_arduino();
             switch (ret) {
             case(0):qDebug()<<"arduino is available and connected to :"<<a.getarduino_port_name();
                 break;
             case(1):qDebug()<<"arduino is available but not connected to :"<<a.getarduino_port_name();
                 break;
             case(-1):qDebug()<<"arduino is not available";
             }
       QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));*/

     // guichet && ticket && achat
       // constructeur user interface ui -> setpUi(this dialog)

       // initialisation du programme
       // 1) remplissage des tableu guichet + ticket + achat
       ui->guichetList->setModel(g.afficher()); // / table guichetList va presenter le model guichet.afficher
       ui->ticketList_3->setModel(t.afficher()); // / table ticketList va presenter le model ticket.afficher
       ui->achatsList_3->setModel(a.afficher()); // table achatsList va presenter le model achat.afficher
       ui->ticketListFront->setModel(t.afficherParId(0));
       // 2) controle de saisie des lineEdits
       ui->g_categorie_edit->hide();
       ui->t_id_e_3->setValidator(new QIntValidator(0,9999999,this));
       ui->t_prix_e_3->setValidator(new QIntValidator(0,9999999,this));
       ui->t_quantite_e_3->setValidator(new QIntValidator(0,9999999,this));
       ui->g_id_add->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie lineedit va accepter juste les nombre de 0 a 9999999
       ui->t_id_add_3->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie
       ui->g_id_add->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie
       ui->t_prix_add_3->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie
       ui->t_quantite_add_3->setValidator(new QIntValidator(0,9999999,this)); // controle de saisie
       ui->g_nom_edit->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));// controle de saisie lineedit va accepter juste les lettres miniscules + majuscules
       ui->g_description_edit->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
       ui->g_nom_add->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
       // Remplissage du combobox guichet_id ( ajout du ticket au guichet X )
       ui->t_guichet_id_add_3->setModel(g.affichercatId());
       // Les lineEdit + buttons invisibles :
       hideElements();


       ui->tableView->setModel(P.afficher());
       ui->comboBox_supp->setModel(P.afficher());
       ui->comboBox_cin_modi->setModel(P.afficher());
       ui->cin->setValidator(new QIntValidator(0,9999999,this));
      // ui->cin_admin->setValidator(new QIntValidator(0,9999999,this));
       ui->telephone->setValidator(new QIntValidator(0,99999999,this));
       ui->telephone_2->setValidator(new QIntValidator(0,99999999,this));
}

S_park::~S_park()
{
    delete ui;
}


/*-----------Navigaton ----------------------------*/

void S_park::on_employer_clicked()
{
  ui->stackedWidget_Park->setCurrentIndex(0);
}

void S_park::on_aniamaux_clicked()
{
   ui->stackedWidget_Park->setCurrentIndex(1);
}

void S_park::on_clients_clicked()
{
 // ui->stackedWidget->setcurentIndex(0);
}

void S_park::on_Guichet_2_clicked()
{
    ui->stackedWidget_Park->setCurrentIndex(2);
}

void S_park::on_tickets_clicked()
{
    ui->stackedWidget_Park->setCurrentIndex(3);
}

void S_park::on_acahts_tickets_clicked()
{
    ui->stackedWidget_Park->setCurrentIndex(4);
}

void S_park::on_achats_clicked()
{
    ui->stackedWidget_Park->setCurrentIndex(5);
}


void S_park::on_approvisionement_clicked()
{

}




/*--------------------------------------GESTION CLIENT------------------------------*/

/*void S_park::on_start_client_clicked()
{
     ui->clientStacked->setCurrentIndex(2);
}*/


/*----------------------------------------------------------------------------------------*/




/*--------------------------------------GESTION ANIMAUX------------------------------*/

void S_park::refresh(){



       // affichage table Animeaux
       ui->tabAnimal->setModel(an.afficher());

       // affichage statistiques dans tab stat
      // ui->an_statTable->setModel(an.afficherStat());

           //Controle saisie du formulaire ajout Animal :
       ui->an_id_add->setValidator(new QIntValidator(0,9999999,this));
       ui->an_nom_add->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
       ui->an_classe_add->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
       //Controle saisie du formulaire Modifier  Animal :
       ui->an_id_e->setValidator(new QIntValidator(0,9999999,this));
       ui->an_nom_e->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
       ui->an_classe->setValidator(new QRegExpValidator( QRegExp("[A-Za-z ]*") , this ));
       // Controlse  saisie affichage du formulaire edit and delete
       ui->an_edit->hide();
       ui->an_delete->hide();
       ui->an_id_e->hide();
       ui->an_nom_e->hide();
       ui->an_classe->hide();
       ui->an_sexe_e->hide();
       ui->an_classe->clear();
       ui->an_nom_e->clear();
       ui->an_id_e->clear();

}






void S_park::on_an_addBtn_clicked()
{
    QString id = ui->an_id_add->text();
    QString nom  = ui->an_nom_add->text();
    QString classe = ui->an_classe_add->text();
    QDate test = QDate::currentDate();
    QString date_ajout = test.toString("yyyy/MM/dd");
    QString sexe = ui->an_sexe_add->currentText();
    if (id.toInt()<=0){
        QMessageBox::critical(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("ID invalide! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(nom.size()<=2){
        QMessageBox::critical(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("Nom invalide! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);
        }
    else if(classe.size()<=2) {
        QMessageBox::critical(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("Classe invalide! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(sexe=="SEXE"){
        QMessageBox::critical(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("Choissir un Sexe! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }

    else{
    animal an(id,nom,classe,date_ajout,sexe);
    bool validation = an.ajouter();
    if (validation){
        refresh();
        QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                        notifier->setIcon(QIcon(""));
                         notifier->show();
                         notifier->showMessage("Animal ajouté","Reussi",QSystemTrayIcon::Information,10000);

    }
    else{

            QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                            notifier->setIcon(QIcon(""));
                             notifier->show();
                             notifier->showMessage("Animal non ajouté","Echec",QSystemTrayIcon::Critical,10000);

    }
    }
}

void S_park::on_tabAnimal_activated(const QModelIndex &index)
{
    ui->an_edit->show();
    ui->an_delete->show();
    ui->an_id_e->show();
    ui->an_id_e->setEnabled(0);
    ui->an_nom_e->show();
    ui->an_classe->show();
    ui->an_sexe_e->show();

    QString val=ui->tabAnimal->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("Select nom,classe from animal where  id='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {
                        ui->an_id_e->setText(val);
                        ui->an_nom_e->setText(qry.value(0).toString());
                        ui->an_classe->setText(qry.value(1).toString());
                    }
        }
}

void S_park::on_an_delete_clicked()
{
    QString ref = ui->an_id_e->text();
    bool test = an.supprimer(ref);
    if (test){
        refresh();
        QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                        notifier->setIcon(QIcon(""));
                         notifier->show();
                         notifier->showMessage("Animal supprimé","Reussi",QSystemTrayIcon::Information,10000);

    }
    else{
        refresh();
        QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                        notifier->setIcon(QIcon(""));
                         notifier->show();
                         notifier->showMessage("Animal non supprimé","Echec",QSystemTrayIcon::Critical,10000);

    }
}

void S_park::on_an_edit_clicked()
{
    QString id = ui->an_id_e->text();
    QString nom  = ui->an_nom_e->text();
    QString classe = ui->an_classe->text();
    QDate test = QDate::currentDate();
    QString date_ajout = test.toString("yyyy/MM/dd");
    QString sexe = ui->an_sexe_e->currentText();
    if (id.toInt()<=0){
        QMessageBox::critical(nullptr, QObject::tr("Animal Modifier"),
                                      QObject::tr("ID invalide! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(nom.size()<=2){
        QMessageBox::critical(nullptr, QObject::tr("Animal Modifier"),
                                      QObject::tr("Nom invalide! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);
        }
    else if(classe.size()<=2) {
        QMessageBox::critical(nullptr, QObject::tr("Animal Modifier"),
                                      QObject::tr("Classe invalide! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else if(sexe=="SEXE"){
        QMessageBox::critical(nullptr, QObject::tr("Animal Modifier"),
                                      QObject::tr("Choissir un Sexe! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }

    else{
    animal an(id,nom,classe,date_ajout,sexe);
    bool validation = an.modifier(id);
    if (validation){
        refresh();
        QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                        notifier->setIcon(QIcon(""));
                         notifier->show();
                         notifier->showMessage("Animal modifié","Reussi",QSystemTrayIcon::Information,10000);

    }
    else{
        QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                        notifier->setIcon(QIcon(""));
                         notifier->show();
                         notifier->showMessage("Animal non modifié","Echec",QSystemTrayIcon::Critical,10000);

    }
    }
}

void S_park::on_an_recherche_textChanged(const QString &arg1)
{
    if(arg1.size()<=0){
        refresh();
    }
    else{
        ui->tabAnimal->setModel(an.recherche(arg1));
     }
}

void S_park::on_an_imprimer_clicked()
{
    QString strStream;
                       QTextStream out(&strStream);

                        const int rowCount = ui->tabAnimal->model()->rowCount();
                        const int columnCount = ui->tabAnimal->model()->columnCount();
                       out <<  "<html>\n"
                       "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                        <<  QString("<title>%1</title>\n").arg("strTitle")
                                        <<  "</head>\n"
                                        "<body bgcolor=#ffffff link=#5000A0>\n"



                                        "<center> <H1>Liste des animaux</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                    // headers
                                    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                    out<<"<cellspacing=10 cellpadding=3>";
                                    for (int column = 0; column < columnCount; column++)
                                        if (!ui->tabAnimal->isColumnHidden(column))
                                            out << QString("<th>%1</th>").arg(ui->tabAnimal->model()->headerData(column, Qt::Horizontal).toString());
                                    out << "</tr></thead>\n";

                                    // data table
                                    for (int row = 0; row < rowCount; row++) {
                                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                        for (int column = 0; column < columnCount; column++) {
                                            if (!ui->tabAnimal->isColumnHidden(column)) {
                                                QString data = ui->tabAnimal->model()->data(ui->tabAnimal->model()->index(row, column)).toString().simplified();
                                                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                            }
                                        }
                                        out << "</tr>\n";
                                    }
                                    out <<  "</table> </center>\n"
                                        "</body>\n"
                                        "</html>\n";

                              QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                               QPrinter printer (QPrinter::PrinterResolution);
                                printer.setOutputFormat(QPrinter::PdfFormat);
                               printer.setPaperSize(QPrinter::A4);
                              printer.setOutputFileName(fileName);

                               QTextDocument doc;
                                doc.setHtml(strStream);
                                doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                doc.print(&printer);

}

void S_park::on_an_statTable_activated(const QModelIndex &index)
{
    /*QString val=ui->an_statTable->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("Select count(*) from animal where  sexe='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {
                        ui->an_total->setText(qry.value(0).toString());
                        ui->an_sexe_stat->setText(val);

                    }
        }*/
}

void S_park::on_an_tri_asc_clicked()
{
    ui->tabAnimal->setModel(an.afficherTri(1));
}

void S_park::on_an_tri_desc_clicked()
{
    ui->tabAnimal->setModel(an.afficherTri(0));
    //ui->an_tri_asc->set

}


/*----------------------------------------------------------------------------------------*/





/*---------------------------------GESTION TICKET---------------------------------------------------*/

void S_park::on_g_add_clicked()
{
    int id = ui->g_id_add->text().toInt();
    QString nom = ui->g_nom_add->text();
    QString description = ui->g_description_add->toPlainText();
     QString categorie =ui->g_cat_combo->currentText();
    guichet s(id,nom,description,categorie);
    bool test = s.ajouter();
    if(test)
    {
        ui->ticketList_3->setModel(t.afficher());
        ui->t_guichet_id_add_3->setModel(g.affichercatId());
        ui->t_guichet_id_e_3->setModel(g.affichercatId());

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
void S_park::on_guichetList_activated(const QModelIndex &index)
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
                        ui->t_guichet_id_e_3->setModel(g.affichercatId());
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

void S_park::on_edit_g_clicked()
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
        ui->t_guichet_id_add_3->setModel(g.affichercatId()); // combobox  (guichet)  ajout ticket refresh
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

void  S_park::on_delete_g_clicked()
{
    // suppression des guichet
    int id=ui->g_id_edit->text().toInt();

    bool test2=g.supprimer(id);
    if(test2){
        hideElements();
        //la constrainte foreign key (id_guichet dans ticket ) a un reglage on delete cascade si on sup un guichet leur ticket vont etres sup aussi
        ui->t_guichet_id_add_3->setModel(g.affichercatId());
        ui->guichetList->setModel(g.afficher());
        // refresh du table ticket list d'ils-ya des ticket supprimer after deleting the guichet
        ui->ticketList_3->setModel(t.afficher());
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

void S_park::on_t_add_clicked()
{
 // on va prendre les values saisies par l'utilisateur
    int id = ui->t_id_add_3->text().toInt();
    int guichet_id = ui->t_guichet_id_add_3->currentText().toInt();
    int prix = ui->t_prix_add_3->text().toInt();
    int quantite = ui->t_quantite_add_3->text().toInt();
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
        ui->ticketList_3->setModel(t.afficher());
        // back to ticket tableview
        //ui->user_management_stacked_2->setCurrentIndex(0);
         ui->t_id_add_3->clear();
         ui->t_prix_add_3->clear();
        ui->t_quantite_add_3->clear();


    }
    else{
        // ticket non ajouter
        QMessageBox::information(nullptr, QObject::tr("USER ADD "),
                                      QObject::tr("USERNAME OR EMAIL ARE ALREADY IN USE.\n"), QMessageBox::Ok);

}
}
// lorsque on double click sur un iD d'un ticket du tableau

void S_park::on_ticketList_activated(const QModelIndex &index)
{
    // val = id du ticket selectionée
    QString val=ui->ticketList_3->model()->data(index).toString();
        QSqlQuery qry;
        // recupérer les information de cet ticket du base de données
        qry.prepare("Select id,prix,quantite from ticket where  id='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {

                        ui->t_id_e_3->setText(qry.value(0).toString());
                        ui->t_prix_e_3->setText(qry.value(1).toString());
                        ui->t_quantite_e_3->setText(qry.value(2).toString());
                        ui->t_id_e_3->show();
                        ui->t_id_e_3->setEnabled(false);
                        ui->t_quantite_e_3->show();
                        ui->t_prix_e_3->show();
                        ui->edit_g->show();
                        ui->delete_g->show();
                        ui->t_edit_3->show();
                        ui->t_delete_3->show();
                        ui->t_guichet_id_e_3->show();
                        ui->t_guichet_id_e_3->setModel(g.affichercatId());
                    }
        }
}

void S_park::on_t_edit_clicked()
{
    // on va prendre les values saisies par l'utilisateur
    int id= ui->t_id_e_3->text().toInt();
    int quantity= ui->t_quantite_e_3->text().toInt();
    int prix= ui->t_prix_e_3->text().toInt();
    // valeur du comobox ( choix du id categorie pour une ticket)
    int catID =ui->t_guichet_id_e_3->currentText().toInt();
     bool test = false;
     // creation d'un object du class ticket avec les valeurs saisie par l'user
     ticket cp(id,catID,prix,quantity);
     // test de modification du ticket qui a id = int id= ui->t_id_e->text().toInt();
    test = cp.modifier(id);
    if(test){
        //MOdification success
        // remplissage du table ticket aprees la modification ( refresh table)
        ui->ticketList_3->setModel(t.afficher());
        //  //Methode pour mettres des buttons , lineedits invisible dans des cas ...
        hideElements();
        QMessageBox::information(nullptr, QObject::tr("TICKET MODIFY"),
                                      QObject::tr("TICKET MODIFIED SUCCESSFULY .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        //modification failed
        // refresh table ticketlist
        ui->ticketList_3->setModel(t.afficher());
          //Methode pour mettres des buttons , lineedits invisible dans des cas ...
        hideElements();
            //
        QMessageBox::critical(nullptr, QObject::tr("TICKET MODIFY"),
                                      QObject::tr("ERROR !\n"), QMessageBox::Cancel);

    }


}
void S_park::hideElements(){
    //Methode pour mettres des buttons , lineedits invisible dans des cas ...
    ui->g_id_edit->hide();
    ui->g_categorie_edit->hide();
    ui->g_nom_edit->hide();
    ui->g_description_edit->hide();
    ui->edit_g->hide();
    ui->delete_g->hide();
    ui->t_id_e_3->hide();
    ui->t_quantite_e_3->hide();
    ui->t_prix_e_3->hide();
    ui->edit_g->hide();
    ui->delete_g->hide();
    ui->t_edit_3->hide();
    ui->t_delete_3->hide();
    ui->t_guichet_id_e_3->hide();
    ui->t_id_achat->hide();
    ui->t_id_achat->setEnabled(false);
    ui->t_prix->hide();
    ui->t_quantite->hide();
    ui->t_quantite_achat->hide();
    ui->acheter_t->hide();
    ui->cancelBtn->hide();
    ui->a_id->hide();

}

void S_park::on_t_delete_clicked()
{
    int id = ui->t_id_e_3->text().toInt();
    bool test  = t.supprimer(id);
    if(test){
          //Methode pour mettres des buttons , lineedits invisible dans des cas ...
        hideElements();
        //refresh table ticketlist
        ui->ticketList_3->setModel(t.afficher());

        QMessageBox::information(nullptr, QObject::tr("TICKET Delete"),
                                      QObject::tr("TICKET deleted SUCCESSFULY .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);



    }
    else{
        //Methode pour mettres des buttons , lineedits invisible dans des cas ...
      hideElements();
      //refresh table ticketlist
        ui->ticketList_3->setModel(t.afficher());

        QMessageBox::critical(nullptr, QObject::tr("TICKET delete"),
                                      QObject::tr("ERROR .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);


    }
}

/*void S_park::on_stat_btn_clicked()
{
    dial = new statistiques();
    dial->start_stat();
    dial->exec();
}*/

void S_park::on_lineEdit_textChanged(const QString &arg1)
{
    ui->guichetList->setModel(g.recherche(arg1));
}

void S_park::on_t_recherche_textChanged(const QString &arg1)
{
    ui->ticketList_3->setModel(t.recherche(arg1));
}

void S_park::on_guichetPDF_clicked()
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

void S_park::on_comboBox_currentIndexChanged(int index)
{
    ui->guichetList->setModel(g.Tri(index));
}

void S_park::on_pushButton_clicked()
{
    QPrinter printer;
    QPrintDialog dialog(&printer,this);
    dialog.setWindowTitle("Print Document");
    dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if( dialog.exec() != QDialog::Accepted){
        return;
    }
}

// stat tickets

void S_park::start_stat()
{
QSqlQuery q1,q2,q3,q4;
qreal tot=0, c1=0,c2=0,c3=0;
q1.prepare("SELECT * FROM guichet");
q1.exec();
q2.prepare("SELECT * FROM guichet WHERE categorie='INDIVIDUEL'");
q2.exec();
q3.prepare("SELECT * FROM GUICHET WHERE categorie='COUPLE'");
q3.exec();
q4.prepare("SELECT * FROM GUICHET WHERE categorie='FAMILLE' ");
q4.exec();

while (q1.next()){tot++;}
while (q2.next()){c1++;}
while (q3.next()){c2++;}
while (q4.next()){c3++;}


c1=c1/tot;
c2=c2/tot;
c3=c3/tot;
// Assign names to the set of bars used
        QBarSet *set0 = new QBarSet("INDIVIDUELLE");
        QBarSet *set1 = new QBarSet("COUPLE");
        QBarSet *set2 = new QBarSet("FAMILLE");


        // Assign values for each bar
        *set0 << c1;
        *set1 << c2;
        *set2 << c3;
        // Add all sets of data to the chart as a whole
        // 1. Bar Chart
        QBarSeries *series = new QBarSeries();
        // 2. Stacked bar chart
        series->append(set0);
        series->append(set1);
        series->append(set2);
        // Used to define the bar chart to display, title
        // legend,
        QChart *chart = new QChart();
        // Add the chart
        chart->addSeries(series);
        // Adds categories to the axes
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        // 1. Bar chart
        chart->setAxisX(axis, series);

        // Used to change the palette
        QPalette pal = qApp->palette();
        // Change the color around the chart widget and text
        pal.setColor(QPalette::Window, QRgb(0xffffff));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
        // Apply palette changes to the application
        qApp->setPalette(pal);

// Used to display the chart
chartView = new QChartView(chart,ui->stats);
chartView->setRenderHint(QPainter::Antialiasing);
chartView->setMinimumSize(400,400);

chartView->show();
}


/*----------------------------------------------------------------------------------------*/




/*--------------------------------------GESTION PERSONNEL------------------------------*/


void S_park::on_pb_ajouter_clicked()
{
    int cin = ui->cin->text().toInt();
   // int cin_admin = ui->cin_admin->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QDate date_naissance = ui->date_naissance->date();
    int age = ui->age->text().toInt();
    QString ville = ui->ville->text();
    QString adresse = ui->adresse->text();
    int tel = ui->telephone->text().toInt();
    QDate d ;
    //d.currentDate().year(); date_naissance.year();

    Personnel P(nom,prenom,cin,date_naissance,ville,adresse,age,tel);
     bool test = P.ajouter();
    if(ui->nom->text().isEmpty()||ui->nom->text().isEmpty()||ui->cin->text().isEmpty()||age!=(d.currentDate().year()-date_naissance.year()))
    {
        QMessageBox::warning(nullptr, QObject::tr("Error"),
                    QObject::tr("Ajout non effectué.\n" "Entrer le nom,le prenom,la cin ou verifier la cohesion entre la date de naissance et l'age \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
   else if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
         ui->comboBox_supp->setModel(P.afficher());
         ui->comboBox_cin_modi->setModel(P.afficher());
         ui->tableView->setModel(P.afficher());

            ui->cin->clear();
            //ui->cin_admin->clear();
            ui->nom->clear();
            ui->prenom->clear();
            ui->date_naissance->clear();
            ui->age->clear();
            ui->ville->clear();
            ui->adresse->clear();
            ui->telephone->clear();


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
        QObject::tr("Ajout non effectué. \n"
                    "Click cancel to exit."),QMessageBox::Cancel);
}

void S_park::on_pushButton_2_clicked()
{
 P.setCin(ui->comboBox_supp->currentText().toInt());
  bool test = P.supprimer(P.getCin());

  if(test)
  {
      QMessageBox::information(nullptr, QObject::tr("ok"),
                  QObject::tr("Suppresion effectué.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
      ui->comboBox_supp->setModel(P.afficher());
      ui->comboBox_cin_modi->setModel(P.afficher());
      ui->tableView->setModel(P.afficher());
  }
  else
      QMessageBox::critical(nullptr,QObject::tr("Not ok"),
      QObject::tr("Suppresion non effectué. \n"
                  "Click cancel to exit."),QMessageBox::Cancel);

}



void S_park::on_pb_modifier_clicked()
{
     P.setCin(ui->comboBox_cin_modi->currentText().toInt());
     QDate d;

    /* QString nom = ui->nom->text();
     QString prenom = ui->prenom->text();
     QDate date_naissance = ui->date_naissance->date();
     int age = ui->age->text().toInt();
     QString ville = ui->ville->text();
     QString adresse = ui->adresse->text();
     int tel = ui->telephone->text().toInt();*/

    //Personnel P(P.getNom(),P.getPrenom(),P.getCin(),P.getDate(),P.getAge(),P.getVille(),P.getAdresse(),P.getTel());

    //bool test = P.modifier(P.getNom(),P.getPrenom(),P.getCin(),P.getDate(),P.getAge(),P.getVille(),P.getAdresse(),P.getTel());

     bool test = P.modifier(P.getCin());
     if(P.getAge()!=(d.currentDate().year()-P.getDate().year()))
     {
         QMessageBox::warning(nullptr, QObject::tr("Error"),
                     QObject::tr("Ajout non effectué.\n" "verifier la cohesion entre la date de naissance et l'age \n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
     }
     else if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("Modification effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->comboBox_cin_modi->setModel(P.afficher());
        ui->comboBox_supp->setModel(P.afficher());
        ui->tableView->setModel(P.afficher());
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
        QObject::tr("Modification non effectué. \n"
                    "Click cancel to exit."),QMessageBox::Cancel);

}

void S_park::on_comboBox_cin_modi_activated(int index)
{
    QSqlQuery dry;
    QString val=ui->comboBox_cin_modi->currentText();
    QString res = QString::number(index);

    //QString val=ui->comboBox_cin_modi->
    dry.prepare("SELECT nom,prenom,date_naissance,age,ville,adresse,telephone FROM gs_personnels  WHERE cin ='"+val+"''" );
    //dry.bindValue(":cin",val);
    if(dry.exec())
    {
        while(dry.next())
                {
            ui->nom_2->setText(dry.value(0).toString());
            ui->prenom_2->setText(dry.value(1).toString());
            ui->date_naissance_2->setDate(dry.value(2).toDate());
            ui->age_2->setValue(dry.value(3).toInt());
            ui->ville_2->setText(dry.value(4).toString());
            ui->adresse_2->setText(dry.value(5).toString());
            ui->telephone_2->setText(dry.value(6).toString());
                }
    }
}
/*void Personnels::on_comboBox_cin_modi_currentIndexChanged(int index)
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
                        ui->t_guichet_id_e_3->setModel(g.affichercatId());
                        ui->g_id_edit->setEnabled(false);
                        ui->g_nom_edit->show();
                        ui->g_description_edit->show();
                        ui->edit_g->show();
                        ui->delete_g->show();
                        ui->g_categorie_edit->show();
                    }
        }

    QSqlQuery dry;
    QString res = QString::number(index);
    //QString val=ui->comboBox_cin_modi->
    dry.prepare("SELECT nom,prenom,date_naissance,age,ville,adresse,telephone FROM gs_personnels  WHERE cin=:index" );
    dry.bindValue(":cin",res);
    if(dry.exec())
    {
        while(dry.next())
                {
            ui->nom_2->setText(dry.value(0).toString());
            ui->prenom_2->setText(dry.value(1).toString());
            ui->date_naissance_2->setDate(dry.value(2).toDate());
            ui->age_2->setValue(dry.value(3).toInt());
            ui->ville_2->setText(dry.value(4).toString());
            ui->adresse_2->setText(dry.value(5).toString());
            ui->telephone_2->setText(dry.value(6).toString());
                }
    }
}*/

void S_park::on_tri_ageh_clicked()
{
    ui->tableView->setModel(P.Trie_age_A());
}

void S_park::on_tri_ageb_clicked()
{
    ui->tableView->setModel(P.Trie_age_D());
}

void S_park::on_tri_nomh_clicked()
{
     ui->tableView->setModel(P.Trie_Nom_A());
}

void S_park::on_tri_nomb_clicked()
{
     ui->tableView->setModel(P.Trie_Nom_D());
}

void S_park::on_tri_cinh_clicked()
{
 ui->tableView->setModel(P.Trie_cin_A());
}

void S_park::on_tri_cinb_clicked()
{
 ui->tableView->setModel(P.Trie_cin_D());
}


/*void Personnels::on_nom_recherche_textEdited(const QString &arg1)
{

}*/

void S_park::on_nom_recherche_textChanged(const QString &arg1)
{
    QString ch = arg1;

   /* if(ch == "")
    {
        ui->tableView_2->setModel(P.afficher());
    }
    else
    {*/
        ui->tableView_2->setModel(P.rechercher(ch));
    //}

}

/*void Personnels::on_Gestion_currentChanged(int index)
{

}*/

//statistique
void S_park::on_Statistique_clicked()
{
    ui->Gestion->setCurrentIndex(3);

        P.stat(ui->widget);
}

// mailing

/*void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );*/

void S_park::on_browse_clicked()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );
}

void S_park::on_Envoyer_Mail_clicked()
{
    Smtp* smtp = new Smtp(ui->e_mail->text(),ui->password->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(Mail_Envoyer(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->e_mail->text() , ui->recipient->text() , ui->subject->text(),ui->message->toPlainText(), files );
    else
        smtp->sendMail(ui->e_mail->text() , ui->recipient->text() , ui->subject->text(),ui->message->toPlainText());
}

void S_park::Mail_Envoyer(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->e_mail->clear();
    ui->recipient->clear();
    ui->password->clear();
    ui->message->clear();
    ui->subject->clear();
    ui->file->clear();
}




