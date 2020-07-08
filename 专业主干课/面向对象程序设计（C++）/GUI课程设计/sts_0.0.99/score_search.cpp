#include "score_search.h"
#include "ui_score_search.h"

#include "about.h"

score_search::score_search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::score_search)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.92);
    setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
    this->model = new QStandardItemModel;
    this->ui->tableView->setModel(model);

    this->ui->tableView->setMouseTracking(true);
    this->ui->radioButton->setVisible(false);
    this->ui->line_lower->setVisible(false);
    this->ui->line_upper->setVisible(false);
    this->ui->label->setVisible(false);
    this->ui->cbb_subject->setVisible(false);
    this->ui->line_class->setVisible(false);
    this->ui->line_lower->setReadOnly(true);
    this->ui->line_upper->setReadOnly(true);
    this->ui->line_lower->setValidator(new QIntValidator(0, 100, this));
    this->ui->line_upper->setValidator(new QIntValidator(0, 100, this));
    isAnalysis(false);
}

score_search::~score_search()
{
    delete ui;
}

void score_search::showEvent(QShowEvent *)
{
    if(isNotShow){
        if (readfile(scoreFile)==-1){
            scoreLine.removeAt(0);//移除初始化的数据
            QMessageBox::critical(this,"错误","成绩文件读取失败！","确认");
        }
//初始化科目
        if (readfile(moduleFile)==-1){
            QMessageBox::critical(this,"错误","课程文件读取失败！无法初始化科目","确认");
        }
        int i=0,modLen=moduleLine.length();
        for (i=0;i<modLen;i++) {
            QString line=moduleLine.at(i);
            line=line.trimmed();
            QStringList linesplit=line.split(" ");
            this->ui->cbb_subject->addItem(linesplit.at(0));
        }
        isNotShow=false;
    }
}

void score_search::saveFile(){
    tempFilename();
    QFile fileNew(tempFile);
    QFile fileOld(scoreFile);
    if(!fileNew.open(QIODevice::Append|QIODevice::Text)){
        QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
        return;
    }
    int i=0,j=0;
    int row=this->model->rowCount();                 //获取行数
    int col=this->model->columnCount();              //获取列数
    fileNew.open(QIODevice::Append|QIODevice::Text);
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
    fileNew.rename(scoreFile);
    QMessageBox::information(this,"通知","修改成功！","确认");
}

void score_search::closeEvent(QCloseEvent * event)
{
    if(saveFlag==1&&isChanged==true){
        int ret=QMessageBox::question(this,"保存","是否保存对成绩的更改？","是(Y)","否(N)","取消");
        if(ret==0){
            saveFile();
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

void score_search::initialization()
{
    this->model->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("学号"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("班级"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("科目"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("学分"));
    this->model->setHorizontalHeaderItem(5,new QStandardItem("成绩"));
    this->model->setHorizontalHeaderItem(6,new QStandardItem("绩点"));
    this->model->setHorizontalHeaderItem(7,new QStandardItem("任课教师"));
    this->model->setHorizontalHeaderItem(8,new QStandardItem("教师工号"));
    this->ui->tableView->setColumnWidth(0,120);
    this->ui->tableView->setColumnWidth(1,150);
    this->ui->tableView->setColumnWidth(2,120);
    this->ui->tableView->setColumnWidth(3,180);
    this->ui->tableView->setColumnWidth(4,80);
    this->ui->tableView->setColumnWidth(5,80);
    this->ui->tableView->setColumnWidth(6,80);
    this->ui->tableView->setColumnWidth(7,80);
    this->ui->tableView->setColumnWidth(8,120);
}

void score_search::isAnalysis(int saveflag)
{
    int subject=this->ui->cbb_subject->currentIndex();
    QString classes=this->ui->line_class->text();
    if((saveflag==4&&subject!=0)||(saveflag==5&&classes.length()==6)){
        this->ui->tableView->resize(1081,511);
        this->ui->label_average->setVisible (true);
        this->ui->label_passrate->setVisible (true);
        this->ui->label_standard_deviation->setVisible (true);
        this->ui->label_2->setVisible (true);
        this->ui->label_3->setVisible (true);
        this->ui->label_4->setVisible (true);
        calculation();
    }
    else {
        this->ui->label_average->setVisible (false);
        this->ui->label_passrate->setVisible (false);
        this->ui->label_standard_deviation->setVisible (false);
        this->ui->label_2->setVisible (false);
        this->ui->label_3->setVisible (false);
        this->ui->label_4->setVisible (false);
    }
}

void score_search::on_button_search_clicked()
{
    this->model->clear();
    this->ui->tableView->resize(1081,591);
    initialization();
    saveFlag=this->ui->cbb_findway->currentIndex();
    QString infor=this->ui->line_infor->text();
    if(saveFlag==0){
        QMessageBox::critical(this,"错误","请选择查询方式！","确认");
    }
    else if(infor.length()<1&&saveFlag!=1){
        QMessageBox::critical(this,"错误","请输入要查询的信息！","确认");
    }
    else {
        display(saveFlag,infor);
        isAnalysis(saveFlag);
    }
}

void score_search::display(int flag,QString infor)
{
    int i=0,row=0,scoreLen=scoreLine.length();
    bool ischecked=this->ui->radioButton->isChecked();
    if(flag==1){
        for (i=0;i<scoreLen;i++,row++) {
            QString line=scoreLine.at(i);
            line=line.trimmed();
            QStringList linesplit=line.split(" ");
            int j=0,lineLen=linesplit.length();
            for (j=0;j<lineLen;j++) {
                this->model->setItem(row,j,new QStandardItem(linesplit.at(j)));
                this->model->item(row,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }
        }
    }
    else if (flag==2||flag==3) {
        for (i=0;i<scoreLen;i++) {
            QString line=scoreLine.at(i);
            line=line.trimmed();
            QStringList linesplit=line.split(" ");
            if(infor==linesplit.at(flag-2)){
                int j=0,lineLen=linesplit.length();
                for (j=0;j<lineLen;j++) {
                    this->model->setItem(row,j,new QStandardItem(linesplit.at(j)));
                    this->model->item(row,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                }
                row++;
            }
        }
    }
    else if (flag==4) {
        int subject=this->ui->cbb_subject->currentIndex();
        QString subinfor=this->ui->cbb_subject->currentText();
        QString strLower=this->ui->line_lower->text();
        QString strUpper=this->ui->line_upper->text();
        double lower=strLower.toDouble();
        double upper=strUpper.toDouble();
        if(ischecked&&subject==0){
            bool isInputRight=strLower.length()>0&&strUpper.length()>0&&lower>=0&&upper<=100&&lower<=upper;
            if(isInputRight){
                for (i=0;i<scoreLen;i++) {
                    QString line=scoreLine.at(i);
                    line=line.trimmed();
                    QStringList linesplit=line.split(" ");
                    double score=linesplit.at(5).toDouble();
                    if(infor==linesplit.at(flag-2)&&score>=lower&&score<=upper){
                        int j=0,lineLen=linesplit.length();
                        for (j=0;j<lineLen;j++) {
                            this->model->setItem(row,j,new QStandardItem(linesplit.at(j)));
                            this->model->item(row,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                        }
                        row++;
                    }
                }
            }
            else {
                QMessageBox::critical(this,"错误","成绩范围输入错误，请重试！","确认");
            }
        }
        else if (!ischecked&&subject==0) {
            for (i=0;i<scoreLen;i++) {
                QString line=scoreLine.at(i);
                line=line.trimmed();
                QStringList linesplit=line.split(" ");
                if(infor==linesplit.at(flag-2)){
                    int j=0,lineLen=linesplit.length();
                    for (j=0;j<lineLen;j++) {
                        this->model->setItem(row,j,new QStandardItem(linesplit.at(j)));
                        this->model->item(row,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    }
                    row++;
                }
            }
        }
        else if (ischecked&&subject!=0) {
            bool isInputRight=strLower.length()>0&&strUpper.length()>0&&lower>=0&&upper<=100&&lower<=upper;
            if(isInputRight){
                for (i=0;i<scoreLen;i++) {
                    QString line=scoreLine.at(i);
                    line=line.trimmed();
                    QStringList linesplit=line.split(" ");
                    double score=linesplit.at(5).toDouble();
                    if(infor==linesplit.at(flag-2)&&subinfor==linesplit.at(3)&&score>=lower&&score<=upper){
                        int j=0,lineLen=linesplit.length();
                        for (j=0;j<lineLen;j++) {
                            this->model->setItem(row,j,new QStandardItem(linesplit.at(j)));
                            this->model->item(row,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                        }
                        row++;
                    }
                }
            }
            else {
                QMessageBox::critical(this,"错误","成绩范围输入错误，请重试！","确认");
            }
        }
        else if (!ischecked&&subject!=0) {
            for (i=0;i<scoreLen;i++) {
                QString line=scoreLine.at(i);
                line=line.trimmed();
                QStringList linesplit=line.split(" ");
                if(infor==linesplit.at(flag-2)&&subinfor==linesplit.at(3)){
                    int j=0,lineLen=linesplit.length();
                    for (j=0;j<lineLen;j++) {
                        this->model->setItem(row,j,new QStandardItem(linesplit.at(j)));
                        this->model->item(row,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    }
                    row++;
                }
            }
        }
    }
    else if (flag==5) {
        QString classes=this->ui->line_class->text();
        QString strLower=this->ui->line_lower->text();
        QString strUpper=this->ui->line_upper->text();
        double lower=strLower.toDouble();
        double upper=strUpper.toDouble();
        if (ischecked&&classes.length()>0){
            bool isInputRight=strLower.length()>0&&strUpper.length()>0&&lower>=0&&upper<=100&&lower<=upper;
            if(isInputRight){
                for (i=0;i<scoreLen;i++) {
                    QString line=scoreLine.at(i);
                    line=line.trimmed();
                    QStringList linesplit=line.split(" ");
                    double score=linesplit.at(5).toDouble();
                    if(infor==linesplit.at(flag-2)&&classes==linesplit.at(2)&&score>=lower&&score<=upper){
                        int j=0,lineLen=linesplit.length();
                        for (j=0;j<lineLen;j++) {
                            this->model->setItem(row,j,new QStandardItem(linesplit.at(j)));
                            this->model->item(row,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                        }
                        row++;
                    }
                }
            }
            else {
                QMessageBox::critical(this,"错误","成绩范围输入错误，请重试！","确认");
            }
        }
        else if (ischecked&&classes.length()==0) {
            bool isInputRight=strLower.length()>0&&strUpper.length()>0&&lower>=0&&upper<=100&&lower<=upper;
            if(isInputRight){
                for (i=0;i<scoreLen;i++) {
                    QString line=scoreLine.at(i);
                    line=line.trimmed();
                    QStringList linesplit=line.split(" ");
                    double score=linesplit.at(5).toDouble();
                    if(infor==linesplit.at(flag-2)&&score>=lower&&score<=upper){
                        int j=0,lineLen=linesplit.length();
                        for (j=0;j<lineLen;j++) {
                            this->model->setItem(row,j,new QStandardItem(linesplit.at(j)));
                            this->model->item(row,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                        }
                        row++;
                    }
                }
            }
            else {
                QMessageBox::critical(this,"错误","成绩范围输入错误，请重试！","确认");
            }
        }
        else if (!ischecked&&classes.length()>0) {
            QString classes=this->ui->line_class->text();
            for (i=0;i<scoreLen;i++) {
                QString line=scoreLine.at(i);
                line=line.trimmed();
                QStringList linesplit=line.split(" ");
                if(infor==linesplit.at(flag-2)&&classes==linesplit.at(2)){
                    int j=0,lineLen=linesplit.length();
                    for (j=0;j<lineLen;j++) {
                        this->model->setItem(row,j,new QStandardItem(linesplit.at(j)));
                        this->model->item(row,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    }
                    row++;
                }
            }
        }
        else if (!ischecked&&classes.length()==0) {
            for (i=0;i<scoreLen;i++) {
                QString line=scoreLine.at(i);
                line=line.trimmed();
                QStringList linesplit=line.split(" ");
                if(infor==linesplit.at(flag-2)){
                    int j=0,lineLen=linesplit.length();
                    for (j=0;j<lineLen;j++) {
                        this->model->setItem(row,j,new QStandardItem(linesplit.at(j)));
                        this->model->item(row,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    }
                    row++;
                }
            }
        }
    }
}


void score_search::calculation()
{
    QString infor=this->ui->line_infor->text();
    int row=this->model->rowCount();
//初始化
    double totalGrades=0,passNum=0,variance=0,dAverage=0,dPassrate=0,dStandardDeviation=0;
//计算平均分
    int i=0;
    for (i=0;i<row;i++) {
        QModelIndex index=model->index(i,5,QModelIndex());
        double get=index.data().toString().toDouble();
        totalGrades=totalGrades+get;
    }
//计算及格率,标准差
    for (i=0;i<row;i++) {
        QModelIndex index=model->index(i,5,QModelIndex());
        double get=index.data().toString().toDouble();
        variance=variance+(get-dAverage)*(get-dAverage);      //未除以人数
        if(get>=60)
            passNum++;
    }
    if(row>0){
        dAverage=totalGrades/row;
        dPassrate=passNum/row;
        dStandardDeviation=sqrt(variance/row);
    }
    QString average= QString::number(dAverage,10,2);
    QString passrate= QString::number(dPassrate,10,2);
    QString standardDeviation= QString::number(dStandardDeviation,10,2);
    this->ui->label_average->setText(average);
    this->ui->label_passrate->setText(passrate);
    this->ui->label_standard_deviation->setText(standardDeviation);
}

void score_search::on_tableView_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    isChanged=true;
}

void score_search::on_cbb_findway_currentIndexChanged(int index)
{   
    switch (index) {
    case 1:{
        this->ui->line_infor->setDisabled(true);
        this->ui->radioButton->setVisible(false);
        this->ui->radioButton->setChecked(false);
        this->ui->line_lower->setVisible(false);
        this->ui->line_upper->setVisible(false);
        this->ui->label->setVisible(false);
        this->ui->cbb_subject->setVisible(false);
        this->ui->line_class->setVisible(false);
        break;
    }
    case 4:{
        this->ui->line_infor->setEnabled(true);
        this->ui->radioButton->setVisible(true);
        this->ui->radioButton->setChecked(false);
        this->ui->line_lower->setVisible(true);
        this->ui->line_upper->setVisible(true);
        this->ui->label->setVisible(true);
        this->ui->line_class->setVisible(false);
        this->ui->cbb_subject->setVisible(true);
        break;
    }
    case 5:{
        this->ui->line_infor->setEnabled(true);
        this->ui->radioButton->setVisible(true);
        this->ui->radioButton->setChecked(false);
        this->ui->line_lower->setVisible(true);
        this->ui->line_upper->setVisible(true);
        this->ui->label->setVisible(true);
        this->ui->line_class->setVisible(true);
        this->ui->cbb_subject->setVisible(false);
        break;
    }
    default:{
        this->ui->line_infor->setEnabled(true);
        this->ui->radioButton->setVisible(false);
        this->ui->line_lower->setVisible(false);
        this->ui->line_upper->setVisible(false);
        this->ui->label->setVisible(false);
        this->ui->cbb_subject->setVisible(false);
        this->ui->line_class->setVisible(false);
        break;
    }
    }
    if(saveFlag==1&&isChanged){
        QMessageBox::question(this,"保存","将对修改过的信息进行保存","确定");
        saveFile();
        isChanged=false;
    }
    else if(isChanged){
        QMessageBox::information(this,"不保存","修改过的信息不会进行保存","确定");
        isChanged=false;
    }
}

void score_search::on_tableView_entered(const QModelIndex &index)
{
    QString get=index.data().toString();
    if(!get.isEmpty()){
        QToolTip::showText(QCursor::pos(), "双击进行修改");
    }
}

void score_search::on_radioButton_clicked()
{
 bool ischecked=this->ui->radioButton->isChecked();
 if(ischecked){
     this->ui->line_lower->setReadOnly(false);
     this->ui->line_upper->setReadOnly(false);
 }
 else{
     this->ui->line_lower->setReadOnly(true);
     this->ui->line_upper->setReadOnly(true);
 }
}
