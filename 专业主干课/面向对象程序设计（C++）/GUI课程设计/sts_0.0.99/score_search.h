#ifndef SCORE_SEARCH_H
#define SCORE_SEARCH_H

#include <QDialog>
#include<QStandardItem>
#include<QStandardItemModel>

namespace Ui {
class score_search;
}

class score_search : public QDialog
{
    Q_OBJECT

public:
    explicit score_search(QWidget *parent = nullptr);
    ~score_search();

    void showEvent(QShowEvent *);
    void search(int mode,int flag,QString infor,QString subORcls,double lower,double upper);
    void display(int flag,QString infor);
    void initialization();
    void calculation();
    void saveFile();
    void isAnalysis(int saveflag);

protected :
    void closeEvent(QCloseEvent *event);

private slots:
    void on_button_search_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_cbb_findway_currentIndexChanged(int index);

    void on_tableView_entered(const QModelIndex &index);

    void on_radioButton_clicked();

private:
    Ui::score_search *ui;
    bool isChanged=false;
    QStandardItemModel *model;
    int saveFlag=-1;
    bool isNotShow=true;
};

#endif // SCORE_SEARCH_H
