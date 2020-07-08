#ifndef COURSE_SELECT_H
#define COURSE_SELECT_H

#include <QDialog>
#include<QStandardItem>
#include<QStandardItemModel>

namespace Ui {
class course_select;
}

class course_select : public QDialog
{
    Q_OBJECT

public:
    explicit course_select(QWidget *parent = nullptr);
    ~course_select();

    void showEvent(QShowEvent *);
    void display(int row,QStringList moduleLine);
    void initialization();
    void calculation();

protected :
    void closeEvent(QCloseEvent *event);

private slots:

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableView_entered(const QModelIndex &index);


private:
    Ui::course_select *ui;
    QStandardItemModel *model;
    double dCredit;
};

#endif // COURSE_SELECT_H
