#ifndef DIALOGADMIN_H
#define DIALOGADMIN_H

#include <QDialog>
#include "guichet.h"
#include "ticket.h"
#include "statistiques.h"
#include "achat.h"
#include <QMessageBox>
#include "connexionsql.h"


namespace Ui {
class Dialogadmin;
}

class Dialogadmin : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogadmin(QWidget *parent = nullptr);
    ~Dialogadmin();

private slots:
    void on_g_add_clicked();
    void hideElements();
    void on_guichetList_activated(const QModelIndex &index);

    void on_edit_g_clicked();

    void on_delete_g_clicked();

    void on_routeTicket_clicked();

    void on_routeGuichet_2_clicked();

    void on_backGuichet_clicked();

    void on_nextrouteUser_clicked();

    void on_backrouteAchat_clicked();

    void on_t_add_selected_clicked();

    void on_t_add_clicked();

    void on_ticketList_activated(const QModelIndex &index);

    void on_t_edit_clicked();

    void on_t_delete_clicked();

    void on_stat_btn_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_t_recherche_textChanged(const QString &arg1);

    void on_guichetPDF_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::Dialogadmin *ui;
    guichet g;
    ticket t;
    achat a;
    statistiques *dial;
};

#endif // DIALOGADMIN_H
