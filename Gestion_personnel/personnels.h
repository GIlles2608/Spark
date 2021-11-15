#ifndef PERSONNELS_H
#define PERSONNELS_H

#include <QDialog>
#include "personnel.h"
#include <QSystemtrayicon>
namespace Ui {
class Personnels;
}

class Personnels : public QDialog
{
    Q_OBJECT

public:
    explicit Personnels(QWidget *parent = nullptr);
    ~Personnels();


private slots:
    void on_pb_ajouter_clicked();

    void on_pushButton_2_clicked();

    void on_pb_modifier_clicked();

    void on_tri_ageh_clicked();

    void on_tri_ageb_clicked();

    void on_tri_nomh_clicked();

    void on_tri_nomb_clicked();

   // void on_nom_recherche_textEdited(const QString &arg1);

    void on_nom_recherche_textChanged(const QString &arg1);

private:
    Ui::Personnels *ui;
     Personnel P;

};

#endif // PERSONNELS_H
