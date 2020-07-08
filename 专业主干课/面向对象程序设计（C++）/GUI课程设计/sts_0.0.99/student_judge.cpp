#include "student_judge.h"
#include "ui_student_judge.h"
#include "about.h"

student_judge::student_judge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::student_judge)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.92);
    setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
//对输入内容做一定限制
    this->ui->line_score->setValidator(new QIntValidator(0, 100, this));             //限制成绩输入范围为0~100,但实际好像999也能输,后面再判断吧...
}

student_judge::~student_judge()
{
    delete ui;
}


int student_judge::readJudge()
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


void student_judge::showEvent(QShowEvent *)
{
    if(isNotShow){ 
        if (readJudge()==-1){
            QMessageBox::critical(this,"错误","评价文件读取失败！","确认");
            }
        if (readfile(scoreFile)==-1){
            scoreLine.removeAt(0);//移除初始化的数据
            QMessageBox::critical(this,"错误","成绩文件读取失败！","确认");
        }
        int i=0,scoreLen=scoreLine.length();
        this->ui->cbb_subject->addItem("科目");
        for (i=0;i<scoreLen;i++) {
            QString line=scoreLine.at(i);
            line=line.trimmed();
            QStringList linesplit=line.split(" ");
            if(account==linesplit.at(1)){
                this->ui->cbb_subject->addItem(linesplit.at(3));
            }
        }
        isNotShow=false;
    }
}

void student_judge::clearInterface()
{
    this->ui->line_id->clear();
    this->ui->line_name->clear();
    this->ui->line_score->clear();
    this->ui->text_judge->clear();
}

void student_judge::writeInformation(QString information,QString inforLine)
{
    QFile file(judgeFile);
    if(!file.open(QIODevice::Append|QIODevice::Text)){
        QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
        return;
    }
    QTextStream out(&file);
    out<<information;
    file.close();
    judgeLine.append(inforLine);           //将新添加的数据保存到list中，用于删除时重新写入
}

void student_judge::on_button_add_clicked()
{
    QString subject=this->ui->cbb_subject->currentText();
    QString id=this->ui->line_id->text();
    QString name=this->ui->line_name->text();
    QString score=this->ui->line_score->text();
    QString judge=this->ui->text_judge->toPlainText().trimmed();
    QString information="\n~~acooz我是开始分隔符acooz~~\n"+account+" "+accountName+" "+subject+" "+name+" "+id+" "+score+" "+judge+"\n~~acooz我是结束分隔符acooz~~\n";
    QString inforLine=account+" "+accountName+" "+subject+" "+name+" "+id+" "+score+" "+judge;
    if(subject=="科目"||score.length()<1||score.toDouble()>100||judge.length()<1){
        QMessageBox::critical(this,"错误","信息填写不完整或错误，请检查","确定");
    }else{
        writeInformation(information,inforLine);
        clearInterface();
        this->ui->cbb_subject->setCurrentIndex(0);
        QMessageBox::information(this,"请确认","评价成功！","确认");
    }
}

void student_judge::on_button_revision_clicked()
{
    tempFilename();
    QString subject=this->ui->cbb_subject->currentText();
    QString id=this->ui->line_id->text();
    QString name=this->ui->line_name->text();
    QString score=this->ui->line_score->text();
    QString judge=this->ui->text_judge->toPlainText().trimmed();
    QString information=account+" "+accountName+" "+subject+" "+name+" "+id+" "+score+" "+judge;
    if(subject=="科目"||score.length()<1||score.toDouble()>100||judge.length()<1){
        QMessageBox::critical(this,"错误","信息填写不完整或错误，请检查","确定");
    }else{
        QFile file(tempFile);
        if(!file.open(QIODevice::Append|QIODevice::Text)){
            QMessageBox::critical(this,"错误","文件打开失败，信息没有修改","确认");
            return;
        }

        judgeLine[modifyNum]=information;
        int i=0,judgeLen=judgeLine.length();
        for (i=0;i<judgeLen;i++) {
            QString line="\n~~acooz我是开始分隔符acooz~~\n"+judgeLine.at(i).trimmed()+"\n~~acooz我是结束分隔符acooz~~\n";
            QTextStream out(&file);
            out<<line;
        }
        file.close();
        QFile fileOld(judgeFile);
        QFile fileNew(tempFile);
        if (fileOld.exists()){
            fileOld.remove();
            fileNew.rename(judgeFile);
            QMessageBox::information(this,"通知","修改成功！","确认");
            clearInterface();
            this->ui->cbb_subject->setCurrentIndex(0);
        }
        else {
            QMessageBox::critical(this,"错误","未有信息保存为文件，无法修改","确认");
        }
        QMessageBox::information(this,"请确认","修改成功！","确认");
    }
}

void student_judge::on_cbb_subject_currentTextChanged(const QString &arg1)
{
    clearInterface();
    int i=0,scoreLen=scoreLine.length();
    for (i=0;i<scoreLen;i++) {
        QString line=scoreLine.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        if(account==linesplit.at(1)&&arg1==linesplit.at(3)){
            this->ui->line_name->setText(linesplit.at(7));
            this->ui->line_id->setText(linesplit.at(8));
        }
    }
    this->ui->button_add->setEnabled(true);
    this->ui->button_revision->setDisabled(true);
    int j=0,judgeLen=judgeLine.length();
    for (j=0;j<judgeLen;j++) {
        QString line=judgeLine.at(j);
            QStringList linesplit=line.trimmed().split(" ");
            if(account==linesplit.at(0)&&arg1==linesplit.at(2)){
                modifyNum=j;
                this->ui->button_add->setDisabled(true);
                this->ui->button_revision->setEnabled(true);
                this->ui->line_score->setText(linesplit.at(5));
                int k=6,lineLen=linesplit.length();
                QString judge;
                for (k=6;k<lineLen;k++) {
                    judge+=linesplit.at(k);
                }
                this->ui->text_judge->setText(judge);
            }
    }
}
