#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDate>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include "animal.h"
#include <QPainter>
#include <QtPrintSupport/QPrinter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refresh();
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
       int ret=a.connect_arduino();
             switch (ret) {
             case(0):qDebug()<<"arduino is available and connected to :"<<a.getarduino_port_name();
                 break;
             case(1):qDebug()<<"arduino is available but not connected to :"<<a.getarduino_port_name();
                 break;
             case(-1):qDebug()<<"arduino is not available";
             }
       QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::update_label()
{
data=a.read_from_arduino();

if (data == "1")
  {
    a.write_to_arduino("a");
    QSound::play("C:/Users/MSI/Desktop/cooper_fulleon_sounder_tone_25.wav");
    QMessageBox::information (nullptr, QObject::tr("alert"),
                QObject::tr("\n un animal s'est sauvé !\n"), QMessageBox::Ok);
     a.write_to_arduino("b");
}

}
void MainWindow::refresh(){

       //stackedWidget Animal Ajout  done
       ui->animeaux_management->setCurrentIndex(0);
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

void MainWindow::on_an_statTable_activated(const QModelIndex &index)
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

void MainWindow::on_an_tri_asc_clicked()
{
    ui->tabAnimal->setModel(an.afficherTri(1));
}

void MainWindow::on_an_tri_desc_clicked()
{
    ui->tabAnimal->setModel(an.afficherTri(0));
    //ui->an_tri_asc->set

}
