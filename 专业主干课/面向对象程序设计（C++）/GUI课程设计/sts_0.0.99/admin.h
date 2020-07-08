#ifndef SYSTEM_H
#define SYSTEM_H

#include <QDialog>
#include"student_manage.h"
#include"staff_manage.h"
#include"course_manage.h"
#include"admin_display.h"

namespace Ui {
class admin;
}

class admin : public QDialog
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();

private slots:
    bool closeDialog();

    void on_button_student_manage_clicked();

    void on_button_staff_manage_clicked();

    void on_button_course_manage_clicked();

    void on_button_return_clicked();

    void on_button_find_clicked();

private:
    Ui::admin *ui;

    student_manage openStudentManage;
    staff_manage openStaffManage;
    course_manage openModuleManage;
    admin_display openAdminDisplay;
};

#endif // SYSTEM_H
