#include "about.h"
#include "ui_about.h"

//初始化
QString account="null";
QString accountName="null";
QString studentFile="student.txt";
QString staffFile="staff.txt";
QString moduleFile="module.txt";
QString personalModuleFile="null.txt";
QString scoreFile="score.txt";
QString judgeFile="judge.txt";
QString tempFile="temp.txt";
QList<QString> studentLine=QList<QString>()<<"null 00000000000 男 18 null 000000 000000";
QList<QString> staffLine=QList<QString>()<<"null 99999999999 男 18 null 999999";
QList<QString> moduleLine=QList<QString>()<<"null 00000 null 0.0 00 000000";
QList<QString> personalModuleLine=QList<QString>()<<"null 00000 null 0.0 00 191100";
QList<QString> scoreLine=QList<QString>()<<"null 00000000000 000000 null 0.0 0 0.0";
QList<QString> judgeLine=QList<QString>()<<"null 00000000000 null 0 null";
QList<QString> textLine=QList<QString>()<<"null null null null null null null null null null null ";
int readfile(QString fileName)
{
    textLine.clear();
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line=in.readLine();
        textLine.append(line);
    }
    if(fileName==studentFile){
        studentLine=textLine;
    }
    else if (fileName==staffFile) {
        staffLine=textLine;
    }
    else if (fileName==scoreFile) {
        scoreLine=textLine;
    }
    else if (fileName==moduleFile) {
        moduleLine=textLine;
    }
    else if (fileName==judgeFile) {
        judgeLine=textLine;
    }
    else {
        personalModuleLine=textLine;
    }
    file.close();
    return 0;
}
//用于随机生成一个临时文件名
void tempFilename()
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    QString tempName;
    int randomx = 0;
    for (int i = 0; i <= 16; i++){
        randomx= rand() % (36);
        tempName += chars[randomx];
    }
    tempFile=tempName+".txt";
    qDebug()<<tempFile;
}

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.92);
    setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
    QMovie* movie = new QMovie(":/image/image/about.gif");
    this->ui->label_gif->setMovie(movie);
    movie->start();
    ui->label_blog->setOpenExternalLinks(true);
    ui->label_github->setOpenExternalLinks(true);
}

about::~about()
{
    delete ui;
}
