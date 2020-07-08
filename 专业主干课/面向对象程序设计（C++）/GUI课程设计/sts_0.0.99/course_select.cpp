#include "course_select.h"
#include "ui_course_select.h"

#include "about.h"

extern QString account;

course_select::course_select(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::course_select)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.92);
    setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
    this->model = new QStandardItemModel;
    this->ui->tableView->setModel(model);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setShowGrid(false);

    this->ui->tableView->setMouseTracking(true);
}

course_select::~course_select()
{
    delete ui;
}

void course_select::showEvent(QShowEvent *)
{
    if (readfile(moduleFile)==-1){
        QMessageBox::critical(this,"错误","课程文件读取失败！","确认");
        return;
    }
    personalModuleFile=account+"Module.txt";
    if(readfile(personalModuleFile)==-1){
        QMessageBox::information(this,"通知","未查询到个人选课信息，将进行文件初始化","确认");
        personalModuleLine.removeAt(0);
    }
    this->model->clear();
    initialization();
    int i=0,inRow=0,modLen=moduleLine.length();
    for (i=0;i<modLen;i++) {
        QString line=moduleLine.at(i);
        line=line.trimmed()+" 未选";
        QStringList linesplit=line.split(" ");
        display(inRow++, linesplit);
//复杂度有点高...
        int j=0,perModLen=personalModuleLine.length();
        for (j=0;j<perModLen;j++) {
            QString personLine=personalModuleLine.at(j);
            personLine=personLine.trimmed();
            QStringList perLinesplit=personLine.split(" ");
            if(perLinesplit.at(1)==linesplit.at(1)){
                int m=0;
//使用row-1的原因是此处row的值还未变化，否则会发生越界闪退
                for (m=0;m<9;m++) {
                    model->item(inRow-1, m)->setForeground(QBrush(QColor(255,255,255)));       //选课后字体颜色设置为白色
                    model->item(inRow-1, m)->setBackground(QBrush(QColor(102,204,255)));       //选课后背景颜色设置为天依色
                }
                model->item(inRow-1, 8)->setText("已选");
            }
        }
    }
    calculation();
}

void course_select::closeEvent(QCloseEvent * event)
{
    if(dCredit<20){
        int ret=QMessageBox::question(this,"请确认","选课总学分未达到20学分！\n是否退出？","确认","取消");
        if(ret==1){
            event->ignore();
        }
    }
}

void course_select::initialization()
{
    dCredit=0;

    this->model->setHorizontalHeaderItem(0,new QStandardItem("课程名称"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("课程编号"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("课程类型"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("任课教师"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("教师工号"));
    this->model->setHorizontalHeaderItem(5,new QStandardItem("开课学院"));
    this->model->setHorizontalHeaderItem(6,new QStandardItem("学分设置"));
    this->model->setHorizontalHeaderItem(7,new QStandardItem("学时设置"));
    this->model->setHorizontalHeaderItem(8,new QStandardItem("选课情况"));

    this->ui->tableView->setColumnWidth(0,196);
    this->ui->tableView->setColumnWidth(1,92);
    this->ui->tableView->setColumnWidth(2,114);
    this->ui->tableView->setColumnWidth(3,128);
    this->ui->tableView->setColumnWidth(4,144);
    this->ui->tableView->setColumnWidth(5,156);
    this->ui->tableView->setColumnWidth(6,70);
    this->ui->tableView->setColumnWidth(7,70);
    this->ui->tableView->setColumnWidth(8,80);
}

void course_select::display(int row, QStringList moduleLine)
{
    int i=0,modLen=moduleLine.length();
    for (i=0;i<modLen;i++) {
        this->model->setItem(row,i,new QStandardItem(moduleLine.at(i)));
        this->model->item(row,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
}

void course_select::calculation()
{
    dCredit=0;
    int i=0,perModLen=personalModuleLine.length();
    for (i=0;i<perModLen;i++) {
        QString line=personalModuleLine.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        dCredit += linesplit.at(6).toDouble();
    }
    QString credit= QString::number(dCredit,10,2);
    this->ui->label_all_credit->setText(credit);
}

void course_select::on_tableView_doubleClicked(const QModelIndex &index)
{
    tempFilename();
    int curRow=index.row(),i=0,dropNum=-1,perModLen=personalModuleLine.length();
    QString id= model->index(curRow,1,QModelIndex()).data().toString();
    bool issearched=false;
    for (i=0;i<perModLen;i++) {
        QString line=personalModuleLine.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        if(id==linesplit.at(1)){
            issearched=true;
            dropNum=i;
            break;
        }
    }
    if(issearched){
        QFile file(tempFile);
        if(!file.open(QIODevice::Append|QIODevice::Text)){
            QMessageBox::critical(this,"错误","文件打开失败，无法进行退课！","确认");
            return;
        }
        personalModuleLine.removeAt(dropNum);              //移除list中要修改的数据
        --perModLen;
        int j=0,m=0;
        for (j=0;j<perModLen;j++) {
            QString line=personalModuleLine.at(j);
            line=line.trimmed()+"\n";
            QTextStream out(&file);
            out<<line;
        }
        file.close();
        for (m=0;m<9;m++) {
           model->item(curRow, m)->setForeground(QBrush(QColor(0,0,0)));       //退课后字体颜色设置为黑色
           model->item(curRow, m)->setBackground(QBrush(QColor(255,255,255))); //退课后背景颜色设置为白色
        }
        model->item(curRow, 8)->setText("未选");
        QFile fileOld(personalModuleFile);
        QFile fileNew(tempFile);
        if (fileOld.exists()){
            fileOld.remove();
            fileNew.rename(personalModuleFile);
            calculation();
            QMessageBox::information(this,"通知","退课成功！","确认");
        }
        else {
            QMessageBox::critical(this,"错误","未有信息保存为文件，无法进行退课","确认");
        }
    }
    else {
        QFile file(personalModuleFile);
        if(!file.open(QIODevice::Append|QIODevice::Text)){
            QMessageBox::critical(this,"错误","文件打开失败，无法进行选课","确认");
            return;
        }
        int i=0;
        QString infor;
        for (i=0;i<8;i++) {
            QString strGet= model->index(curRow,i,QModelIndex()).data().toString();
            infor += strGet+" ";
        }
        QTextStream out(&file);
        out<<infor+"\n";
        file.close();
        int m=0;
        for (m=0;m<9;m++) {
           model->item(curRow, m)->setForeground(QBrush(QColor(255,255,255)));       //选课后字体颜色设置为白色
           model->item(curRow, m)->setBackground(QBrush(QColor(102,204,255)));       //选课后背景颜色设置为天依色
        }
        model->item(curRow, 8)->setText("已选");
        personalModuleLine.append(infor);
        calculation();
        QMessageBox::information(this,"通知","选课成功！","确认");
    }
}

void course_select::on_tableView_entered(const QModelIndex &index)
{
    QString get=index.data().toString();
    if(!get.isEmpty()){
        QToolTip::showText(QCursor::pos(), "双击进行选退课");
    }
}

