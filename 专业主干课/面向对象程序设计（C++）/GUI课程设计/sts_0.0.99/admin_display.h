#ifndef SYSTEM_DISPLAY_H
#define SYSTEM_DISPLAY_H

#include <QDialog>
#include<QStandardItem>
#include<QStandardItemModel>

namespace Ui {
class system_display;
}

class system_display : public QDialog
{
    Q_OBJECT

public:
    explicit system_display(QWidget *parent = nullptr);
    ~system_display();

    void showEvent(QShowEvent *);
    void initialization();
    void display(int row,QStringList score_line);
    void saveFile(int flag);
    void calculation();
    int readJudge();

protected :
    void closeEvent(QCloseEvent *event);

private slots:
    void on_button_search_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_button_save_clicked();

    void on_cbb_findway_currentIndexChanged(int index);

private:
    Ui::system_display *ui;
    bool isChanged=false;
    QStandardItemModel *model;
    QList<QString> textLine;
    int saveFlag=-1;
    bool isNotShow=true;
    bool START,DONE;
    QString judgeText;
};

#endif // SYSTEM_DISPLAY_H
