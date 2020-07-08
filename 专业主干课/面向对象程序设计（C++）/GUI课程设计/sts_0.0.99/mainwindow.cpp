#include "mainwindow.h"
#include "ui_mainwindow.h"

#include"student.h"
#include"staff.h"
#include"system.h"
#include"about.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(0.91);
    animation->start();
//晶，到最后都没有找到只隐藏最大化窗口的办法，采用隐藏框架自己单独写一个最小化和关闭按钮
    //setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    //setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
    //this->setAttribute(Qt::WA_TranslucentBackground);      //设置窗口背景透明
    this->setWindowFlags(Qt::FramelessWindowHint);         //设置无边框窗口
    isMove=false;

    if(readfile(studentFile)==-1){
        QMessageBox::critical(this,"错误","学生信息读取失败，\n学生账户无法登录，\n可登录管理员账户修改！","确认");
    }
    if (readfile(staffFile)==-1) {
        QMessageBox::critical(this,"错误","教师信息读取失败，\n教师账户无法登录，\n可登录管理员账户修改！","确认");
    } 
    this->ui->line_account->setAttribute(Qt::WA_InputMethodEnabled,false);                 //密码屏蔽输入法
}

MainWindow::~MainWindow()
{
    delete ui;
}

//响应Enter键
void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Return:{       //数字键盘Enter键
        on_button_login_clicked();
        break;
    }
    case Qt::Key_Enter: {       //Enter键
        on_button_login_clicked();
        break;
    }
    default:
        break;
    }
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isMove = true;
        startPoint = event->globalPos();
        windowPoint = this->frameGeometry().topLeft();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - startPoint;      //移动中的鼠标位置相对于初始位置的相对位置
        this->move(windowPoint + relativePos );                    //移动窗体
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isMove = false;                                     //改变移动状态
    }
}

void MainWindow::delay(int mSec)                            //延迟登录
{
    QEventLoop loop;
    QTimer::singleShot(mSec, &loop, SLOT(quit()));
    loop.exec();
}

void MainWindow::animation(int mSec,QString windowType)     //登录动画
{
    delay(mSec);
    if(windowType=="student"){
        QPropertyAnimation *animation = new QPropertyAnimation(&openStudent,"windowOpacity");
        animation->setDuration(300);
        animation->setStartValue(0);
        animation->setEndValue(0.91);
        animation->start();
        openStudent.show();
        this->hide();
        //opstudent_manage.exec();    另一种实现新窗口方式，不在private添加成员 模态窗口
    }
    else if (windowType=="staff") {
        QPropertyAnimation *animation = new QPropertyAnimation(&openStaff,"windowOpacity");
        animation->setDuration(300);
        animation->setStartValue(0);
        animation->setEndValue(0.91);
        animation->start();
        openStaff.show();
        this->hide();
    }
    else if (windowType=="system") {
        QPropertyAnimation *animation = new QPropertyAnimation(&openSystem,"windowOpacity");
        animation->setDuration(300);
        animation->setStartValue(0);
        animation->setEndValue(0.91);
        animation->start();
        openSystem.show();
        this->hide();
    }
}

void MainWindow::on_button_login_clicked()
{
    QString isLogin=this->ui->button_login->text();
    if(isLogin=="登录"){
                account=this->ui->line_account->text();
        QString password=this->ui->line_password->text();
        if(account.length()<1){
           QMessageBox::critical(this,"错误","请您输入账号后再登录","确认");
        }
        else if(password.length()<1){
           QMessageBox::critical(this,"错误","请您输入密码后再登录","确认");
        }
        else{   
//判断账号密码是否相符
           this->ui->button_login->setText("登录中...");
           int i=0,j=0,stuLen=studentLine.length(),staLen=staffLine.length();
           bool flag=false;
           if(account==adminAccount&&password==adminPassword){
               flag=true;
               animation(700,"system");
           }
           for (i=0;i<stuLen;i++) {
               QString line=studentLine.at(i);
               line=line.trimmed();
               QStringList linesplit=line.split(" ");
               if(account==linesplit.at(1)&&password==linesplit.at(6)){
                   flag=true;
                   animation(700,"student");
                   accountName=linesplit.at(0);
                   break;
               }
           }
           for (j=0;j<staLen;j++) {
               QString line=staffLine.at(j);
               line=line.trimmed();
               QStringList linesplit=line.split(" ");
               if(account==linesplit.at(1)&&password==linesplit.at(5)){
                   flag=true;
                   animation(700,"staff");
                   accountName=linesplit.at(0);
                   break;
               }
           }
//均登录不上弹窗提醒用户
           if(flag==false){
               delay(1500);
               QMessageBox::critical(this,"错误","你输入的账户名或密码不正确，原因可能是：\n1、账户名输入有误；\n2、忘记密码；\n3、未区分字母大小写；\n4、未开启小键盘。\n\n如果你的密码丢失或遗忘，可寻找管理员找回密码。\n","确认");
               this->ui->button_login->setText("登录");
           }
        }
    }
}

void MainWindow::on_button_about_clicked()
{
    about opabout;
    opabout.exec();
}

void MainWindow::on_button_close_clicked()
{
    this->close();
}

void MainWindow::on_button_mini_clicked()
{
    this->showMinimized();
}
