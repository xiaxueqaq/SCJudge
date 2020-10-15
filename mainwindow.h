#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dstruct.h"
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum ButtonStatus{btnDone, btnRunning, btnUnknown, btnError,btnCancelled};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

private:
    void add_Prob(QString,int,int,QString,QString,QString,QString,int);
    void TableInputAdd(int, QString, int, int, QString, QString);
    void TableScoreAdd(int, QString,int, QString);
    void TableScoreAdd(int rowNo, QStudent* student);
    void ExportScore(int index, QString filename);
    void UpdateTable(int);
    void Restore();
    void Save();
    void SetBtnStatus(QWidget* panel, int status);

    int btnRunStatus, btnRunAllStatus, btnExportStatus, btnScanCodeStatus;

private slots:
    void on_toolButton_4_clicked();

    void on_listWidget_currentRowChanged(int currentRow);    

    void on_btn_Run_clicked();

    void on_btn_About_clicked();

    void on_btn_Export_clicked();

    void on_btn_RunAll_clicked();

    void on_btn_Scan_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
