#ifndef CHECKER_H
#define CHECKER_H
#include<QString>
#include<QtCore>
#include<QDebug>
#include<QProcess>

#ifdef WIN32
#include <windows.h>

extern "C" {
    typedef struct _PROCESS_MEMORY_COUNTERS {
        DWORD cb;
        DWORD PageFaultCount;
        DWORD PeakWorkingSetSize;
        DWORD WorkingSetSize;
        DWORD QuotaPeakPagedPoolUsage;
        DWORD QuotaPagedPoolUsage;
        DWORD QuotaPeakNonPagedPoolUsage;
        DWORD QuotaNonPagedPoolUsage;
        DWORD PagefileUsage;
        DWORD PeakPagefileUsage;
    } PROCESS_MEMORY_COUNTERS,*PPROCESS_MEMORY_COUNTERS;

    typedef struct _PROCESS_MEMORY_COUNTERS_EX {
        DWORD cb;
        DWORD PageFaultCount;
        DWORD PeakWorkingSetSize;
        DWORD WorkingSetSize;
        DWORD QuotaPeakPagedPoolUsage;
        DWORD QuotaPagedPoolUsage;
        DWORD QuotaPeakNonPagedPoolUsage;
        DWORD QuotaNonPagedPoolUsage;
        DWORD PagefileUsage;
        DWORD PeakPagefileUsage;
        DWORD PrivateUsage;
    } PROCESS_MEMORY_COUNTERS_EX,*PPROCESS_MEMORY_COUNTERS_EX;

    BOOL WINAPI GetProcessMemoryInfo(HANDLE,PPROCESS_MEMORY_COUNTERS,DWORD);
}

#endif

enum ResultState {status_AC, status_WA, status_TLE, status_RE, status_JF};
//Accepted, Wrong Answer, Time Limit Exceed, Runtime Error, Judgement Failure

class checker{
public:
    void setInput(QString);
    void setOutput(QString);
    void setSource(QString);
    void setInputData(QString);
    void setAnswer(QString);
    void setCode(QString);
    void setTimeLimit(int);
    QString getStatement();
    int check();
    checker(int type, QString input, QString output, QString source, QString inputData, QString answer, QString code, QString spj, int TL);
    checker();

private:
    QString _input,_output,_source,_inputData,_answer,_code,_spj,_statement;
    int _timelimit, _type;
    int CompareOutput();
    void ConcatFile(QString, QString, QString);
    int JudgeTrad();
    int JudgeIntr();
    int JudgeSPJ();

};

void checker::setInput(QString input){
    _input=input;
}

void checker::setOutput(QString output){
    _output=output;
}

void checker::setSource(QString source){
    _source=source;
}

void checker::setCode(QString code){
    _code=code;
}

void checker::setInputData(QString inputData){
    _inputData=inputData;
}

void checker::setAnswer(QString answer){
    _answer=answer;
}

void checker::setTimeLimit(int TL){
    _timelimit=TL;
}

QString checker::getStatement(){
    return _statement;
}

checker::checker(int type, QString input, QString output, QString source, QString inputData, QString answer, QString code, QString spj, int TL){
    _type=type;
    _input=input;
    _output=output;
    _source=source;
    _inputData=inputData;
    _answer=answer;
    _code=code;
    _spj=spj;
    _timelimit=TL;
}

checker::checker(){
    _type=0;
    _input="";
    _output="";
    _source="";
    _inputData="";
    _answer="";
    _code="";
    _spj="";
    _timelimit=MAXLONG;
}

int checker::CompareOutput(){
    //qDebug()<<_output.toLocal8Bit().data()<<";"<<_answer;
    QString curDir=qApp->applicationDirPath();
    FILE *OP=fopen((curDir+'\\'+_output).toLocal8Bit().data(),"r");
    if (OP==NULL){
        _statement="Cannot open the output";
        return status_JF;
    }
    FILE *std=fopen(_answer.toLocal8Bit().data(),"r");
    if (std==NULL){
        _statement="Cannot open the standard output";
        return status_JF;
    }
    char ch1='\n', ch2='\n';
    char str1[20],str2[20];
    int flag1, flag2;
    while(true){
        if(ch1=='\n'||ch1=='\r'||ch1==EOF){
            if (ch1=='\r'){
                ch1=fgetc(OP);
                if (ch1=='\n')
                    ch1=fgetc(OP);
            }
            else
                ch1=fgetc(OP);
            while (ch1==' ' || ch1== '\t'){
                ch1=fgetc(OP);
            }
            flag1=2;
        }
        else{
            if(ch1==' '|| ch1=='\t'){
                while (ch1==' '||ch1=='\t'){
                    ch1=fgetc(OP);
                }
                if(ch1=='\n'||ch1=='\r'||ch1==EOF){
                    if (ch1=='\r'){
                        ch1=fgetc(OP);
                        if (ch1=='\n')
                            ch1=fgetc(OP);
                    }
                    else
                        ch1=fgetc(OP);
                    while (ch1==' ' || ch1== '\t'){
                        ch1=fgetc(OP);
                    }
                    flag1=2;
                }
                else{
                    flag1=1;
                }
            }
            else{
                flag1=0;
            }
        }

        if(ch2=='\n'||ch2=='\r'||ch2==EOF){
            if (ch2=='\r'){
                ch2=fgetc(std);
                if (ch2=='\n')
                    ch2=fgetc(std);
            }
            else
                ch2=fgetc(std);
            while (ch2==' ' || ch2== '\t'){
                ch2=fgetc(std);
            }
            flag2=2;
        }
        else{
            if(ch2==' '|| ch2=='\t'){
                while (ch2==' '||ch2=='\t'){
                    ch2=fgetc(std);
                }
                if(ch2=='\n'||ch2=='\r'||ch2==EOF){
                    if (ch2=='\r'){
                        ch2=fgetc(std);
                        if (ch2=='\n')
                            ch2=fgetc(std);
                    }
                    else
                        ch2=fgetc(std);
                    while (ch2==' ' || ch2== '\t'){
                        ch2=fgetc(std);
                    }
                    flag2=2;
                }
                else{
                    flag2=1;
                }
            }
            else{
                flag2=0;
            }
        }

        if(flag1!=flag2){
            _statement="Presentation Error";
            fclose(OP);
            fclose(std);
            return status_WA;
        }

        int len1 = 0;
        while (len1 < 10) {
            if (ch1 != ' ' && ch1 != '\t' && ch1 != '\n' && ch1 != '\r' && ch1 != EOF) {
                str1[len1 ++] = ch1;
            } else {
                break;
            }
            ch1 = fgetc(OP);
        }
        str1[len1] = '\0';

        int len2 = 0;
        while (len2 < 10) {
            if (ch2 != ' ' && ch2 != '\t' && ch2 != '\n' && ch2 != '\r' && ch2 != EOF) {
                str2[len2 ++] = ch2;
            } else {
                break;
            }
            ch2 = fgetc(std);
        }
        str2[len2] = '\0';

        if(len1!=len2 || strcmp(str1,str2)!=0){
            _statement=QString("Read %1 but expect %2").arg(str1).arg(str2);
            fclose(OP);
            fclose(std);
            return status_WA;
        }

        if(ch1==EOF && ch2==EOF)
            break;
        QCoreApplication::processEvents();
    }
    fclose(OP);
    fclose(std);
    _statement="OK! Answer Accepted!";
    return status_AC;
}

void checker::ConcatFile(QString inFile1, QString inFile2, QString Target)
{
    /*
    FILE *p1, *p2, *ptar;
    qDebug()<<inFile1.toLocal8Bit().data()<<inFile2.toLocal8Bit().data();
    p1=fopen(inFile1.toLocal8Bit().data(),"rb");
    p2=fopen(inFile2.toLocal8Bit().data(),"rb");
    ptar=fopen(Target.toLocal8Bit().data(),"wb");
    char ch;
    ch=getc(p1);
    while(ch!=EOF){
        putc(ch,ptar);
        ch=getc(p1);
    }
    ch=getc(p2);
    while(ch!=EOF){
        putc(ch,ptar);
        ch=getc(p2);
    }
    fclose(p1);
    fclose(p2);
    fclose(ptar);
    */
    QFile p1(inFile1);
    QFile p2(inFile2);
    QFile ptar(Target);
    if(p1.open(QFile::ReadOnly)&&p2.open(QFile::ReadOnly)&&ptar.open(QFile::WriteOnly)){
        while (not p1.atEnd()){
            ptar.write(p1.readLine());
        }
        while (not p2.atEnd()){
            ptar.write(p2.readLine());
        }
    }


}

int checker::JudgeTrad(){
#ifdef WIN32
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES sa;

    ZeroMemory(&si,sizeof (si));
    si.cb=sizeof(si);
    si.dwFlags=STARTF_USESTDHANDLES;
    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&sa, sizeof(sa));
    sa.bInheritHandle= TRUE ;
    QString curDir;
    curDir=qApp->applicationDirPath();
    //qDebug()<<curDir;
    si.hStdInput=GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = CreateFile((const WCHAR*)((curDir + "\\_tmpout").utf16()), GENERIC_WRITE,
                               FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, &sa,
                               CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    si.hStdError = CreateFile((const WCHAR*)((curDir + "\\_tmperr").utf16()), GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, &sa,
                              CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    QProcessEnvironment env=QProcessEnvironment::systemEnvironment();
    QString values = env.toStringList().join('\0')+'\0';    

    QFileInfo fii(curDir+"/"+_input);
    QFileInfo fis(curDir+"/"+_source);
    if(fii.exists())
        while (true){
            if (DeleteFile((WCHAR*)((curDir+"/"+_input).utf16())))
                break;
            QCoreApplication::processEvents();
            Sleep(100);
            qDebug()<<"Waiting for deleting input";
        }
    if(fis.exists())
        while (true){
            if (DeleteFile((WCHAR*)((curDir+"/"+_source).utf16())))
                break;
            QCoreApplication::processEvents();
            Sleep(100);
            qDebug()<<"Waiting for deleting source";
        }
    QFile::copy(_inputData,curDir+"/"+_input);
    QFile::copy(_code,curDir+"/"+_source);
    if(_code.endsWith(".mpl",Qt::CaseInsensitive)){
        if(!CreateProcess(NULL,(WCHAR*)(QString("cmaple "+curDir+"\\"+_source).utf16()),NULL,&sa,
                          TRUE, HIGH_PRIORITY_CLASS | CREATE_NO_WINDOW, /*(LPVOID)(values.toLocal8Bit().data())*/ NULL,(const WCHAR*)(curDir.utf16()), &si, &pi)){
            _statement="Unable to start process cmaple, Judgement terminated. Exitcode="+QString::number(GetLastError());
            QFile::remove(curDir+"/"+_input);
            QFile::remove(curDir+"/"+_source);
            return status_JF;
        }
    }
    if(_code.endsWith(".wls",Qt::CaseInsensitive)){
        if(!CreateProcess(NULL,(WCHAR*)(QString("wolframscript "+curDir+"\\"+_source).utf16()),NULL,&sa,
                          TRUE, HIGH_PRIORITY_CLASS | CREATE_NO_WINDOW, /*(LPVOID)(values.toLocal8Bit().data())*/ NULL,(const WCHAR*)(curDir.utf16()), &si, &pi)){
            _statement="Unable to start process wolframscript, Judgement terminated. Exitcode="+QString::number(GetLastError());
            QFile::remove(curDir+"/"+_input);
            QFile::remove(curDir+"/"+_source);
            return status_JF;
        }
    }
    bool flag;
    flag=false;
    QElapsedTimer timer;
    timer.start();

    while (timer.elapsed()<=_timelimit*1000){
        if (WaitForSingleObject(pi.hProcess,0)==WAIT_OBJECT_0){
            flag = true;
            break;
        }
        QCoreApplication::processEvents();
        Sleep(10);
    }

    if(!flag){
        TerminateProcess(pi.hProcess,0);

        //CloseHandle(si.hStdInput);
        CloseHandle(si.hStdError);
        CloseHandle(si.hStdOutput);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        _statement="Time Limit Exceeded, expect: "+QString::number(_timelimit)+"s";
        QFile qf;
        if(fii.exists())
            while (true){
                if (DeleteFile((WCHAR*)((curDir+"/"+_input).utf16())))
                    break;
                QCoreApplication::processEvents();
                Sleep(100);
                qDebug()<<"Waiting for deleting input";
            }
        if(fis.exists())
            while (true){
                if (DeleteFile((WCHAR*)((curDir+"/"+_source).utf16())))
                    break;
                QCoreApplication::processEvents();
                Sleep(100);
                qDebug()<<"Waiting for deleting source";
            }
        return status_TLE;
    }
    unsigned long exitCode;
    GetExitCodeProcess(pi.hProcess,&exitCode);
    if (exitCode!=0){
        CloseHandle(si.hStdError);
        CloseHandle(si.hStdOutput);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        _statement="Runtime Error, ExitCode="+QString::number(exitCode);
        QFile::remove(curDir+"/"+_input);
        QFile::remove(curDir+"/"+_source);
        return status_RE;
    }
    CloseHandle(si.hStdError);
    CloseHandle(si.hStdOutput);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    int ret=CompareOutput();
    QFile::remove(curDir+"/"+_input);
    QFile::remove(curDir+"/"+_source);
    QFile::remove(curDir+"/"+_output);
    return ret;
#endif

}

int checker::JudgeIntr(){
#ifdef WIN32
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES sa;

    ZeroMemory(&si,sizeof (si));
    si.cb=sizeof(si);
    si.dwFlags=STARTF_USESTDHANDLES;
    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&sa, sizeof(sa));
    sa.bInheritHandle= TRUE ;
    QString curDir;
    curDir=qApp->applicationDirPath();
    //qDebug()<<curDir;
    si.hStdInput=GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = CreateFile((const WCHAR*)((curDir + "\\_tmpout").utf16()), GENERIC_WRITE,
                               FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, &sa,
                               CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    si.hStdError = CreateFile((const WCHAR*)((curDir + "\\_tmperr").utf16()), GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, &sa,
                              CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    QProcessEnvironment env=QProcessEnvironment::systemEnvironment();
    QString values = env.toStringList().join('\0')+'\0';

    QFileInfo fii(curDir+"/"+_input);
    QFileInfo fis(curDir+"/"+_source);
    if(fii.exists())
        while (true){
            if (DeleteFile((WCHAR*)((curDir+"/"+_input).utf16())))
                break;
            QCoreApplication::processEvents();
            Sleep(100);
            qDebug()<<"Waiting for deleting input";
        }
    if(fis.exists())
        while (true){
            if (DeleteFile((WCHAR*)((curDir+"/"+_source).utf16())))
                break;
            QCoreApplication::processEvents();
            Sleep(100);
            qDebug()<<"Waiting for deleting source";
        }
    QFile::copy(_inputData,curDir+"/"+_input);

    FILE *resf=fopen("spj_result.log","w");
    fprintf(resf,"%d",status_RE);
    fclose(resf);


    if(_code.endsWith(".mpl",Qt::CaseInsensitive)){
        ConcatFile(_code,_spj+".mpl",_source);
        if(!CreateProcess(NULL,(WCHAR*)(QString("cmaple "+curDir+"\\"+_source).utf16()),NULL,&sa,
                          TRUE, HIGH_PRIORITY_CLASS | CREATE_NO_WINDOW, /*(LPVOID)(values.toLocal8Bit().data())*/ NULL,(const WCHAR*)(curDir.utf16()), &si, &pi)){
            _statement="Unable to start process cmaple, Judgement terminated. Exitcode="+QString::number(GetLastError());
            QFile::remove(curDir+"/"+_input);
            QFile::remove(curDir+"/"+_source);
            QFile::remove(curDir+"/spj_result.log");
            return status_JF;
        }
    }
    if(_code.endsWith(".wls",Qt::CaseInsensitive)){
        ConcatFile(_code,_spj+".wls",_source);
        if(!CreateProcess(NULL,(WCHAR*)(QString("wolframscript "+curDir+"\\"+_source).utf16()),NULL,&sa,
                          TRUE, HIGH_PRIORITY_CLASS | CREATE_NO_WINDOW, /*(LPVOID)(values.toLocal8Bit().data())*/ NULL,(const WCHAR*)(curDir.utf16()), &si, &pi)){
            _statement="Unable to start process wolframscript, Judgement terminated. Exitcode="+QString::number(GetLastError());
            QFile::remove(curDir+"/"+_input);
            QFile::remove(curDir+"/"+_source);
            QFile::remove(curDir+"/spj_result.log");
            return status_JF;
        }
    }
    bool flag;
    flag=false;
    QElapsedTimer timer;
    timer.start();

    while (timer.elapsed()<=_timelimit*1000){
        if (WaitForSingleObject(pi.hProcess,0)==WAIT_OBJECT_0){
            flag = true;
            break;
        }
        QCoreApplication::processEvents();
        Sleep(10);
    }
    if(!flag){
        TerminateProcess(pi.hProcess,0);

        //CloseHandle(si.hStdInput);
        CloseHandle(si.hStdError);
        CloseHandle(si.hStdOutput);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        _statement="Time Limit Exceeded, expect: "+QString::number(_timelimit)+"s";
        QFile qf;
        if(fii.exists())
            while (true){
                if (DeleteFile((WCHAR*)((curDir+"/"+_input).utf16())))
                    break;
                QCoreApplication::processEvents();
                Sleep(100);
                qDebug()<<"Waiting for deleting input";
            }
        if(fis.exists())
            while (true){
                if (DeleteFile((WCHAR*)((curDir+"/"+_source).utf16())))
                    break;
                QCoreApplication::processEvents();
                Sleep(100);
                qDebug()<<"Waiting for deleting source";
            }
        if(QFile(curDir+"/spj_result.log").exists())
            while(true){
                if (QFile::remove(curDir+"/spj_result.log"))
                    break;
                QCoreApplication::processEvents();
                Sleep(100);
                qDebug()<<"Waiting for deleting result";
            }
        return status_TLE;
    }
    unsigned long exitCode;
    GetExitCodeProcess(pi.hProcess,&exitCode);
    if (exitCode!=0){
        CloseHandle(si.hStdError);
        CloseHandle(si.hStdOutput);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        _statement="Runtime Error, ExitCode="+QString::number(exitCode);
        QFile::remove(curDir+"/"+_input);
        QFile::remove(curDir+"/"+_source);
        QFile::remove(curDir+"/spj_result.log");
        return status_RE;
    }
    CloseHandle(si.hStdError);
    CloseHandle(si.hStdOutput);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    //resf=fopen("spj_result.log","r");
    QFile fp("spj_result.log");
    int ret;
    if (fp.open(QFile::ReadOnly)){
        QTextStream istr(&fp);
        ret=istr.readLine().toInt();
        _statement=istr.readLine();
    }
    else{
        ret=status_JF;
        _statement="Unable to open spj_result.log, Judgement failed!";
    }
    //char s[255];
    //fscanf(resf,"%d",&ret);

    //scanf("%s",s);
    //fclose(resf);
    //_statement=QString::fromLocal8Bit(s);
    QFile::remove(curDir+"/"+_input);
    QFile::remove(curDir+"/"+_source);
    QFile::remove(curDir+"/spj_result.log");
    return ret;
#endif
}

int checker::JudgeSPJ(){
    return status_AC;
}

int checker::check(){
    switch(_type){
    case 1:{
        return JudgeTrad();
    }
    case 2:{
        return JudgeIntr();
    }
    case 3:{
        return JudgeSPJ();
    }
    }
    return -1;
}






#endif // CHECKER_H
