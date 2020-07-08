#ifndef STUDENT_INQUIRY_H
#define STUDENT_INQUIRY_H

#include <QDialog>
#include<QStandardItem>
#include<QStandardItemModel>

namespace Ui {
class student_inquiry;
}

class student_inquiry : public QDialog
{
    Q_OBJECT

public:
    explicit student_inquiry(QWidget *parent = nullptr);
    ~student_inquiry();

    void showEvent(QShowEvent *);
    void initialization();
    void display(int row, QStringList student_score_line);

private:
    Ui::student_inquiry *ui;

    QStandardItemModel *model;

};

#endif // STUDENT_INQUIRY_H
