#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDate>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include "animal.h"
#include <QPainter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh(){

       //stackedWidget Animal Ajout  done
       ui->animeaux_management->setCurrentIndex(0);
       // affichage table Animeaux
       ui->tabAnimal->setModel(an.afficher());

       // affichage statistiques dans tab stat
       ui->an_statTable->setModel(an.afficherStat());

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



void MainWindow::on_an_add_selected_clicked()
{
    ui->animeaux_management->setCurrentIndex(1);
}

void MainWindow::on_add_cancel_animal_clicked()
{
    ui->animeaux_management->setCurrentIndex(0);
}

void MainWindow::on_an_addBtn_clicked()
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
        QMessageBox::information(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("Animal ajouté.\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("ID est deja utiliser!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    }
}

void MainWindow::on_tabAnimal_activated(const QModelIndex &index)
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

void MainWindow::on_an_delete_clicked()
{
    QString ref = ui->an_id_e->text();
    bool test = an.supprimer(ref);
    if (test){
        refresh();
        QMessageBox::information(nullptr, QObject::tr("Animal Suppression"),
                                      QObject::tr("Animal supprimer!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        refresh();
        QMessageBox::critical(nullptr, QObject::tr("Animal Suppression"),
                                      QObject::tr("Erreur ID!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
}

void MainWindow::on_an_edit_clicked()
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
        QMessageBox::information(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("Animal ajouté.\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Animal ajout"),
                                      QObject::tr("ID est deja utiliser!! .\n"
                                                  "Click Ok to exit."), QMessageBox::Ok);

    }
    }
}

void MainWindow::on_an_recherche_textChanged(const QString &arg1)
{
    if(arg1.size()<=0){
        refresh();
    }
    else{
        ui->tabAnimal->setModel(an.recherche(arg1));
     }
}

void MainWindow::on_an_imprimer_clicked()
{
    QString sexe =ui->an_sexe_stat->text();
    QDate test = QDate::currentDate();
    QString dattte = test.toString("yyyy_MM_dd");
    QPdfWriter pdf("C:/Users/MSI/Desktop/PDF/Animal"+dattte+".pdf");

                      QPainter painter(&pdf);
                     int i = 4000;
                          painter.setPen(Qt::blue);
                          painter.setFont(QFont("Arial", 30));
                          painter.drawText(2000,1200,"Statistique Des Animeaux "+sexe);
                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Arial", 50));
                         // painter.drawText(1100,2000,afficheDC);
                          painter.drawRect(1500,200,7300,2600);
                          //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                          painter.drawRect(0,3000,9600,500);
                          painter.setFont(QFont("Arial", 9));
                          painter.drawText(300,3300,"SEXE");
                          painter.drawText(2300,3300,"TOTAL");
                          painter.drawText(4300,3300,"ANIMEAU");
                          painter.drawText(6300,3300,"DATE AJOUT");



                          QSqlQuery query;
                          QString noms = "";
                          QString dates = "";
                          query.prepare("select nom,date_ajout from animal where sexe=:sexe");
                          query.bindValue(":sexe",ui->an_sexe_stat->text());
                          query.exec();
                          while (query.next())
                          {
                            noms = noms +" "+ query.value(0).toString();
                            dates = dates +" "+  query.value(1).toString();
                          }
                          painter.drawText(300,i,sexe);
                          painter.drawText(2300,i,ui->an_total->text());
                          painter.drawText(4300,i,noms);
                          painter.drawText(6300,i,dates);
                         i = i +500;
                          int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                              if (reponse == QMessageBox::Yes)
                              {
                                  QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/MSI/Desktop/PDF/Animal"+dattte+".pdf"));

                                  painter.end();
                              }
                              if (reponse == QMessageBox::No)
                              {
                                   painter.end();
                              }

}

void MainWindow::on_an_statTable_activated(const QModelIndex &index)
{
    QString val=ui->an_statTable->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("Select count(*) from animal where  sexe='"+val+"'");
        if(qry.exec())
        {
            while(qry.next())
                    {
                        ui->an_total->setText(qry.value(0).toString());
                        ui->an_sexe_stat->setText(val);

                    }
        }
}

void MainWindow::on_an_tri_asc_clicked()
{
    ui->tabAnimal->setModel(an.afficherTri(1));
}

void MainWindow::on_an_tri_desc_clicked()
{
    ui->tabAnimal->setModel(an.afficherTri(0));
    //ui->an_tri_asc->set

}
