#include "dialog_newpbl.h"
#include "ui_dialog_newpbl.h"
#include<QFileDialog>
//#include<QDebug>

dialog_newpbl::dialog_newpbl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_newpbl)
{
    ui->setupUi(this);
}

dialog_newpbl::~dialog_newpbl()
{
    delete ui;
}

void dialog_newpbl::on_radBtn_Trad_clicked()
{
    ui->edt_inp->setEnabled(true);
    ui->edt_out->setEnabled(true);
    ui->edt_inp->setText(ui->edt_prob->text()+".in");
    ui->edt_out->setText(ui->edt_prob->text()+".out");
    QString tmpStr;
    tmpStr=ui->edt_prob->text();
    if(ui->ckBox_Maple->isChecked() && ui->ckBox_MMA->isChecked())
        ui->lbl_src_suf->setText(".mpl/.wls");
    else
        if (ui->ckBox_Maple->isChecked())
            ui->lbl_src_suf->setText(".mpl");
        else
            if (ui->ckBox_MMA->isChecked())
                ui->lbl_src_suf->setText(".wls");
            else
                ui->lbl_src_suf->setText(".");
    ui->edt_src->setText(tmpStr);
    ui->edt_spj->setText("Unable to set SPJ due to problem type");
    ui->edt_spj->setEnabled(false);
    ui->btn_spj->setEnabled(false);
    ui->lbl_spj->setText("Special Judge");
}

void dialog_newpbl::on_pushButton_clicked()
{
    emit dlgRet(ui->edt_prob->text(),
                ui->radBtn_spj->isChecked()*3+ui->radBtn_Intr->isChecked()*2+ui->radBtn_Trad->isChecked()*1,
                ui->ckBox_Maple->isChecked()*2+ui->ckBox_MMA->isChecked()*1,
                ui->edt_inp->text(),
                ui->edt_src->text(),
                ui->edt_out->text(),
                ui->edt_spj->text(),
                ui->edt_score->text().toInt());
    close();
}

void dialog_newpbl::on_buttonBox_accepted()
{
    emit dlgRet(ui->edt_prob->text(),
                ui->radBtn_spj->isChecked()*3+ui->radBtn_Intr->isChecked()*2+ui->radBtn_Trad->isChecked()*1,
                ui->ckBox_Maple->isChecked()*2+ui->ckBox_MMA->isChecked()*1,
                ui->edt_inp->text(),
                ui->edt_src->text(),
                ui->edt_out->text(),
                ui->edt_spj->text(),
                ui->edt_score->text().toInt());
    close();
}

QString dialog_newpbl::dlg_getSpj(){
    return ui->edt_spj->text();
}

QString dialog_newpbl::dlg_getInpF(){
    return ui->edt_inp->text();
}

QString dialog_newpbl::dlg_getOutF(){
    return ui->edt_out->text();
}

void dialog_newpbl::on_ckBox_Maple_clicked()
{
    QString tmpStr;
    tmpStr=ui->edt_prob->text();
    if(ui->ckBox_Maple->isChecked() && ui->ckBox_MMA->isChecked())
        ui->lbl_src_suf->setText(".mpl/.wls");
    else
        if (ui->ckBox_Maple->isChecked())
            ui->lbl_src_suf->setText(".mpl");
        else
            if (ui->ckBox_MMA->isChecked())
                ui->lbl_src_suf->setText(".wls");
            else
                ui->lbl_src_suf->setText(".");
    ui->edt_src->setText(tmpStr);
}

void dialog_newpbl::on_ckBox_MMA_clicked()
{
    QString tmpStr;
    tmpStr=ui->edt_prob->text();
    if(ui->ckBox_Maple->isChecked() && ui->ckBox_MMA->isChecked())
        ui->lbl_src_suf->setText(".mpl/.wls");
    else
        if (ui->ckBox_Maple->isChecked())
            ui->lbl_src_suf->setText(".mpl");
        else
            if (ui->ckBox_MMA->isChecked())
                ui->lbl_src_suf->setText(".wls");
            else
                ui->lbl_src_suf->setText(".");
    ui->edt_src->setText(tmpStr);
}

void dialog_newpbl::on_radBtn_Intr_clicked()
{
    //ui->edt_inp->setEnabled(false);
    ui->edt_out->setEnabled(false);
    ui->edt_inp->setText(ui->edt_prob->text()+".in");
    ui->edt_out->setText("Unable to set output due to problem type");
    ui->edt_spj->setEnabled(true);
    ui->edt_spj->setText(ui->edt_prob->text()+"_spj");
    ui->lbl_spj->setText("Interactor");
    ui->btn_spj->setEnabled(true);
    QString tmpStr;
    tmpStr=ui->edt_prob->text();
    if(ui->ckBox_Maple->isChecked() && ui->ckBox_MMA->isChecked())
        ui->lbl_src_suf->setText(".mpl/.wls");
    else
        if (ui->ckBox_Maple->isChecked())
            ui->lbl_src_suf->setText(".mpl");
        else
            if (ui->ckBox_MMA->isChecked())
                ui->lbl_src_suf->setText(".wls");
            else
                ui->lbl_src_suf->setText(".");
    ui->edt_src->setText(tmpStr);
}

void dialog_newpbl::on_btn_src_dir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,"Source Code Directory",".");
    ui->edt_src_dir->setText(dir);
    QDir directory(dir);
    directory.setFilter(QDir::Dirs|QDir::Files);
    directory.setSorting(QDir::DirsFirst);
    QFileInfoList lst= directory.entryInfoList();
    int i=0;
    num_source=0;
    do{
        QFileInfo fi=lst.at(i);
        if (fi.fileName()=="."|| fi.fileName()==".."){
            i++;
            continue;
        }
        if (fi.isDir()){
            if (ui->ckBox_Maple->isChecked()){
                QFileInfo f2;
                f2.setFile(dir+"/"+fi.fileName()+"/"+ui->edt_src->text()+".mpl");
                //qDebug()<<dir+"/"+fi.fileName()+"/"+ui->edt_src->text()+".mpl"<<f2.isFile()<<endl;
                if (f2.isFile()){
                    num_source++;
                    i++;
                    continue;
                }
            }
            if (ui->ckBox_MMA->isChecked()){
                QFileInfo f2;
                f2.setFile(dir+"/"+fi.fileName()+"/"+ui->edt_src->text()+".wls");
                //qDebug()<<dir+"/"+fi.fileName()+"/"+ui->edt_src->text()+".mpl"<<f2.isFile()<<endl;
                if (f2.isFile()){
                    num_source++;
                    i++;
                    continue;
                }
            }
        }
        i++;
    }while(i<lst.size());
    if (num_source!=0){
        ui->lbl_src_cnt->setText(QString::number(num_source)+" codes found");
    }
}

int dialog_newpbl::get_Data_num(){
    return num_data;
}

int dialog_newpbl::get_Source_num(){
    return num_source;
}

int dialog_newpbl::get_Prob_Type(){
    return ui->radBtn_spj->isChecked()*3+ui->radBtn_Intr->isChecked()*2+ui->radBtn_Trad->isChecked()*1;
}

void dialog_newpbl::on_btn_src_dir_2_clicked()
{

}

void dialog_newpbl::on_btn_data_dir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(NULL,"Test Data Directory",".");
    ui->edt_data_dir->setText(dir);
    if(get_Prob_Type()!=2){
        int i,dot_pos1,dot_pos2;
        QString in_prefix, in_suffix, inf, out_prefix, out_suffix, outf;
        inf= ui->edt_inp->text();
        outf=ui->edt_out->text();
        dot_pos1=inf.lastIndexOf(".");
        in_prefix=inf.left(dot_pos1);
        in_suffix=inf.right(inf.length()-dot_pos1);
        dot_pos2=outf.lastIndexOf(".");
        out_prefix=outf.left(dot_pos2);
        out_suffix=outf.right(outf.length()-dot_pos2);
        //qDebug()<<in_prefix<<";"<<in_suffix<<";"<<out_prefix<<";"<<out_suffix<<endl;
        for (i=1;;i++) {
            QFileInfo f1,f2;
            f2.setFile(dir+"/"+out_prefix+QString::number(i)+out_suffix);
            f1.setFile(dir+"/"+in_prefix+QString::number(i)+in_suffix);
            //qDebug()<<dir+"/"+in_prefix+QString::number(i)+in_suffix<<f1.isFile()<<endl;
            //qDebug()<<dir+"/"+out_prefix+QString::number(i)+out_suffix<<f2.isFile()<<endl;
            if (not (f1.isFile() && f2.isFile()))
                break;
        }
        num_data=i-1;
        if (num_data!=0){
            ui->edt_score->setText(QString::number(100/num_data));
            ui->lbl_data_cnt->setText(QString::number(num_data)+" data files found");
        }
    }
    else{
        int i,dot_pos1;
        QString in_prefix, in_suffix, inf;
        inf= ui->edt_inp->text();

        dot_pos1=inf.lastIndexOf(".");
        in_prefix=inf.left(dot_pos1);
        in_suffix=inf.right(inf.length()-dot_pos1);

        for(i=1;;i++){
            QFileInfo f1;
            f1.setFile(dir+"/"+in_prefix+QString::number(i)+in_suffix);
            if (not f1.isFile())
                break;
        }
        num_data=i-1;
        if (num_data!=0){
            ui->edt_score->setText(QString::number(100/num_data));
            ui->lbl_data_cnt->setText(QString::number(num_data)+" data files found");
        }
    }
}

QString dialog_newpbl::dlg_getSrc(){
    return ui->edt_src->text();
}

QString dialog_newpbl::get_Prob_name(){
    return ui->edt_prob->text();
}

int dialog_newpbl::get_Lang(){
    return ui->ckBox_Maple->isChecked()*2+ui->ckBox_MMA->isChecked()*1;
}

int dialog_newpbl::get_TL(){
    bool flag;
    return ui->edt_TL->text().toInt(&flag);
}

int dialog_newpbl::get_score(){
    bool flag;
    return ui->edt_score->text().toInt(&flag);
}

QString dialog_newpbl::get_code_dir(){
    return ui->edt_src_dir->text();
}

QString dialog_newpbl::get_data_dir(){
    return ui->edt_data_dir->text();
}

void dialog_newpbl::on_btn_spj_clicked()
{
    QString tmpStr;
    tmpStr=QFileDialog::getOpenFileName(this,"Select Special Judge","","Maple / Mathematica Source (*.mpl *.wls)");
    ui->edt_spj->setText(tmpStr.left(tmpStr.lastIndexOf(".")));
}
