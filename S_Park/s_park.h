#ifndef S_PARK_H
#define S_PARK_H

#include <QDialog>
#include <QtCharts>
#include <QChartView>
#include <QtCharts/QChartView>
#include <QPieSeries>
#include <QMessageBox>
#include <QDate>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSlice>
#include "QPrintDialog"
#include "smtp.h"
#include "achat.h"
#include "ticket.h"
#include "guichet.h"
#include "animal.h"
#include "animal.h"
#include "personnel.h"


namespace Ui {
class S_park;
}

class S_park : public QDialog
{
    Q_OBJECT

public:
    explicit S_park(QWidget *parent = nullptr);
    ~S_park();

private slots:


    void on_employer_clicked();

    void on_aniamaux_clicked();

    void on_clients_clicked();

    void on_tickets_clicked();

    void on_approvisionement_clicked();

/*stackwidget ANimaux--------------------------------------------------------*/

    void on_an_addBtn_clicked();

    void refresh();

    void on_tabAnimal_activated(const QModelIndex &index);

    void on_an_delete_clicked();

    void on_an_edit_clicked();

    void on_an_recherche_textChanged(const QString &arg1);

    void on_an_imprimer_clicked();

    void on_an_statTable_activated(const QModelIndex &index);

    void on_an_tri_asc_clicked();

    void on_an_tri_desc_clicked();

  //  void on_start_client_clicked();

 /*stackwidget Guichet && Achat--------------------------------------------------------*/
    void on_g_add_clicked();

    void hideElements();

    void on_guichetList_activated(const QModelIndex &index);

    void on_edit_g_clicked();

    void on_delete_g_clicked();

    void on_t_add_clicked();

    void on_ticketList_activated(const QModelIndex &index);

    void on_t_edit_clicked();

    void on_t_delete_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_t_recherche_textChanged(const QString &arg1);

    void on_guichetPDF_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

  //  void on_ticketListFront_activated(const QModelIndex &index);

    void start_stat();



    void on_acahts_tickets_clicked();

    void on_achats_clicked();

    void on_Guichet_2_clicked();

   /*stackwidget Personnel--------------------------------------------------------*/

    void on_pb_ajouter_clicked();

    void on_pushButton_2_clicked();

    void on_pb_modifier_clicked();

    void on_tri_ageh_clicked();

    void on_tri_ageb_clicked();

    void on_tri_nomh_clicked();

    void on_tri_nomb_clicked();

    void on_tri_cinh_clicked();

    void on_tri_cinb_clicked();
   // void on_nom_recherche_textEdited(const QString &arg1);

    void on_nom_recherche_textChanged(const QString &arg1);

   // void on_Gestion_currentChanged(int index);

    void on_Statistique_clicked();

    void on_Envoyer_Mail_clicked();

    void Mail_Envoyer(QString);

    void on_browse_clicked();

    // void on_comboBox_cin_modi_currentIndexChanged(int index);

     void on_comboBox_cin_modi_activated(int index);


private:
    Ui::S_park *ui;
     animal an;
     guichet g;
     ticket t;
     achat a;
     QChartView *chartView ;
     Personnel P;
     QStringList files;

};

#endif // S_PARK_H
