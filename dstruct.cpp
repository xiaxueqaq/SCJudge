#include "dstruct.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>

QString QStudent::getName(){
    return _name;
}

int QStudent::getScore(){
    return  _score;
}

QString QStudent::getDetails(){
    return _details;
}

QString QStudent::getCode(){
    return _code;
}

vector<QString>* QStudent::getResults(){
    return &_results;
}

void QStudent::setResults(int index, QString res){
    _results[index]=res;
}

void QStudent::setName(QString str){
    _name=str;
}

void QStudent::setScore(int sc){
    _score=sc;
}

void QStudent::setDetails(QString str){
    _details=str;
}

void QStudent::setCode(QString codeDir){
    _code=codeDir;
}

QStudent::QStudent(QString name, int score, QString details, QString code){
    _name=name;
    _score=score;
    _details=details;
    _code=code;
    _results.resize(code.length());
}

QStudent::QStudent(){
    _name="";
    _score=-1;
    _details="";
    _code="";
}

QString QProblemData::getInput(){
    return  _input;
}

QString QProblemData::getOutput(){
    return _output;
}

int QProblemData::getScore(){
    return  _score;
}

int QProblemData::getTL(){
    return _timelimit;
}

void QProblemData::setInput(QString str){
    _input= str;
}

void QProblemData::setOutput(QString str){
    _output= str;
}

void QProblemData::setScore(int s){
    _score=s;
}

void QProblemData::setTL(int tl){
    _timelimit=tl;
}

QProblemData::QProblemData(QString input, QString output, int score, int tl){
    _input=input;
    _output=output;
    _score=score;
    _timelimit=tl;
}


QString QProblem::getName(){
    return _name;
}

QString QProblem::getInput(){
    return _input;
}

QString QProblem::getOutput(){
    return _output;
}

QString QProblem::getSpj(){
    return  _spj;
}

QString QProblem::getSource(){
    return _source;
}

int QProblem::getType(){
    return _type;
}

int QProblem::getLang(){
    return _lang;
}

void QProblem::setName(QString str){
    _name=str;
}

void QProblem::setInput(QString str){
    _input=str;
}

void QProblem::setOutput(QString str){
    _output=str;
}

void QProblem::setSpj(QString str){
    _spj=str;
}

void QProblem::setSource(QString str){
    _source=str;
}

void QProblem::setType(int t){
    _type=t;
}

void QProblem::setLang(int l){
    _lang=l;
}

void QProblem::AddData(QString strIn, QString strOut, int score, int TL){
    QProblemData* d=new QProblemData(strIn,strOut,score,TL);
    _data.push_back(d);
    //_data.push_back(QProblemData(strIn,strOut,score,TL));
}

void QProblem::AddStudent(QString name, int score, QString details, QString code){
    QStudent* s=new QStudent(name,score,details,code);
    _student.push_back(s);
}

vector<QProblemData*>* QProblem::getData(){
    return &_data;
}

vector<QStudent*>* QProblem::getStudent(){
    return &_student;
}

QProblem::QProblem(QString name, QString input, QString output, QString src, QString spj,int TYPE,int LANG){
    _name=name;
    _input=input;
    _output=output;
    _source=src;
    _spj=spj;
    _type=TYPE;
    _lang=LANG;
}

QProblem::QProblem(QString fromFile){
    int cnt;
    QFile fp(fromFile);
    if(fp.open(QFile::ReadOnly)){
        QTextStream i_str(&fp);
        _name=i_str.readLine();
        _type=i_str.readLine().toInt();
        _lang=i_str.readLine().toInt();
        _input=i_str.readLine();
        _output=i_str.readLine();
        _source=i_str.readLine();
        _spj=i_str.readLine();
        cnt=i_str.readLine().toInt();
        //qDebug()<<"IStream returns cnt="<<cnt<<_name<<_type<<_lang<<_input<<_output<<_source<<_spj;
        for(int i=0;i<cnt;i++){
            QString tmpStr,tmpInput,tmpOutput;
            int tmpScore, tmpTL;
            tmpStr=i_str.readLine(); //parse here
            int idx=tmpStr.indexOf('|');
            tmpInput=tmpStr.left(idx);
            int idx2=tmpStr.indexOf('|',idx+1);
            tmpOutput=tmpStr.mid(idx+1,idx2-idx-1);
            idx=idx2;
            idx2=tmpStr.indexOf('|',idx+1);
            tmpScore=tmpStr.mid(idx+1,idx2-idx-1).toInt();
            tmpTL=tmpStr.mid(idx2+1,-1).toInt();
            QProblemData *pd=new QProblemData(tmpInput,tmpOutput,tmpScore,tmpTL);
            //qDebug()<<tmpInput<<tmpOutput<<tmpScore<<tmpTL;
            _data.push_back(pd);
        }
        cnt=i_str.readLine().toInt();
        for(int i=0;i<cnt;i++){
            QString tmpStr;
            tmpStr=i_str.readLine();
            int idx=tmpStr.indexOf('|');
            QStudent* student=new QStudent;
            student->setName(tmpStr.left(idx));
            int idx2=tmpStr.indexOf('|',idx+1);
            student->setScore(tmpStr.mid(idx+1,idx2-idx-1).toInt());
            idx=idx2;
            idx2=tmpStr.indexOf('|',idx+1);
            student->setDetails(tmpStr.mid(idx+1,idx2-idx-1));
            idx=idx2;
            idx2=tmpStr.indexOf('|',idx+1);
            student->setCode(tmpStr.mid(idx+1,idx2-idx-1));
            for(int j=0;j<student->getDetails().length()-1;j++){
                idx=idx2;
                idx2=tmpStr.indexOf('|',idx+1);
                student->getResults()->push_back(tmpStr.mid(idx+1,idx2-idx-1)); // Actually QStudent leaks the control of _result, but whatever, who cares?
            }
            student->getResults()->push_back(tmpStr.mid(idx2+1,-1));
            _student.push_back(student);
        }
    }
}

QProblem::QProblem(){
    _name="Untitled Problem";
    _input="";
    _output="";
    _source="";
    _spj="";
    _type=0;
    _lang=0;
}

QProblem::~QProblem(){
    unsigned long long i;
    for(i=0;i<_data.size();i++){
        delete _data[i];
    }
    _data.clear();
    for(i=0;i<_student.size();i++){
        delete _student[i];
    }
    _student.clear();
}

void QProblem::SaveToFile(QString path){

    QFile fp(path);
    if (fp.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream out(&fp);
        out<<_name<<endl;
        out<<_type<<endl;
        out<<_lang<<endl;
        out<<_input<<endl;
        out<<_output<<endl;
        out<<_source<<endl;
        out<<_spj<<endl;
        out<<_data.size()<<endl;
        for(int i=0;0<-i+_data.size();i++){
            out<<_data[i]->getInput()<<"|"<<_data[i]->getOutput()<<"|"<<_data[i]->getScore()<<"|"<<_data[i]->getTL()<<endl;
        }
        out<<_student.size()<<endl;
        for(int i=0;0<-i+_student.size();i++){
            out<<_student[i]->getName()<<"|"<<_student[i]->getScore()<<"|"<<_student[i]->getDetails()<<"|"<<_student[i]->getCode();
            for(int j=0;0<-j+_student[i]->getDetails().length();j++){
                out<<"|"<<_student[i]->getResults()->at(j);
            }
            out<<endl;
        }

    }
}
