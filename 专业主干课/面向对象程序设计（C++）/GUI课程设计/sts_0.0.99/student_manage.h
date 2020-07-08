#ifndef STUDENT_MANAGE_H
#define STUDENT_MANAGE_H

#include <QDialog>

namespace Ui {
class student_manage;
}

class student_manage : public QDialog
{
    Q_OBJECT

public:
    explicit student_manage(QWidget *parent = nullptr);
    ~student_manage();

    void clearInterface();
    void writeInformation(QString information);


private slots:
    void on_button_ok_clicked();

    void on_button_delete_clicked();

    void on_line_id_textChanged(const QString &arg1);

    void on_button_revision_clicked();

    void on_line_id_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::student_manage *ui;
    int modifyNum=-1;
    bool isback=false;

};

#endif // STUDENT_MANAGE_H
