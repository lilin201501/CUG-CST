#ifndef ABOUT_H
#define ABOUT_H

//全部使用的头文件及全局变量
//仍需完善的一些小功能

//building :模糊查找
//building n:学习数据库，通过数据库实现上述操作

#include <QDebug>
#include <QDialog>
#include <QMovie>
#include <QString>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QIODevice>
#include <QStringList>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QtMath>
#include <QCheckBox>
#include <QAbstractItemView>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QtMath>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QValidator>
#include <QTimer>
#include <QPropertyAnimation>
#include <QHeaderView>
#include <QTime>
#include <QToolTip>

//用于账号传递
extern QString account;
extern QString accountName;
//用于储存文件名
extern QString studentFile;
extern QString staffFile;
extern QString moduleFile;
extern QString personalModuleFile;
extern QString scoreFile;
extern QString judgeFile;
extern QString tempFile;
//用于储存数据
extern QList<QString> studentLine;
extern QList<QString> staffLine;
extern QList<QString> moduleLine;
extern QList<QString> personalModuleLine;
extern QList<QString> scoreLine;
extern QList<QString> judgeLine;
extern QList<QString> textLine;
//文件读取函数
extern int readfile(QString filename);
extern void tempFilename();
namespace Ui {
class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = nullptr);
    ~about();
private:
    Ui::about *ui;
};

#endif // ABOUT_H
