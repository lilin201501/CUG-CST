#include "system.h"
#include "ui_system.h"
#include"mainwindow.h"
#include"student_manage.h"
#include"staff_manage.h"
#include"course_manage.h"
#include"system_display.h"

extern MainWindow *main_window;

system::system(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::system)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
    connect(ui->button_return,SIGNAL(clicked()),this,SLOT(closeDialog()));
}

system::~system()
{
    delete ui;
}


bool system::closeDialog()
{
   QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
   animation->setDuration(1000);
   animation->setStartValue(0.91);
   animation->setEndValue(0);
   animation->start();
   connect(animation, SIGNAL(finished()), this, SLOT(close()));
   return true;
}

void system::on_button_student_manage_clicked()
{
    openStudentManage.show();
}

void system::on_button_staff_manage_clicked()
{
    openStaffManage.show();
}

void system::on_button_course_manage_clicked()
{
    openModuleManage.show();
}

void system::on_button_find_clicked()
{
    openSystemDisplay.show();
}

void system::on_button_return_clicked()
{
    MainWindow *main_window = new MainWindow ();
    main_window->show();
}
