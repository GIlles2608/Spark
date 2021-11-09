#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "produit.h"
#include <QIntValidator>
#include <QApplication>
#include <QMessageBox>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_ID_A ->setValidator(new QIntValidator(0, 9999999, this));
    ui->tab_GS_ANIMAUX->setModel( P1.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Button_Ajouter_clicked()
{
    QString ID_A=ui->le_ID_A->text();
    QString NOM=ui->le_NOM->text();
    int PRENOM=ui->le_PRENOM->text().toInt();
    QString SEXE =ui->le_SEXE->text();
   int CLASSE=ui->le_CLASSE->text().toInt();
    GS_ANIMAUX P(ID_A,NOM,PRENOM,SEXE,CLASSE);
    bool test=P.ajouter();


    if(test)
    {
        ui->tab_GS_ANIMAUX->setModel(P1.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                   QObject::tr("ajout effectue\n"
                               "click cancel te exit."), QMessageBox::Cancel);
    }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                   QObject::tr("ajout non effectue\n"
                               "click cancel te exit."), QMessageBox::Cancel);

}

void MainWindow::on_ButtonSupprimer_clicked()
{
    GS_ANIMAUX P2; P2.setref(ui->le_ID_A_sup->text());
    bool test=P2.supprimer(P2.getref());
    QMessageBox msgBox;

    if(test)
    {
        ui->tab_GS_ANIMAUX->setModel(P1.afficher());
        msgBox.setText("suppression avec succes");
    }
    else
    msgBox.setText("echec de suppression");
    msgBox.exec();

}

void MainWindow::on_Button_Modification_clicked()
{
    QString ID_A=ui->le_ID_A_2->text();
    QString NOM=ui->le_NOM_2->text();
    int PRENOM=ui->le_PRENOM_2->text().toInt();
    QString SEXE=ui->le_SEXE_2->text();
    int CLASSE=ui->le_CLASSE_2->text().toInt();

    GS_ANIMAUX c(ID_A,NOM,PRENOM,SEXE,CLASSE);
    bool test=c.modifier(ID_A);
    if(test)
    {

        ui->tab_GS_ANIMAUX->setModel(c.afficher());//refresh

               QMessageBox::information(nullptr, QObject::tr("effectué"),
                    QObject::tr(" Modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
               ui->le_ID_A_2->clear();
               ui->le_NOM_2->clear();
               ui->le_PRENOM_2->clear();
               ui->le_SEXE_2->clear();
                ui->le_CLASSE_2->clear();
   }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("non effectué"),
                    QObject::tr("non modifié !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->le_ID_A_2->clear();
        ui->le_NOM_2->clear();
        ui->le_PRENOM_2->clear();
        ui->le_SEXE_2->clear();
         ui->le_CLASSE_2->clear();



    }

}
