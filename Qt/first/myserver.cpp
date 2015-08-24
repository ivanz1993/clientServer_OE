#include "myserver.h"
#include <qstring.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include <QtGui/QImage>
 #include <QtSql>
#include <set>
#include <QFile>
#include  <QElapsedTimer>
using namespace std;
QString strN="",copyStrN,logg="";
QElapsedTimer timer; int t=0;
MyServer::MyServer(QObject *parent) :
    QObject(parent)
{
       tcpServer = new QTcpServer(this);
       connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newuser()));
       if (!tcpServer->listen(QHostAddress::Any, 8080)) {
           qDebug() << QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
       } else {
           qDebug() << tcpServer->isListening() << "TCPSocket listen on port";
           qDebug() << QString::fromUtf8("Server is runiing");
       }

}
void MyServer::newuser()
{
    qDebug() << QString::fromUtf8("New Linking");
    QTcpSocket* clientSocket=tcpServer->nextPendingConnection();
    int idusersocs=clientSocket->socketDescriptor();
    SClients[idusersocs]=clientSocket;
    connect(SClients[idusersocs],SIGNAL(readyRead()),this, SLOT(slotReadClient()));

}
void MyServer::slotReadClient()
{

    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    QString name="";
     int idusersocs=clientSocket->socketDescriptor();
    QByteArray s = clientSocket->readAll();
    qDebug() << ("ReadClient:"+s+"\n\r");
    int i=4; 
    QString str ="";
    while (s[i+1]!='H')
    {
        str+=s[i];
        i++;
    }
  //   qDebug() << ("ReadClient:\n\r"+str+"*\n\r");
    
    /*QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
     sdb.setDatabaseName("db_name.sqlite");

     if (!sdb.open()) {
            //....
     }*/
     //html_form_action.asp?first=city&second=price"

    if(str=="/")
    {
        QTextStream os(clientSocket);
        os.setAutoDetectUnicode(true);
        QString res;
        res = "HTTP/1.0 200 Ok\r\nContent-Type: text/html; charset=\"utf-8\"\r\n\r\n";

        std::ifstream in("Site/main.html");

        qDebug()<<("*read;");
        char ch=in.get();
        while ( ch != std::istream::traits_type::eof() ) {
            res+=ch;
            ch = in.get();

        }
        strN=QString(res);
        copyStrN=QString(res);
    //   qDebug()<<(res);
       // strN=res;

//                QElapsedTimer timer;
//                timer.start();

        os<<res;
        qDebug()<<("Answer:\r\n"+res);
        if (/*(logg.length()!=0) &&*/ (timer.elapsed()/1000>3)){
    //           QTextStream os(clientSocket);
    //           os.setAutoDetectUnicode(true);
    //           os<<copyStrN;
           qDebug() <<  timer.elapsed()/1000;
            qDebug() << "oblalaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        }
        qDebug() <<("!!!!!!!!second");
        qDebug() <<(timer.elapsed()/1000);
         if ((logg.length()!=0) && (timer.elapsed()/1000>3))   {
             qDebug() << ("Strinh login is not nul!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
             QTextStream os(clientSocket);
             os.setAutoDetectUnicode(true);
             os<<copyStrN;
         }
    }
    else
        if(str=="/header.jpg"||str=="/img3.jpg" || str=="/img8.jpg" || str=="/img5.jpg" || str=="/fon.jpg")
        {
            char* ss;
            if(str == "/header.jpg")
                ss= "Site/header.jpg";
            else
            if(str == "/img3.jpg")
                ss= "Site/img3.jpg";
            else
            if(str == "/img8.jpg")
                ss= "Site/img8.jpg";
                    else
                    if(str == "/img5.jpg")
                ss= "Site/img5.jpg";
                       else
                       if(str == "/fon.jpg")
                ss= "Site/fon.jpg";

            std::ifstream is(ss,std::ifstream::binary);

            qDebug()<<("*read;");

            is.seekg (0, is.end);
                int length = is.tellg();
                is.seekg (0, is.beg);

                char * buffer = new char [length];

                std::cout << "Reading " << length << " characters... ";
                // read data as a block:
                is.read (buffer,length);

             qDebug()<<("Answer:\r\n");
           clientSocket->write("HTTP/1.0 200 Ok\r\nContent-Type: image/jpeg; Content-Transfer-Encoding:binary; Content-Length:");
           qDebug()<<("HTTP/1.0 200 Ok\r\nContent-Type: image/jpeg; Content-Transfer-Encoding:binary; Content-Length:");

             char buf[11];
             sprintf(buf,"%d",length);
                clientSocket->write(buf);
             qDebug()<<(length);
             clientSocket->write("charset=ISO-8859-4\r\n\r\n");
             qDebug()<<"charset=ISO-8859-4\r\n\r\n";
             clientSocket->write(buffer,length);
             qDebug()<<(buffer);
            //qDebug()<<("Answer:\r\n"+res);
        }
    else






    if(str=="/style.css")
    {
        QTextStream os(clientSocket);
        os.setAutoDetectUnicode(true);
        QString res;
        res = "HTTP/1.0 200 Ok\r\nContent-Type: text/css; charset=\"utf-8\"\r\n\r\n";

        std::ifstream in("Site/style.css");
        qDebug()<<("*read;");
        char ch=in.get();
        while ( ch != std::istream::traits_type::eof() ) {
            res+=ch;
            ch = in.get();

        }
        os<<res;
        //qDebug()<<("Answer:\r\n"+res);
    }
    else
        if((str=="/html_form_action.asp?first=city&second=price")
                ||(str=="/html_form_action.asp?first=city&second=date")||
                (str=="/html_form_action.asp?first=price&second=date")
                ||(str=="/html_form_action.asp?first=price&second=city")
                || (str=="/html_form_action.asp?first=date&second=city") ||
                (str=="/html_form_action.asp?first=date&second=price")){

            char* ff;char* sf; char* tf;
            if (str=="/html_form_action.asp?first=city&second=price"){
                ff="city"; sf="price"; tf="date";
             } else
            if (str=="/html_form_action.asp?first=city&second=date"){
                ff="city"; sf="date";tf="price";
            } else
            if (str=="/html_form_action.asp?first=price&second=date"){
                ff="price"; sf="date";tf="city";
            }else

            if (str=="/html_form_action.asp?first=price&second=city"){
                ff="price"; sf="city";tf="date";
            }else

            if (str=="/html_form_action.asp?first=date&second=city"){
                ff="date"; sf="city";tf="price";
            }else

            if (str=="/html_form_action.asp?first=date&second=price"){
                ff="date"; sf="price";tf="city";
            } else
                 {

                     QTextStream os(clientSocket);
                     os.setAutoDetectUnicode(true);
                     QString res;
                     res = "HTTP/1.0 200 Ok\r\nContent-Type: text/html; charset=\"utf-8\"\r\n\r\n<body>Error 404<br/>Page not found<body>";
                     os<<res;

                 }


            QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
            sdb.setDatabaseName("mydatabase.sqlite");

            if (!sdb.open()) {
                qDebug()<<"DataBase is not opened";
            }

            QSqlQuery a_query(sdb);

                bool b = a_query.exec(str);

               b = a_query.exec();

                b = a_query.exec(str);
               if (!b) {
                   qDebug() << "!INSERTING" << a_query.lastError();
               }
               //.....
               if (!a_query.exec("SELECT * FROM my_table")) {
                   qDebug() << "!SELECT";

               }

               QSqlRecord rec = a_query.record();
               QString price = "";
                  QString     date ="";
                  QString city = "";

                  QTextStream os(clientSocket);
                  os.setAutoDetectUnicode(true);
                  QString res;

           res = "HTTP/1.0 200 Ok\r\nContent-Type: text/html; charset=\"utf-8\"\r\n\r\n<body>";
           set<QString> fv;
           set<QString> sv;
           map< pair<QString, QString>, QString> tv;
           QString st="",r="";
                  while (a_query.next()) {

                     QString fff=a_query.value(rec.indexOf(ff)).toString();
                     QString sss=a_query.value(rec.indexOf(sf)).toString();
                     fv.insert(fff);
                     sv.insert(sss);
                     tv[make_pair(fff,sss)]=a_query.value(rec.indexOf(tf)).toString();

                 }
                  QString q=ff,qq=sf;
                  res +="<TABLE BORDER><tr><td>"+q+"/"+qq+"</td>";
                  for(set<QString>::iterator it1 = sv.begin(); it1!=sv.end();it1++)
                  {
                     res+="<td>"+*it1+"</td>";
                  }
                  res+="</tr>";
                  for (set<QString>::iterator it = fv.begin(); it!=fv.end();it++)
                  {
                      QString ffff=*it;
                      res+="<tr><td>"+ffff+"</td>";

                      for(set<QString>::iterator it1 = sv.begin(); it1!=sv.end();it1++)
                      {
                          QString ssss=*it1;
                          QString p = "<td>"+tv[make_pair(ffff,ssss)] +"</td>";
                          res+=p;
                          qDebug()<<p;
                      }
                      res+="</tr>";
                  }
                  //res +=  "<body><TABLE BORDER><TR><TD>"
                  //        +date+"</TD> <TD>B</TD><TD>C</TD></TR> <TR><TD>"
                  //        +"f"+"</TD> <TD>E</TD> <TD>F</TD></TR></TABLE><body>";

                   res += "</TABLE><body>";
                os<<res;



        qDebug()<<(ff);
        qDebug()<<(sf);
    }
         else
            if (( str.indexOf("log")>=0 ) ) {  // str=="/html_form_action.asp?log=jon&pas=a"){
                 timer.start();


                 logg="";
                for (int i= str.indexOf("=")+1; i<str.indexOf("&"); i++){
                    logg+=str[i];
                }
                qDebug()<<(strN);
                QString resN="";
                bool t=true;
                for (int j=0; j<strN.length(); j++){

                    if ((t)&&(strN[j]=='<')&&(strN[j+1]=='/')&&(strN[j+2]=='h')&&(strN[j+3]=='e')&&(strN[j+4]=='a')&&(strN[j+5]=='d')&&(strN[j+6]=='>'))
                    {
                        resN+="<script type=\"text/javascript\">\nfunction sleep(ms) {\nvar unixtime_ms = new Date().getTime();\n while(new Date().getTime() < unixtime_ms + ms) {}} window.onload = function(){ sleep(5000); alert('You are not login'); document.location.href = \"http://127.0.0.1:8080\"};\n </script>";
                        t=false;
                        qDebug()<<"YREFNDHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHh";
                    }
                    if (strN[j]!='~') resN+=strN[j];else
                        resN+="Hello, "+logg;

                }
                QTextStream os(clientSocket);
                os.setAutoDetectUnicode(true);
                os<<resN;



                 qDebug()<<(logg);
                 QFile file("login.txt");
                 file.open(QIODevice::Append | QIODevice::Text);
                 QTextStream out(&file);

                 out << logg;
                 out<<" ";

                 //            QString res;
                 //            res = "HTTP/1.0 200 Ok\r\nContent-Type: text/html; charset=\"utf-8\"\r\n\r\n<body>Error 404<br/>Page not found<body>";

                 out << "\n";
                 file.close();
                             QString res;
                             res = "HTTP/1.0 200 Ok\r\nContent-Type: text/html; charset=\"utf-8\"\r\n\r\n<body>Error 404<br/>Page not found<body>";


           }

             else
        {
//timer.
//                qDebug()<<("our time!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
//             qDebug()<<(timer.elapsed()/1000);
//            QString res;
//            res = "HTTP/1.0 200 Ok\r\nContent-Type: text/html; charset=\"utf-8\"\r\n\r\n<body>Error 404<br/>Page not found<body>";
//            os<<res;

        }

//http://127.0.0.1:8080/

    // Если нужно закрыть сокет
    clientSocket->close();
    SClients.remove(idusersocs);

    qDebug()<<("*End;");
}

