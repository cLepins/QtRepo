#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <Qtsql>
#include <QSqlDatabase>
#include <QDataWidgetMapper>

class IDatabase : public QObject
{
    Q_OBJECT
public:

    //返回这个类，本质是在单例模式下，调用下面的IDatabase构造函数，然后构造函数里面有initDatabase
    static IDatabase& getInstance()
    {
        static IDatabase    instance; // Guaranteed to be destroyed.
            // Instantiated on first use.
        return instance;
    }

    //用户登录
    QString userLogin(QString userName ,QString password);


private:
    explicit IDatabase(QObject *parent = nullptr);
    IDatabase(IDatabase const&)               = delete;
    void operator=(IDatabase const&)  = delete;

    QSqlDatabase database;


    void ininDatabase();

signals:

public:
    //病人
    bool sortPatientList(const QString &sortField, bool ascending);
    bool initPatientModel();

    int addNewPatient();    
    bool searchPatient(QString filter);  
    void deleteCurrentPatient();
    bool submitPatientEdit();
    void revertPatientEdit();

    //医生
    bool sortDoctorList(const QString &sortField,bool ascending);
    bool initDoctorModel();
    void revertDoctorEdit();
    // int calculateAge(const QString &dob);
    int addNewDoctor();
    bool submitDoctorEdit();
    bool searchDoctor(QString filter);
    void deleteCurrentDoctor();
    bool importDoctorData(const QString &fileName);

    //记录
    bool sortRecordList(const QString &sortField,bool ascending);
    bool initRecordModel();
    void revertRecordEdit();

    int addNewRecord();
    bool submitRecordEdit();//同步到数据库
    bool searchRecord(QString filter);
    void deleteCurrentRecord();
   // bool importRecordData(const QString &fileName);
    bool exportRecordData(const QString &fileName);

    //药物

    bool sortMedicineList(const QString &sortField,bool ascending);
    bool initMedicineModel();
    void revertMedicineEdit();

    int addNewMedicine();
    bool submitMedicineEdit();
    bool searchMedicine(QString filter);
    void deleteCurrentMedicine();
    bool importMedicineData(const QString &fileName);
    bool exportMedicineData(const QString &fileName);


    QSqlTableModel *patientTabModel;
    QSqlTableModel *doctorTabModel;
    QSqlTableModel *medicineTabModel;
    QSqlTableModel *recordTabModel;

    QItemSelectionModel *thePatientSelection;
    QItemSelectionModel *theDoctorSelection;
    QItemSelectionModel *theMedicineSelection;
    QItemSelectionModel *theRecordSelection;


    // --------------------------------------------
    QSqlDatabase& getDatabase() {
        return database; // `database` 是 IDatabase 类的成员变量，类型为 QSqlDatabase
    }

};

#endif // IDATABASE_H
