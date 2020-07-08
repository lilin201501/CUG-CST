#include "student_inquiry.h"
#include "ui_student_inquiry.h"

#include "about.h"

extern QString account;

student_inquiry::student_inquiry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::student_inquiry)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.92);
    setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
    this->model = new QStandardItemModel;
    initialization();
    this->ui->tableView->setModel(model);
}

student_inquiry::~student_inquiry()
{
    delete ui;
}

void student_inquiry::showEvent(QShowEvent *)
{
    if (readfile(scoreFile)==-1){
        QMessageBox::critical(this,"错误","成绩文件读取失败！","确认");
        return;
    }
    this->model->clear();
    initialization();
    double dCredit=0, dGPA=0;
    int i=0,row=0,scoreLen=scoreLine.length();
    for (i=0;i<scoreLen;i++) {
        QString line=scoreLine.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        if(account==linesplit.at(1)){
            display(row++, linesplit);
            dCredit += linesplit.at(4).toDouble();
            dGPA += (linesplit.at(4).toDouble())*(linesplit.at(6).toDouble());
        }
    }
    if(dCredit>0){
        dGPA=dGPA/dCredit;
    }
    QString credit= QString::number(dCredit,10,2);
    QString GPA= QString::number(dGPA,10,2);
    this->ui->label_credit->setText(credit);
    this->ui->label_average_credit->setText(GPA);

}

void student_inquiry::initialization(){
    this->model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("学号"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("班级"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("科目"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("学分"));
    this->model->setHorizontalHeaderItem(5,new QStandardItem("成绩"));
    this->model->setHorizontalHeaderItem(6,new QStandardItem("绩点"));
    this->ui->tableView->setColumnWidth(0,180);
    this->ui->tableView->setColumnWidth(1,210);
    this->ui->tableView->setColumnWidth(2,150);
    this->ui->tableView->setColumnWidth(3,240);
    this->ui->tableView->setColumnWidth(4,93);
    this->ui->tableView->setColumnWidth(5,93);
    this->ui->tableView->setColumnWidth(6,94);
}

void student_inquiry::display(int row, QStringList scoreLine){
    int i=0,scoreLen=scoreLine.length();
    for (i=0;i<scoreLen;i++) {
        this->model->setItem(row,i,new QStandardItem(scoreLine.at(i)));
        this->model->item(row,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
}
