#include "system_display.h"
#include "ui_system_display.h"

#include"about.h"

system_display::system_display(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::system_display)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.92);
    setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
    this->model = new QStandardItemModel;
    this->ui->tableView->setModel(model);
}

system_display::~system_display()
{
    delete ui;
}

int system_display::readJudge()
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

void system_display::showEvent(QShowEvent *)
{
    if (readfile(moduleFile)==-1){
        QMessageBox::critical(this,"错误","课程文件读取失败！","确认");
        return;
    }

    if (readJudge()==-1){
        QMessageBox::critical(this,"错误","评价文件读取失败！","确认");
        return;
    }
}

void system_display::closeEvent(QCloseEvent * event)
{
    if(isChanged==true){
        int ret=QMessageBox::question(this,"保存","是否保存对信息的更改？","是(Y)","否(N)","取消");
        if(ret==0){
            saveFile(saveFlag);
            isChanged=false;
        }
        else if(ret==1) {
            isChanged=false;
        }
        else{
            event->ignore();
        }
    }
}

void system_display::initialization()
{
    int flag=this->ui->cbb_findway->currentIndex();
    switch (flag) {
    case 1:{
        this->model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
        this->model->setHorizontalHeaderItem(1,new QStandardItem("学号"));
        this->model->setHorizontalHeaderItem(2,new QStandardItem("性别"));
        this->model->setHorizontalHeaderItem(3,new QStandardItem("年龄"));
        this->model->setHorizontalHeaderItem(4,new QStandardItem("学院"));
        this->model->setHorizontalHeaderItem(5,new QStandardItem("班级"));
        this->model->setHorizontalHeaderItem(6,new QStandardItem("密码"));

        this->ui->tableView->setColumnWidth(0,180);
        this->ui->tableView->setColumnWidth(1,210);
        this->ui->tableView->setColumnWidth(2,100);
        this->ui->tableView->setColumnWidth(3,100);
        this->ui->tableView->setColumnWidth(4,210);
        this->ui->tableView->setColumnWidth(5,120);
        this->ui->tableView->setColumnWidth(6,150);

        break;
    }
    case 2:{
        this->model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
        this->model->setHorizontalHeaderItem(1,new QStandardItem("工号"));
        this->model->setHorizontalHeaderItem(2,new QStandardItem("性别"));
        this->model->setHorizontalHeaderItem(3,new QStandardItem("年龄"));
        this->model->setHorizontalHeaderItem(4,new QStandardItem("学院"));
        this->model->setHorizontalHeaderItem(5,new QStandardItem("密码"));
        this->model->setHorizontalHeaderItem(6,new QStandardItem("评分"));
        this->ui->tableView->setColumnWidth(0,180);
        this->ui->tableView->setColumnWidth(1,180);
        this->ui->tableView->setColumnWidth(2,120);
        this->ui->tableView->setColumnWidth(3,80);
        this->ui->tableView->setColumnWidth(4,210);
        this->ui->tableView->setColumnWidth(5,180);
        this->ui->tableView->setColumnWidth(6,100);
        break;
    }
    case 3:{
        this->model->setHorizontalHeaderItem(0,new QStandardItem("课程名称"));
        this->model->setHorizontalHeaderItem(1,new QStandardItem("课程编号"));
        this->model->setHorizontalHeaderItem(2,new QStandardItem("课程类型"));
        this->model->setHorizontalHeaderItem(3,new QStandardItem("任课教师"));
        this->model->setHorizontalHeaderItem(4,new QStandardItem("教师工号"));
        this->model->setHorizontalHeaderItem(5,new QStandardItem("开课学院"));
        this->model->setHorizontalHeaderItem(6,new QStandardItem("学分"));
        this->model->setHorizontalHeaderItem(7,new QStandardItem("学时"));
        this->ui->tableView->setColumnWidth(0,240);
        this->ui->tableView->setColumnWidth(1,100);
        this->ui->tableView->setColumnWidth(2,120);
        this->ui->tableView->setColumnWidth(3,100);
        this->ui->tableView->setColumnWidth(4,120);
        this->ui->tableView->setColumnWidth(5,180);
        this->ui->tableView->setColumnWidth(6,90);
        this->ui->tableView->setColumnWidth(7,109);
        break;
    }
  }
}

void system_display::on_button_search_clicked()
{
    this->model->clear();
    initialization();
    saveFlag=this->ui->cbb_findway->currentIndex();
    switch (saveFlag) {
    case 1:{
        textLine=studentLine;
        break;
    }
    case 2:{
        textLine=staffLine;
        break;
    }
    case 3:{
        textLine=moduleLine;
        break;
    }
    default:
        break;
    }
    if(saveFlag){
        int i=0,row=0,textLen=textLine.length();
        for (i=0;i<textLen;i++) {
            QString line=textLine.at(i);
            line=line.trimmed();
            QStringList linesplit=line.split(" ");
            display(row++, linesplit);
        }
        if(saveFlag==2){
            int j=0,row=model->rowCount();
            for (j=0;j<row;j++) {
                QString id= model->index(j,1,QModelIndex()).data().toString();
                int num=0; double score=0;
                int i=0,judgeLen=judgeLine.length();
                for (i=0;i<judgeLen;i++) {
                    QString line=judgeLine.at(i);
                        QStringList linesplit=line.trimmed().split(" ");
                        if(id==linesplit.at(4)){
                            num++;
                            score+=linesplit.at(5).toDouble();
                        }
                }
                if(num>0){
                    score=score/num;
                    QString strScore= QString::number(score,10,2);
                    this->model->setItem(j,6,new QStandardItem(strScore));
                    this->model->item(j,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                }
                else {
                    this->model->setItem(j,6,new QStandardItem("null"));
                    this->model->item(j,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                }

            }
        }
    }
    else{
        QMessageBox::critical(this,"错误","请选择查询方式！","确认");
    }
}

void system_display::display(int row, QStringList linesplit)
{
    int i=0,lineLen=linesplit.length();
    for (i=0;i<lineLen;i++) {
        this->model->setItem(row,i,new QStandardItem(linesplit.at(i)));
        this->model->item(row,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
}

void system_display::on_tableView_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    isChanged=true;
}

void system_display::saveFile(int saveFlag){
    tempFilename();
    if(saveFlag){
        QString fileName;
        switch (saveFlag) {
        case 1:
            fileName=studentFile;
            break;
        case 2:
            fileName=staffFile;
            break;
        case 3:
            fileName=moduleFile;
            break;
        default:
            break;
      }
        QFile fileNew(tempFile);
        QFile fileOld(fileName);
        if(!fileNew.open(QIODevice::Append|QIODevice::Text)){
            QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
            return;
        }
        int row=this->model->rowCount();                 //获取行数
        int col=this->model->columnCount();              //获取列数
        int i=0,j=0;
        for (i=0;i<row;i++) {
            QString line;
            for (j=0;j<col;j++) {
                QModelIndex index=model->index(i,j,QModelIndex());
                line= line+index.data().toString()+" ";
            }
            line=line.trimmed()+"\n";
            QTextStream out(&fileNew);
            out<<line;
        }
        fileNew.close();
        fileOld.remove();
        fileNew.rename(fileName);
        isChanged=false;
        QMessageBox::information(this,"通知","修改成功！","确认");
        readfile(fileName);
    }
    else {
        QMessageBox::critical(this,"错误","未查询到信息，无法保存！","确认");
    }
}

void system_display::on_button_save_clicked()
{
    saveFile(saveFlag);
}

void system_display::on_cbb_findway_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    if(isChanged==true){
        QMessageBox::question(this,"保存","将对修改过的信息进行保存","确定");
        saveFile(saveFlag);
        isChanged=false;
    }
}
