#include "student.h"
#include "ui_student.h"
#include"mainwindow.h"
#include"course_select.h"
#include"student_inquiry.h"

extern MainWindow *main_window;

student::student(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::student)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
    connect(ui->button_return,SIGNAL(clicked()),this,SLOT(closeDialog()));
}

student::~student()
{
    delete ui;
}

bool student::closeDialog()
{
   QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
   animation->setDuration(1000);
   animation->setStartValue(0.91);
   animation->setEndValue(0);
   animation->start();
   connect(animation, SIGNAL(finished()), this, SLOT(close()));
   return true;
}

void student::on_button_course_select_clicked()
{
    openCourseSelect.show();
}

void student::on_button_score_inquiry_clicked()
{
    openScoreInquiry.show();
}

void student::on_button_judge_clicked()
{
    openStudentJudge.show();
}

void student::on_button_return_clicked()
{
    MainWindow *main_window = new MainWindow ();
    main_window->show();
}
