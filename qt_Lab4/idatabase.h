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

    bool initPatientModel();
    int addNewPatient();    
    bool searchPatient(QString filter);  
    bool deleteCurrentPatient();
    bool submitPatientEdit();
    void revertPatientEdit();


    QSqlTableModel *patientTabModel;
    QItemSelectionModel *thePatientSelection;

};

#endif // IDATABASE_H
