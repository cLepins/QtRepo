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
    patientTabModel->setTable("Patient");
    // patientTabModel->setTable("patient");
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    patientTabModel->setSort(patientTabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(patientTabModel->select()))
    {
        qDebug()<<"select false";
        return false;
    }
    thePatientSelection = new QItemSelectionModel(patientTabModel);
        return true;

        //
    //patientTabModel->setPrimaryKey(QSqlIndex("ID")); // 设置主键（如适用）
    //patientTabModel->select();

}

// int IDatabase::addNewPatient()
// {
//     patientTabModel->insertRow(patientTabModel->rowCount(),QModelIndex());
//     QModelIndex curIndex = patientTabModel->index(patientTabModel->rowCount() - 1,1);

//     int curRecNo = curIndex.row();
//     QSqlRecord curRec = patientTabModel->record(curRecNo);

//     QString uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
//     QString newId = uuid.mid(0, 16); // 截取前 16 个字符
//     qDebug() << "Shortened ID:" << newId;

//     curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
//     curRec.setValue("ID",newId);

//     if (!patientTabModel->setRecord(curRecNo, curRec)) {
//         qDebug() << "Failed to set record to model.";
//         return -1;
//     }


//      qDebug() << "New ID:" << newId; // 调试输出

//     return curIndex.row();
// }

int IDatabase::addNewPatient()
{
    // 插入新行
    int newRow = patientTabModel->rowCount();
    patientTabModel->insertRow(newRow);

    // 设置默认值
    QString uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
    patientTabModel->setData(patientTabModel->index(newRow, patientTabModel->fieldIndex("ID")), uuid); // 设置 ID
    patientTabModel->setData(patientTabModel->index(newRow, patientTabModel->fieldIndex("CREATEDTIMESTAMP")), QDateTime::currentDateTime().toString("yyyy-MM-dd")); // 设置时间戳

    // 提交模型更改
    // if (!patientTabModel->submitAll()) {
    //     qDebug() << "Submit failed:" << patientTabModel->lastError().text();
    //     return -1; // 插入失败
    // }

    qDebug() << "New Patient ID:" << uuid;
    return newRow;
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

// bool IDatabase::submitPatientEdit()
// {
//     QSqlRecord curRec = patientTabModel->record(patientTabModel->rowCount() - 1);
//     qDebug() << "ID before submit:" << curRec.value("ID").toString();

//     if (!patientTabModel->submitAll()) {
//         qDebug() << "Submit failed: " << patientTabModel->lastError().text();
//         return -1; // 返回错误码，表示插入失败
//     }
//     return 1;
// }

bool IDatabase::submitPatientEdit()
{
    QSqlDatabase db = QSqlDatabase::database();

    //可删
    if (!db.transaction()) {
        qDebug() << "1.Failed to start transaction:" << db.lastError().text();
        return false;
    }

    if (!patientTabModel->submitAll()) {
        qDebug() << "2.Submit failed: " << patientTabModel->lastError().text();
        db.rollback(); // 回滚事务
        return false;
    }

    if (!db.commit()) {
        qDebug() << "3.Commit failed:" << db.lastError().text();
        return false;
    }

    return true;
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
                return "loginOK:normal"; // 普通医生
            } else if (role == 1) {
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


//排序
// void IDatabase::sortPatientList(const QString &fieldName, bool ascending)
// {
//     Qt::SortOrder order = ascending ? Qt::AscendingOrder : Qt::DescendingOrder;
//     patientTabModel->setSort(patientTabModel->fieldIndex(fieldName), order);

//     // 提交排序
//     if (!patientTabModel->select()) {
//         qDebug() << "Failed to sort by field:" << fieldName
//                  << "Error:" << patientTabModel->lastError().text();
//     }
// }

void debugPatientModelContent(QSqlTableModel *model) {
    for (int row = 0; row < model->rowCount(); ++row) {
        QString rowContent;
        for (int col = 0; col < model->columnCount(); ++col) {
            rowContent += model->data(model->index(row, col)).toString() + " ";
        }
        qDebug() << "Row" << row << ":" << rowContent;
    }
}

// bool IDatabase::sortPatientList(const QString &fieldName, bool ascending)
// {
//     if (!patientTabModel) {
//         qDebug() << "Patient model not initialized!";
//         return false;
//     }

//     int fieldIndex = patientTabModel->fieldIndex(fieldName);
//     if (fieldIndex == -1) {
//         qDebug() << "Invalid field name:" << fieldName;
//         return false;
//     }

//     patientTabModel->setSort(fieldIndex, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
//     if (!patientTabModel->select()) {
//         qDebug() << "Error in select():" << patientTabModel->lastError().text();
//         return false;
//     }

//     qDebug() << "Patient model sorted by:" << fieldName;
//     for (int i = 0; i < patientTabModel->rowCount(); ++i) {
//         qDebug() << patientTabModel->data(patientTabModel->index(i, fieldIndex)).toString();
//     }

//     return true;
// }


bool IDatabase::sortPatientList(const QString &sortField, bool ascending)
{
    QSqlTableModel *model = patientTabModel;

    // 根据排序字段选择对应的数据库列
    QString orderByField;
    if (sortField == "CREATEDTIMESTAMP") {
        orderByField = "CREATEDTIMESTAMP"; // 按挂号时间排序
    } else if (sortField == "AGE") {
        orderByField = "AGE"; // 按年龄排序
    } else {
        qDebug() << "Invalid sort field:" << sortField;
        return false;
    }

    // 设置排序的顺序（升序或降序）
    QString order = ascending ? "ASC" : "DESC";

    // 更新模型的查询，添加ORDER BY子句
    model->setFilter(""); // 清除当前的过滤条件
    model->setSort(model->fieldIndex(orderByField), ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
    model->select(); // 重新执行查询，加载排序后的数据
    // qDebug() << "Patient model sorted by:" << sortField;
    // for (int i = 0; i < patientTabModel->rowCount(); ++i) {
    //     qDebug() << patientTabModel->data(patientTabModel->index(i, patientTabModel->fieldIndex(sortField))).toString();
    // }
    return true;
}





