#include "student_manage.h"
#include "ui_student_manage.h"

#include "about.h"

student_manage::student_manage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::student_manage)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.92);
    setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
//对输入内容做一定限制
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->line_id );
    this->ui->line_id->setValidator(validator);                                      //学号只能输入数字
    this->ui->line_class->setValidator(validator);                                      //班级只能输入数字
    this->ui->button_ok->setEnabled(true);
    this->ui->button_revision->setDisabled(true);
    this->ui->button_delete->setDisabled(true);
    this->ui->line_id->setFocus();
}

student_manage::~student_manage()
{
    delete ui;
}

void student_manage::on_button_ok_clicked()
{
    QString name=this->ui->line_name->text();                                                                     //获取用户输入信息
    QString id=this->ui->line_id->text();
    QString sex=this->ui->sexGroup->checkedButton()->text();
    QString age=this->ui->cbb_age->currentText();
    QString faculty=this->ui->cbb_faculty->currentText();
    QString student_class=this->ui->line_class->text();
    QString password=this->ui->line_password->text();
    QString messagebox_out="姓名："+name+"\n"+"学号："+id+"\n"+"性别："+sex+"\n"+"年龄："+age+"\n"+"学院："+faculty+"\n"+"班级："+student_class+"\n"+"密码："+password;  //拼接成一个字符串用于messagebox输出
    QString information=name+" "+id+" "+sex+" "+age+" "+faculty+" "+student_class+" "+password+"\n";                                            //拼接成一个字符串用于写入文本

//检查用户输入是否合法，以及再次确认是否写入txt
    if(name.length()<1||id.length()!=11||student_class.length()<6||age=="年龄"||faculty=="学院"||password.length()<6){
        QMessageBox::critical(this,"错误","信息填写不完整或错误，请检查","确定");
    }else{
        int ret=QMessageBox::question(this,"请确认",messagebox_out,"确认","取消");
        if(ret==0){
            clearInterface();
            writeInformation(information);
        }
    }
}


void student_manage::clearInterface()
{
    this->ui->line_id->clear();
    this->ui->line_name->clear();
    this->ui->rbt_male->setChecked(true);
    this->ui->cbb_age->setCurrentIndex(0);
    this->ui->cbb_faculty->setCurrentIndex(0);
    this->ui->line_class->clear();
    this->ui->line_password->clear();
    this->ui->line_id->setFocus();
}

void student_manage::writeInformation(QString information)
{
    QFile file(studentFile);
    if(!file.open(QIODevice::Append|QIODevice::Text)){
        QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
        return;
    }
    QTextStream out(&file);
    out<<information;
    file.close();
    studentLine.append(information);
}

//查找并删除
void student_manage::on_button_delete_clicked()
{
    tempFilename();
    QString id=this->ui->line_id->text();
    int ret=QMessageBox::question(this,"删除学生信息","确定要删除学号为"+id+"学生的信息吗？\n\n"+"删除仅通过学号进行匹配!\n一经删除，数据无法恢复！\n","是(Y)","否(N)");
    if(ret==0){
        if(modifyNum>=0){
            QFile file(tempFile);
            if(!file.open(QIODevice::Append|QIODevice::Text)){
                QMessageBox::critical(this,"错误","文件打开失败，信息没有写入","确认");
                return;
            }
            studentLine.removeAt(modifyNum);        //移除列表中的已删除的数据
            int i=0, stuLen=studentLine.length();
            for (i=0;i<stuLen;i++) {
                QString line=studentLine.at(i);
                line=line.trimmed()+"\n";
                QStringList linesplit=line.split(" ");
                QTextStream out(&file);
                out<<line;
            }
            file.close();
            QFile fileOld(studentFile);
            QFile fileNew(tempFile);
            if (fileOld.exists()){
                fileOld.remove();
                fileNew.rename(studentFile);
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

void student_manage::on_button_revision_clicked()
{
    tempFilename();
    QString name=this->ui->line_name->text();                          //获取用户输入信息
    QString id=this->ui->line_id->text();
    QString sex=this->ui->sexGroup->checkedButton()->text();
    QString age=this->ui->cbb_age->currentText();
    QString faculty=this->ui->cbb_faculty->currentText();
    QString student_class=this->ui->line_class->text();
    QString password=this->ui->line_password->text();
    QString messagebox_out="姓名："+name+"\n"+"学号："+id+"\n"+"性别："+sex+"\n"+"年龄："+age+"\n"+"学院："+faculty+"\n"+"班级："+student_class+"\n"+"密码："+password;  //拼接成一个字符串用于messagebox输出
    QString information=name+" "+id+" "+sex+" "+age+" "+faculty+" "+student_class+" "+password+"\n";                                            //拼接成一个字符串用于写入文本
//检查用户输入是否合法，以及再次确认是否写入txt
    if(name.length()<1||id.length()!=11||student_class.length()<6||age=="年龄"||faculty=="学院"||password.length()<6){
        QMessageBox::critical(this,"错误","信息填写不完整或错误，无法修改，请检查！","确定");
    }else{
        int ret=QMessageBox::question(this,"修改学生信息","确定要修改学号为“"+id+"”姓名为“"+name+"”的信息吗？\n"+"修改后的学生信息如下\n\n"+messagebox_out+"\n\n修改通过学号进行匹配!\n","是(Y)","否(N)");
        if(ret==0){
            QFile file(tempFile);
            if(!file.open(QIODevice::Append|QIODevice::Text)){
                QMessageBox::critical(this,"错误","文件打开失败，信息没有修改","确认");
                return;
            }
            studentLine[modifyNum]=information;
            int i=0,stuLen=studentLine.length();
            for (i=0;i<stuLen;i++) {
                QString line=studentLine.at(i);
                line=line.trimmed()+"\n";
                QStringList linesplit=line.split(" ");
                QTextStream out(&file);
                out<<line;
            }
            file.close();
            QFile fileOld(studentFile);
            QFile fileNew(tempFile);
            if (fileOld.exists()){
                fileOld.remove();
                fileNew.rename(studentFile);
                QMessageBox::information(this,"通知","修改成功！","确认");
                clearInterface();
            }
            else {
                QMessageBox::critical(this,"错误","未有信息保存为文件，无法修改","确认");
            }
        }
    }
}

void student_manage::on_line_id_textChanged(const QString &arg1)
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
    if(arg1.length()==11){
        isback=true;
        QString id=this->ui->line_id->text();
        int i=0,stuLen=studentLine.length();
        for (i=0;i<stuLen;i++) {
            QString line=studentLine.at(i);
            line=line.trimmed();
            QStringList linesplit=line.split(" ");
            if(id==linesplit.at(1)){
                this->ui->line_name->setText(linesplit.at(0));
                if(linesplit.at(2)=="女"){
                    this->ui->rbt_female->setChecked(true);
                }
                this->ui->cbb_age->setCurrentText(linesplit.at(3));
                this->ui->cbb_faculty->setCurrentText(linesplit.at(4));
                this->ui->line_class->setText(linesplit.at(5));
                this->ui->line_password->setText(linesplit.at(6));
                modifyNum=i;
                this->ui->button_ok->setDisabled(true);
                this->ui->button_revision->setEnabled(true);
                this->ui->button_delete->setEnabled(true);
            }
         }
    }
}

