#include "staff_check.h"
#include "ui_staff_check.h"
#include "about.h"
staff_check::staff_check(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::staff_check)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.92);
    setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
    this->model = new QStandardItemModel;
    this->ui->tableView->setModel(model);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

staff_check::~staff_check()
{
    delete ui;
}

int staff_check::readJudge()
{
    START=false;
    DONE=false;
    judgeLine.clear();
    QFile file(judgeFile);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line=in.readLine();
        while (line=="~~acooz我是开始分隔符acooz~~") {
            START=true;
            line.clear();
            break;
        }
        while (line=="~~acooz我是结束分隔符acooz~~") {
            DONE=true;
            line.clear();
            break;
        }
        if(START){
            judgeText+=line;
        }
        if(DONE){
            judgeLine.append(judgeText);
            judgeText.clear();
            START=false;
            DONE=false;
        }
    }
    file.close();
    return 0;
}

void staff_check::showEvent(QShowEvent *)
{
    if(isNotShow){
        if (readJudge()==-1){
            QMessageBox::critical(this,"错误","评价文件读取失败！","确认");
            return;
        }
        this->model->setHorizontalHeaderItem(0,new QStandardItem("学号"));
        this->model->setHorizontalHeaderItem(1,new QStandardItem("姓名"));
        this->model->setHorizontalHeaderItem(2,new QStandardItem("评价分数"));
        this->model->setHorizontalHeaderItem(3,new QStandardItem("评语"));
        this->ui->tableView->setColumnWidth(0,150);
        this->ui->tableView->setColumnWidth(1,150);
        this->ui->tableView->setColumnWidth(2,100);
        this->ui->tableView->setColumnWidth(3,660);
        int i=0,row=0,judgeLen=judgeLine.length();
        for (i=0;i<judgeLen;i++) {
            QString line=judgeLine.at(i);
                QStringList linesplit=line.trimmed().split(" ");
                if(account==linesplit.at(4)){
                    this->model->setItem(row,0,new QStandardItem(linesplit.at(0)));
                    this->model->setItem(row,1,new QStandardItem(linesplit.at(1)));
                    this->model->setItem(row,2,new QStandardItem(linesplit.at(5)));
                    int k=6,lineLen=linesplit.length();
                    QString judge;
                    for (k=6;k<lineLen;k++) {
                        judge+=linesplit.at(k);
                    }
                    this->model->setItem(row,3,new QStandardItem(judge));
                    this->model->item(row,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    this->model->item(row,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    this->model->item(row,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    row++;
                }
        }
    }
}
