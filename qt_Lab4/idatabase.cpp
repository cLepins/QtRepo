#include "idatabase.h"
#include <QUuid>
#include <QDebug>
#include <QTextStream>
#include <QSqlQuery>
#include <QFile>

//0.用户登录调用数据库判断是否能够进入，并且区分管理员和普通医生的身份
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


//初始化
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

bool IDatabase::initDoctorModel()
{
    doctorTabModel = new QSqlTableModel(this,database);
    doctorTabModel->setTable("Doctor");
    // patientTabModel->setTable("patient");
    doctorTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    doctorTabModel->setSort(doctorTabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(doctorTabModel->select()))
    {
        qDebug()<<"select false";
        return false;
    }
    theDoctorSelection = new QItemSelectionModel(doctorTabModel);
    return true;

}

bool IDatabase::initMedicineModel()
{
    medicineTabModel = new QSqlTableModel(this,database);
    medicineTabModel->setTable("Medicine");
    // patientTabModel->setTable("patient");
    medicineTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    medicineTabModel->setSort(medicineTabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(medicineTabModel->select()))
    {
        qDebug()<<"select false";
        return false;
    }
    theMedicineSelection = new QItemSelectionModel(medicineTabModel);
    return true;
}

bool IDatabase::initRecordModel()
{
    recordTabModel = new QSqlTableModel(this,database);
    recordTabModel->setTable("Record");
    // patientTabModel->setTable("patient");
    recordTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    recordTabModel->setSort(recordTabModel->fieldIndex("name"),Qt::AscendingOrder);
    if(!(recordTabModel->select()))
    {
        qDebug()<<"select false";
        return false;
    }
    theRecordSelection = new QItemSelectionModel(recordTabModel);
    return true;

}
//查找工作
bool IDatabase::searchDoctor(QString filter)
{
    doctorTabModel->setFilter(filter);
    return doctorTabModel->select();
}
bool IDatabase::searchPatient(QString filter)
{
    patientTabModel->setFilter(filter);
    return patientTabModel->select();
}
bool IDatabase::searchMedicine(QString filter)
{
    medicineTabModel->setFilter(filter);
    return medicineTabModel->select();
}
bool IDatabase::searchRecord(QString filter)
{
    recordTabModel->setFilter(filter);
    return recordTabModel->select();
}



//添加
int IDatabase::addNewPatient()
{
    // 插入新行
    int newRow = patientTabModel->rowCount();
    patientTabModel->insertRow(newRow);

    // 设置默认值
    QString uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
    patientTabModel->setData(patientTabModel->index(newRow, patientTabModel->fieldIndex("ID")), uuid); // 设置 ID
    patientTabModel->setData(patientTabModel->index(newRow, patientTabModel->fieldIndex("CREATEDTIMESTAMP")), QDateTime::currentDateTime().toString("yyyy-MM-dd")); // 设置时间戳


    qDebug() << "New Patient ID:" << uuid;
    return newRow;
}

int IDatabase::addNewDoctor()
{
    // 插入新行
    int newRow = doctorTabModel->rowCount();
    doctorTabModel->insertRow(newRow);

    // 设置默认值
    QString uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
    doctorTabModel->setData(doctorTabModel->index(newRow, doctorTabModel->fieldIndex("ID")), uuid); // 设置 ID
    doctorTabModel->setData(doctorTabModel->index(newRow, doctorTabModel->fieldIndex("CREATEDTIMESTAMP")), QDateTime::currentDateTime().toString("yyyy-MM-dd")); // 设置时间戳


    qDebug() << "New Doctor ID:" << uuid;
    return newRow;
}

int IDatabase::addNewMedicine()
{
    // 插入新行
    int newRow = medicineTabModel->rowCount();
    medicineTabModel->insertRow(newRow);

    // 设置默认值
    QString uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
    medicineTabModel->setData(medicineTabModel->index(newRow, medicineTabModel->fieldIndex("ID")), uuid); // 设置 ID
    medicineTabModel->setData(medicineTabModel->index(newRow, medicineTabModel->fieldIndex("CREATEDTIMESTAMP")), QDateTime::currentDateTime().toString("yyyy-MM-dd")); // 设置时间戳


    qDebug() << "New Medicine ID:" << uuid;
    return newRow;
}

int IDatabase::addNewRecord()
{
    // 插入新行
    int newRow = recordTabModel->rowCount();
    recordTabModel->insertRow(newRow);

    // 设置默认值
    QString uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
    recordTabModel->setData(recordTabModel->index(newRow, recordTabModel->fieldIndex("ID")), uuid); // 设置 ID
    recordTabModel->setData(recordTabModel->index(newRow, recordTabModel->fieldIndex("CREATEDTIMESTAMP")), QDateTime::currentDateTime().toString("yyyy-MM-dd")); // 设置时间戳

    qDebug() << "New Record ID:" << uuid;
    return newRow;
}



//删除操作
void IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();
    patientTabModel->removeRow(curIndex.row());
    patientTabModel->submitAll();
    patientTabModel->select();

}

void IDatabase::deleteCurrentDoctor()
{
    QModelIndex curIndex = theDoctorSelection->currentIndex();
    doctorTabModel->removeRow(curIndex.row());
    doctorTabModel->submitAll();
    doctorTabModel->select();
}

void IDatabase::deleteCurrentMedicine()
{
    QModelIndex curIndex = theMedicineSelection->currentIndex();
    medicineTabModel->removeRow(curIndex.row());
    medicineTabModel->submitAll();
    medicineTabModel->select();
}
void IDatabase::deleteCurrentRecord()
{
    QModelIndex curIndex = theRecordSelection->currentIndex();
    recordTabModel->removeRow(curIndex.row());
    recordTabModel->submitAll();
    recordTabModel->select();
}




//提交
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

bool IDatabase::submitDoctorEdit()
{
    QSqlDatabase db = QSqlDatabase::database();

    //可删
    if (!db.transaction()) {
        qDebug() << "1.Failed to start transaction:" << db.lastError().text();
        return false;
    }

    if (!doctorTabModel->submitAll()) {
        qDebug() << "2.Submit failed: " << doctorTabModel->lastError().text();
        db.rollback(); // 回滚事务
        return false;
    }

    if (!db.commit()) {
        qDebug() << "3.Commit failed:" << db.lastError().text();
        return false;
    }

    return true;
}

bool IDatabase::submitMedicineEdit()
{
    QSqlDatabase db = QSqlDatabase::database();

    //可删
    if (!db.transaction()) {
        qDebug() << "1.Failed to start transaction:" << db.lastError().text();
        return false;
    }

    if (!medicineTabModel->submitAll()) {
        qDebug() << "2.Submit failed: " << medicineTabModel->lastError().text();
        db.rollback(); // 回滚事务
        return false;
    }

    if (!db.commit()) {
        qDebug() << "3.Commit failed:" << db.lastError().text();
        return false;
    }

    return true;
}

//提交到数据库
bool IDatabase::submitRecordEdit()
{
    QSqlDatabase db = QSqlDatabase::database();

    //可删
    if (!db.transaction()) {
        qDebug() << "1.Failed to start transaction:" << db.lastError().text();
        return false;
    }

    if (!recordTabModel->submitAll()) {
        qDebug() << "2.Submit failed: " << recordTabModel->lastError().text();
        db.rollback(); // 回滚事务
        return false;
    }

    if (!db.commit()) {
        qDebug() << "3.Commit failed:" << db.lastError().text();
        return false;
    }

    return true;
}




//撤回操作
void IDatabase::revertPatientEdit()
{
    patientTabModel->revertAll();
}

void IDatabase::revertDoctorEdit()
{
    doctorTabModel->revertAll();
}

void IDatabase::revertMedicineEdit()
{
    medicineTabModel->revertAll();
}


void IDatabase::revertRecordEdit()
{
    recordTabModel->revertAll();
}




void debugPatientModelContent(QSqlTableModel *model) {
    for (int row = 0; row < model->rowCount(); ++row) {
        QString rowContent;
        for (int col = 0; col < model->columnCount(); ++col) {
            rowContent += model->data(model->index(row, col)).toString() + " ";
        }
        qDebug() << "Row" << row << ":" << rowContent;
    }
}



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


bool IDatabase::sortDoctorList(const QString &sortField, bool ascending)
{
    QSqlTableModel *model = doctorTabModel;

    // 根据排序字段选择对应的数据库列
    QString orderByField;
    if (sortField == "CREATEDTIMESTAMP") {
        orderByField = "CREATEDTIMESTAMP"; // 按入职时间排序
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
    return true;
}


bool IDatabase::sortMedicineList(const QString &sortField, bool ascending)
{
    QSqlTableModel *model = medicineTabModel;

    // 根据排序字段选择对应的数据库列
    QString orderByField;
    if (sortField == "CREATEDTIMESTAMP") {
        orderByField = "CREATEDTIMESTAMP"; // 按入职时间排序
    } else if (sortField == "STOCK") {
        orderByField = "STOCK"; // 按年龄排序
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
    return true;
}

bool IDatabase::sortRecordList(const QString &sortField, bool ascending)
{
    QSqlTableModel *model = recordTabModel;

    // 根据排序字段选择对应的数据库列
    QString orderByField;
    if (sortField == "PATIENTNAME") {
        orderByField = "PATIENTNAME"; // 按入职时间排序
    } else if (sortField == "DOCTORNAME") {
        orderByField = "DOCTORNAME"; // 按ID排序，不知道什么用就是了
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
    return true;
}



//从文件导入数据
bool IDatabase::importDoctorData(const QString &filePath)
{
    // 打开数据库
    if (!database.open()) {
        qDebug() << "Failed to open database:" << database.lastError().text();
        return false;
    }
    // 检查表是否存在，如果不存在则创建表
    QString createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS Doctor (
            ID INTEGER PRIMARY KEY,
            Name TEXT NOT NULL,
            Sex TEXT,
            Specialization TEXT,
            License TEXT,
            CreatedTimeStamp TEXT,
            Age INTEGER
        )
    )";
    QSqlQuery query(database);
    if (!query.exec(createTableSQL)) {
        qDebug() << "Failed to create table:" << query.lastError().text();
        return false;
    }

    // 打开 CSV 文件
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open CSV file:" << filePath;
        return false;
    }

    QTextStream in(&file);
    bool isFirstLine = true; // 跳过表头
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (isFirstLine) {
            isFirstLine = false; // 跳过第一行
            continue;
        }

        // 按逗号分割数据
        QStringList values = line.split(',');
        if (values.size() != 7) { // 确保列数一致
            qDebug() << "Invalid line format:" << line;
            continue;
        }

        // 插入数据到数据库
        query.prepare("INSERT INTO Doctor (ID, Name, Sex, Specialization, License, CreatedTimeStamp, Age) "
                      "VALUES (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(values[0].toInt());   // ID
        query.addBindValue(values[1]);          // Name
        query.addBindValue(values[2]);          // Sex
        query.addBindValue(values[3]);          // Specialization
        query.addBindValue(values[4]);          // License
        query.addBindValue(values[5]);          // CreatedTimeStamp
        query.addBindValue(values[6].toInt());  // Age

        if (!query.exec()) {
            qDebug() << "Failed to insert data:" << query.lastError().text();
        }
    }

    file.close();
    qDebug() << "Data import completed.";
    return true;
}

bool IDatabase::importMedicineData(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading!";
        return false;
    }

    QTextStream in(&file);
    QStringList headers = in.readLine().split(","); // 第一行作为表头
    QSqlQuery query;

    while (!in.atEnd()) {
        QStringList line = in.readLine().split(",");
        if (line.size() != headers.size()) continue;

        query.prepare("INSERT INTO Medicine (ID, NAME, DOSAGE, STOCK, CREATEDTIMESTAMP) VALUES (?, ?, ?, ?, ?)");
        query.addBindValue(line[0]);
        query.addBindValue(line[1]);
        query.addBindValue(line[2]);
        query.addBindValue(line[3].toInt());
        query.addBindValue(line[4]);

        if (!query.exec()) {
            qDebug() << "Failed to insert data:" << query.lastError();
        }
    }

    file.close();
    return true;
}


//从文件导出数据库
bool IDatabase::exportMedicineData(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for writing!";
        return false;
    }


    QTextStream out(&file);
    out << QChar(0xFEFF); // 写入 UTF-8 BOM

    QSqlQuery query("SELECT * FROM Medicine");

    // 生成CSV表头
    out << "ID,NAME,DOSAGE,STOCK,CREATEDTIMESTAMP\n";

    while (query.next()) {
        out << query.value(0).toString() << ","
            << query.value(1).toString() << ","
            << query.value(2).toString() << ","
            << query.value(3).toInt() << ","
            << query.value(4).toString() << "\n";
    }

    file.close();
    return true;
}


bool IDatabase::exportRecordData(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open file for writing!";
        return false;
    }

    QTextStream out(&file);
    out << QChar(0xFEFF); // 写入 UTF-8 BOM

    QSqlQuery query("SELECT * FROM Record");

    // 生成 CSV 表头
    out << "ID,PATIENTNAME,DOCTORNAME,MEDICINE,CREATEDTIMESTAMP,DIAGNOSIS\n";

    while (query.next()) {
        out << query.value(0).toString() << ","
            << query.value(1).toString() << ","
            << query.value(2).toString() << ","
            << query.value(3).toString() << ","
            << query.value(4).toString() << ","
            << query.value(5).toString() << "\n";
    }

    file.close();
    return true;
}

