#include "admin.h"
#include "ui_admin.h"

#include"mainwindow.h"
#include"student_manage.h"
#include"staff_manage.h"
#include"course_manage.h"
#include"admin_display.h"

extern MainWindow *main_window;

admin::admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
    connect(ui->button_return,SIGNAL(clicked()),this,SLOT(closeDialog()));
}

admin::~admin()
{
    delete ui;
}


bool admin::closeDialog()
{
   QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
   animation->setDuration(1000);
   animation->setStartValue(0.91);
   animation->setEndValue(0);
   animation->start();
   connect(animation, SIGNAL(finished()), this, SLOT(close()));
   return true;
}

void admin::on_button_student_manage_clicked()
{
    openStudentManage.show();
}

void admin::on_button_staff_manage_clicked()
{
    openStaffManage.show();
}

void admin::on_button_course_manage_clicked()
{
    openModuleManage.show();
}

void admin::on_button_find_clicked()
{
    openAdminDisplay.show();
}

void admin::on_button_return_clicked()
{
    MainWindow *main_window = new MainWindow ();
    main_window->show();
}
