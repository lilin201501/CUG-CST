#ifndef STUDENT_H
#define STUDENT_H

#include <QDialog>
#include"course_select.h"
#include"student_inquiry.h"
#include"student_judge.h"

namespace Ui {
class student;
}

class student : public QDialog
{
    Q_OBJECT

public:
    explicit student(QWidget *parent = nullptr);
    ~student();

private slots:
    bool closeDialog();

    void on_button_course_select_clicked();

    void on_button_score_inquiry_clicked();

    void on_button_return_clicked();

    void on_button_judge_clicked();

private:
    Ui::student *ui;

    course_select openCourseSelect;
    student_inquiry openScoreInquiry;
    student_judge openStudentJudge;
};

#endif // STUDENT_H
