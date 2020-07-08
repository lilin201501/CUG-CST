#include "score_input.h"
#include "ui_score_input.h"

#include "about.h"

score_input::score_input(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::score_input)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.92);
    setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
//对输入内容做一定限制
    this->ui->line_score->setValidator(new QIntValidator(0, 100, this));             //限制成绩输入范围为0~100,但实际好像999也能输,后面再判断吧...
    this->ui->line_class->setValidator(new QIntValidator(0, 999999, this));          //限制班级只能输入小于六位的数字
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->line_id );
    this->ui->line_id->setValidator(validator);                                      //学号只能输入数字
}

score_input::~score_input()
{
    delete ui;
}

void score_input::showEvent(QShowEvent *)
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
        this->ui->cbb_subject->addItem("科目");
        for (i=0;i<modLen;i++) {
            QString line=moduleLine.at(i);
            line=line.trimmed();
            QStringList linesplit=line.split(" ");
            this->ui->cbb_subject->addItem(linesplit.at(0));
            credit[i+1]=linesplit.at(6);
        }
        isNotShow=false;
    }
}

void score_input::on_button_add_clicked()
{
    QString name=this->ui->line_name->text();
    QString id=this->ui->line_id->text();
    QString student_class=this->ui->line_class->text();
    QString subject=this->ui->cbb_subject->currentText();
    int subjectIndex=this->ui->cbb_subject->currentIndex();
    QString score=this->ui->line_score->text();
    QString point="0";  double d_point=0;
    if(score.toDouble()>60){
        d_point=floor((score.toDouble()-60)/5)*0.5+1;
        point= QString::number(d_point,10,2);
        if(score.toDouble()>100){
            d_point=666;               //输入分数超过100报错
        }
    }
    QString messagebox_out="姓名："+name+"\n"+"学号："+id+"\n"+"班级："+student_class+"\n"+"科目："+subject+"\n"+"学分："+credit[subjectIndex]+"\n"+"成绩："+score+"\n"+"绩点："+point+"\n"+"任课教师："+accountName+"\n"+"工号："+account;
    QString information=name+" "+id+" "+student_class+" "+subject+" "+credit[subjectIndex]+" "+score+" "+point+" "+accountName+" "+account+"\n";
    bool isInputfine=name.length()<1||subjectIndex==0||score.length()<1||d_point>5;
    if(isInputfine){
        QMessageBox::critical(this,"错误","信息填写不完整或错误，请检查","确定");
    }else{
        int ret=QMessageBox::question(this,"请确认",messagebox_out,"确认","取消");
        if(ret==0){
            clear_and_write(information);
        }
    }
}

void score_input::clear_and_write(QString information)
{
    this->ui->line_id->clear();               //清除用户输入
    this->ui->cbb_subject->setCurrentIndex(0);
    this->ui->line_id->setFocus();           //将光标闪烁点重置到学号

    QFile file(scoreFile);
    if(!file.open(QIODevice::Append|QIODevice::Text)){
        QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
        return;
    }
    QTextStream out(&file);
    out<<information;
    file.close();
    scoreLine.append(information);           //将新添加的数据保存到list中，用于修改/删除时重新写入
}

void score_input::on_button_delete_clicked()
{
    tempFilename();
    QString id=this->ui->line_id->text();
    QString subject=this->ui->cbb_subject->currentText();
    int ret=QMessageBox::question(this,"删除学生成绩","确定要删除学号为“"+id+"”学生的“"+subject+"”成绩吗？\n\n"+"删除通过学号和科目进行匹配!\n一经删除，数据无法恢复！\n","是(Y)","否(N)");
    if(ret==0){
        if(modifyNum>=0){
            QFile file(tempFile);
            if(!file.open(QIODevice::Append|QIODevice::Text)){
                QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
                return;
            }
            scoreLine.removeAt(modifyNum);        //移除列表中的已删除的数据
            int i=0, scoreLen=scoreLine.length();
            for (i=0;i<scoreLen;i++) {
                QString line=scoreLine.at(i);
                line=line.trimmed()+"\n";
                QStringList linesplit=line.split(" ");
                QTextStream out(&file);
                out<<line;
            }
            file.close();
            QFile fileOld(scoreFile);
            QFile fileNew(tempFile);
            if (fileOld.exists()){
                fileOld.remove();
                fileNew.rename(scoreFile);
            }
            else {
                QMessageBox::critical(this,"错误","未有信息保存为文件，无法删除","确认");
            }
            QMessageBox::information(this,"通知","删除成功！","确认");
            this->ui->line_id->clear();
            this->ui->cbb_subject->setCurrentIndex(0);
            this->ui->line_id->setFocus();
            modifyNum=-1;
        }
        else {
            QString strNum= QString::number(modifyNum,10,1);
            QMessageBox::critical(this,"错误","未知错误，removeNum:"+strNum,"确认");
        }
    }
}

void score_input::on_button_revision_clicked()
{
    tempFilename();
    QString name=this->ui->line_name->text();
    QString id=this->ui->line_id->text();
    QString student_class=this->ui->line_class->text();
    QString subject=this->ui->cbb_subject->currentText();
    int subjectIndex=this->ui->cbb_subject->currentIndex();
    QString score=this->ui->line_score->text();
    QString point="0";  double d_point=0;
    if(score.toDouble()>=60){
        d_point=floor((score.toDouble()-60)/5)*0.5+1;
        point= QString::number(d_point,10,2);
        if(score.toDouble()>100){
            d_point=666;               //输入分数超过100报错
        }
    }
    QString messagebox_out="姓名："+name+"\n"+"学号："+id+"\n"+"班级："+student_class+"\n"+"科目："+subject+"\n"+"学分："+credit[subjectIndex]+"\n"+"成绩："+score+"\n"+"绩点："+point+"\n"+"任课教师："+accountName+"\n"+"工号："+account;
    QString information=name+" "+id+" "+student_class+" "+subject+" "+credit[subjectIndex]+" "+score+" "+point+" "+accountName+" "+account+"\n";
    bool isInputfine=name.length()<1||subjectIndex==0||score.length()<1||d_point>5;
    if(isInputfine){
        QMessageBox::critical(this,"错误","信息填写不完整或错误，无法修改，请检查！","确定");
    }else{
        int ret=QMessageBox::question(this,"修改学生成绩","确定要修改学号为“"+id+"”学生“"+subject+"”的信息吗？\n"+"修改后的学生信息如下\n\n"+messagebox_out+"\n\n修改通过学号和科目进行匹配!\n","是(Y)","否(N)");
        if(ret==0){
            QFile file(tempFile);
            if(!file.open(QIODevice::Append|QIODevice::Text)){
                QMessageBox::critical(this,"错误","文件打开失败，信息没有修改","确认");
                return;
            }
            scoreLine[modifyNum]=information;
            int i=0,scoreLen=scoreLine.length();
            for (i=0;i<scoreLen;i++) {
                QString line=scoreLine.at(i);
                line=line.trimmed()+"\n";
                QStringList linesplit=line.split(" ");
                QTextStream out(&file);
                out<<line;
            }
            file.close();
            QFile fileOld(scoreFile);
            QFile fileNew(tempFile);
            if (fileOld.exists()){
                fileOld.remove();
                fileNew.rename(scoreFile);
                QMessageBox::information(this,"通知","修改成功！","确认");
                this->ui->line_id->clear();                 //清除用户界面
                this->ui->cbb_subject->setCurrentIndex(0);
                this->ui->line_id->setFocus();           //将光标闪烁点重置到学号
            }
            else {
                QMessageBox::critical(this,"错误","未有信息保存为文件，无法修改","确认");
            }
        }
    }
}

void score_input::on_cbb_subject_currentIndexChanged(int index)
{
    this->ui->line_score->clear();
    this->ui->button_add->setEnabled(true);
    this->ui->button_revision->setDisabled(true);
    this->ui->button_delete->setDisabled(true);
    this->ui->line_credit->setText(credit[index]);
    QString id=this->ui->line_id->text();
    QString subject=this->ui->cbb_subject->currentText();
    int i=0,scoreLen=scoreLine.length();
    for (i=0;i<scoreLen;i++) {
        QString line=scoreLine.at(i);
        line=line.trimmed();
        QStringList linesplit=line.split(" ");
        if((id==linesplit.at(1))&&(subject==linesplit.at(3))){
            this->ui->line_score->setText(linesplit.at(5));
            this->ui->button_add->setDisabled(true);
            this->ui->button_revision->setEnabled(true);
            this->ui->button_delete->setEnabled(true);
            modifyNum=i;
        }
    }
}

void score_input::on_line_id_textChanged(const QString &arg1)
{
    this->ui->line_name->clear();
    this->ui->line_class->clear();

    if(arg1.length()==11){
         QString id=this->ui->line_id->text();
         int i=0,stuLen=studentLine.length();
         for (i=0;i<stuLen;i++) {
             QString line=studentLine.at(i);
             line=line.trimmed();
             QStringList linesplit=line.split(" ");
             if(id==linesplit.at(1)){
                 this->ui->line_name->setText(linesplit.at(0));
                 this->ui->line_class->setText(linesplit.at(5));
             }
         }
    }
}
