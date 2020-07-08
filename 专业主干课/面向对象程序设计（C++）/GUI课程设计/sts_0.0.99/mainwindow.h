#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QProcess>

#include"student.h"
#include"staff.h"
#include"system.h"
#include"about.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void delay(int mSec);
    void animation(int mSec,QString windowType);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_button_login_clicked();

    void keyPressEvent(QKeyEvent *event);

    void on_button_about_clicked();

    void on_button_close_clicked();

    void on_button_mini_clicked();

private:
    Ui::MainWindow *ui;
    QString adminAccount="admin";
    QString adminPassword="admin";
    student openStudent;
    staff openStaff;
    class system openSystem;
    about opAbout;
    bool isMove;
    QPoint startPoint;
    QPoint windowPoint;
};

#endif // MAINWINDOW_H
