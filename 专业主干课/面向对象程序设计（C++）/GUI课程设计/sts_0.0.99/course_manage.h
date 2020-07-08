#ifndef COURSE_MANAGE_H
#define COURSE_MANAGE_H

#include<QDialog>

namespace Ui {
class course_manage;
}

class course_manage : public QDialog
{
    Q_OBJECT

public:
    explicit course_manage(QWidget *parent = nullptr);
    ~course_manage();

    void clearInterface();
    void writeInformation(QString information);
    void showEvent(QShowEvent *);

private slots:
    void on_button_ok_clicked();

    void on_button_delete_clicked();

    void on_button_revision_clicked();

    void on_line_id_textChanged(const QString &arg1);

    void on_line_tid_textChanged(const QString &arg1);

private:
    Ui::course_manage *ui;
    int modifyNum=-1;
    bool isback=false;
};

#endif // COURSE_MANAGE_H
