#ifndef STAFF_MANAGE_H
#define STAFF_MANAGE_H

#include <QDialog>

namespace Ui {
class staff_manage;
}

class staff_manage : public QDialog
{
    Q_OBJECT

public:
    explicit staff_manage(QWidget *parent = nullptr);
    ~staff_manage();

    void clearInterface();
    void writeInformation(QString information);

private slots:
    void on_button_add_clicked();

    void on_button_delete_clicked();

    void on_button_revision_clicked();

    void on_line_id_textChanged(const QString &arg1);

private:
    Ui::staff_manage *ui;
    int modifyNum=-1;
    bool isback=false;
};

#endif // STAFF_MANAGE_H
