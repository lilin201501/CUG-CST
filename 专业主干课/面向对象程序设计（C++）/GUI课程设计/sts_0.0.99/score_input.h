#ifndef SCORE_INPUT_H
#define SCORE_INPUT_H

#include <QDialog>

namespace Ui {
class score_input;
}

class score_input : public QDialog
{
    Q_OBJECT

public:
    explicit score_input(QWidget *parent = nullptr);
    ~score_input();

    void showEvent(QShowEvent *);
    void clear_and_write(QString information);

private slots:
    void on_button_add_clicked();

    void on_button_delete_clicked();

    void on_button_revision_clicked();

    void on_cbb_subject_currentIndexChanged(int index);

    void on_line_id_textChanged(const QString &arg1);

private:
    Ui::score_input *ui;
    QString credit[50]={"学分"};
    int modifyNum=-1;
    bool isNotShow=true;
};

#endif // SCORE_INPUT_H
