#ifndef DSTRUCT_H
#define DSTRUCT_H
#include<QString>
#include<vector>
using std::vector;

class QStudent{
public:
    QString getName();
    int getScore();
    QString getDetails();
    QString getCode();
    vector<QString>* getResults();
    void setName(QString);
    void setScore(int);
    void setDetails(QString);
    void setCode(QString);
    //void appendResults(QString res);
    void setResults(int index, QString res);

    QStudent(QString , int, QString, QString);
    QStudent();
    //~QStudent();

private:
        QString _name;
        int _score;
        QString _details;
        QString _code;
        vector<QString> _results;
};

class QProblemData{
public:
    QString getInput();
    QString getOutput();
    int getScore();
    int getTL();
    void setInput(QString);
    void setOutput(QString);
    void setScore(int);
    void setTL(int);
    QProblemData(QString, QString, int, int);

private:
    QString _input, _output;
    int _score, _timelimit;
};

class QProblem{
public:
    QString getName();
    QString getInput();
    QString getOutput();
    QString getSource();
    QString getSpj();
    int getType();
    int getLang();
    void setName(QString);
    void setInput(QString);
    void setOutput(QString);
    void setSource(QString);
    void setSpj(QString);
    void setType(int);
    void setLang(int);
    void AddData(QString, QString ,int, int);
    void AddStudent(QString, int, QString, QString);
    vector<QProblemData*>* getData();
    vector<QStudent*>* getStudent();
    void SaveToFile(QString path);
    QProblem(QString, QString , QString, QString,QString, int,int );
    QProblem(QString fromFile);
    QProblem();
    ~QProblem();

private:
    QString  _name;
    int _type,_lang;
    QString _input,_output,_source,_spj;
    vector<QProblemData*> _data;
    //vector<QProblemData> _data;
    vector<QStudent*> _student;
};


#endif // DSTRUCT_H
