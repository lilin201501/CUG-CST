#ifndef STAFF_CHECK_H
#define STAFF_CHECK_H

#include <QDialog>
#include<QStandardItem>
#include<QStandardItemModel>

namespace Ui {
class staff_check;
}

class staff_check : public QDialog
{
    Q_OBJECT

public:
    explicit staff_check(QWidget *parent = nullptr);
    ~staff_check();
    void showEvent(QShowEvent *);
    int readJudge();

private slots:

private:
    Ui::staff_check *ui;
    QStandardItemModel *model;
    bool isNotShow=true;
    bool START,DONE;
    QString judgeText;
};

#endif // STAFF_CHECK_H
