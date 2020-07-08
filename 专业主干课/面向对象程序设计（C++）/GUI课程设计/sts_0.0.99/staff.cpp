#include "staff.h"
#include "ui_staff.h"
#include"mainwindow.h"
#include"score_input.h"
#include"score_search.h"

extern MainWindow *main_window;

staff::staff(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::staff)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
    connect(ui->button_return,SIGNAL(clicked()),this,SLOT(closeDialog()));
}

staff::~staff()
{
    delete ui;
}

bool staff::closeDialog()
{
   QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
   animation->setDuration(1000);
   animation->setStartValue(0.91);
   animation->setEndValue(0);
   animation->start();
   connect(animation, SIGNAL(finished()), this, SLOT(close()));
   return true;
}

void staff::on_button_score_input_clicked()
{
    openScoreInput.show();
}

void staff::on_button_score_search_clicked()
{
    openScoreSearch.show();
}

void staff::on_button_check_clicked()
{
    openStaffCheck.show();
}

void staff::on_button_return_clicked()
{
    MainWindow *main_window = new MainWindow ();
    main_window->show(); 
}



