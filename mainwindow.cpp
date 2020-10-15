#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_newpbl.h"
#include "dialog_about.h"
#include<QMessageBox>
#include<QFileDialog>
#include <QtWidgets/QGroupBox>
//#include "dstruct.h"
#include "checker.h"

#include<vector>
#include<QDebug>

using std::vector;

dialog_newpbl *dlg;
vector<QProblem*> ProblemSet;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);   
    //dlg=new dialog_newpbl(this);
    //connect(dlg,SIGNAL(dlgRet(QString,int,int,QString,QString,QString,QString,int,int)),this,SLOT(add_prob(QString,int,int,QString,QString,QString,QString,int,int)));
    Restore();
    SetBtnStatus(ui->wg_Run,btnUnknown);
    SetBtnStatus(ui->wg_RunAll,btnUnknown);
    SetBtnStatus(ui->wg_Export,btnUnknown);
    SetBtnStatus(ui->wg_Scan,btnUnknown);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString sPrb,sInp,sSrc,sOut,sSpj;
int pType, pScore, pLang=2;

void MainWindow::add_Prob(QString strProb,int Prob_type, int Lang, QString strInp, QString strSrc, QString strOut, QString strSpj, int score){
    sPrb=strProb;
    sInp=strInp;
    sSrc=strSrc;
    sOut=strOut;
    sSpj=strSpj;
    pType=Prob_type;
    pScore=score;
    pLang=Lang;
    QMessageBox::information(this,strProb,sPrb,QMessageBox::Yes);
}

void MainWindow::TableInputAdd(int rowNo, QString Inp, int TimeLimit, int Score, QString Outp, QString SPJ){
    QTableWidgetItem *item;
    item= new QTableWidgetItem(Inp,1001);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item->setBackgroundColor(QColor(255,255,255));
    ui->tableWidget_input->setItem(rowNo,0,item);
    item= new QTableWidgetItem(QString::number(TimeLimit,10),1002);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item->setBackgroundColor(QColor(255,255,255));
    ui->tableWidget_input->setItem(rowNo,1,item);
    item= new QTableWidgetItem(QString::number(Score,10),1003);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item->setBackgroundColor(QColor(255,255,255));
    ui->tableWidget_input->setItem(rowNo,2,item);
    item= new QTableWidgetItem(Outp,1004);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item->setBackgroundColor(QColor(255,255,255));
    ui->tableWidget_input->setItem(rowNo,3,item);
    item= new QTableWidgetItem(SPJ,1005);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item->setBackgroundColor(QColor(255,255,255));
    ui->tableWidget_input->setItem(rowNo,4,item);
}

void MainWindow::on_toolButton_4_clicked()
{
    dlg=new dialog_newpbl(this);
    if (dlg->exec()==QDialog::Accepted){
        //ui->tableWidget_input->clearContents();
        for(int i=ui->tableWidget_input->rowCount();i>=0;i--){
            ui->tableWidget_input->removeRow(i);
        }
        for(int i=ui->tableWidget_score->rowCount();i>=0;i--){
            ui->tableWidget_score->removeRow(i);
        }
        QProblem* ps= new QProblem(dlg->get_Prob_name(),dlg->dlg_getInpF(),dlg->dlg_getOutF(),dlg->dlg_getSrc(),dlg->dlg_getSpj(),dlg->get_Prob_Type(),dlg->get_Lang());
        sInp=dlg->dlg_getInpF();
        sOut=dlg->dlg_getOutF();
        sSpj=dlg->dlg_getSpj();
        //TableInputAdd(curRow, sInp, dlg->get_TL() , dlg->get_score(), sOut, sSpj);
        int i,dot_pos1,dot_pos2;
        QString in_prefix, in_suffix, inf, out_prefix, out_suffix, outf, dir;
        inf= dlg->dlg_getInpF();
        outf=dlg->dlg_getOutF();
        dot_pos1=inf.lastIndexOf(".");
        in_prefix=inf.left(dot_pos1);
        in_suffix=inf.right(inf.length()-dot_pos1);
        dot_pos2=outf.lastIndexOf(".");
        out_prefix=outf.left(dot_pos2);
        out_suffix=outf.right(outf.length()-dot_pos2);
        dir=dlg->get_data_dir();
        for (i=1;;i++) {
            QFileInfo f1,f2;
            f2.setFile(dir+"/"+out_prefix+QString::number(i)+out_suffix);
            f1.setFile(dir+"/"+in_prefix+QString::number(i)+in_suffix);
            if (not (f1.isFile() && (f2.isFile() || ps->getType()==2)))
                break;
            else{
                int curRow=ui->tableWidget_input->rowCount();
                ui->tableWidget_input->insertRow(curRow);
                TableInputAdd(curRow,dir+"/"+in_prefix+QString::number(i)+in_suffix,dlg->get_TL(),dlg->get_score(),dir+"/"+out_prefix+QString::number(i)+out_suffix,sSpj);
                ps->AddData(dir+"/"+in_prefix+QString::number(i)+in_suffix,dir+"/"+out_prefix+QString::number(i)+out_suffix,dlg->get_score(),dlg->get_TL());
            }
        }    
        int data_cnt;
        data_cnt=i-1;

        dir=dlg->get_code_dir();
        QDir directory(dir);
        directory.setFilter(QDir::Dirs|QDir::Files);
        directory.setSorting(QDir::DirsFirst);
        QFileInfoList lst= directory.entryInfoList();
        i=0;
        do{
            QFileInfo fi=lst.at(i);
            if (fi.fileName()=="."|| fi.fileName()==".."){
                i++;
                continue;
            }
            if (fi.isDir()){
                if (dlg->get_Lang()&0x2){
                    QFileInfo f2;
                    f2.setFile(dir+"/"+fi.fileName()+"/"+dlg->dlg_getSrc()+".mpl");
                    if (f2.isFile()){
                        i++;
                        int curRow=ui->tableWidget_score->rowCount();
                        ui->tableWidget_score->insertRow(curRow);
                        QString tmpStr;
                        tmpStr="";
                        for(int j=0;j<data_cnt;j++){
                            tmpStr=tmpStr+"U";
                        }
                        TableScoreAdd(curRow,fi.fileName(),-1,tmpStr);
                        ps->AddStudent(fi.fileName(),-1,tmpStr,dir+"/"+fi.fileName()+"/"+dlg->dlg_getSrc()+".mpl");
                        continue;
                    }
                }
                if (dlg->get_Lang()&0x1){
                    QFileInfo f2;
                    f2.setFile(dir+"/"+fi.fileName()+"/"+dlg->dlg_getSrc()+".wls");
                    if (f2.isFile()){
                        i++;
                        int curRow=ui->tableWidget_score->rowCount();
                        ui->tableWidget_score->insertRow(curRow);
                        QString tmpStr;
                        tmpStr="";
                        for(int j=0;j<data_cnt;j++){
                            tmpStr=tmpStr+"U";
                        }
                        TableScoreAdd(curRow,fi.fileName(),-1,tmpStr);
                        ps->AddStudent(fi.fileName(),-1,tmpStr,dir+"/"+fi.fileName()+"/"+dlg->dlg_getSrc()+".mpl");
                        continue;
                    }
                }
            }
            i++;
        }while(i<lst.size());
        ProblemSet.push_back(ps);
        QListWidgetItem* WI=new QListWidgetItem(ps->getName(),ui->listWidget);
        //WI->foreground().setColor(qRgb(226,226,226));
        //WI->background().setColor(qRgb(226,226,226));
        WI->setTextColor(qRgb(226,226,226));

        ui->listWidget->addItem(WI);
        ui->listWidget->setCurrentItem(WI);
        //ui->listWidget->addItem(ps->getName());
    }
    delete dlg;
}

void MainWindow::TableScoreAdd(int rowNo, QString name, int score, QString details){
    QTableWidgetItem *item;
    item = new QTableWidgetItem(name, 2001);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item->setBackgroundColor(QColor(255,255,255));
    ui->tableWidget_score->setItem(rowNo, 0, item);
    if (score>=0){
        item = new QTableWidgetItem(QString::number(score),2002);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item->setBackgroundColor(QColor(255,255,255));
        ui->tableWidget_score->setItem(rowNo,1,item);
    }
    else{
        item = new QTableWidgetItem("Score Unavailable yet",2002);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item->setBackgroundColor(QColor(255,255,255));
        ui->tableWidget_score->setItem(rowNo,1,item);
    }
    int i;
    QGroupBox *grBox;
    grBox= new QGroupBox();
    grBox->setStyleSheet("background-color:rgb(255,255,255);");

    for (i=0;i<details.length();i++){
        QRadioButton *radBtn;
        radBtn= new QRadioButton(grBox);
        radBtn->setGeometry((i)*25+10,10,20,20);
        radBtn->setCheckable(false);
        radBtn->setAutoExclusive(false);
        switch (details.toLocal8Bit()[i]){
        case 'U':{
            radBtn->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(150, 150, 150);border:2px solid white;}");
            break;
        }
        case 'A':{
            radBtn->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(59, 213, 31);border:2px solid white;}");
            break;
        }
        case 'W':{
            radBtn->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 17, 48);border:2px solid white;}");
            break;
        }
        case 'F':{
            radBtn->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 17, 48);border:2px solid white;}");
            break;
        }
        case 'R':{
            radBtn->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 17, 48);border:2px solid white;}");
            break;
        }
        case 'T':{
            radBtn->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 183, 38);border:2px solid white;}");
            break;
        }
        }
    }
    ui->tableWidget_score->setCellWidget(rowNo,2,grBox);
}

void MainWindow::TableScoreAdd(int rowNo, QStudent* student){
    QTableWidgetItem *item;
    item = new QTableWidgetItem(student->getName(), 2001);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item->setBackgroundColor(QColor(255,255,255));
    ui->tableWidget_score->setItem(rowNo, 0, item);
    if (student->getScore()>=0){
        item = new QTableWidgetItem(QString::number(student->getScore()),2002);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item->setBackgroundColor(QColor(255,255,255));
        ui->tableWidget_score->setItem(rowNo,1,item);
    }
    else{
        item = new QTableWidgetItem("Score Unavailable yet",2002);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item->setBackgroundColor(QColor(255,255,255));
        ui->tableWidget_score->setItem(rowNo,1,item);
    }
    int i;
    QGroupBox *grBox;
    grBox= new QGroupBox();
    grBox->setStyleSheet("background-color:rgb(255,255,255);");

    for (i=0;i<student->getDetails().length();i++){
        QRadioButton *radBtn;
        radBtn= new QRadioButton(grBox);
        radBtn->setGeometry((i)*25+10,10,20,20);
        radBtn->setCheckable(false);
        radBtn->setAutoExclusive(false);
        switch (student->getDetails().toLocal8Bit()[i]){
        case 'U':{
            radBtn->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(150, 150, 150);border:2px solid white;}");
            break;
        }
        case 'A':{
            radBtn->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(59, 213, 31);border:2px solid white;}");
            break;
        }
        case 'W':{
            radBtn->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 17, 48);border:2px solid white;}");
            break;
        }
        case 'F':{
            radBtn->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 17, 48);border:2px solid white;}");
            break;
        }
        case 'R':{
            radBtn->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 17, 48);border:2px solid white;}");
            break;
        }
        case 'T':{
            radBtn->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 183, 38);border:2px solid white;}");
            break;
        }
        }
        radBtn->setToolTip(student->getResults()->at(i));
    }
    ui->tableWidget_score->setCellWidget(rowNo,2,grBox);
}

void MainWindow::UpdateTable(int index){
    QProblem* problem;
    problem=ProblemSet[index];
    for(int i=ui->tableWidget_input->rowCount();i>=0;i--){
        ui->tableWidget_input->removeRow(i);
    }
    for(int i=ui->tableWidget_score->rowCount();i>=0;i--){
        ui->tableWidget_score->removeRow(i);
    }
    for (int i=0;0<problem->getData()->size()-i;i++) {
        ui->tableWidget_input->insertRow(i);
        TableInputAdd(i,problem->getData()->at(i)->getInput(),problem->getData()->at(i)->getTL(),problem->getData()->at(i)->getScore(),problem->getData()->at(i)->getOutput(),problem->getSpj());
    }
    for (int i=0;0<problem->getStudent()->size()-i;i++){
        ui->tableWidget_score->insertRow(i);
        //TableScoreAdd(i,problem->getStudent()->at(i)->getName(),problem->getStudent()->at(i)->getScore(),problem->getStudent()->at(i)->getDetails());
        TableScoreAdd(i,problem->getStudent()->at(i));
    }

}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    //qDebug()<<currentRow;
    UpdateTable(currentRow);
}

void MainWindow::on_btn_Run_clicked()
{   
    int curRow=ui->tableWidget_score->currentRow();
    if (curRow<0){
        SetBtnStatus(ui->wg_Run,btnError);
        return;        
    }
    ui->btn_Run->setEnabled(false);
    ui->btn_RunAll->setEnabled(false);
    SetBtnStatus(ui->wg_Run,btnRunning);
    QProblem* problem;
    problem=ProblemSet[ui->listWidget->currentRow()];
    vector<QProblemData*>* problem_data=problem->getData();
    QString src;
    src=problem->getSource();
    if (problem->getStudent()->at(curRow)->getCode().endsWith(".mpl",Qt::CaseInsensitive))
        src=src+".mpl";
    if (problem->getStudent()->at(curRow)->getCode().endsWith(".wls",Qt::CaseInsensitive))
        src=src+".wls";
    ui->tableWidget_score->removeCellWidget(curRow,2);
    QGroupBox *grBox;
    grBox= new QGroupBox();
    grBox->setStyleSheet("background-color:rgb(255,255,255);");
    vector<QRadioButton*> btn_lst;
    for(int i=0;0<problem_data->size()-i;i++){
        QRadioButton* radBtn;
        radBtn=new QRadioButton(grBox);
        radBtn->setGeometry((i)*25+10,10,20,20);
        radBtn->setCheckable(false);
        radBtn->setAutoExclusive(false);
        radBtn->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(26, 144, 255);border:2px solid white;}");
        btn_lst.push_back(radBtn);
    }
    ui->tableWidget_score->setCellWidget(curRow,2,grBox);
    QString ret_details;
    int final_score;
    final_score=0;
    ret_details=problem->getStudent()->at(curRow)->getDetails();
    for(int i=0;0<problem_data->size()-i;i++){
        checker grd(problem->getType(),problem->getInput(),problem->getOutput(),src,problem_data->at(i)->getInput() , problem_data->at(i)->getOutput() ,problem->getStudent()->at(curRow)->getCode(),problem->getSpj(),problem_data->at(i)->getTL());
        int ret=grd.check();
        switch(ret){
        case status_AC:{
            btn_lst[i]->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(59, 213, 31);border:2px solid white;}");
            ret_details[i]='A';
            final_score+=problem_data->at(i)->getScore();
            break;
        }
        case status_WA:{
            btn_lst[i]->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 17, 48);border:2px solid white;}");
            ret_details[i]='W';
            break;
        }
        case status_TLE:{
            btn_lst[i]->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 183, 38);border:2px solid white;}");
            ret_details[i]='T';
            break;
        }
        case status_RE:{
            btn_lst[i]->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 17, 48);border:2px solid white;}");
            ret_details[i]='R';
            break;
        }
        case status_JF:{
            btn_lst[i]->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 17, 48);border:2px solid white;}");
            ret_details[i]='F';
            break;
        }
        }
        qDebug()<<grd.getStatement();
        problem->getStudent()->at(curRow)->setResults(i,grd.getStatement());
        btn_lst[i]->setToolTip(grd.getStatement());
    }
    problem->getStudent()->at(curRow)->setDetails(ret_details);
    qDebug()<<ret_details;
    problem->getStudent()->at(curRow)->setScore(final_score);
    QTableWidgetItem* item= ui->tableWidget_score->item(curRow,1);
    item->setText(QString::number(final_score));
    ui->btn_Run->setEnabled(true);
    ui->btn_RunAll->setEnabled(true);
    SetBtnStatus(ui->wg_Run,btnDone);
}

void MainWindow::on_btn_About_clicked()
{
    dialog_about* dlg_abt;
    dlg_abt=new dialog_about(this);
    dlg_abt->exec();
    delete dlg_abt;
}

void MainWindow::ExportScore(int index, QString filename){
    QProblem* problem;
    problem=ProblemSet[index];
    FILE *csv;
    csv=fopen(filename.toLocal8Bit().data(),"w");
    fprintf(csv,"sep=;\n");
    for(int i=0;0<-i+problem->getStudent()->size();i++){
        fprintf(csv,"%s;%d;%s",problem->getStudent()->at(i)->getName().toLocal8Bit().data(),
                               problem->getStudent()->at(i)->getScore(),
                               problem->getStudent()->at(i)->getDetails().toLocal8Bit().data()
                );
        for(int j=0;j<problem->getStudent()->at(i)->getDetails().length();j++){
            fprintf(csv,";%s",problem->getStudent()->at(i)->getResults()->at(j).toLocal8Bit().data());
        }
        fprintf(csv,"\n");

    }
    fclose(csv);
}
void MainWindow::on_btn_Export_clicked()
{
    if (ui->listWidget->currentRow()<0){
        SetBtnStatus(ui->wg_Export, btnError);
        return;
    }
    SetBtnStatus(ui->wg_Export,btnRunning);
    QString toExport=QFileDialog::getSaveFileName(this,"Export Score To","","Comma Separated Values (*.csv)");
    if (toExport!=""){
        ExportScore(ui->listWidget->currentRow(),toExport);
        SetBtnStatus(ui->wg_Export,btnDone);
    }
    else{
        SetBtnStatus(ui->wg_Export,btnCancelled);
    }
}

void MainWindow::on_btn_RunAll_clicked()
{
    if (ui->listWidget->currentRow()<0){
        SetBtnStatus(ui->wg_RunAll,btnError);
        return;
    }
    SetBtnStatus(ui->wg_RunAll,btnRunning);
    ui->btn_Run->setEnabled(false);
    ui->btn_RunAll->setEnabled(false);
    QProblem* problem;    
    problem=ProblemSet[ui->listWidget->currentRow()];
    for(int j=0;0<-j+problem->getStudent()->size();j++){

        vector<QProblemData*>* problem_data=problem->getData();
        QString src;
        src=problem->getSource();
        if (problem->getStudent()->at(j)->getCode().endsWith(".mpl",Qt::CaseInsensitive))
            src=src+".mpl";
        if (problem->getStudent()->at(j)->getCode().endsWith(".wls",Qt::CaseInsensitive))
            src=src+".wls";
        ui->tableWidget_score->removeCellWidget(j,2);
        QGroupBox *grBox;
        grBox= new QGroupBox();
        grBox->setStyleSheet("background-color:rgb(255,255,255);");
        vector<QRadioButton*> btn_lst;
        for(int i=0;0<problem_data->size()-i;i++){
            QRadioButton* radBtn;
            radBtn=new QRadioButton(grBox);
            radBtn->setGeometry((i)*25+10,10,20,20);
            radBtn->setCheckable(false);
            radBtn->setAutoExclusive(false);
            radBtn->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(26, 144, 255);border:2px solid white;}");
            btn_lst.push_back(radBtn);
        }
        ui->tableWidget_score->setCellWidget(j,2,grBox);
        QString ret_details;
        int final_score;
        final_score=0;
        ret_details=problem->getStudent()->at(j)->getDetails();
        for(int i=0;0<problem_data->size()-i;i++){
            checker grd(problem->getType(),problem->getInput(),problem->getOutput(),src,problem_data->at(i)->getInput() , problem_data->at(i)->getOutput() ,problem->getStudent()->at(j)->getCode(),problem->getSpj(),problem_data->at(i)->getTL());
            int ret=grd.check();
            switch(ret){
            case status_AC:{
                btn_lst[i]->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(59, 213, 31);border:2px solid white;}");
                ret_details[i]='A';
                final_score+=problem_data->at(i)->getScore();
                break;
            }
            case status_WA:{
                btn_lst[i]->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 17, 48);border:2px solid white;}");
                ret_details[i]='W';
                break;
            }
            case status_TLE:{
                btn_lst[i]->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 183, 38);border:2px solid white;}");
                ret_details[i]='T';
                break;
            }
            case status_RE:{
                btn_lst[i]->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 17, 48);border:2px solid white;}");
                ret_details[i]='R';
                break;
            }
            case status_JF:{
                btn_lst[i]->setStyleSheet("QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:rgb(59, 213, 31);border:2px solid white;}QRadioButton::indicator:unchecked {background-color:rgb(255, 17, 48);border:2px solid white;}");
                ret_details[i]='F';
                break;
            }
            }
            qDebug()<<grd.getStatement();
            problem->getStudent()->at(j)->setResults(i,grd.getStatement());
            btn_lst[i]->setToolTip(grd.getStatement());
        }
        problem->getStudent()->at(j)->setDetails(ret_details);
        qDebug()<<ret_details;
        problem->getStudent()->at(j)->setScore(final_score);
        QTableWidgetItem* item= ui->tableWidget_score->item(j,1);
        item->setText(QString::number(final_score));
    }
    ui->btn_Run->setEnabled(true);
    ui->btn_RunAll->setEnabled(true);
    SetBtnStatus(ui->wg_RunAll,btnDone);
}

void MainWindow::Restore(){
    QFile fp("problem.log");
    if(fp.exists()&&fp.open(QFile::ReadOnly)){
        QTextStream i_str(&fp);
        QString tmpStr=i_str.readLine();
        while (tmpStr!=""){
            QProblem* p=new QProblem(tmpStr);
            ProblemSet.push_back(p);
            tmpStr=i_str.readLine();
            QListWidgetItem* WI=new QListWidgetItem(p->getName(),ui->listWidget);
            WI->setTextColor(qRgb(226,226,226));
            ui->listWidget->addItem(WI);
        }
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
        //UpdateTable(ui->listWidget->count()-1);
    }

}

void MainWindow::Save(){
    FILE *fs;
    fs=fopen("problem.log","w");
    for(int i=0;0<-i+ProblemSet.size();i++){
        //qDebug()<<i<<" -th problem being dumped.";
        fprintf(fs,"%s\n",(ProblemSet[i]->getName()+"/"+ProblemSet[i]->getName()+".log").toLocal8Bit().data());
        QDir d=QDir(QDir::currentPath()+"/"+ProblemSet[i]->getName());
        if (not d.exists()){
            d.mkdir(QDir::currentPath()+"/"+ProblemSet[i]->getName());
        }
        ProblemSet[i]->SaveToFile(ProblemSet[i]->getName()+"/"+ProblemSet[i]->getName()+".log");
    }

    fclose(fs);
}

void MainWindow::closeEvent(QCloseEvent *event){
    Save();
    event->accept();
}

void MainWindow::on_btn_Scan_clicked()
{
    //Save();
}

void MainWindow::SetBtnStatus(QWidget *panel, int status){
    switch(status){
    case btnDone:{
        panel->setStyleSheet("background-color: rgb(80,223,32);");
        break;
    }
    case btnRunning:{
        panel->setStyleSheet("background-color: rgb(32,128,223);");
        break;
    }
    case btnError:{
        panel->setStyleSheet("background-color: rgb(213,4,7);");
        break;
    }
    case btnUnknown:{
        panel->setStyleSheet("background-color: rgb(130, 130, 130);");
        break;
    }
    case btnCancelled:{
        panel->setStyleSheet("background-color: rgb(255,190,24)");
        break;
    }
    }
}
