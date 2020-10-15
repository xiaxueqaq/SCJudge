#ifndef DIALOG_NEWPBL_H
#define DIALOG_NEWPBL_H

#include <QDialog>

namespace Ui {
class dialog_newpbl;
}

class dialog_newpbl : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_newpbl(QWidget *parent = nullptr);
    ~dialog_newpbl();
    QString dlg_getInpF();
    QString dlg_getOutF();
    QString dlg_getSpj();
    QString dlg_getSrc();
    QString get_Prob_name();
    QString get_code_dir();
    QString get_data_dir();

    int get_score();
    int get_Data_num();
    int get_Prob_Type();
    int get_Source_num();
    int get_Lang();
    int get_TL();

private slots:

    void on_radBtn_Trad_clicked();

    void on_pushButton_clicked();

    void on_buttonBox_accepted();

    void on_ckBox_Maple_clicked();

    void on_ckBox_MMA_clicked();

    void on_radBtn_Intr_clicked();

    void on_btn_src_dir_clicked();

    void on_btn_src_dir_2_clicked();

    void on_btn_data_dir_clicked();

    void on_btn_spj_clicked();

signals:
    void dlgRet(QString,int,int,QString,QString,QString,QString,int);

private:
    Ui::dialog_newpbl *ui;
    int num_data,num_source;
};

#endif // DIALOG_NEWPBL_H
