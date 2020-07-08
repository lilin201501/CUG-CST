#include "course_manage.h"
#include "ui_course_manage.h"

#include "about.h"

course_manage::course_manage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::course_manage)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.92);
    setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
//对输入内容做一定限制
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->line_id );
    this->ui->line_id->setValidator(validator);                                       //课程编号只能输入数字
    this->ui->line_tid->setValidator(validator);                                      //工号只能输入数字
    this->ui->line_time->setValidator(new QIntValidator(0, 999, this));              //限制学时只能输入小于三位的数字
    this->ui->button_ok->setEnabled(true);
    this->ui->button_revision->setDisabled(true);
    this->ui->button_delete->setDisabled(true);
    this->ui->line_id->setFocus();
}

course_manage::~course_manage()
{
    delete ui;
}

void course_manage::showEvent(QShowEvent *)
{
    if (readfile(moduleFile)==-1)
        QMessageBox::critical(this,"错误","课程文件读取失败！","确认");
}

void course_manage::on_button_ok_clicked()
{
    QString id=this->ui->line_id->text();
    QString name=this->ui->line_name->text();
    QString category=this->ui->cbb_category->currentText();
    QString teacherId=this->ui->line_tid->text();
    QString teacherName=this->ui->line_tname->text();
    QString faculty_op=this->ui->cbb_faculty_op->currentText();
    QString credit=this->ui->cbb_credit->currentText();
    QString time=this->ui->line_time->text();
//拼接成字符串分别用于messagebox输出和于写入文件
    QString messagebox_out="课程名称："+name+"\n"+"课程编号："+id+"\n"+"课程类别："+category+"\n"+"任课教师："+teacherName+"\n"+"工号："+teacherId+"\n"+"开课学院："+faculty_op+"\n"+"学分设置："+credit+"\n"+"学时设置："+time+"\n";
    QString information=name+" "+id+" "+category+" "+teacherName+" "+teacherId+" "+faculty_op+" "+credit+" "+time+"\n";
//检查用户输入是否合法，以及再次确认是否写入文件
    bool isInputWrong=id.length()!=5||name.length()<1||category=="课程类别"||teacherId.length()!=11||teacherName.length()<1||faculty_op=="开课学院"||credit=="学分设置"||time.length()<1;
    if(isInputWrong){
        QMessageBox::critical(this,"错误","信息填写不完整，请检查","确定");
    }else{
        int ret=QMessageBox::question(this,"请确认",messagebox_out,"确认","取消");
        if(ret==0){
            clearInterface();
            writeInformation(information);
        }
    }
}

void course_manage::clearInterface()
{
    this->ui->line_id->clear();
    this->ui->line_name->clear();
    this->ui->cbb_category->setCurrentIndex(0);
    this->ui->line_tid->clear();
    this->ui->line_tname->clear();
    this->ui->cbb_faculty_op->setCurrentIndex(0);
    this->ui->cbb_credit->setCurrentIndex(0);
    this->ui->line_time->clear();
    this->ui->line_id->setFocus();
}

void course_manage::writeInformation(QString information)
{
    QFile file(moduleFile);
    if(!file.open(QIODevice::Append|QIODevice::Text)){
        QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
        return;
    }
    QTextStream out(&file);
    out<<information;
    file.close();
    moduleLine.append(information);
}

void course_manage::on_button_delete_clicked()
{
    tempFilename();
    QString id=this->ui->line_id->text();
    int ret=QMessageBox::question(this,"删除课程信息","确定要删除课程编号为"+id+"课程的信息吗？\n\n"+"删除仅通过课程编号进行匹配!\n一经删除，数据无法恢复！\n","是(Y)","否(N)");
    if(ret==0){
        if(modifyNum>=0){
            QFile file(tempFile);
            if(!file.open(QIODevice::Append|QIODevice::Text)){
                QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
                return;
            }
            moduleLine.removeAt(modifyNum);        //移除列表中的已删除的数据
            int i=0, modLen=moduleLine.length();
            for (i=0;i<modLen;i++) {
                QString line=moduleLine.at(i);
                line=line.trimmed()+"\n";
                QStringList linesplit=line.split(" ");
                QTextStream out(&file);
                out<<line;
            }
            file.close();
            QFile fileOld(moduleFile);
            QFile fileNew(tempFile);
            if (fileOld.exists()){
                fileOld.remove();
                fileNew.rename(moduleFile);
            }
            else {
                QMessageBox::critical(this,"错误","未有信息保存为文件，无法删除","确认");
            }
            QMessageBox::information(this,"通知","删除成功！","确认");
            clearInterface();
            modifyNum=-1;
        }
        else {
            QString strNum= QString::number(modifyNum,10,1);
            QMessageBox::critical(this,"错误","未知错误，removeNum:"+strNum,"确认");
        }
    }
}

void course_manage::on_button_revision_clicked()
{
    tempFilename();
    QString id=this->ui->line_id->text();
    QString name=this->ui->line_name->text();
    QString category=this->ui->cbb_category->currentText();
    QString teacherId=this->ui->line_tid->text();
    QString teacherName=this->ui->line_tname->text();
    QString faculty_op=this->ui->cbb_faculty_op->currentText();
    QString credit=this->ui->cbb_credit->currentText();
    QString time=this->ui->line_time->text();

//拼接成字符串分别用于messagebox输出和于写入文件
    QString messagebox_out="课程名称："+name+"\n"+"课程编号："+id+"\n"+"课程类别："+category+"\n"+"任课教师："+teacherName+"\n"+"工号："+teacherId+"\n"+"开课学院："+faculty_op+"\n"+"学分设置："+credit+"\n"+"学时设置："+time+"\n";
    QString information=name+" "+id+" "+category+" "+teacherName+" "+teacherId+" "+faculty_op+" "+credit+" "+time+"\n";
//检查用户输入是否合法，以及再次确认是否写入文件
    bool isInputWrong=id.length()!=5||name.length()<1||category=="课程类别"||teacherId.length()!=11||teacherName.length()<1||faculty_op=="开课学院"||credit=="学分设置"||time.length()<1;
    if(isInputWrong){
        QMessageBox::critical(this,"错误","信息填写不完整，请检查","确定");
    }else{
        int ret=QMessageBox::question(this,"修改课程信息","确定要修改课程编号为“"+id+"”课程名为“"+name+"”的信息吗？\n"+"修改后的课程信息如下\n\n"+messagebox_out+"\n\n修改通过课程编号进行匹配!\n","是(Y)","否(N)");
        if(ret==0){
            QFile file(tempFile);
            if(!file.open(QIODevice::Append|QIODevice::Text)){
                QMessageBox::critical(this,"错误","文件打开失败，信息没有修改","确认");
                return;
            }
            moduleLine[modifyNum]=information;
            int i=0,modLen=moduleLine.length();
            for (i=0;i<modLen;i++) {
                QString line=moduleLine.at(i);
                line=line.trimmed()+"\n";
                QStringList linesplit=line.split(" ");
                QTextStream out(&file);
                out<<line;
            }
            file.close();
            QFile fileOld(moduleFile);
            QFile fileNew(tempFile);
            if (fileOld.exists()){
                fileOld.remove();
                fileNew.rename(moduleFile);
                QMessageBox::information(this,"通知","修改成功！","确认");
                clearInterface();
            }
            else {
                QMessageBox::critical(this,"错误","未有信息保存为文件，无法修改","确认");
            }
        }
    }
}

void course_manage::on_line_id_textChanged(const QString &arg1)
{
    if(isback){
        QString id=arg1;
        clearInterface();
        this->ui->line_id->setText(id);
        this->ui->button_ok->setEnabled(true);
        this->ui->button_revision->setDisabled(true);
        this->ui->button_delete->setDisabled(true);
        isback=false;
    }
    if(arg1.length()==5){
        isback=true;
        QString id=this->ui->line_id->text();
        int i=0,modLen=moduleLine.length();
        for (i=0;i<modLen;i++) {
            QString line=moduleLine.at(i);
            line=line.trimmed();
            QStringList linesplit=line.split(" ");
            if(id==linesplit.at(1)){
                this->ui->line_name->setText(linesplit.at(0));
                this->ui->cbb_category->setCurrentText(linesplit.at(2));
                this->ui->line_tname->setText(linesplit.at(3));
                this->ui->line_tid->setText(linesplit.at(4));
                this->ui->cbb_faculty_op->setCurrentText(linesplit.at(5));
                this->ui->cbb_credit->setCurrentText(linesplit.at(6));
                this->ui->line_time->setText(linesplit.at(7));
                modifyNum=i;
                this->ui->button_ok->setDisabled(true);
                this->ui->button_revision->setEnabled(true);
                this->ui->button_delete->setEnabled(true);
             }
         }
    }
}

void course_manage::on_line_tid_textChanged(const QString &arg1)
{
    this->ui->line_tname->clear();
    if(arg1.length()==11){
         QString teacherId=this->ui->line_tid->text();
         int i=0,staffLen=staffLine.length();
         for (i=0;i<staffLen;i++) {
             QString line=staffLine.at(i);
             line=line.trimmed();
             QStringList linesplit=line.split(" ");
             if(teacherId==linesplit.at(1)){
                 this->ui->line_tname->setText(linesplit.at(0));
             }
         }
    }
}
