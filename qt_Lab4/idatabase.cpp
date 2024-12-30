#include "idatabase.h"
#include <QUuid>
#include <QDebug>

//2.打开数据库，看是否成功
void IDatabase::ininDatabase()
{
    //在这里打开文件
    database = QSqlDatabase::addDatabase("QSQLITE");
    QString aFile = "D:\\myQtCode\\lab4a.db";
    database.setDatabaseName(aFile);

    if(!database.open()){
        qDebug()<<"failed to open database";
    }else
    {
        qDebug()<<"open database is ok";
    }
}

bool IDatabase::initPatientModel()
{
    patientTabModel = new QSqlTableModel(this,database);
    patientTabModel->setTable("patient");
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    patientTabModel->setSort(patientTabModel->fieldIndex("name"),Qt::AscendingOrder);
        if(!(patientTabModel->select()))
            return false;

    thePatientSelection = new QItemSelectionModel(patientTabModel);
        return true;
}

int IDatabase::addNewPatient()
{
    patientTabModel->insertRow(patientTabModel->rowCount(),QModelIndex());
    QModelIndex curIndex = patientTabModel->index(patientTabModel->rowCount() - 1,1);

    int curRecNo = curIndex.row();
    QSqlRecord curRec = patientTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));

    patientTabModel->setRecord(curRecNo,curRec);

    return curIndex.row();
}

bool IDatabase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();
}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();
    patientTabModel->removeRow(curIndex.row());
    patientTabModel->submitAll();
    patientTabModel->select();

}

bool IDatabase::submitPatientEdit()
{
    return patientTabModel->submitAll();
}

void IDatabase::revertPatientEdit()
{
    patientTabModel->revertAll();
}

//3.登录验证  //所以要在这里修改 userName的匹配问题
// QString IDatabase::userLogin(QString userName, QString password)
// {
//     //return "LoginOK";
//     QSqlQuery query;
//     query.prepare("select username,password from user where username = :USER");
//     query.bindValue(":USER",userName);
//     query.exec();
//     if(query.first()&& query.value("username").isValid()){
//         QString passwd = query.value("password").toString();
//         if(passwd == password)
//         {
//             qDebug()<<"login ok";
//             return "loginOK";
//         }
//         else{
//             qDebug()<<"wrong password";
//             return "wrongPassword";
//         }
//     }
//     else{
//         qDebug()<<"no such user";
//         return "wrongUsername";
//     }
// }


QString IDatabase::userLogin(QString userName, QString password) {
    QSqlQuery query;
    query.prepare("SELECT username, password, role FROM user WHERE username = :USER");
    query.bindValue(":USER", userName);
    query.exec();

    // 查询到用户信息并验证用户名有效
    if (query.first() && query.value("username").isValid()) {
        QString passwd = query.value("password").toString();
        int role = query.value("role").toInt(); // 获取用户权限

        // 验证密码
        if (passwd == password) {
            qDebug() << "Login OK";

            // 返回不同权限的登录结果
            if (role == 0) {
                qDebug()<<"i am cleo";
                return "loginOK:normal"; // 普通医生
            } else if (role == 1) {
                qDebug()<<"i am admin";
                return "loginOK:admin"; // 管理员医生
            } else {
                return "unknownRole"; // 未知角色
            }
        } else {
            qDebug() << "Wrong password";
            return "wrongPassword";
        }
    } else {
        qDebug() << "No such user";
        return "wrongUsername";
    }
}


//1.创建单例模式的IDatabase，调用 2.initDatabase
IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{

    ininDatabase();

}
