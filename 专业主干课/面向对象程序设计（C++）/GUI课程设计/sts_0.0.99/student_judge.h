#ifndef STUDENT_JUDGE_H
#define STUDENT_JUDGE_H

#include <QDialog>

namespace Ui {
class student_judge;
}

class student_judge : public QDialog
{
    Q_OBJECT

public:
    explicit student_judge(QWidget *parent = nullptr);
    ~student_judge();
    void clearInterface();
    void writeInformation(QString information,QString inforLine);
    int readJudge();
    void showEvent(QShowEvent *);
private slots:
    void on_button_add_clicked();

    void on_button_revision_clicked();

    void on_cbb_subject_currentTextChanged(const QString &arg1);

private:
    Ui::student_judge *ui;
    bool isNotShow=true;
    QString judgeText;
    int modifyNum=-1;
    bool START,DONE;
};

#endif // STUDENT_JUDGE_H
