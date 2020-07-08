#include "mainwindow.h"
#include <QApplication>

extern MainWindow *main_window;                   //将主窗口设为全局变量，方便在子窗口中调出

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *main_window = new MainWindow ();
    main_window->show();
    return a.exec();
}
