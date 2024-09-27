#include "dialoguser.h"
#include "ui_dialoguser.h"

Dialoguser::Dialoguser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialoguser)
{
    ui->setupUi(this);
    ui->ticketListFront->setModel(t.afficherParId(0));

}

Dialoguser::~Dialoguser()
{
    delete ui;
}

void Dialoguser::on_ticketListFront_activated(const QModelIndex &index)
{

}
void Dialoguser::hideElements(){
    ui->t_id_achat->hide();
    ui->t_id_achat->setEnabled(false);
    ui->t_prix->hide();
    ui->t_quantite->hide();
    ui->t_quantite_achat->hide();
    ui->acheter_t->hide();
    ui->cancelBtn->hide();
    ui->a_id->hide();
}
