#ifndef DIALOGUSER_H
#define DIALOGUSER_H
#include "achat.h"
#include "ticket.h"
#include "guichet.h"
#include <QDialog>


#include <QMessageBox>
#include "connexionsql.h"
#include <QStatusBar>
#include <QDialog>

namespace Ui {
class Dialoguser;
}

class Dialoguser : public QDialog
{
    Q_OBJECT

public:
    explicit Dialoguser(QWidget *parent = nullptr);
    ~Dialoguser();

private slots:
    void hideElements();
    void on_ticketListFront_activated(const QModelIndex &index);

private:
    Ui::Dialoguser *ui;
    ticket t;
    guichet g;
    achat a;
};

#endif // DIALOGUSER_H
