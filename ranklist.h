#ifndef RANKLIST_H
#define RANKLIST_H

#include <QMainWindow>
#include <client.hpp>
#include <QCloseEvent>
#include "header.hpp"
namespace Ui {
class Ranklist;
}

class Ranklist : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ranklist(QMainWindow *parent=0);
    ~Ranklist();


private:
    Ui::Ranklist *ui;
    QString rank[13];
    QIcon ic[1];
    QMainWindow* parent;

protected:
     void closeEvent(QCloseEvent *event);
private slots:
     void on_pushButton_clicked();
     void on_pushButton_pressed();
};

#endif // RANKLIST_H
