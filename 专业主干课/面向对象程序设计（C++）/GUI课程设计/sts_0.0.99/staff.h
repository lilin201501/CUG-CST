#ifndef STAFF_H
#define STAFF_H

#include <QDialog>

#include"score_input.h"
#include"score_search.h"
#include"staff_check.h"
namespace Ui {
class staff;
}

class staff : public QDialog
{
    Q_OBJECT

public:
    explicit staff(QWidget *parent = nullptr);
    ~staff();

private slots:
    bool closeDialog();

    void on_button_score_input_clicked();

    void on_button_score_search_clicked();

    void on_button_return_clicked();

    void on_button_check_clicked();

private:
    Ui::staff *ui;
    score_input openScoreInput;
    score_search openScoreSearch;
    staff_check openStaffCheck;
};

#endif // STAFF_H
